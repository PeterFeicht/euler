/*
 * Define functions for finding prime numbers.
 */

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

using Long = unsigned long long int;

// Internal function, do not use.
void do_sieve(std::vector<Long> &primes, std::vector<char> &mark, Long &offset,
        Long limit, std::size_t maxSegmentSize) {
    auto sq = [](Long x) { return x * x; };

    std::size_t segmentSize = std::min<Long>(sq(primes.back()), limit) - offset;
    segmentSize = std::min(segmentSize, maxSegmentSize);

    mark.reserve(segmentSize);
    std::fill_n(mark.begin(), segmentSize, 1);
    for(auto it = primes.begin(); sq(*it) < offset + segmentSize; ++it) {
        // Round up to the next multiple of *it >= offset
        auto start = ((offset + *it - 1) / *it) * *it;
        for(auto idx = start - offset; idx < segmentSize; idx += *it) {
            mark[idx] = 0;
        }
    }
    for(std::size_t j = 0; j < segmentSize; j++) {
        if(mark[j]) {
            primes.push_back(offset + j);
        }
    }
    offset += segmentSize + (segmentSize % 2);
}

/**
 * Create a vector with all prime numbers up to the specified limit.
 *
 * @param limit The upper limit, inclusive.
 * @return A vector with all prime numbers up to and including `limit`.
 */
std::vector<Long> sieve(Long limit) {
    // The segment size roughly corresponds to the working memory in bytes
    static constexpr std::size_t maxSegmentSize = 250'000;

    std::vector<Long> primes{2, 3, 5, 7, 11, 13, 17, 19};
    std::vector<char> mark;
    auto offset = primes.back() + 2;
    while(offset < limit) {
        do_sieve(primes, mark, offset, limit, maxSegmentSize);
    }
    return primes;
}

/**
 * Fill the specified vector with prime numbers and return the `n`th number.
 *
 * @param primes A vector that will be filled with at least `n` prime numbers.
 *        If the specified vector is not empty, it must already contain the
 *        first `primes.size()` prime numbers, otherwise the result is
 *        undefined. Note that the vector may be resized, so all iterators may
 *        be invalidated (this is also true when its size is greater than `n`).
 * @param n The number of prime numbers to generate (must be positive).
 * @return The `n`th prime number (2 being the 1st prime number).
 */
Long sieve(std::vector<Long> &primes, std::size_t n) {
    static constexpr std::size_t maxSegmentSize = 100'000;

    if(primes.empty()) {
        primes = {2, 3, 5, 7, 11, 13, 17, 19};
    }
    if(primes.size() >= n) {
        return primes[n - 1];
    }

    std::vector<char> mark;
    auto offset = primes.back() + 2;
    while(primes.size() < n) {
        do_sieve(primes, mark, offset, 2 * primes.back(), maxSegmentSize);
    }
    return primes[n - 1];
}
