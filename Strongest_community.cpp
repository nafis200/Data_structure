#include<bits/stdc++.h> 
using namespace std; 
const int N = 1e5+7, inf = 1e9+9; 
int a[N]; 
struct node{ 
    int first_element, first_occ; 
    int last_element, last_occ; 
    int community; 
}; 
node s[N*4]; 
node merge(node l, node r){ 
    node ans; 
    ans.first_element = l.first_element; 
    ans.first_occ = l.first_occ; 
    if(l.first_element == r.first_element){ 
        ans.first_occ += r.first_occ; 
    } 
    ans.last_element = r.last_element; 
    ans.last_occ = r.last_occ; 
    if(r.last_element == l.last_element){ 
        ans.last_occ += l.last_occ; 
    } 
    ans.community = max(l.community, r.community); 
    if(l.last_element == r.first_element){ 
     ans.community = max(ans.community, l.last_occ + r.first_occ); 
    } 
    return ans; 
} 
void build(int n, int b, int e){ 
    if(b == e){ 
        s[n].first_element = s[n].last_element = a[b]; 
        s[n].first_occ = s[n].last_occ = 1; 
        s[n].community = 1; 
        return; 
    } 
    int l = n * 2; 
    int r = n *2 + 1; 
    int mid = (b + e) / 2; 
    build(l, b, mid); 
    build(r, mid+1, e); 
    s[n] = merge(s[l],s[r]); 
} 
node query(int n, int b, int e, int i, int j){ 
    if(b > j or e < i) 
    return {-1,-1,-1,-1,-1}; 
    if(b >= i and e <= j) 
    return s[n]; 
    int l = n * 2; 
    int r = n *2 + 1; 
    int mid = (b + e) / 2; 
    return merge(query(l, b, mid, i, j), query(r, mid+1, e, i, j)); 
 
} 
int main(){ 
        int t, cs = 0; cin >> t; 
        while(t--){ 
            int n, c, q; cin >> n >> c >> q; 
            for(int i=1; i <=n; i++){ 
                cin >> a[i]; 
            } 
            build(1,1,n); 
            cout << "Case " << ++cs <<":" << "\n"; 
            while(q--){ 
                int l, r; cin >> l >> r; 
                node ans = query(1, 1, n, l, r); 
                cout << ans.community << "\n"; 
            } 
        } 
}