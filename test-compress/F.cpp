#include <bits/stdc++.h>
#include <unordered_set>
#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;
// Write implementation prototypes Here
bool valid(vector<vector<char>> &maze, pair<ll,ll> coords, ll height, ll width) {
    ll row = coords.fi;
    ll col = coords.se;
    // boundary check
    if (row < 0 || row > height - 1 || col < 0 || col > width - 1) {
        return false;
    }
    // wall check
    if (maze[row][col] == '#') {
        return false;
    }
    return true;
}


vector<pair<ll,ll>> adjacent(pair<ll,ll> coords, vector<vector<char>> &maze, ll height, ll width){
    vector<pair<ll,ll>> returnval;
    ll row = coords.fi;
    ll col = coords.se;

    if (valid(maze, {row, col + 1}, height, width)) {
        returnval.push_back({row, col + 1});
    }
    if (valid(maze, {row, col - 1}, height, width)) {
        returnval.push_back({row, col - 1});
    }
    if (valid(maze, {row + 1, col}, height, width)) {
        returnval.push_back({row + 1, col});
    }
    if (valid(maze ,{row - 1, col}, height, width)) {
        returnval.push_back({row - 1, col});
    }
    
    return returnval;
}

void print_grid(vector <vector<char>> &grid){
    for (vector<char> row : grid) {
        for (char pixel : row) {
            cout << pixel;
        }
        cout << endl;
    }
}

ll bfs(pair<ll, ll> starting_coords,
        vector<vector<char>> &maze,
        vector<vector<pair<ll, ll>>> &distance,
        vector<vector<ll>> &distance_i,
        vector<vector<bool>> &checked,
        ll height,
        ll width) {
    queue<pair<ll,ll>> q;
    q.push(starting_coords);
    
    ll max_distance = 0;
    while (!q.empty()) {
        pair<ll,ll> coords = q.front();
        ll row = coords.fi;
        ll col = coords.se;
        checked[row][col] = true;
        q.pop();

        for (pair<ll,ll> neighbour_coords : adjacent(coords, maze, height, width)) {
            ll n_row = neighbour_coords.fi;
            ll n_col = neighbour_coords.se;
            if (!checked[n_row][n_col]) {
                q.push(neighbour_coords);
                checked[n_row][n_col] = true;
                distance_i[n_row][n_col] = distance_i[row][col] + 1;
                distance[distance_i[n_row][n_col]].push_back(neighbour_coords); 
                
                if (max_distance < distance_i[n_row][n_col]) {
                    max_distance = distance_i[n_row][n_col];
                }
            }
        }
    }

    return max_distance;
}


void solve(){
    ll height; ll width; ll target;
    cin >> height >> width >> target;

    vector <vector<char>> maze(height, vector <char> (width, 0));
    // vector storing distances of each point away from a starting point
    // [distance] [pairs of coordinates]
    vector<vector<pair<ll, ll>>> distance(height * width + 1);
    vector<vector<bool>> checked(height, vector <bool> (width, false));
    // index of the distance from the starting integer
    vector<vector<ll>> distance_i(height, vector <ll> (width, 0));



    // defining maze 
    int iter = 0;
    pair <ll, ll> starting_coords;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            char pixel;
            cin >> pixel;
            maze[row][col] = pixel;
            if (pixel == '.' && iter == 0) {
                iter = 1;
                starting_coords = {row, col};
            }
        }
    }

    // bfs to number each coordinate with distance from a starting point
    ll max_distance = bfs(starting_coords, maze, distance, distance_i, checked, height, width);

    ll i = 0;
    while(i < target) {
        if (!distance[max_distance].empty()) {
            ll row = distance[max_distance][0].fi;
            ll col = distance[max_distance][0].se;
            maze[row][col] = 'X';
            distance[max_distance].erase(distance[max_distance].begin());
            i++;
        } else {
            max_distance--;
        }
    }

    print_grid(maze);
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
    for(int i = 0; i < test_cases; ++i){
        solve();
    }
    return 0;
}