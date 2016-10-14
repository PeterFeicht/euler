/*
 * Quadratic primes
 *
 * Euler discovered the remarkable quadratic formula:
 *      n^2 + n + 41 .
 * It turns out that the formula will produce 40 primes for the consecutive
 * integer values 0 ≤ n ≤ 39. However, when n = 40,
 * 40^2 + 40 + 41 = 40 (40 + 1) + 41 is divisible by 41, and certainly when
 * n = 41, 41^2 + 41 + 41 is clearly divisible by 41.
 *
 * The incredible formula n^2 − 79 n + 1601 was discovered, which produces 80
 * primes for the consecutive values 0 ≤ n ≤ 79. The product of the
 * coefficients, −79 and 1601, is −126479.
 *
 * Considering quadratics of the form:
 *      n^2 + a n + b, where |a| < 1000 and |b| ≤ 1000
 * where |n| is the absolute value of n, e.g. |11| = 11 and |−4| = 4.
 *
 * Find the product of the coefficients, a and b, for the quadratic expression
 * that produces the maximum number of primes for consecutive values of n,
 * starting with n = 0.
 */

#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <utility>
#include <vector>

#include "sieve.hpp"

bool isPrime(Long n);

/**
 * Represents a range of integers that can be iterated over.
 */
class Range
{
    int mBegin;
    int mEnd;

public:
    class iterator
    {
        int mState;
        bool mForward;

        friend class Range;
        iterator(int start, bool forward) : mState(start), mForward(forward) {
        }

    public:
        using iterator_category = std::input_iterator_tag;
        using value_type = int;
        using difference_type = int;
        using pointer = const int*;
        using reference = const int&;

        iterator(const iterator& other) = default;
        iterator& operator=(const iterator& other) = default;

        iterator& operator++() {
            if(mForward) {
                mState++;
            } else {
                mState--;
            }
            return *this;
        }
        iterator operator++(int) {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return mState == other.mState;
        }
        bool operator!=(const iterator& other) const {
            return !(*this == other);
        }

        reference operator*() const {
            return mState;
        }
        pointer operator->() const {
            return &mState;
        }

        friend void swap(iterator& lhs, iterator& rhs) {
            std::swap(lhs.mState, rhs.mState);
            std::swap(lhs.mForward, rhs.mForward);
        }
    }; // iterator

    /**
     * Construct a Range from 0 to the specified value.
     *
     * @param end The end of the range, inclusive.
     */
    explicit Range(int end) : mBegin(0), mEnd(end) {
    }

    /**
     * Construct a Range between the specified values.
     *
     * @param begin The start of the range, inclusive.
     * @param end The end of the range, inclusive.
     */
    Range(int begin, int end) : mBegin(begin), mEnd(end) {
    }

    bool forward() const {
        return mEnd >= mBegin;
    }

    iterator begin() const {
        return iterator(mBegin, this->forward());
    }
    iterator end() const {
        return iterator(this->forward() ? mEnd + 1 : mEnd - 1, this->forward());
    }
}; // Range

/**
 * Represents an instance of the quadratic formula with specific values for `a`
 * and `b`.
 */
struct Formula
{
    int a;
    int b;

    explicit Formula(int b) : b(b) {
    }
    Formula() = default;
    Formula(const Formula&) = default;
    Formula& operator=(const Formula&) = default;

    /**
     * Compute the product of `a` and `b`.
     */
    explicit operator int() const {
        return a * b;
    }

    /**
     * Test whether the formula yields a prime number for the specified value.
     *
     * @param n The number to test.
     * @return `true` if the formula yields a prime number, `false` otherwise.
     */
    bool operator()(int n) const {
        auto tmp = n * n + a * n + b;
        if(tmp < 2) {
            return false;
        }
        return isPrime(static_cast<Long>(tmp));
    }
}; // Formula

// Absolute value must be less than or equal
constexpr int aLimit = 999;
constexpr int bLimit = 1000;

int main(int, char**) {
    Formula max{};
    int maxCount = 0;

    // Since n starts with 0 in the above formula, we need only try values for
    // b which are already prime (0^2 + 0 a + b must be prime).
    Range r(std::numeric_limits<int>::max());
    for(auto b : sieve(bLimit)) {
        Formula f(b);
        for(auto a = -aLimit; a <= aLimit; a++) {
            f.a = a;
            auto n = std::find_if_not(r.begin(), r.end(), f);
            if(*n > maxCount) {
                maxCount = *n;
                max = f;
            }
        }
    }

    std::cout << "Project Euler - Problem 27: Quadratic primes\n\n";
    std::cout << "The formula producing the most consecutive primes ("
              << maxCount << ") is\n  n^2 + " << max.a << " n + " << max.b
              << '\n';
    std::cout << "The product of a and b is " << static_cast<int>(max) << '\n';
}

/**
 * Test whether the specified number is prime.
 *
 * @param n The number to test.
 * @return `true` if `n` is prime, `false` otherwise.
 */
bool isPrime(Long n) {
    static std::vector<Long> primes;

    if(n > 3 && n % 2 == 0) {
        return false;
    }
    sieve_limit(primes, n);
    return std::binary_search(primes.begin(), primes.end(), n);
}
