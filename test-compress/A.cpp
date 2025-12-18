#include <bits/stdc++.h>
#include <iomanip>

#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;

/* NOTES
    will try to use naive bfs first
    could probably speed up the code with memoization

    dfs is more efficient, but needs to avoid recursion due to limited call stack size
*/

// Write implementation prototypes Here
void dfs(vector<vector<ll>> &graph, vector<bool> &checked_nodes, vector<ll> &output) {
    stack <ll> st;
    st.push(1);

    while (!st.empty()){
        ll node = st.top();
        if (!checked_nodes[node]) {
            checked_nodes[node] = true;
            for (ll child : graph[node]) {
                st.push(child);
            }
        } else {
            st.pop();
            ll count = 0;
            for (ll child : graph[node]) {
                count += 1 + output[child];
            }
            output[node] = count;
        }
    }
}

void solve(){
    ll n {}; cin >> n;
    vector<ll> output(n + 1, 0); // index be employee, value is number of subordinates
    vector<vector<ll>> graph(n + 1); // index be employee, vector be subordinates 
    vector<bool> checked_nodes(n + 1, false); // index is the employee

    for (ll employee = 2; employee < n + 1; employee++) {
        int ipt {};
        cin >> ipt;
        graph[ipt].push_back(employee);
    }

    // dfs section
    dfs(graph, checked_nodes, output);

    // printing values
    for (ll i = 1; i < n + 1; i++) {
        cout << output[i] << " ";
    }
    cout << endl;
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
    
    ll test_cases = 1;
    //cin >> test_cases;
    for(int i = 0; i < test_cases; ++i){
        solve();
    }
    return 0;
}

// Implementation Here

