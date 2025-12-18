#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <stack>
#include <utility>

#define ll long long
#define debug(x) std::cerr << #x << " = " << (x) << std::endl

using namespace std;

#define print_vec(v) do {for(const auto& val : (v)) std::cerr << val << " "; std::cerr << std::endl;} while (0);
#define print_pair(p) std::cerr << "(" << (p).first << ", " << (p).second << ")" << std::endl
#define print_mat(m) for(const auto& vec: m) print_vec(vec)

/* Custom printing statements*/
void print_set(set<ll> s){
    for (auto it=s.begin(); it != s.end(); ++it)     
        cerr << *it << " ";
    cerr << endl;
}

void print_map(map<ll, ll> m){
    for(auto it = m.begin(); it != m.end(); ++it){
        cerr << it->first << "->" << it->second;
        cerr << endl;
    }
    cerr << endl;
}

template<typename T>
void print_pq(T pq){
    cerr << "pq: ";
    while (!pq.empty()){
        ll top = pq.top();
        pq.pop();
        cerr << top << ", ";
    }
    cerr << endl;
}