#include <bits/stdc++.h>
#include <unordered_set>

#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;
/*NOTES
    despite the large number of operations, we only need to perform it until 
    there's no more changes
    BFS until no changes
*/

// prints grid
void print_grid(vector <vector<char>> &grid){
    for (vector<char> row : grid) {
        for (char pixel : row) {
            cout << pixel;
        }
        cout << endl;
    }
}
// determines the valid neighbours
vector <pair<ll, ll>> neighbours(pair<ll, ll> coordinates, ll width, ll height) {
    ll row = coordinates.fi;
    ll col = coordinates.se;

    vector <pair<ll, ll>> returnvector;

    // determining the valid rows
    if (row > 0 && row < height - 1) {
        returnvector.push_back({row - 1, col});
        returnvector.push_back({row + 1, col});
    } else if (row == 0) {
        returnvector.push_back({row + 1, col});
    } else { // row == height - 1
        returnvector.push_back({row - 1, col});
    }

    if (col > 0 && col < width - 1) {
        returnvector.push_back({row, col + 1});
        returnvector.push_back({row, col - 1});
    } else if (col == 0) {
        returnvector.push_back({row, col + 1});
    } else {
        returnvector.push_back({row, col - 1});
    }

    return returnvector;
}

void solve(){
    ll height; ll width;
    cin >> height >> width;

    vector <vector<char>> grid(height, vector<char>(width, 0));
    vector <vector<bool>> grid_checked(height, vector<bool>(width, false));
    queue <pair<ll, ll>> holding_q;

    ll num_black = 0;

    queue<pair<ll, ll>> q; // stores coordinates {row, col}
    queue<pair<ll, ll>> next_q; // stores next generation's coordinates {row, col}


    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            char pixel;
            cin >> pixel;
            grid[row][col] = pixel;
            if (pixel == '#') {
                q.push({row,col});
                num_black++;
                grid_checked[row][col] = true;
            }
        }
    }

    // bfs
    ll iter = 0;
    while ((!next_q.empty()) || iter == 0) {
        if (iter == 1) {
            q = std::move(next_q);
        }
        iter = 1;

        while (!q.empty()) {
            pair <ll, ll> coords = q.front();
            q.pop(); 
            for (pair<ll, ll> neighbour : neighbours(coords, width, height)){
                int num_adj_black = 0;
                ll neighbour_row = neighbour.fi;
                ll neighbour_col = neighbour.se;
                
                // check for single adjacent black
                for (pair<ll, ll> adj : neighbours(neighbour, width, height)) {
                    ll adj_row = adj.fi;
                    ll adj_col = adj.se;
                    if (grid[adj_row][adj_col] == '#') {
                        num_adj_black += 1;
                    }
                }

                if (num_adj_black == 1 && !grid_checked[neighbour_row][neighbour_col]) {
                    grid_checked[neighbour_row][neighbour_col] = true;

                    holding_q.push({neighbour_row,neighbour_col});
                    next_q.push({neighbour_row,neighbour_col});

                    num_black++;
                }
            }

        }

        // updates the next generation of black cells
        while(!holding_q.empty()){
            pair<ll, ll> update_coords = holding_q.front();
            ll update_row = update_coords.fi;
            ll update_col = update_coords.se;
            grid[update_row][update_col] = '#';
            holding_q.pop();
        }
    }
    

    
    cout << num_black << endl;
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