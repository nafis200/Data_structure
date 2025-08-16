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



// segment tree

// #include<bits/stdc++.h> 
// using namespace std; 
// const int N = 5e4+9; 
// int a[N],Q[N]; 
// int b[N]; 
// long long s[N * 4]; 
// void build_(int n, int b, int e){ 
//      if(b == e) 
//      { 
//         s[n] = 0; 
//         return; 
//      } 
//      int l = n * 2; 
//      int r = n *2 + 1; 
//      int mid = (b + e) / 2; 
//      build_(l, b, mid); 
//      build_(r, mid + 1, e); 
//      s[n] = s[l] + s[r]; 
// }  
// void update_(int n, int b, int e, int i, int x){ 
//    if(b > i or e < i) 
//    return; 
//    if(b == e and b == i){ 
//       s[n] += x; 
//       return; 
//    } 
//    int l = n * 2; 
//    int r = n *2 + 1; 
//    int mid = (b + e) / 2; 
//    update_(l, b, mid ,i ,x); 
//    update_(r, mid+1, e, i, x); 
//    s[n] = s[l] + s[r]; 
// } 
// int query(int n, int b, int e, int i, int j){ 
//    if(b > j or e < i) 
//    return 0; 
//    if(b >= i and e <=j){ 
//       return s[n]; 
//    } 
//    int l = n * 2; 
//    int r = n *2 + 1; 
//    int mid = (b + e) / 2; 
//    return query(l, b, mid, i, j) + query(r, mid+1, e, i, j); 
 
// } 
// int main(){ 
//     int t; cin >> t; 
//     int cs = 0; 
//     while(t--){ 
//         int n, q; cin >> n >> q; 
//         set<int>st; 
//         cout << "Case" << " " << ++cs << ":" << "\n"; 
//         for(int i = 1; i<=n; i++){ 
//              cin >> a[i] >> b[i]; 
//              st.insert(a[i]); 
//              st.insert(b[i]); 
//         } 
//         for(int i = 1; i <= q; i++){ 
//              cin >> Q[i]; 
//              st.insert(Q[i]); 
//         } 
//         int ind = 0; 
//         map<int,int>mp; 
//         for(auto it : st){ 
//           mp[it] = ++ind; 
//         } 
//         for(int i = 1; i <= n; i++){ 
//           a[i] = mp[a[i]]; 
//           b[i] = mp[b[i]]; 
//         } 
//         for(int i = 1; i <=q; i++){ 
//          Q[i] = mp[Q[i]]; 
//         } 
//         build_(1,1,ind); 
//         for(int i =1; i <=n; i++){ 
//           int l =a[i], r = b[i]; 
//           update_(1,1,ind,l,+1); 
//           if(r+1 <= ind){ 
//              update_(1,1,ind,r+1,-1); 
//           } 
//         } 
         
//         for(int i = 1; i <= q; i++) 
//         { 
//           int ans= 0; 
//           int x = Q[i]; 
//           ans = query(1,1,ind,1,x); 
//           cout << ans << "\n"; 
//         }     
 
//      } 
// } 