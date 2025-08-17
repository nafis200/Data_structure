// #include <bits/stdc++.h>
// using namespace std;
// const int N = 131072 + 5;
// int a[N], t[N * 4];

// void pull(int n, int b, int e, int cnt)
// {
//     if (cnt == 1)
//     {

//         t[n] = t[b] | t[e];
//     }
//     else
//     {
//         t[n] = t[b] ^ t[e];
//     }
// }

// void build(int n, int b, int e, int cnt)
// {
//     if (b == e)
//     {
//         t[n] = a[b];
//         return;
//     }
//     int l = n * 2;
//     int r = n * 2 + 1;
//     int mid = (b + e) / 2;
//     build(l, b, mid, (cnt + 1) % 2);
//     build(r, mid + 1, e, (cnt + 1) % 2);
//     pull(n, l, r, cnt);
// }

// void update(int n, int b, int e, int i, int v, int cnt)
// {
//     if (b > i or e < i)
//     {
//         return;
//     }
//     if (b == e and b == i)
//     {
//         t[n] = v;
//         return;
//     }
//     int l = n * 2;
//     int r = n * 2 + 1;
//     int mid = (b + e) / 2;
//     update(l, b, mid, i, v, (cnt + 1) % 2);
//     update(r, mid + 1, e, i, v, (cnt + 1) % 2);
//     pull(n, l, r, cnt);
// }

// int query(int n, int b, int e, int i, int j)
// {
//     if (b > j or e < i)
//     {
//         return 0;
//     }
//     if (b >= i and e <= j)
//     {
//         return t[n];
//     }
//     int l = n * 2;
//     int r = n * 2 + 1;
//     int mid = (b + e) / 2;
//     int left = query(l, b, mid, i, j);
//     int right = query(r, mid + 1, e, i, j);
//     return left + right;
// }

// int main()
// {
//     ios::sync_with_stdio(false);
//     cin.tie(0);
//     int n, q;
//     cin >> n >> q;
//     n = pow(2, n);
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> a[i];
//     }
//     build(1, 1, n, 0);
//     while (q--)
//     {
//         int i, v;
//         cin >> i >> v;
//         update(1, 1, n, i, v, 0);
//         // cout << query(1, 1, n, 1, n) << "\n";
//            cout << t[1] << "\n"; 
//     }
// }



// right approch


#include<bits/stdc++.h>
using namespace std;
const int N = (1 << 17) + 2;
vector<int>a(N,0);
vector<long long>s(4 * N,0);
int merge(int ans_l, int ans_r, int b, int e){
        int len = e - b + 1;
        int sg = __lg(len);
        if(sg % 2){
           return (ans_l | ans_r);
        }
        return(ans_l ^ ans_r);
}
void build(int n,int b, int e){
    if(b == e){
        s[n] = a[b];
        return;
    }
    int l = n * 2;
    int r = n *2 + 1;
    int mid = (b + e) /  2;
    build(l, b, mid);  
    build(r, mid+1, e);
    s[n] = merge(s[l],s[r],b, e);
    return;
}
void update(int n, int b, int e, int i, int j){
    if(i < b or e < i)
    return;
    if(b == e){
        s[n] = j;
        return;
    }
    int mid = (b + e) / 2;
    int l = n * 2;
    int r = n * 2 + 1;
    update(l, b, mid, i, j);
    update(r, mid + 1, e, i, j);
    s[n] = merge(s[l],s[r],b,e);
 
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m; cin >> n >> m;
    n = (1 << n);
    for(int i = 1; i <= n; i++)
    cin >> a[i];
    build(1, 1, n);
    while(m--){
        int i, j; cin >> i >> j;
        update(1, 1, n, i, j);
        cout << s[1] << "\n";
    }
}