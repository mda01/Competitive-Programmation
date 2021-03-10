#ifndef ALGO_KNAPSACK_H
#define ALGO_KNAPSACK_H

#include <vector>
#include <queue>

using namespace std;

class Knapsack {
public:
    /**
     * Solving knapsack 0/1 problem
     * @param n the number of elements
     * @param c the capacity of the knapsack
     * @param w the weights of the elements
     * @param v the values of the elements
     * @return the maximum value we can get
     */
    static long long
    knapsack01(const long long n, const long long c, const std::vector<long long> &w, const std::vector<long long> &v) {
        vector<long long> dp(c + 1, 0);
        dp[0] = 0;
        for (long long i = 0; i < n; i++) {
            long long wi = w[i];
            for (long long j = c; j >= wi; j--) {
                dp[j] = std::max(dp[j - wi] + v[i], dp[j]);
            }
        }
        return dp[c];
    }

    /**
     * Solving the unbounded knapsack problem
     * @param n the number of elements
     * @param c the capacity of the knapsack
     * @param w the weights of the elements
     * @param v the values of the elements
     * @return the maximum value we can get
     */
    static long long
    unbounded_knapsack(const long long n, const long long c, const std::vector<long long> &w,
                       const std::vector<long long> &v) {
        vector<long long> dp(c + 1, 0);
        dp[0] = 0;
        for (long long i = 0; i <= c; i++) {
            for (long long j = 0; j < n; j++) {
                if (w[j] <= i) {
                    dp[i] = max(dp[i], dp[i - w[j]] + v[j]);
                }
            }
        }
        return dp[c];
    }

/**
     * Solving fractional knapsack problem
     * @param n the number of elements
     * @param c the capacity of the knapsack
     * @param w the weights of the elements
     * @param v the values of the elements
     * @return the maximum value we can get
     */
    static double fractional_knapsack(const long long n, const long long c, const std::vector<long long> &w,
                                      const std::vector<long long> &v) {
        priority_queue<Item, vector<Item>, greater<>> items{};
        for (long long i = 0; i < n; i++) {
            items.push(Item{v[i], w[i]});
        }
        double res = 0;
        long long remaining = c;
        while (!items.empty() && remaining - items.top().weight >= 0) {
            res += items.top().value;
            remaining -= items.top().weight;
            items.pop();
        }
        if (!items.empty()) {
            res += (double) items.top().value * (double) remaining / (double) items.top().weight;
        }
        return res;
    }


private:
    struct Item {
        long long value, weight;

        bool operator<(const Item &rhs) const {
            return (double) value / (double) weight < (double) rhs.value / (double) weight;
        }

        bool operator>(const Item &rhs) const {
            return rhs < *this;
        }

        bool operator<=(const Item &rhs) const {
            return !(rhs < *this);
        }

        bool operator>=(const Item &rhs) const {
            return !(*this < rhs);
        }
    };
};


#endif //ALGO_KNAPSACK_H
