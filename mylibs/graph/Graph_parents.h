#ifndef ALGO_GRAPH_CHILDREN_H
#define ALGO_GRAPH_CHILDREN_H


#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <set>

using ll = long long;
using namespace std;

#define INF ll(1ull<<60u)
using Node = unordered_map<ll, ll>;

class [[maybe_unused]] Graph_parents {
private:
    bool directed;
    ll nb_nodes;
    vector<Node> parents;

public:
    /**
     * Creates an undirected graph with nb_nodes nodes
     * @param nb_nodes the number of nodes
     */
    [[maybe_unused]] explicit Graph_parents(ll nb_nodes) : directed(false), nb_nodes(nb_nodes),
                                                           parents(vector<Node>(nb_nodes)) {}

    /**
     * Creates an empty graph
     * @param directed specifies if the graph is directed
     */
    [[maybe_unused]] explicit Graph_parents(bool directed) : directed(directed), nb_nodes(0),
                                                             parents(vector<Node>(0)) {}

    /**
     * Creates a graph
     * @param directed specifies if the graph is directed
     * @param nb_nodes the number of nodes
     */
    [[maybe_unused]] explicit Graph_parents(bool directed, ll nb_nodes) : directed(directed), nb_nodes(nb_nodes),
                                                                          parents(vector<Node>(nb_nodes, Node())) {}

    [[nodiscard]] ll size() const {
        return nb_nodes;
    }

    /**
     * Enlarge the graph
     */
    [[maybe_unused]] void add_node() {
        nb_nodes++;
        parents.emplace_back();
    }

    /**
     * Get a node parents
     * @param node the index of the requested node
     * @return a Node containing the parents
     */
    [[maybe_unused]] [[nodiscard]] Node get_parents(ll node) const {
        return parents[node];
    }

    /**
     * Add a parent to a node (distance 1), and reciprocally if undirected
     * @param parent the parent
     * @param child the child
     */
    [[maybe_unused]] void add_parent(ll child, ll parent) {
        add_parent(child, parent, 1);
    }

    /**
     * Add a child to a node, and reciprocally if undirected
     * @param parent the parent
     * @param child the child
     * @param dist the distance between the nodes
     */
    void add_parent(ll child, ll parent, ll dist) {
        parents[child][parent] = dist;
        if (!directed)
            parents[parent][child] = dist;
    }

    /**
     * Remove ALL vertices between two nodes
     * @param parent the parent
     * @param child the child
     */
    [[maybe_unused]] void parent(ll child, ll parent) {
        if (has_parent(child, parent)) {
            parents[parent].erase(child);
            if (!directed)
                parents[child].erase(parent);
            return;
        }
    }

    /**
     * Finds if n1 has n2 as a direct child
     * @param n1 the first node
     * @param n2 the parent
     * @return true if there are vertices between n1 and n2
     */
    [[nodiscard]] bool has_parent(ll n1, ll n2) const {
        return parents[n1].find(n2) != parents[n1].end();
    }

    /**
     * Finds the distance between n1 and n2, INF if n2 is not a direct child of n1
     * @param n1 the first node
     * @param n2 the child
     * @return the distance between n1 and n2 if n2 is a child of n1, INF else.
     */
    [[maybe_unused]] [[nodiscard]] ll parent_dist(ll n1, ll n2) const {
        if (has_parent(n1, n2))
            return parents[n1].at(n2);
        return INF;
    }

    /**
     * Finds via a DFS if two node are connected
     * @param n1 the first node
     * @param n2 the goal
     * @return true if n1 and n2 are connected, false else
     */
    [[maybe_unused]] [[nodiscard]] bool connected(ll n1, ll n2) const {
        vector<ll> ignored;
        return connected(n1, n2, ignored);
    }

    /**
     * Finds via a DFS if two node are connected
     * @param n1 the first node
     * @param n2 the goal
     * @param path the path from n1 to n2 (modified)
     * @return true if n1 and n2 are connected, false else
     */
    [[maybe_unused]] bool connected(ll n1, ll n2, vector<ll> &path) const {
        vector<bool> visited(nb_nodes, false);
        return path_dfs(n1, n2, visited, path);
    }

    /**
     * Find the connected components in an undirected graph
     * @return a vector of nodes (long), in which each node is in a different component
     */
    [[maybe_unused]] [[nodiscard]] vector<ll> find_connected_components() const {
        if (!directed) {
            vector<ll> components;
            vector<bool> visits(nb_nodes, false);
            for (ll i = 0; i < nb_nodes; i++) {
                if (!visits[i]) {
                    components.push_back(i);
                    visit_dfs(i, visits);
                }
            }
            return components;
        } else {
            cerr << "Not available for directed graphs, see strongly connected components" << endl;
            exit(100);
        }
    }

    /**
     * Determines if an undirected graph has cycles
     * @return true if the graph has a cycle, false else
     */
    [[maybe_unused]] [[nodiscard]] bool has_cycles() const {
        if (!directed) {
            vector<ll> components = find_connected_components();

            bool has_cycle = false;
            for (ll &c : components) {
                has_cycle = has_cycle || find_cycle_dfs(c);
            }
            return has_cycle;
        } else {
            cerr << "Not implemented yet" << endl;
            exit(100);
        }
    }

    /**
     * Return true if the graph can be bicolored, and a color distribution, or else false
     * @return a pair of the result and a vector of the colors
     */
    [[maybe_unused]] [[nodiscard]] pair<bool, vector<int>> is_bicolor() const {
        if (!directed) {
            bool is_bic = true;
            vector<int> colors(nb_nodes, -1);
            for (int i = 0; i < nb_nodes; i++) {
                if (colors[i] == -1) {
                    is_bic = is_bic && bicolor_dfs(i, 0, colors);
                }
            }
            return make_pair(is_bic, colors);
        } else {
            cerr << "Not available for directed graphs" << endl;
            exit(100);
        }
    }


private:
    bool path_dfs(ll start, ll end, vector<bool> &visited, vector<ll> &path) const {
        if (start == end) return true;
        visited[start] = true;
        for (auto &child: parents[start]) {
            if (!visited[child.first]) {
                path.push_back(child.first);
                if (path_dfs(child.first, end, visited, path))
                    return true;
                path.pop_back();
            }
        }
        return false;
    }

    void visit_dfs(ll node, vector<bool> &visited) const {
        visited[node] = true;
        for (auto &child: parents[node]) {
            if (!visited[child.first])
                visit_dfs(child.first, visited);
        }
    }

    [[nodiscard]] bool find_cycle_dfs(ll node) const {
        vector<bool> v(nb_nodes, false);
        return find_cycle_dfs(node, -1, v);
    }

    bool find_cycle_dfs(ll node, ll parent, vector<bool> &visited) const {
        visited[node] = true;
        bool found_cycle = false;
        for (auto &child: parents[node]) {
            if (!visited[child.first])
                found_cycle = found_cycle || find_cycle_dfs(child.first, node, visited);
            else if (child.first != parent)
                return true;
        }
        return found_cycle;
    }

    bool bicolor_dfs(ll node, ll color, vector<int> &colors) const {
        colors[node] = color;
        bool is_bic = true;
        for (auto &child : parents[node]) {
            ll c_col = colors[child.first];
            if (c_col == color) {
                return false;
            } else if (c_col == -1) {
                is_bic = is_bic && bicolor_dfs(child.first, 1 - color, colors);
            }
        }
        return is_bic;
    }
};

#endif //ALGO_GRAPH_CHILDREN_H
