#ifndef ALGO_SEGMENTTREE_H
#define ALGO_SEGMENTTREE_H


#include <limits>
#include <cmath>
#include <vector>

class SegmentTree {

    struct node {
        int sum = 0;
        int min = std::numeric_limits<int>::max();
        int from = 0;
        int to = -1;
        bool pending = false;
        int pending_val;

        int size() const {
            return to - from + 1;
        }
    };

    std::vector<node> heap;
    std::vector<int> array;
    int heap_size;
    int array_size;

    inline int left(int p) { return p << 1; }

    inline int right(int p) { return (p << 1) + 1; }

    inline bool contains(int from1, int to1, int from2, int to2) {
        return from1 <= from2 && to2 <= to1;
    }

    inline bool intersects(int from1, int to1, int from2, int to2) {
        return (from1 <= from2 && to1 >= from2) ||
               (from1 >= from2 && from1 <= to2);
    }

public:
    SegmentTree(const std::vector<int> &array) {
        this->array = array;
        array_size = array.size();
        heap_size = 2 * (1 << ((int) log2(array.size()) + 1));
        heap.resize(heap_size);
        build(1, 0, array_size - 1);
    }

private:
    void build(int heap_index, int from, int to) {
        node &n = heap[heap_index];
        n.from = from;
        n.to = to;
        if (from == to) {
            n.sum = array[from];
            n.min = array[from];
        } else {
            int middle = from + (to - from) / 2;
            build(left(heap_index), from, middle);
            build(right(heap_index), middle + 1, to);
            n.sum = heap[left(heap_index)].sum + heap[right(heap_index)].sum;
            n.min = std::min(heap[left(heap_index)].min, heap[right(heap_index)].min);
        }
    }

public:
    int get_sum(int from, int to) {
        return get_sum(1, from, to);
    }

private:
    int get_sum(int heap_index, int from, int to) {
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
    int get_min(int from, int to) {
        return get_min(1, from, to);
    }

private:
    int get_min(int heap_index, int from, int to) {
        node &n = heap[heap_index];
        if (n.pending && contains(n.from, n.to, from, to))
            return n.pending_val;

        if (contains(from, to, n.from, n.to))
            return n.min;

        if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            return std::min(get_min(left(heap_index), from, to), get_min(right(heap_index), from, to));
        }
        return std::numeric_limits<int>::max();
    }

public:
    void update(int from, int to, int value) {
        update(1, from, to, value);
    }

private:
    void update(int heap_index, int from, int to, int value) {
        node &n = heap[heap_index];
        if (contains(from, to, n.from, n.to)) {
            change(n, value);
        } else if (intersects(from, to, n.from, n.to)) {
            propagate(heap_index);
            update(left(heap_index), from, to, value);
            update(right(heap_index), from, to, value);
            n.sum = heap[left(heap_index)].sum + heap[right(heap_index)].sum;
            n.min = std::min(heap[left(heap_index)].min, heap[right(heap_index)].min);
        }
    }

    void propagate(int heap_index) {
        node &n = heap[heap_index];
        if (n.pending) {
            if (n.size() != 1) {
                change(heap[left(heap_index)], n.pending_val);
                change(heap[right(heap_index)], n.pending_val);
            }
            n.pending = false;
        }
    }

    void change(node &n, int value) {
        n.pending = true;
        n.pending_val = value;
        n.sum = n.size() * value;
        n.min = value;
        array[n.from] = value;
    }
};


#endif //ALGO_SEGMENTTREE_H
