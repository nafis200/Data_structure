#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, q;
    set<int>st;
    cin >> n >> q;
    int a[n],b[n],c[q];
    for(int i = 0; i < n; i++){
        cin >> a[i] >> b[i];
        st.insert(a[i]);
        st.insert(b[i]);
    }
    for(int i = 0; i < q; i++){
        cin >> c[i];
        st.insert(c[i]);
    }

    map<int,int>mp;
    int x = 1;
    int mx = 0;
    for(auto it : st){
        mp[it] = x;
        ++x;
        mx = max(mx,it);
    }

    for(int i = 0; i < n; i++){
        a[i] = mp[a[i]];
        b[i] = mp[b[i]];
    }
    for(int i = 0; i < q; i++){
        c[i] = mp[c[i]];
    }

    for(int i = 0; i < n; i++){
        cout << a[i] << " " << b[i] << "\n";
    }

    int p[mx + 1] = {0};

    for(int i = 0; i < n; i++){
        p[a[i]] += 1;
        p[b[i] + 1] -= 1;
    }

    for(int i = 1; i <= mx; i++){
        p[i] = p[i - 1] + p[i];
    }

    for(int i = 0; i < q; i++){
        cout << p[c[i]] << "\n";
    }

    
}