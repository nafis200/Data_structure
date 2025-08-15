#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
int a[N], t[N * 4];

void pull(int n, int b, int e)
{
    t[n] = t[b] + t[e];
}

void build(int n, int b, int e)
{
    if (b == e)
    {
        t[n] = a[b];
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    build(l, b, mid);
    build(r, mid + 1, e);
    pull(n, l, r);
}

void update(int n, int b, int e, int i, int v)
{
    if (b > i or e < i)
    {
        return;
    }
    if (b == e and b == i)
    {
        t[n] += v;
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    update(l, b, mid, i, v);
    update(r, mid + 1, e, i, v);
    pull(n, l, r);
}

int update_delete(int n, int b, int e, int i, int v)
{
    if (b > i or e < i)
    {
        return 0;
    }
    if (b == e and b == i)
    {
        int x = 0;
        x = t[n];
        t[n] = v;
        return x;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    int left = update_delete(l, b, mid, i, v);
    int right = update_delete(r, mid + 1, e, i, v);
    pull(n, l, r);
    return left + right;
}

int query(int n, int b, int e, int i, int j)
{
    if (b > j or e < i)
    {
        return 0;
    }
    if (b >= i and e <= j)
    {
        return t[n];
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    int left = query(l, b, mid, i, j);
    int right = query(r, mid + 1, e, i, j);
    return left + right;
}

int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    build(1, 1, n);
    while (q--)
    {
        int num;
        cin >> num;
        if (num == 1)
        {
            int i;
            cin >> i;
            i++;
            cout << update_delete(1, 1, n, i, 0) << "\n";
        }
        if (num == 2)
        {
            int i, v;
            cin >> i >> v;
            i++;
            update(1, 1, n, i, v);
        }
        if (num == 3)
        {
            int i, j;
            cin >> i >> j;
            i++;
            j++;
            cout << query(1, 1, n, i, j) << "\n";
        }
    }
}