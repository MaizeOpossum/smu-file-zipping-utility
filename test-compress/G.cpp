#include <bits/stdc++.h>
#include <unordered_set>
#define fi first
#define se second
#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;
// Write implementation prototypes Here
void solve(){
    ll num_skills;
    cin >> num_skills;

    ll num_skills_learned{};
    queue <ll> q;
    // [index = skill required] [value = skills learned]
    vector<vector<ll>> graph (num_skills + 1);
    vector<bool> skill_learned(num_skills + 1);

    for(ll i = 1; i < num_skills + 1; i++) {
        ll num_1; ll num_2;
        cin >> num_1 >> num_2;
        if (num_1 == 0 && num_2 == 0) {
            q.push(i);
            num_skills_learned++;
            continue;
        }

        graph[num_1].push_back(i);
        if (num_1 != num_2) {
            graph[num_2].push_back(i);
        }
    }

    while (!q.empty()) {
        ll skill = q.front();
        skill_learned[skill] = true;
        q.pop();
        for (ll skill_learnable : graph[skill]) {
            if (!skill_learned[skill_learnable]) {
                q.push(skill_learnable);
                skill_learned[skill_learnable] = true;
                num_skills_learned++;
            }
        }
    }

    cout << num_skills_learned << endl;
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