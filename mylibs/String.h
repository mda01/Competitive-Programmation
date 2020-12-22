#ifndef ALGO_STRING_H
#define ALGO_STRING_H

#include <cstring>
#include <vector>
#include <string>

typedef long long ll;
typedef unsigned long long ull;

using std::vector, std::string, std::pair;


struct PTrie_a {
private:
    struct MP {
        ll child, count;

        MP(ll parent, ll count) : child(parent), count(count) {}
    };

public:
    const int als;
    vector<vector<MP>> trie;
    ll nb_nodes;

    explicit PTrie_a(const ll max_nodes, const int als = 26) : als(als), nb_nodes(0) {
        trie = vector(max_nodes, vector<MP>(als, {-1, 0}));
    }

    void insert_word(const string &word) {
        ll current = 0;
        for (const char &c: word) {
            auto &next = trie[current][c - 'a'];
            if (next.child == -1) {
                nb_nodes++;
                next.child = nb_nodes;
            }
            next.count++;
            current = next.child;
        }
    }

private:
    [[nodiscard]] bool till_the_end(const string &word, ll current) const {
        for (char c : word) {
            if (trie[current][c - 'a'].child == -1)
                return false;
            current = trie[current][c - 'a'].child;
        }
        return true;
    }

public:
    [[nodiscard]] bool is_in_tree(const string &word, ll current = 0) const {
        if (word.empty()) {
            return true;
        }
        bool is_in = false;
        for (int i = 0; i < 26; i++) {
            ll next = trie[current][i].child;
            if (next != -1) {
                if ((word[0] - 'a') == i)
                    is_in = is_in || till_the_end(word, current);
                is_in = is_in || is_in_tree(word, next);
            }
        }
        return is_in;
    }

private:
    [[nodiscard]] ll count_till_the_end(const string &word, ll current) const {
        ll res = 0;
        for (char c : word) {
            auto x = trie[current][c - 'a'];
            if (x.child == -1)
                return 0;
            res = x.count;
            current = trie[current][c - 'a'].child;
        }
        return res;
    }

public:
    [[nodiscard]] ll count_occurences(const string &word, ll current = 0) const {
        if (word.empty()) return 0; // should not end here
        ll cnt = 0;
        for (int i = 0; i < 26; i++) {
            ll next = trie[current][i].child;
            if (next != -1) {
                if ((word[0] - 'a') == i) {
                    cnt += count_till_the_end(word, current);
                }
                cnt += count_occurences(word, next);
            }
        }

        return cnt;
    }

};

class String {
private:
    static const ll A = 911382323, B = 972663749;
public:
    /**
     * Hashes a string using polynomial hash
     * @param s the string to be hashed
     * @return a vector of pairs <hash, a^k%B>
     */
    static vector<pair<ll, ll>> hash_string(const string &s) {
        vector<pair<ll, ll>> hash_table(s.length());
        hash_table[0] = {s[0], 1};
        ll h, p;
        for (ull k = 1; k < s.length(); k++) {
            h = hash_table[k - 1].first, p = hash_table[k - 1].second;
            hash_table[k] = {
                    (h * A + s[k]) % B,
                    (p * A) % B
            };
        }
        return hash_table;
    }

    /**
     * Gets the hash of a substring given a hashtable
     * @param hp the hashtable
     * @param a the starting index (included)
     * @param b the ending index (included!!)
     * @return the hash of the substring
     */
    static ll get_hash(const vector<pair<ll, ll>> &hp, const ll &a, const ll &b) {
        if (a == 0)
            return hp[b].first;
        ll res = (hp[b].first - (hp[a - 1].first * hp[b - a + 1].second)) % B;
        if (res < 0)
            return res + B;
        return res;
    }

private:
    void computeLPSArray(string pat, ll M, vector<ll> &lps) {
        // length of the previous longest prefix suffix
        int len = 0;

        lps[0] = 0; // lps[0] is always 0

        // the loop calculates lps[i] for i = 1 to M-1
        ll i = 1;
        while (i < M) {
            if (pat[i] == pat[len]) {
                len++;
                lps[i] = len;
                i++;
            } else {
                // (pat[i] != pat[len])

                // This is tricky. Consider the example.
                // AAACAAAA and i = 7. The idea is similar
                // to search step.
                if (len != 0) {
                    len = lps[len - 1];

                    // Also, note that we do not increment
                    // i here
                } else {
                    // if (len == 0)
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

public:
    vector<ll> KMPSearch(string pat, string txt) {
        ll M = pat.length(), N = txt.length();
        vector<ll> res;
        vector<ll> lps(M);
        computeLPSArray(pat, M, lps);
        ll i = 0, j = 0;
        while (i < N) {
            if (pat[j] == txt[i]) {
                i++;
                j++;
            }
            if (j == M) {
                res.push_back(i - j);
                j = lps[j - 1];
            } else if (i < N && pat[j] != txt[i]) {
                if (j != 0)
                    j = lps[j - 1];
                else
                    i++;
            }
        }
        return res;
    }
};


#endif //ALGO_STRING_H
