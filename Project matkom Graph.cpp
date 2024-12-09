#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm> // Untuk fungsi reverse

using namespace std;

// Struktur data untuk merepresentasikan edge
struct Edge {
    int to, weight;
};

// Fungsi untuk menghitung rute terpendek menggunakan algoritma Dijkstra
void dijkstra(int start, int end, const vector<vector<Edge>>& graph) {
    int n = graph.size();
    vector<int> distance(n, INT_MAX); // Menyimpan jarak terpendek ke setiap node
    vector<int> parent(n, -1);        // Menyimpan jalur sebelumnya untuk merekonstruksi jalur
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    distance[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [currentDist, currentNode] = pq.top();
        pq.pop();

        // Jika jarak yang ditemukan lebih besar, abaikan
        if (currentDist > distance[currentNode]) continue;

        for (const auto& edge : graph[currentNode]) {
            int nextNode = edge.to;
            int weight = edge.weight;

            // Jika menemukan jarak yang lebih pendek
            if (distance[currentNode] + weight < distance[nextNode]) {
                distance[nextNode] = distance[currentNode] + weight;
                parent[nextNode] = currentNode;
                pq.push({distance[nextNode], nextNode});
            }
        }
    }

    // Menampilkan hasil untuk node akhir
    cout << "Node Awal: " << start << endl;
    cout << "Node Akhir: " << end << endl;
    cout << "Jarak Terpendek: ";
    if (distance[end] == INT_MAX) {
        cout << "Unreachable" << endl;
        return;
    }
    cout << distance[end] << " m" << endl;

    cout << "Path: ";
    vector<int> path;
    for (int v = end; v != -1; v = parent[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    for (size_t i = 0; i < path.size(); ++i) {
        cout << path[i] << (i + 1 < path.size() ? " -> " : "");
    }
    cout << endl;
}

int main() {
    // Data graph sudah disiapkan
    int n = 11; // Jumlah node
    int m = 14; // Jumlah edge

    // Membuat graph dengan jumlah node 'n'
    vector<vector<Edge>> graph(n);

    // Data edge (from, to, weight) yang diberikan
    vector<tuple<int, int, int>> edges = {
        {0, 1, 150}, {0, 4, 81}, {0, 8, 160},
        {1, 2, 110}, {2, 4, 140}, {2, 3, 100},
        {3, 5, 110}, {3, 6, 140}, {4, 6, 100},
        {4, 9, 87}, {5, 7, 135}, {6, 10, 186},
        {7, 6, 164}, {8, 9, 87}, {9, 10, 110}
    };

    // Menambahkan edges ke graph
    for (const auto& edge : edges) {
        int from, to, weight;
        tie(from, to, weight) = edge;
        graph[from].push_back({to, weight});
        graph[to].push_back({from, weight}); // Jika graph undirected
    }

    // Input dari pengguna untuk node awal dan node akhir
    int start, end;
    cout << "Masukkan node awal: ";
    cin >> start;
    cout << "Masukkan node akhir: ";
    cin >> end;

    // Validasi input
    if (start < 0 || start >= n || end < 0 || end >= n) {
        cout << "Node yang dimasukkan tidak valid!" << endl;
        return 1; // Keluar dari program jika input tidak valid
    }

    // Menjalankan algoritma Dijkstra
    dijkstra(start, end, graph);

    return 0;
}
