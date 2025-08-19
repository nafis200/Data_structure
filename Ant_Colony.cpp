#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 7;
int a[N];
struct node
{
    int g, mn, cnt;
};
node s[N * 4];
node merge(node l, node r)
{
    node ans;
    ans.g = __gcd(l.g, r.g);
    ans.mn = min(l.mn, r.mn);
    ans.cnt = 0;
    if (ans.mn == l.mn)
    {
        ans.cnt += l.cnt;
    }
    if (ans.mn == r.mn)
    {
        ans.cnt += r.cnt;
    }
    return ans;
}
void bulid_(int n, int b, int e)
{
    if (b == e)
    {
        s[n].g = a[b];
        s[n].mn = a[b];
        s[n].cnt = 1;
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    bulid_(l, b, mid);
    bulid_(r, mid + 1, e);
    s[n] = merge(s[l], s[r]);
}
node query(int n, int b, int e, int i, int j)
{
    if (b > j or e < i)
        return {0, INT_MAX, 0};
    if (b >= i and e <= j)
    {
        return s[n];
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}

int main()
{
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    bulid_(1, 1, n);
    int q;
    cin >> q;
    while (q--)
    {
        int l, r;
        cin >> l >> r;
        int count = 0;
        node ans = query(1, 1, n, l, r);
        if (ans.mn == ans.g)
        {
            count = ans.cnt;
        }
        cout << (r - l + 1) - count << "\n";
    }
}