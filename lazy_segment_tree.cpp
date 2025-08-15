#include<bits/stdc++.h> 
using namespace std; 
const int N = 1e5 + 7; 
int a[N]; 
int t[4 * N],lazy[4 * N]; 
 
void push(int n, int b, int e){ 
   if(lazy[n] == 0) 
   return; 
   t[n] = t[n] + lazy[n] * (e - b + 1); 
   if(b != e){ 
      int l = n *2; 
      int r = n *2 + 1; 
      lazy[l] = lazy[l] + lazy[n]; 
      lazy[r] = lazy[r] + lazy[n];  
   } 
   lazy[n] = 0; 
} 
void pull(int n, int l, int r){ 
   t[n] = t[l] + t[r]; 
} 
 
void bulid(int n, int b, int e){ 
   lazy[n] = 0; 
   if(b == e){ 
      t[n] = a[b]; 
      return; 
   } 
   int l = n * 2; 
   int r = n * 2 + 1; 
   int mid = (b + e) / 2; 
   bulid(l, b, mid); 
   bulid(r, mid+1, e); 
   pull(n, l, r); 
} 
void upd(int n, int b, int e, int i, int j, int v){ 
   push(n,b,e); 
   if(j < b or e < i) 
   return; 
   if(i <= b and e <= j){ 
      lazy[n] = v; 
      push(n, b, e); 
      return; 
   } 
   int l = n * 2; 
   int r = n *2 + 1; 
   int mid = (b + e) / 2; 
   upd(l, b, mid, i, j, v); 
   upd(r, mid + 1, e, i, j, v); 
   pull(n, l, r); 
} 
int query(int n, int b, int e, int i, int j){ 
   push(n,b,e); 
   if(b > j or e < i) 
   return 0; 
   if(b >= i and e <= j) 
   return t[n]; 
   int l = n * 2; 
   int r = n *2 + 1; 
   int mid = (b + e) / 2; 
   return (query(l, b, mid, i, j) + query(r, mid+1, e, i, j)); 
} 
 
int main() 
{ 
   int n = 4; 
   for(int i = 1; i <= n; i++) 
   a[i] = i; 
   bulid(1,1,n); 
   cout << query(1,1,n,2,3) << "\n"; 
   upd(1,1,n,2,3,2); 
   cout << " after update" << "\n"; 
   cout << query(1,1,n,2,3) << "\n"; 
     upd(1,1,n,2,3,4); 
   cout << " after update" << "\n"; 
   cout << query(1,1,n,2,3) << "\n"; 
     upd(1,1,n,2,3,4); 
      cout << " after update" << "\n"; 
   cout << query(1,1,n,2,3) << "\n"; 
   for(int i = 1; i <= 2 * n; i++) 
   cout << t[i] << " "; 
}