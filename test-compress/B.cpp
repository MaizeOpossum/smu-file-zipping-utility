#include <bits/stdc++.h>

#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;
/*NOTES
    dfs + memoisation to find all the 'blocks'

*/
void solve() {
    ll num_cities; ll num_roads;
    cin >> num_cities >> num_roads;

    vector <vector<ll>> city_graph(num_cities + 1);
    
    for (int i = 0; i < num_roads; i++) { // making the graph
        ll start_city; ll end_city;
        cin >> start_city >> end_city;
        city_graph[start_city].push_back(end_city);
        city_graph[end_city].push_back(start_city); 
    }

    
    stack <ll> st;
    vector <bool> cities_checked(num_cities + 1, false);
    vector <ll> disjoint_cities;
    for (int city = 1; city < num_cities + 1; city++) {
        // going through every city to ensure no disjoint graphs are unchecked
        if (!cities_checked[city]) {
            st.push(city);
            disjoint_cities.push_back(city);
        }

        // dfs part
        while (!st.empty()) {
            ll current_city = st.top();
            if (!cities_checked[current_city]) {
                cities_checked[current_city] = true;
                for (ll neighbour : city_graph[current_city]) {
                    st.push(neighbour);
                }
            } else {
                st.pop();
            }
        }   
    }

    cout << disjoint_cities.size() - 1 << endl;
    for (int i = 0; i < disjoint_cities.size() - 1; i++) {
        cout << disjoint_cities[i] << " " << disjoint_cities[i + 1] << endl;
    }
}

// Driver code
int main(){
    if (fopen("test.inp", "r") != NULL) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
        freopen("test.err", "w", stderr);
    }

    ll test_cases = 1;
    // cin >> test_cases;
    for(int i = 0; i < test_cases; ++i){
        solve();
    }
    return 0;
}