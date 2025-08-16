#include<bits/stdc++.h> 
using namespace std; 
const int N = 1e5+9; 
const int mod = 1e9 + 7; 
struct node{ 
    int oc[3]; 
}; 
node s[N * 4]; 
int lazy[N * 4]; 
node merge(node l, node r){ 
    node ans; 
    for(int i = 0; i < 3; i++) 
    ans.oc[i] = l.oc[i] + r.oc[i]; 
    return ans; 
} 
void build(int n,int b, int e){ 
    lazy[n] = 0; 
    if(b == e){ 
        s[n].oc[0] = 1; 
        s[n].oc[1] = 0; 
        s[n].oc[2] = 0; 
        return; 
    } 
    int l = n * 2; 
    int r = n *2 + 1; 
    int mid = (b + e) /  2; 
    build(l, b, mid);   
    build(r, mid+1, e); 
    s[n] = merge(s[l],s[r]); 
 
} 
void push(int n, int b, int e){ 
    if(lazy[n] == 0) 
    return; 
    node cur = s[n]; 
    for(int i = 0; i < 3; i++) 
    s[n].oc[(i + lazy[n])%3] = cur.oc[i]; 
 
    if(b != e){ 
        lazy[n * 2] = (lazy[n * 2] + lazy[n]) % 3; 
        lazy[n *2 + 1] =  (lazy[n * 2 + 1] + lazy[n]) % 3; 
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
    s[n] = merge(s[l],s[r]); 
     
} 
int query(int n, int b, int e, int i, int j){ 
     push(n, b, e); 
     if(b > j or e < i) 
     return 0; 
     if(b >= i and e <= j) 
     return s[n].oc[0]; 
     int l = n * 2; 
     int r = n * 2 + 1; 
     int mid = (b + e) / 2; 
     return (query(l, b, mid, i, j) + query(r, mid+1, e, i, j)); 
} 
int main(){ 
    int t; cin >> t; 
    int cs = 0; 
    while(t--){ 
    int n, q; cin >> n >> q; 
    build(1, 0, n-1); 
    cout << "Case " << ++cs << ":" << "\n"; 
    while(q--){ 
        int k; cin >> k; 
        if(k == 0){ 
            int i, j, v; 
            cin >> i >> j; 
             upd_(1, 0, n-1, i, j, 1); 
        } 
        else{ 
            int l, r; cin >> l >> r; 
            cout << query(1, 0, n-1, l, r) << "\n"; 
        } 
    } 
    } 
}