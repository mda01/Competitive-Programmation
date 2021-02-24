// CSES problems solved: 90
// Kattis score: 23.4 x)

#include <iostream>
#include <algorithm>
#include <utility>
#include <ctime>
#include <chrono>
#include <numeric>
#include <limits>
#include <cmath>
#include <string>
#include <regex>
#include <iterator>
#include <vector>
#include <list>
#include <set>
#include <unordered_set>
#include <queue>
#include <deque>
#include <map>
#include <unordered_map>
#include <stack>

using ll = long long;
using ull = unsigned long long;
using pll = std::pair<ll, ll>;
using namespace std;
const ull MOD = ull(1e9 + 7);
#define endl '\n'
#define getline(s) getline(cin, s)
#define INF ll((1ull<<63u)-25u)
#define print(text) (cout << (text))
#define println(text) (cout << (text) << endl)
#define lowercase(string) for(auto&c: string)c = c >= 'A' && c <= 'Z' ? c - 'A' + 'a' : c;
#define uppercase(string) for(auto&c: string)c = c >= 'a' && c <= 'z' ? c - 'a' + 'A' : c;
#define elapsed_time(start) cerr << "time: " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count() << " us" << endl
#define numeric_elapsed_time(start) ull(std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now()-start).count())

template<class T>
void print_collection(T collection) {
    print(typeid(T).name());
    print("{");
    auto colit = collection.begin();
    for (uint iterator = 0; iterator < collection.size() - 1; iterator++) {
        print(*colit);
        colit++;
        print(", ");
    }
    print(*colit);
    println("}");
}

vector<string> split(const string &s, const char c = ' ', const bool strip = true) {
    vector<string> res;
    ull last = 0;
    for (ull i = 0; i < s.length(); i++) {
        if (s[i] == c) {
            string ss = s.substr(last, i - last);
            if (!(strip && ss.empty()))
                res.push_back(ss);
            last = i + 1;
        }
    }
    string ss = s.substr(last, s.length() - last);
    if (!(strip && ss.empty()))
        res.push_back(ss);
    return res;
}

string strip(const string &s, const char c = ' ') {
    string res;
    for (uint i = 0; i < s.size(); i++) {
        if (s[i] != c) {
            res = s.substr(i, s.size());
            break;
        }
    }

    while (res.back() == c) { res.pop_back(); }
    return res;
}

const vector<pair<int, int>> pos8 = {
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0,  -1},
        {0,  1},
        {1,  -1},
        {1,  0},
        {1,  1}
};
const vector<pair<int, int>> pos4 = {
        {-1, 0},
        {0,  -1},
        {0,  1},
        {1,  0}
};

vector<tuple<int, int, int, int>> gen_pos_4d() {
    vector<tuple<int, int, int, int>> res;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    if (i == 0 && j == 0 && k == 0 && l == 0) continue;
                    res.emplace_back(i, j, k, l);
                }
            }
        }
    }
    return res;
}

vector<pair<int, int>> hex_neigh(int x) {
    vector<pair<int, int>> res = {
            {1,  0},
            {-1, 0},
            {0,  1},
            {0,  -1}
    };
    if (x & 1) {
        res.emplace_back(-1, 1);
        res.emplace_back(-1, -1);
    } else {
        res.emplace_back(1, 1);
        res.emplace_back(1, -1);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    auto start = std::chrono::high_resolution_clock::now();
    elapsed_time(start);
    return 0;
}
