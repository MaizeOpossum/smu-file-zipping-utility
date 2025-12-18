#include <bits/stdc++.h>
#include <stdlib.h>

#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;

// Write implementation prototypes Here
/*NOTES
    use bfs since we want to find the distance away from the first node
*/

int bfs (vector<vector<ll>> &graph, 
        ll node, 
        vector <bool> &checked, 
        vector <bool> &processed,
        vector <ll> &parent_node,
        ll target) {
    queue <ll> q;
    q.push(node);
    processed[node] = true;

    while (!q.empty()) {
        ll current_node = q.front();
        q.pop();
        if (!checked[current_node]) {
            checked[current_node] = true;
            for (ll neighbours : graph[current_node]) {
                if (!checked[neighbours]) {
                    q.push(neighbours);
                    if (!processed[neighbours]) {
                        parent_node[neighbours] = current_node;
                    }
                    processed[neighbours] = true;

                    if (neighbours == target) {
                        return 1;
                    }
                }
            }
        }
    }

    cout << "IMPOSSIBLE";
    return -1;
}

void solve(){
    ll num_nodes; ll num_edges;
    cin >> num_nodes >> num_edges;

    vector<vector<ll>> graph(num_nodes + 1);

    for (ll i = 0; i < num_edges; i++) {
        ll node_in; ll node_out;
        cin >> node_in >> node_out;
        graph[node_in].push_back(node_out);
        graph[node_out].push_back(node_in);
    }

    ll node = 1;
    vector<bool> checked(num_nodes + 1, false);
    vector<bool> processed(num_nodes + 1, false);
    vector<ll> parent_node(num_nodes + 1, -1);
    parent_node[1] = 0;

    ll condition = bfs(graph, node, checked, processed, parent_node, num_nodes);

    if (condition == -1) {
        return;
    }

    ll current_node = parent_node[num_nodes];
    
    vector<ll> path_reversed;
    path_reversed.push_back(num_nodes);

    while (current_node != 1) {
        path_reversed.push_back(current_node);
        current_node = parent_node[current_node];
    }
    path_reversed.push_back(current_node);

    cout << path_reversed.size() << endl;
    for (int i = 0; i < path_reversed.size(); i++) {
        cout << path_reversed[path_reversed.size() - 1 - i] << " ";
    }
}
// Driver code
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    if (fopen("test.inp", "r") != NULL) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
        freopen("test.err", "w", stderr);
    }

    bool multi_testcase = false; // change this
    
    ll test_cases {};

    if (multi_testcase) {
        cin >> test_cases;
    } else {
        test_cases = 1;
    }
    for(int i = 0; i < test_cases; ++i){
        solve();
    }
    return 0;
}