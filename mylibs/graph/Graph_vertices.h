#ifndef ALGO_GRAPH_VERTICES_H
#define ALGO_GRAPH_VERTICES_H


#include <iostream>
#include <vector>
#include <tuple>
#include <queue>

using ll = long long;
using namespace std;
using Vertice = tuple<ll, ll, ll>; // parent child distance
#define INF ll((1ull<<63u)-25u)
//#define INF ll(1ull<<30u)

class Graph_vertices {
private:
    vector<Vertice> vertices;
public:
    [[nodiscard]] const vector<Vertice> &getVertices() const {
        return vertices;
    }

    explicit Graph_vertices() : vertices(vector<Vertice>()) {}

    void add_vertex(ll parent, ll child, ll distance) {
        vertices.emplace_back(parent, child, distance);
    }

    ll remove_vertices(ll parent, ll child) {
        auto it = vertices.begin();
        ll p, c, d, cnt = 0;
        while (it != vertices.end()) {
            tie(p, c, d) = *it;
            if (parent == p && child == c) {
                vertices.erase(it);
                cnt++;
            } else {
                it++;
            }
        }
        return cnt;
    }

    void sort_parent() {
        std::sort(vertices.begin(), vertices.end());
    }

    [[nodiscard]] bool has_child(const ll parent, const ll child) const {
        ll p, c, d;
        for (const auto &v : vertices) {
            tie(p, c, d) = v;
            if (parent == p && child == c) return true;
        }
        return false;
    }

    ll child_dist(const ll parent, const ll child) {
        ll mini = INF;
        ll p, c, d;
        for (const auto &it: vertices) {
            tie(p, c, d) = it;
            if (parent == p && child == c) {
                mini = min(mini, d);
            }
        }
        return mini;
    }

    [[maybe_unused]] vector<ll> simple_bellman_ford(ll start) {
        ll nb_nodes = vertices.size();
        vector<ll> distances(nb_nodes);
        for (ll i = 0; i < nb_nodes; i++) {
            distances[i] = INF;
        }
        distances[start] = 0;
        bool changed = true;
        ll a, b, w;
        for (ll i = 0; changed && i < nb_nodes; i++) {
            changed = false;
            for (auto &arc: vertices) {
                tie(a, b, w) = arc;
                if (distances[a] == INF) continue;
                ll new_dist = distances[a] + w;
                if (new_dist < distances[b]) {
                    distances[b] = new_dist;
                    changed = true;
                }

            }
        }
        return distances;
    }


};


#endif //ALGO_GRAPH_VERTICES_H
