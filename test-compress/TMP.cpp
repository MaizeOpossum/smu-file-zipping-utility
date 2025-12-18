#include <bits/stdc++.h>
#include <unordered_set>

#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;
void solve(){
    ll rating;
    cin >> rating;
    if (rating >= 1900) {
        cout << "Division 1\n";
        return;
    }
    if (rating >= 1600) {
        cout << "Division 2\n";
        return;
    }
    if (rating >= 1400) {
        cout << "Division 3\n";
        return;
    }

    cout << "Division 4\n";
    return;
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

    ll test_cases{};
    cin >> test_cases;
    for(int i = 0; i < test_cases; ++i){
        solve();
    }
    return 0;
}