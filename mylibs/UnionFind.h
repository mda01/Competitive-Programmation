#ifndef DRAFT_UNIONFIND_H
#define DRAFT_UNIONFIND_H

#include <algorithm>
#include <map>
#include <iostream>


template<typename T>
concept Integrals = std::is_integral<T>::value;

// priority_queue<ll, vector<ll>, greater<>> minHeap;
// priority_queue<ll, vector<ll>> maxHeap;
template<typename T>
class UnionFind {
private:
    std::vector<long long> id;
    std::vector<long long> sz;
    long long count;
    std::map<T, long long> m;
public:

    explicit UnionFind<T>(const long long N) : id(N, 0), sz(N, 1) {
        //std::cout << "Non Integral" << std::endl;
        count = N;
        for (long long i = 0; i < N; i++) { id[i] = i; }
    }

    [[nodiscard]] long long nb_components() const {
        return count;
    }

    long long size_set(long long i) {
        return sz[find_set(i)];
    }

    long long size_set(T i) {
        return size_set(m[i]);
    }

    long long find_set(long long i) {
        return (id[i] == i) ? i : (id[i] = find_set(id[i]));
    }

    long long find_set(T i) {
        return find_set(m[i]);
    }

    bool connected(long long i, long long j) {
        return find_set(i) == find_set(j);
    }

    bool connected(T i, T j) {
        return connected(m[i], m[j]);
    }

    void union_set(T p, T q) {
        if (m[p] == 0)
            m[p] = m.size();
        if (m[q] == 0)
            m[q] = m.size();
        union_set(m[p], m[q]);
    }

    void union_set(long long p, long long q) {
        long long i = find_set(p);
        long long j = find_set(q);
        if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        --count;
    }
};

template<Integrals T>
class UnionFind<T> {
private:
    std::vector<long long> id;
    std::vector<long long> sz;
    long long count;
public:
    explicit UnionFind(const long long N) : id(N, 0), sz(N, 1) {
        //std::cout << "Integral" << std::endl;
        count = N;
        for (long long i = 0; i < N; i++) { id[i] = i; }
    }

    [[nodiscard]] long long nb_components() const {
        return count;
    }

    long long size_set(long long i) {
        return sz[find_set(i)];
    }

    long long find_set(long long i) {
        return (id[i] == i) ? i : (id[i] = find_set(id[i]));
    }

    bool connected(long long i, long long j) {
        return find_set(i) == find_set(j);
    }

    void union_set(long long p, long long q) {
        long long i = find_set(p);
        long long j = find_set(q);
        if (i == j) return;
        // make smaller root point to larger one
        if (sz[i] < sz[j]) {
            id[i] = j;
            sz[j] += sz[i];
        } else {
            id[j] = i;
            sz[i] += sz[j];
        }
        --count;
    }
};

#endif //DRAFT_UNIONFIND_H
