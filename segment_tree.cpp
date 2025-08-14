#include<bits/stdc++.h> 
using namespace std; 
const int N = 1e5+7; 
int a[N]; 
int s[N]; 
void bulid_(int n, int b, int e){ 
     if(b == e) 
     { 
        s[n] = a[b]; 
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
      cout << n << endl; 
      return s[n]; 
   } 
   int l = n * 2; 
   int r = n *2 + 1; 
   int mid = (b + e) / 2; 
   return query(l, b, mid, i, j) + query(r, mid+1, e, i, j); 
 
} 
void update_(int n, int b, int e, int i, int x){ 
   if(b > i or e < i) 
   return; 
   if(b == e and b == i){ 
      s[n] = x; 
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
   int n; cin >> n; 
   for(int i = 1; i <= n; i++) 
   cin >> a[i]; 
   bulid_(1,1,n); 
   for(int i = 1; i <= 2 * n - 1; i++) 
  cout << s[i] << "\n"; 
   update_(1,1,n,2,10); 
   cout << "after update" << "\n"; 
 
  for(int i = 1; i <= 2 * n - 1; i++) 
  cout << s[i] << "\n"; 
} 