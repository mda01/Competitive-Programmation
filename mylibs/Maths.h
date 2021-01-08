#ifndef ALGO_MATHS_H
#define ALGO_MATHS_H

using ll = unsigned long long;

class Maths {
public:
/**
 * Computes a^n modulo mod
 * @param a the number to exponent
 * @param n the exponent
 * @param mod the modulo
 * @return a^n%mod
 */
    static ll exp(const ll &a, const ll &n, const ll &mod) {
        if (n == 0) return 1;
        ll y = exp(a, n / 2, mod);
        y = (y * y) % mod;
        if (n & 1) {
            y = (a * y) % mod;
        }
        return y;
    }

/**
 * Computes a^b^c modulo mod using Fermat's theorem.
 * Time optimisation are possible using memoisation
 * @return (a^b^c)%mod
 */
    [[maybe_unused]] static ll exp(const ll &a, const ll &b, const ll &c, const ll &mod) {
        return exp(a, exp(b, c, mod - 1), mod);
    }

};


#endif //ALGO_MATHS_H
