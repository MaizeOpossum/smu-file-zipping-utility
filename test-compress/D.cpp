#include <bits/stdc++.h>

#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;
/*NOTES
    . Empty cell
    # Obstacle cell
    S Start cell
    G Goal cell
    o open door cell
    x closed door cell
    ? switch cell

Psudocode:
    BFS to find path
    eliminate parity (if at the same coordinate at the same door cycle, redundant)
    eliminate dead ends
    if no more paths = -1
    if reach goal = num ops
    coords must be a tuple to store the parity case (2 - true/false)
        {row, col, parity} - parity will be 1 or -1
*/

// checks if the cell is a switch
bool is_goal(ll row,
               ll col,
               vector<vector<char>> &maze) {
    if (maze[row][col] == 'G')
        return true;
    return false;
}


bool is_switch(ll row,
               ll col,
               vector<vector<char>> &maze) {
    if (maze[row][col] == '?')
        return true;
    return false;
}

// checks if the cell is valid
bool is_valid(ll row,
              ll col,
              ll parity,
              ll width,
              ll height,
              vector<vector<char>> &maze) {
    if (parity == 1) {
        // x = closed, o = open
        // bounds check
        if (row < 0 || col < 0 || row > height - 1 || col > width - 1) {
            return false;
        }
        // pixel check
        char pixel = maze[row][col];
        if (pixel == 'x' || pixel == '#') {
            return false;
        }
        return true;
    }
    if (parity == -1) {
        // x = open, o = closed
        if (row < 0 || col < 0 || row > height - 1 || col > width - 1) {
            return false;
        }
        // pixel check
        char pixel = maze[row][col];
        if (pixel == 'o' || pixel == '#') {
            return false;
        }
        return true;
    }
    cerr << "Error Is_Valid" << endl;
    return false;
}

// returns a list of valid neighbours, handles parity
vector<tuple<ll, ll, ll>> neighbours(tuple<ll, ll, ll> coords,
                                     vector<vector<bool>> &parity_1_visited,
                                     vector<vector<bool>> &parity_2_visited,
                                     vector<vector<char>> &maze,
                                     ll width,
                                     ll height) {
    vector<tuple<ll, ll, ll>> valid_coords;
    vector<ll> x = {1, -1};
    vector<ll> y = {1, -1};
    ll c_row = get<0>(coords);
    ll c_col = get<1>(coords);
    ll c_parity = get<2>(coords);

    for (ll i : x) {
        ll row = c_row;
        ll col = c_col + i;
        ll parity = c_parity;

        if (!is_valid(row, col, parity, width, height, maze)) {
            continue;
        }

        ll next_parity = parity;
        if (is_switch(row, col, maze)) {
            next_parity = -parity;
        }

        if (next_parity == 1) {
            if (!parity_1_visited[row][col]) {
                parity_1_visited[row][col] = true;
                valid_coords.push_back({row, col, next_parity});
            }
        } else {
            if (!parity_2_visited[row][col]) {
                parity_2_visited[row][col] = true;
                valid_coords.push_back({row, col, next_parity});
            }
        }
    }

    for (ll j : y) {
        ll row = c_row + j;
        ll col = c_col;
        ll parity = c_parity;
        
        if (!is_valid(row, col, parity, width, height, maze)) {
            continue;
        }

        ll next_parity = parity;
        if (is_switch(row, col, maze)) {
            next_parity = -parity;
        }
        
        if (next_parity == 1) {
            if (!parity_1_visited[row][col]) {
                parity_1_visited[row][col] = true;
                valid_coords.push_back({row, col, next_parity});
            }
        } else {
            if (!parity_2_visited[row][col]) {
                parity_2_visited[row][col] = true;
                valid_coords.push_back({row, col, next_parity});
            }
        }
    }
    
    return valid_coords;
}

ll bfs(vector<vector<ll>> &distance ,vector<vector<char>> &maze, queue<tuple<ll, ll, ll>> &q, ll width, ll height) {
    // returns -1 if no solution, smallest num of steps otherwise
    vector<vector<bool>> parity_1_visited(height, vector<bool>(width, false));
    vector<vector<bool>> parity_2_visited(height, vector<bool>(width, false));
    
    tuple<ll, ll, ll> start = q.front();
    
    ll row = get<0> (start);
    ll col = get<1> (start);

    parity_1_visited[row][col] = true;

    while (!q.empty()) {
        tuple<ll, ll, ll> coords = q.front();
        q.pop();
        ll c_row = get<0> (coords);
        ll c_col = get<1> (coords);

        for (tuple<ll, ll, ll> neighbour : neighbours(coords, parity_1_visited, parity_2_visited, maze, width, height)) {
            ll n_row = get<0> (neighbour);
            ll n_col = get<1> (neighbour);

            q.push(neighbour);
            distance[n_row][n_col] = distance[c_row][c_col] + 1;

            if (is_goal(n_row, n_col, maze)) {
                return distance[n_row][n_col];
            }
        }
    }
    return -1;
}

void solve() {
    ll height;
    ll width;
    cin >> height >> width;

    vector<vector<char>> maze(height, vector<char>(width, '.'));
    vector<vector<ll>> distance(height, vector<ll>(width, 0));
    queue<tuple<ll, ll, ll>> q;

    for (ll row = 0; row < height; row++) { // maze initialisation
        for (ll col = 0; col < width; col++) {
            char pixel;
            cin >> pixel;
            maze[row][col] = pixel;
            if (pixel == 'S')
                q.push({row, col, 1});
        }
    }

    ll result = bfs(distance, maze, q, width, height);

    cout << result << endl;
}

// Driver code
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    if (fopen("test.inp", "r") != NULL) {
        freopen("test.inp", "r", stdin);
        freopen("test.out", "w", stdout);
        freopen("test.err", "w", stderr);
    }

    ll test_cases = 1;
    for (int i = 0; i < test_cases; ++i) {
        solve();
    }
    return 0;
}