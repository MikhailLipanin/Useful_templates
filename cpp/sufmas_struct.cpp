struct sufmas{
    int n;
    vector <int> p;
    vector <int> c;
    string s;
    sufmas(string &t){
        s = t;
        s += "$";
        n = s.size();
        p.resize(n);
        c.resize(n);
        build();
    }
    void count_sort(){
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
    void build(){
        vector <pair <char, int>> ar;
        for (int i = 0; i < n; i++){
            ar.pb({s[i], i});
        }
        sort(all(ar));
        for (int i = 0; i < n; i++){
            p[i] = ar[i].second;
        }
        c[p[0]] = 0;
        for (int i = 1; i < n; i++){
            if (ar[i].first == ar[i - 1].first)
                c[p[i]] = c[p[i - 1]];
            else
                c[p[i]] = c[p[i - 1]] + 1;
        }

        int k = 0;
        while ((1 << k) < n){
            for (int i = 0; i < n; i++){
                p[i] = (p[i] - (1 << k) + n) % n;
            }
            count_sort();
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
    }
    void out(){
        for (int i = 0; i < n; i++){
            cout << p[i] << ' ';
        }
        cout << '\n';
    }
};
