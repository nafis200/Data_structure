#include<bits/stdc++.h> 
using namespace std; 
const int N = 1e5+9; 
struct node{ 
    int ones,zeroes; 
}; 
string a;  
node s[N * 4]; 
bool lazy[N * 4]; 
node merge(node l, node r){ 
    node ans; 
    ans.ones = l.ones + r.ones; 
    ans.zeroes = l.zeroes + r.zeroes; 
    return ans; 
} 
void build(int n,int b, int e){ 
    lazy[n] = false; 
    if(b == e){ 
        s[n].ones = s[n].zeroes = 0; 
        if(a[b] =='1') 
        s[n].ones = 1; 
        else 
        s[n].zeroes = 1; 
        return; 
    } 
    int l = n * 2; 
    int r = n *2 + 1; 
    int mid = (b + e) /  2; 
    build(l, b, mid); 
    build(r, mid+1, e); 
    s[n] = merge(s[l] , s[r]); 
 
} 
void push(int n, int b, int e){ 
    if(lazy[n] == false) 
    return; 
    swap(s[n].ones,s[n].zeroes); 
    if(b != e){ 
        int l = n * 2; 
        int r = n * 2 + 1; 
        lazy[l] ^= true; 
        lazy[r] ^= true; 
    } 
    lazy[n] = false; 
     
} 
void upd_(int n, int b, int e, int i, int j){ 
    push(n, b, e); 
    if(b > j or e < i) 
    return; 
    if(b >= i and e <= j){ 
        lazy[n] = true; 
        return; 
    } 
    int l = n * 2; 
    int r = n * 2 + 1; 
    int mid = (b + e) /  2;  
    upd_(l, b, mid, i, j); 
    upd_(r, mid+1, e, i, j); 
    s[n] = merge(s[l], s[r]); 
     
} 
node query(int n, int b, int e, int i, int j){ 
     push(n,b,e); 
     if(b > j or e < i) 
     return {0,0}; 
     if(b >= i and e <= j) 
     return s[n]; 
     int l = n * 2; 
     int r = n * 2 + 1; 
     int mid = (b + e) / 2; 
     return merge(query(l, b, mid, i, j) , query(r, mid+1, e, i, j)); 
 
} 
int main(){ 
   int t; cin >> t; int cs = 0; 
   while(t--){ 
    cin >> a; 
    int n = a.size(); 
    n--; 
    build(1,0,n); 
    int q; cin >> q; 
    cout << "Case " << ++cs << ":" << "\n"; 
    while(q--){ 
        char ty; cin >> ty; 
        if(ty == 'I'){ 
            int l, r; cin >> l >> r; 
            l--,r--; 
            upd_(1, 0, n, l, r); 
        } 
        else{ 
            int i; cin >> i; 
            i--; 
            node ans = query(1, 0, n, i, i); 
            if(ans.ones) 
            cout << 1 << "\n"; 
            else 
            cout << 0 << "\n";       
             } 
    } 
   } 
} 