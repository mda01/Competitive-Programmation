#ifndef ALGO_KNAPSACK01_H
#define ALGO_KNAPSACK01_H

#include <vector>

class Knapsack01 {
public:
    /**
     * Solving knapsack problem
     * @param n the number of elements
     * @param c the capacity of the knapsack
     * @param w the weights of the elements
     * @param v the values of the elements
     * @return the maximum value we can get
     */
    static long long knapsack01(long long n, long long c, std::vector<long long> w, std::vector<long long> v) {
        std::vector<long long> dp(c + 1, 0);
        dp[0] = 0;
        for (long long i = 0; i < n; i++) {
            long long wi = w[i];
            for (long long j = c; j >= wi; j--) {
                dp[j] = std::max(dp[j - wi] + v[i], dp[j]);
            }
        }
        return dp[c];
    }
};


#endif //ALGO_KNAPSACK01_H
