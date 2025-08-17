#include <bits/stdc++.h>
using namespace std;
const int N = 30005;
int a[N];
int t[N * 4];
int n;
const int QQ = 200005;
vector<pair<int, int>> Q[QQ];
int ans[QQ];
void pull(int n, int b, int e)
{
    t[n] = t[b] + t[e];
}

void build(int n, int b, int e)
{
    if (b == e)
    {
        t[n] = 0;
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
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    int q;
    cin >> q;
    int q1 = q;
    int i = 1;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        Q[r].push_back({l, i});
        i++;
    }
    map<int, int> mp;
    for (int r = 1; r <= n; r++)
    {
        update(1, 1, n, r, 1);
        if (mp.find(a[r]) != mp.end())
        {
            update(1, 1, n, mp[a[r]], -1);
        }
        mp[a[r]] = r;

        for (auto it : Q[r])
        {
            ans[it.second] = query(1, 1, n, it.first, r);
        }
    }

   for(int j = 1; j <= q1; j++){
    cout << ans[j] << "\n";
   }   
}