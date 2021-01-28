#ifndef ALGO_SEGMENTTREE_H
#define ALGO_SEGMENTTREE_H


#include <limits>
#include <cmath>
#include <vector>

using ll = long long;

class SegmentTree {

    struct node {
        ll sum = 0;
        ll min = std::numeric_limits<ll>::max();
        ll max = std::numeric_limits<ll>::min();
        ll from = 0;
        ll to = -1;
        bool pending = false;
        ll pending_val;

        [[nodiscard]] ll size() const {
            return to - from + 1;
        }
    };

    std::vector<node> heap;
    std::vector<ll> array;
    ll heap_size;
    ll array_size;

    static inline ll left(ll p) { return p << 1; }

    static inline ll right(ll p) { return (p << 1) + 1; }

    static inline bool contains(ll from1, ll to1, ll from2, ll to2) {
        return from1 <= from2 && to2 <= to1;
    }

    static inline bool intersects(ll from1, ll to1, ll from2, ll to2) {
        return (from1 <= from2 && to1 >= from2) ||
               (from1 >= from2 && from1 <= to2);
    }

public:
    explicit SegmentTree(const std::vector<ll> &array) {
        this->array = array;
        array_size = array.size();
        heap_size = 2 * (1 << ((ll) log2(array.size()) + 1));
        heap.resize(heap_size);
        build(1, 0, array_size - 1);
    }

private:
    void build(ll heap_index, ll from, ll to) {
        node &n = heap[heap_index];
        n.from = from;
        n.to = to;
        if (from == to) {
            n.sum = array[from];
            n.min = array[from];
            n.max = array[from];
        } else {
            ll middle = from + (to - from) / 2;
            build(left(heap_index), from, middle);
            build(right(heap_index), middle + 1, to);
            n.sum = heap[left(heap_index)].sum + heap[right(heap_index)].sum;
            n.min = std::min(heap[left(heap_index)].min, heap[right(heap_index)].min);
            n.max = std::max(heap[left(heap_index)].max, heap[right(heap_index)].max);
        }
    }

public:
    ll get_sum(ll from, ll to) {
        return get_sum(1, from, to);
    }

private:
    ll get_sum(ll heap_index, ll from, ll to) {
        node &n = heap[heap_index];
        if (n.pending && contains(n.from, n.to, from, to))
            return (to - from + 1) * n.pending_val;

        if (contains(from, to, n.from, n.to))
            return n.sum;

        if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            return get_sum(left(heap_index), from, to) + get_sum(right(heap_index), from, to);
        }
        return 0;
    }

public:
    ll get_min(ll from, ll to) {
        return get_min(1, from, to);
    }
    ll get_max(ll from, ll to) {
        return get_max(1, from, to);
    }

private:
    ll get_min(ll heap_index, ll from, ll to) {
        node &n = heap[heap_index];
        if (n.pending && contains(n.from, n.to, from, to))
            return n.pending_val;

        if (contains(from, to, n.from, n.to))
            return n.min;

        if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            return std::min(get_min(left(heap_index), from, to), get_min(right(heap_index), from, to));
        }
        return std::numeric_limits<ll>::max();
    }
    ll get_max(ll heap_index, ll from, ll to) {
        node &n = heap[heap_index];
        if (n.pending && contains(n.from, n.to, from, to))
            return n.pending_val;

        if (contains(from, to, n.from, n.to))
            return n.max;

        if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            return std::max(get_max(left(heap_index), from, to), get_max(right(heap_index), from, to));
        }
        return std::numeric_limits<ll>::min();
    }

public:
    void update(ll from, ll to, ll value) {
        update(1, from, to, value);
    }

private:
    void update(ll heap_index, ll from, ll to, ll value) {
        node &n = heap[heap_index];
        if (contains(from, to, n.from, n.to)) {
            change(n, value);
        } else if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            update(left(heap_index), from, to, value);
            update(right(heap_index), from, to, value);
            n.sum = heap[left(heap_index)].sum + heap[right(heap_index)].sum;
            n.min = std::min(heap[left(heap_index)].min, heap[right(heap_index)].min);
            n.max = std::max(heap[left(heap_index)].max, heap[right(heap_index)].max);
        }
    }

    void propagate(ll heap_index) {
        node &n = heap[heap_index];
        if (n.pending) {
            if (n.size() != 1) {
                change(heap[left(heap_index)], n.pending_val);
                change(heap[right(heap_index)], n.pending_val);
            }
            n.pending = false;
        }
    }

    void change(node &n, ll value) {
        n.pending = true;
        n.pending_val = value;
        n.sum = n.size() * value;
        n.min = value;
        n.max = value;
        array[n.from] = value;
    }
};


#endif //ALGO_SEGMENTTREE_H
