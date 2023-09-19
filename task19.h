#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

std::vector<int> prufer_code(std::vector<std::pair<int, int>> edges, int n) {
    std::vector<int> degree(n+1, 0);
    for (auto edge : edges) {
        degree[edge.first]++;
        degree[edge.second]++;
    }
    std::vector<int> prufer(n-2, 0);
    for (int i = 0; i < n-2; i++) {
        int v = -1;
        for (int j = 1; j <= n; j++) {
            if (degree[j] == 1) {
                v = j;
                break;
            }
        }
        int w = -1;
        for (auto edge : edges) {
            if (edge.first == v) {
                w = edge.second;
                break;
            }
            if (edge.second == v) {
                w = edge.first;
                break;
            }
        }
        prufer[i] = w;
        degree[v]--;
        degree[w]--;
        edges.erase(std::remove(edges.begin(), edges.end(), std::make_pair(v, w)), edges.end());
        edges.erase(std::remove(edges.begin(), edges.end(), std::make_pair(w, v)), edges.end());
    }
    return prufer;
}

std::vector<std::pair<int, int>> prufer_decode(std::vector<int> prufer) {
    int n = prufer.size() + 2;
    std::vector<int> degree(n+1, 1);
    for (int i : prufer) {
        degree[i]++;
    }
    std::vector<std::pair<int, int>> edges;
    for (int i : prufer) {
        int v = -1;
        for (int j = 1; j <= n; j++) {
            if (degree[j] == 1) {
                v = j;
                break;
            }
        }
        edges.push_back({v, i});
        degree[v]--;
        degree[i]--;
    }
    int v = -1;
    for (int j = 1; j <= n; j++) {
        if (degree[j] == 1) {
            if (v == -1) {
                v = j;
            } else {
                edges.push_back({v, j});
            }
        }
    }
    return edges;
}

std::vector<int> generate_random_labels() {
    std::vector<int> labels(9);
    for (int i = 0; i < 9; i++) {
        labels[i] = i+1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(labels.begin(), labels.end(), g);
    return labels;
}

std::pair<int, int> get_new_edge(std::pair<int, int> old_edge, std::vector<int> labels) {
    return {labels[old_edge.first-1], labels[old_edge.second-1]};
}

bool compare_edges(std::pair<int, int> edge1, std::pair<int, int> edge2) {
    if(edge1.first == edge2.first)
        return edge1.second < edge2.second;
    return edge1.first < edge2.first;
}

void save_edges(std::vector<std::pair<int, int>> edges, std::string& edges_str) {
    edges_str = "[";
    for(int i = 0; i < edges.size(); i++) {
        if(i == edges.size()-1)
            edges_str += "(" + std::to_string(edges[i].first) + "," + std::to_string(edges[i].second) + ")]";
        else
            edges_str += "(" + std::to_string(edges[i].first) + "," + std::to_string(edges[i].second) + "),";
    }

}

void save_vector(std::vector<int> v, std::string& v_str) {
    v_str = "[";
    for(int i = 0; i < v.size(); i++) {
        if(i == v.size()-1)
            v_str += std::to_string(v[i]) + "]";
        else
            v_str += std::to_string(v[i]) + ",";
    }
    v_str += "";
}

std::vector<std::pair<int, int>> generate_tree(int n) {
    std::vector<int> labels(n);
    for (int i = 0; i < n; i++) {
        labels[i] = i+1;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(labels.begin(), labels.end(), g);
    std::vector<std::pair<int, int>> edges(n-1);
    for (int i = 0; i < n-1; i++) {
        edges[i].first = std::min(labels[i], labels[i+1]);
        edges[i].second = std::max(labels[i], labels[i+1]);
    }
    return edges;
}

void save_tree(std::vector<std::pair<int, int>> edges, std::string& tree_str) {
    tree_str += "[";
    for(int i = 0; i < edges.size(); i++) {
        if(i == edges.size()-1)
            tree_str += "(" + std::to_string(edges[i].first) + "," + std::to_string(edges[i].second) + ")";
        else
            tree_str += "(" + std::to_string(edges[i].first) + "," + std::to_string(edges[i].second) + "),";
    }
    tree_str += "]";
}
