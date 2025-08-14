#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;

const long long N = 200005;
long long a[N];

template <typename T>
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int32_t main() {
    long long t;
    cin >> t;
    while (t--) {
        o_set<long long> st;
        long long n;
        cin >> n;
        for (long long i = 1; i <= n; i++) {
            cin >> a[i];
        }
        long long count = 0;
        for (long long i = n; i >= 1; i--) {
            long long rank = st.order_of_key(a[i]); 
            count += rank;
            st.insert(a[i]);
        }
        cout << count << "\n";
    }
}



