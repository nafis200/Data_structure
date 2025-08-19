// SUM and REPLACE
//     Given TLE
// #include <bits/stdc++.h>
//     using namespace std;
// const int N = 1e6 + 5;
// int d[N];
// int a[N];
// long long s[N * 4];
// void bulid_(int n, int b, int e)
// {
//     if (b == e)
//     {
//         s[n] = a[b];
//         return;
//     }
//     int l = n * 2;
//     int r = n * 2 + 1;
//     int mid = (b + e) / 2;
//     bulid_(l, b, mid);
//     bulid_(r, mid + 1, e);
//     s[n] = s[l] + s[r];
// }
// long long query(int n, int b, int e, int i, int j)
// {
//     if (b > j or e < i)
//         return 0;
//     if (b >= i and e <= j)
//     {
//         return s[n];
//     }
//     int l = n * 2;
//     int r = n * 2 + 1;
//     int mid = (b + e) / 2;
//     return query(l, b, mid, i, j) + query(r, mid + 1, e, i, j);
// }
// void update_(int n, int b, int e, int i, int x)
// {
//     if (b > i or e < i)
//         return;
//     if (b == e)
//     {
//         s[n] = x;
//         return;
//     }
//     int l = n * 2;
//     int r = n * 2 + 1;
//     int mid = (b + e) / 2;
//     update_(l, b, mid, i, x);
//     update_(r, mid + 1, e, i, x);
//     s[n] = s[l] + s[r];
// }

// int main()
// {
//     ios_base::sync_with_stdio(0);
//     cin.tie(0);
//     memset(d, 0, sizeof(d));
//     for (int i = 1; i < N; i++)
//     {
//         for (int j = i; j <= N; j += i)
//         {
//             d[j]++;
//         }
//     }
//     int n, q;
//     cin >> n >> q;
//     for (int i = 1; i <= n; i++)
//     {
//         cin >> a[i];
//     }
//     bulid_(1, 1, n);
//     while (q--)
//     {
//         int ty, l, r;
//         cin >> ty >> l >> r;
//         if (ty == 1)
//         {
//             for (int i = l; i <= r; i++)
//             {
//                 update_(1, 1, n, i, d[a[i]]);
//                 a[i] = d[a[i]];
//             }
//         }
//         else
//         {
//             cout << query(1, 1, n, l, r) << "\n";
//         }
//     }
// }

#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 5;
int d[N];
int a[N];
long long s[N * 4];
void bulid_(int n, int b, int e)
{
    if (b == e)
    {
        s[n] = a[b];
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    bulid_(l, b, mid);
    bulid_(r, mid + 1, e);
    s[n] = s[l] + s[r];
}
long long query(int n, int b, int e, int i, int j)
{
    if (b > j or e < i)
        return 0;
    if (b >= i and e <= j)
    {
        return s[n];
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    return query(l, b, mid, i, j) + query(r, mid + 1, e, i, j);
}
void update_(int n, int b, int e, int i, int x)
{
    if (b > i or e < i)
        return;
    if (b == e)
    {
        s[n] = x;
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    update_(l, b, mid, i, x);
    update_(r, mid + 1, e, i, x);
    s[n] = s[l] + s[r];
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    memset(d, 0, sizeof(d));
    for (int i = 1; i < N; i++)
    {
        for (int j = i; j <= N; j += i)
        {
            d[j]++;
        }
    }
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    bulid_(1, 1, n);

    set<int> st;
    for (int i = 1; i <= n; i++)
    {
        if (a[i] > 2)
        {
            st.insert(i);
        }
    }
    while (q--)
    {
        int ty, l, r;
        cin >> ty >> l >> r;
        vector<int> del;
        if (ty == 1)
        {
            auto it = st.lower_bound(l);
            while (it != st.end() and (*it) <= r)
            {
                int i = *it;
                update_(1, 1, n, i, d[a[i]]);
                a[i] = d[a[i]];
                if (a[i] <= 2)
                    del.push_back(i);
                ++it;
            }
            for (auto it : del)
            {
                st.erase(it);
            }
        }
        else
        {
            cout << query(1, 1, n, l, r) << "\n";
        }
    }
}