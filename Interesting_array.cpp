// n = 3
// constraints:
// 1) 1 2 1  -> 001
// 2) 2 3 3  -> 011

// index
//   0    1     2

//  001  001   001
//  001  011   011    become new array

// Give TLE

#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, m;
int a[N];
int seg[N * 4];

struct Constraint
{
    int l, r, q;
};
vector<Constraint> constraints;

void build(int node, int l, int r)
{
    if (l == r)
    {
        seg[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(node * 2, l, mid);
    build(node * 2 + 1, mid + 1, r);
    seg[node] = seg[node * 2] & seg[node * 2 + 1];
}

int query(int node, int l, int r, int i, int j)
{
    if (r < i || l > j)
        return (1 << 30) - 1;
    if (i <= l && r <= j)
        return seg[node];
    int mid = (l + r) / 2;
    return query(node * 2, l, mid, i, j) & query(node * 2 + 1, mid + 1, r, i, j);
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    constraints.resize(m);

    for (int i = 0; i < m; i++)
    {
        cin >> constraints[i].l >> constraints[i].r >> constraints[i].q;
    }

    for (int i = 1; i <= n; i++)
        a[i] = 0;

    for (auto c : constraints)
    {

        for (int i = c.l; i <= c.r; i++)
        {
            a[i] |= c.q;
        }
    }

    build(1, 1, n);

    for (auto c : constraints)
    {
        int val = query(1, 1, n, c.l, c.r);
        if (val != c.q)
        {
            cout << "NO\n";
            return 0;
        }
    }

    cout << "YES\n";
    for (int i = 1; i <= n; i++)
        cout << a[i] << " ";
    cout << "\n";
}
