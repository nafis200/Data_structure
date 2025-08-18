//  3  n
//  3 2 1 array
// pair (1,1),(2,2),(3,1),(3,2),(3,3) is valid
// total = 5

// here pair is position of 3,2,1
// take an update array to store from 1 - 2 how many pair possiblr 2 - 3 how many pair possible

// p[w] % p[q] == 0

// 3, 2, 1
// P[3] = 1
// P[2] = 2
// P[1] = 3
// (3,3), (3,2), (3,1),(2,2),(1,1)

//  1 er left pashe koto gulo pair possible
//  2 and er left pashe koto gulo pair possible
//  3 and er left pashe kotogulo pair possible
// Sub Array

// sort

// (1,1)
// (2,2)
// (3,1),(3,2),(3,3)

// #include <bits/stdc++.h>
// using namespace std;
// const int N = 2e5 + 9;
// int a[N];
// int p[N];
// int updates[N];
// vector<int> pairs[N];
// vector<pair<int, int>> Q[N];
// int ans[N];
// int main()
// {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
//     int n;
//     cin >> n;
//     int q;
//     cin >> q;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> a[i];
//     }
//     memset(updates, 0, sizeof(updates));

//     for (int i = 1; i <= n; i++)
//     {
//         p[a[i]] = i;
//     }

//     for (int i = 1; i <= n; i++)
//     {
//         for (int j = i; j <= n; j += i)
//         {
//             // here j always divided by i
//             int l = min(p[i], p[j]);
//             int r = max(p[i], p[j]);
//             pairs[r].push_back(l);
//         }
//     }

//     for (int i = 1; i <= q; i++)
//     {
//         int l, r;
//         cin >> l >> r;
//         Q[r].push_back({l, i});
//     }

//     for (int r = 1; r <= n; r++)
//     {
//         for (auto it : pairs[r])
//         {
//             updates[it]++;
//         }
//         for (auto it : Q[r])
//         {
//             int sum = 0;
//             for (int i = it.first; i <= r; i++)
//             {
//                 sum += updates[i];
//             }
//             ans[it.second] = sum;
//         }
//     }

//     for (int i = 1; i <= q; i++)
//     {
//         cout << ans[i] << "\n";
//     }
// }


#include<bits/stdc++.h> 
using namespace std; 
const int N = 2e5 + 9; 
int a[N], pos[N]; 
vector<int>pairs[N]; 
vector<pair<int, int>> Q[N]; 
int cnt[N]; 
long long ans[N]; 
int s[N * 4]; 
void bulid_(int n, int b, int e){ 
     if(b == e) 
     { 
        s[n] = 0; 
        return; 
     } 
     int l = n * 2; 
     int r = n *2 + 1; 
     int mid = (b + e) / 2; 
     bulid_(l, b, mid); 
     bulid_(r, mid + 1, e); 
     s[n] = s[l] + s[r]; 
}  
int query(int n, int b, int e, int i, int j){ 
   if(b > j or e < i) 
   return 0; 
   if(b >= i and e <=j){ 
      return s[n]; 
   } 
   int l = n * 2; 
   int r = n * 2 + 1; 
   int mid = (b + e) / 2; 
   return query(l, b, mid, i, j) + query(r, mid+1, e, i, j); 
 
} 
void update_(int n, int b, int e, int i, int x){ 
   if(b > i or e < i) 
   return; 
   if(b == e){ 
      s[n] += x; 
      return; 
   } 
   int l = n * 2; 
   int r = n *2 + 1; 
   int mid = (b + e) / 2; 
   update_(l, b, mid ,i ,x); 
   update_(r, mid+1, e, i, x); 
   s[n] = s[l] + s[r]; 
} 
 
int main(){ 
   ios_base::sync_with_stdio(0); 
   cin.tie(0); 
   memset(cnt, 0, sizeof(cnt)); 
   int n, q; cin >> n >> q; 
   for(int i = 1; i <= n; i++){ 
      int x; cin >> x; 
      pos[x] = i; 
   } 
   for(int i = 1; i <= n; i++){ 
      for(int j = i; j <= n; j += i){ 
         int l = min(pos[i], pos[j]); 
         int r = max(pos[i], pos[j]); 
 
         pairs[r].push_back(l);  
      } 
   } 
 
   for(int i = 1; i <= q; i++){ 
      int l, r; cin >> l >> r; 
      Q[r].push_back({l, i}); 
   } 
   bulid_(1, 1, n); 
   for(int r = 1; r <= n; r++){ 
      for(auto l : pairs[r]){ 
          update_(1, 1, n, l, 1); 
      } 
   for(auto it : Q[r]){ 
      int sum = 0; 
      sum = query(1, 1, n, it.first, r); 
      ans[it.second] = sum;   
    } 
 
   } 
 
    for(int i = 1; i <= q; i++) 
    cout << ans[i] << "\n"; 
}