// #include <bits/stdc++.h>
// using namespace std;

// int f(vector<int>& a, int l, int r, int x) {
//     int cnt = 0;
//     for (int k = l; k <= r; k++) {
//         if (a[k] == x) cnt++;
//     }
//     return cnt;
// }

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     cin >> n;
//     vector<int> a(n+1);
//     for (int i = 1; i <= n; i++) cin >> a[i];

//     long long ans = 0;
//     for (int i = 1; i < n; i++) {
//         for (int j = i+1; j <= n; j++) {
//             int left = f(a, 1, i, a[i]);
//             int right = f(a, j, n, a[j]);
//             if (left > right) ans++;
//         }
//     }

//     cout << ans << "\n";
//     return 0;
// }


// | i | ai | f(1,i,ai) | j | aj | f(j,n,aj) | Compare |
// | - | -- | --------- | - | -- | --------- | ------- |
// | 3 | 1  | 2         | 6 | 2  | 1         | 2 > 1 ✅ |
// | 3 | 1  | 2         | 7 | 1  | 1         | 2 > 1 ✅ |
// | 4 | 1  | 3         | 5 | 2  | 2         | 3 > 2 ✅ |
// | 4 | 1  | 3         | 6 | 2  | 1         | 3 > 1 ✅ |
// | 4 | 1  | 3         | 7 | 1  | 1         | 3 > 1 ✅ |
// | 5 | 2  | 2         | 6 | 2  | 1         | 2 > 1 ✅ |
// | 5 | 2  | 2         | 7 | 1  | 1         | 2 > 1 ✅ |
// | 6 | 2  | 3         | 7 | 1  | 1         | 3 > 1 ✅ |


// Step 1: i = 3

// এখানে ai = 1

// prefix count: f(1..3, 1) = 2
// (কারণ index 1 এবং 3 এ 1 আছে → মোট 2 বার)

// Step 2: j = 4, 5, 6, 7 (কারণ j > i)
// j = 4

// aj = 1

// suffix count = f(4..7, 1) = 2 (index 4,7 → দুইবার)

// Compare: 2 > 2 ❌ (না)

// j = 5

// aj = 2

// suffix count = f(5..7, 2) = 2 (index 5,6 → দুইবার)

// Compare: 2 > 2 ❌ (না)

// j = 6

// aj = 2

// suffix count = f(6..7, 2) = 1 (index 6 → একবার)

// Compare: 2 > 1 ✅ (হ্যাঁ)

// j = 7

// aj = 1

// suffix count = f(7..7, 1) = 1 (index 7 → একবার)

// Compare: 2 > 1 ✅ (হ্যাঁ)


// #include <bits/stdc++.h>
// using namespace std;

// int main() {
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);

//     int n;
//     cin >> n;
//     vector<int> a(n+1);
//     for (int i = 1; i <= n; i++) cin >> a[i];

//     vector<int> prefix(n+1), suffix(n+1);
//     unordered_map<int,int> cnt;

//     for (int i = 1; i <= n; i++) {
//         cnt[a[i]]++;
//         prefix[i] = cnt[a[i]];
//     }

//     cnt.clear();

//     for (int i = n; i >= 1; i--) {
//         cnt[a[i]]++;
//         suffix[i] = cnt[a[i]];
//     }

//     long long ans = 0;

//     for (int i = 1; i < n; i++) {
//         for (int j = i+1; j <= n; j++) {
//             if (prefix[i] > suffix[j]) ans++;
//         }
//     }

//     cout << ans << "\n";
//     return 0;
// }





#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int t[N * 4];

void pull(int n, int l, int r) {
    t[n] = t[l] + t[r];
}

void update(int n, int b, int e, int idx, int val) {
    if (b > idx || e < idx) return;
    if (b == e && b == idx) {
        t[n] += val;
        return;
    }
    int l = 2*n;
    int r = 2*n+1;
    int mid = (b+e)/2;
    update(l, b, mid, idx, val);
    update(r, mid+1, e, idx, val);
    pull(n, l, r);
}

int query(int n, int b, int e, int i, int j) {
    if (b > j || e < i) return 0;
    if (b >= i && e <= j) return t[n];
    int l = 2*n;
    int r = 2*n+1;
    int mid = (b+e)/2;
    return query(l, b, mid, i, j) + query(r, mid+1, e, i, j);
}

void add(int idx, int val) {
    update(1, 1, N, idx, val);
}

int rangeQuery(int l, int r) {
    if (l > r) return 0;
    return query(1, 1, N, l, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n+1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> prefix(n+1), suffix(n+1);
    unordered_map<int,int> cnt;

    for (int i = 1; i <= n; i++) {
        cnt[a[i]]++;
        prefix[i] = cnt[a[i]];
    }

    cnt.clear();
    for (int i = n; i >= 1; i--) {
        cnt[a[i]]++;
        suffix[i] = cnt[a[i]];
    }

    long long ans = 0;
    for (int j = n; j >= 1; j--) {
        add(suffix[j], 1);
        if (j == 1) continue;
        ans += rangeQuery(1, prefix[j-1]-1);
    }

    cout << ans << "\n";
    return 0;
}

