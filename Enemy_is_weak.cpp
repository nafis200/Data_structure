#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

const long long N = 1e6 + 5;
long long a[N];
long long b[N], c[N];
template <typename T>
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int32_t main()
{

    o_set<long long> st,st1;
    long long n;
    cin >> n;
    for (long long i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++)
    {
        int ans = st.order_of_key(a[i]);

        int ans1 = st.size() - ans;
        b[i] = ans1;
        st.insert(a[i]);
    }
    for (int i = n; i >= 1; i--)
    {
        int ans = st1.order_of_key(a[i]);
        c[i] = ans;
        st1.insert(a[i]);
    }

    long long count = 0;
    for(int i = 1; i <= n; i++){
        count = 1LL * (count + (1LL * b[i] * c[i]));
    }
    cout << count << "\n";
}
