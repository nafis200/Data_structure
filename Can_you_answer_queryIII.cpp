// total sum = left_sum + right_sum
// left_prefix = max(left_prefix, left_total + right_prefix)

// left_suffix = max(right_suffix, right_total + left_suffix)

//  max_sum = max(left max_sum, right max_sum, left_suffix + right_prefix)

#include<bits/stdc++.h> 
using namespace std; 
const int N = 1e5+9; 
const int mod = 1e9 + 7; 


struct node{ 
    long long sum, pref, suff, ans; 
}; 

node s[N * 4]; 
int lazy[N * 4]; 
long long a[N];  

node make_leaf(long long v){
    return node{v, v, v, v};
}

node merge(node L, node R){ 
    node res; 
    res.sum  = L.sum + R.sum;
    res.pref = max(L.pref, L.sum + R.pref);
    res.suff = max(R.suff, R.sum + L.suff);
    res.ans  = max({L.ans, R.ans, L.suff + R.pref});
    return res; 
} 

void build(int n,int b, int e){ 
    lazy[n] = 0; 
    if(b == e){ 
        s[n] = make_leaf(a[b]);
        return; 
    } 
    int l = n * 2; 
    int r = n * 2 + 1; 
    int mid = (b + e) /  2; 
    build(l, b, mid);   
    build(r, mid+1, e); 
    s[n] = merge(s[l],s[r]); 
} 


void upd_(int n, int b, int e, int i, int j, long long v){ 
    if(b > j || e < i) return; 
    if(b == e){ 
        s[n] = make_leaf(v);
        return; 
    } 
    int l = n * 2; 
    int r = n * 2 + 1; 
    int mid = (b + e) /  2; 
    upd_(l, b, mid, i, j, v); 
    upd_(r, mid+1, e, i, j, v); 
    s[n] = merge(s[l],s[r]); 
} 


node query_node(int n, int b, int e, int i, int j){ 
     if(b > j || e < i){ 
         const long long INF = (long long)4e18;
         return node{0, -INF, -INF, -INF};
     }
     if(b >= i && e <= j) return s[n]; 
     int l = n * 2; 
     int r = n * 2 + 1; 
     int mid = (b + e) / 2; 
     node left  = query_node(l, b, mid, i, j);
     node right = query_node(r, mid+1, e, i, j);
     if(left.ans  == (long long)-4e18) return right;
     if(right.ans == (long long)-4e18) return left;
     return merge(left, right); 
} 

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    if(!(cin >> n)) return 0;
    for(int i = 1; i <= n; i++) cin >> a[i];

    build(1, 1, n); 

    int m; 
    cin >> m; 
    while(m--){ 
        int t, x, y; 
        cin >> t >> x >> y; 
        if(t == 0){ 
            upd_(1, 1, n, x, x, y); 
        } 
        else{ 
            node res = query_node(1, 1, n, x, y);
            cout << res.ans << "\n"; 
        } 
    } 
    return 0;
}
