// #include<bits/stdc++.h>
// using namespace std;
// int main(){
//     //  2  -3  4
//     // 1 base index
//     int n;
//     cin >> n;
//     int a[n + 1];
//     for(int i = 1; i <= n; i++){
//         cin >> a[i];
//     }
//     int l, r;
//     cin >> l >> r;

//     int mx = INT_MIN;
//     for(int i = l; i <= r; i++){
//          int sum = 0;
//          for(int j = i; j <= r; j++){
//               sum += a[j];
//               mx = max(mx, sum);

//          }
//     }
//     cout << mx << "\n";
// }

// range query not work prefix sum or kaddone algorithm

// #include <bits/stdc++.h>
// using namespace std;
// int main()
// {
//     //  2  -3  4
//     // 1 base index
//     int n;
//     cin >> n;
//     int a[n + 1];
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> a[i];
//     }

//     int prefix[n + 1] = {0};

//     int mx = INT_MIN;

//     for (int i = 1; i <= n; i++)
//     {
//         if (a[i] > 0)
//         {
//             prefix[i] = prefix[i - 1] + a[i];
//         }
//         else
//         {
//             prefix[i] = 0;
//         }
//     }
//     for (int i = 1; i <= n; i++)
//     {
//         mx = max(prefix[i], mx);
//     }
//     int q;
//     cin >> q;
//     while (q--)
//     {
//         int l, r;
//         cin >> l >> r;
//         cout << prefix[r] - prefix[l - 1] << "\n";
//     }
// }
