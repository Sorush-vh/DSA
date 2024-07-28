#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
const int INF = 1e9;
int n;

vector <pair <int, int>> coords1;
vector <pair <int, int>> coords2;



void get_input(){
    cin >> n;
    coords1.resize(n);
    coords2.resize(n);
    for (int i = 0; i < n; i++)
        cin >> coords1.at(i).first >> coords1.at(i).second;
     for (int i = 0; i < n; i++)
        cin >> coords2.at(i).first >> coords2.at(i).second;
}

bool isThereEdge(int n1, int n2){
    if(coords1.at(n1).first < coords2.at(n2).first && coords1.at(n1).second < coords2.at(n2).second)
        return true;
    else return false;
}


class BipartiteGraph {
public:
    int n, m;
    vector<vector<int>> adj;
    vector<int> pairU, pairV, dist;

    BipartiteGraph(int n, int m) : n(n), m(m) {
        adj.resize(n + 1);
        pairU.assign(n + 1, 0);
        pairV.assign(m + 1, 0);
        dist.assign(n + 1, 0);
    }

    void fillEdges(){
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if(isThereEdge(i,j))
                    adj.at(i+1).push_back(j+1);
    }

    bool bfs() {
        queue<int> Q;
        for (int u = 1; u <= n; u++) {
            if (pairU[u] == 0) {
                dist[u] = 0;
                Q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        dist[0] = INF;
        while (!Q.empty()) {
            int u = Q.front();
            Q.pop();

            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        Q.push(pairV[v]);
                    }
                }
            }
        }

        return dist[0] != INF;
    }

    bool dfs(int u) {
        if (u != 0) {
            for (int v : adj[u]) {
                if (dist[pairV[v]] == dist[u] + 1) {
                    if (dfs(pairV[v])) {
                        pairV[v] = u;
                        pairU[u] = v;
                        return true;
                    }
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    int hopcroftKarp() {
        int matching = 0;
        while (bfs()) {
            for (int u = 1; u <= n; u++) {
                if (pairU[u] == 0 && dfs(u)) {
                    matching++;
                }
            }
        }
        return matching;
    }
};

int main(){
    get_input();
    BipartiteGraph bg(n, n);
    bg.fillEdges();
    cout << bg.hopcroftKarp();

    return 0;
}