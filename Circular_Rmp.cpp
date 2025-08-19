#include<bits/stdc++.h>
using namespace std;
const int N = 2e5+9;
const long long INF = 1e14+9;
int a[N];
long long s[N * 4];
long long lazy[N * 4];
void build(int n,int b, int e){
    lazy[n] = 0;
    if(b == e){
        s[n] = a[b];
        return;
    }
    int l = n * 2;
    int r = n *2 + 1;
    int mid = (b + e) /  2;
    build(l, b, mid);  
    build(r, mid+1, e);
    s[n] = min(s[l],s[r]);

}
void push(int n, int b, int e){
    if(lazy[n] == 0)
    return;
    s[n] = s[n] + lazy[n]; 
    if(b != e){
        lazy[n * 2] = lazy[n * 2] + lazy[n];
        lazy[n *2 + 1] = lazy[n * 2 + 1] + lazy[n];
    }
    lazy[n] = 0;
}
void upd_(int n, int b, int e, int i, int j, int v){
    push(n, b, e);
    if(b > j or e < i)
    return;
    if(b >= i and e <= j){
        lazy[n] = v;
        push(n, b, e);
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) /  2;
    upd_(l, b, mid, i, j, v);
    upd_(r, mid+1, e, i, j, v);
    s[n] = min(s[l] , s[r]);
    
}
long long query(int n, int b, int e, int i, int j){
     push(n, b, e);
     if(b > j or e < i)
     return INF;
     if(b >= i and e <= j)
     return s[n];
     int l = n * 2;
     int r = n * 2 + 1;
     int mid = (b + e) / 2;
     return min(query(l, b, mid, i, j), query(r,mid+1,e,i,j));

}
int main(){
    ios_base:: sync_with_stdio(0);
    cin.tie(0);
    int n, q; cin >> n;
    for(int i = 1; i <= n; i++)
    cin >> a[i];
    build(1, 1, n);
    cin >> q;
    cin.ignore();
    while(q--){
        string line;
        getline(cin, line);
        stringstream ss(line);
        int l , r , v;
        ss >> l >> r;
        ++l, ++r;
        if(ss >> v){
            if(l <= r){
               upd_(1, 1, n, l, r, v);
            }
            else{
               upd_(1, 1, n, l, n, v);
               upd_(1, 1, n, 1, r, v);
            }
        } 
        else{
          long long ans = INF;
          if(l <= r){
            ans = query(1, 1, n, l, r);
          }
          else{
             ans = query(1, 1, n, l, n);
             ans = min(ans, query(1, 1, n, 1, r));
          }
           cout << ans << "\n";
        }
    }
}