#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template<typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define F first
#define S second
#define pb push_back
#define pii pair <int, int>
#define all(a) (a).begin(), (a).end()
#define rall(a) (a).rbegin(), (a).rend()
#define reunique(a) (a).resize(unique(all(a)) - (a).begin())
#define ld long double
#define int long long

void count_sort(vector <int> &p, vector <int> &c){
    int n = p.size();
    vector <int> cnt(n);
    for (auto now : c){
        cnt[now]++;
    }
    vector <int> np(n);
    vector <int> pos(n);
    for (int i = 1; i < n; i++){
        pos[i] = pos[i - 1] + cnt[i - 1];
    }
    for (auto now : p){
        int x = c[now];
        np[pos[x]] = now;
        pos[x]++;
    }
    p = np;
}

void SOLVE(){
    string s;
    cin >> s;
    s += "$";
    int n = s.size();
    vector <int> p(n);
    vector <int> c(n);

    vector <pair <char, int>> a(n);
    for (int i = 0; i < n; i++){
        a[i] = {s[i], i};
    }
    sort(all(a));
    for (int i = 0; i < n; i++){
        p[i] = a[i].second;
    }
    c[p[0]] = 0;
    for (int i = 1; i < n; i++){
        if (a[i].first == a[i - 1].first)
            c[p[i]] = c[p[i - 1]];
        else
            c[p[i]] = c[p[i - 1]] + 1;
    }

    int k = 0;
    while ((1 << k) < n){
        for (int i = 0; i < n; i++){
            p[i] = (p[i] - (1 << k) + n) % n;
        }
        count_sort(p, c);

        vector <int> nc(n);
        nc[p[0]] = 0;
        for (int i = 1; i < n; i++){
            pii now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
            pii was = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
            if (now == was)
                nc[p[i]] = nc[p[i - 1]];
            else
                nc[p[i]] = nc[p[i - 1]] + 1;
        }
        c = nc;
        k++;
    }
    for (int i = 0; i < n; i++){
        cout << p[i] << ' ';
    }
    cout << '\n';

    vector <int> lcp(n);
    k = 0;
    for (int i = 0; i < n - 1; i++){
        int pi = c[i];
        int j = p[pi - 1];
        while (s[i + k] == s[j + k]) k++;
        lcp[pi] = k;
        k = max(0LL, k - 1);
    }
    for (int i = 1; i < n; i++){
        cout << lcp[i] << ' ';
    }
    cout << '\n';
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(12);
    int Q = 1;
    //cin >> Q;
    while (Q--){
        SOLVE();
    }

    return 0;
}
