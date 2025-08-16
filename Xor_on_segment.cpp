#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 9;
const int B = 21;
int a[N];

struct Node {
    int on[B], off[B];
} s[N * 4];  

int lazy[N * 4];
int n;

Node merge(Node l, Node r) {
    Node ans;   
    for (int i = 0; i < B; i++) {
        ans.on[i] = l.on[i] + r.on[i];
        ans.off[i] = l.off[i] + r.off[i];
    }
    return ans;
}

void build(int n, int b, int e) {
    lazy[n] = 0;
    if (b == e) {
        for (int i = 0; i < B; i++) {
            if ((a[b] >> i) & 1) {
                s[n].on[i] = 1;
                s[n].off[i] = 0;
            } else {
                s[n].on[i] = 0;
                s[n].off[i] = 1;
            }
        }
        return; 
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    build(l, b, mid);
    build(r, mid + 1, e);
    s[n] = merge(s[l], s[r]);
}

void push(int n, int b, int e) {
    if (lazy[n] == 0) return;
    for (int i = 0; i < B; i++) {
        if ((lazy[n] >> i) & 1) {
            swap(s[n].on[i], s[n].off[i]);
        }
    }
    if (b != e) {
        int l = n * 2;
        int r = n * 2 + 1;
        lazy[l] ^= lazy[n];
        lazy[r] ^= lazy[n];
    }
    lazy[n] = 0;
}

void upd_(int n, int b, int e, int i, int j, int v) {
    push(n, b, e);
    if (b > j || e < i) return;
    if (b >= i && e <= j) {
        lazy[n] ^= v;
        push(n, b, e);
        return;
    }
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    upd_(l, b, mid, i, j, v);
    upd_(r, mid + 1, e, i, j, v);
    s[n] = merge(s[l], s[r]);
}

Node query(int n, int b, int e, int i, int j) {
    push(n, b, e);
    if (b > j || e < i) {
        Node zero;
        memset(zero.on, 0, sizeof(zero.on));
        memset(zero.off, 0, sizeof(zero.off));
        return zero; 
    }
    if (b >= i && e <= j) return s[n];
    int l = n * 2;
    int r = n * 2 + 1;
    int mid = (b + e) / 2;
    return merge(query(l, b, mid, i, j), query(r, mid + 1, e, i, j));
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    memset(lazy, 0, sizeof(lazy));
    build(1, 1, n);

    int q;
    cin >> q;
    while (q--) {
        int num;
        cin >> num;
        if (num == 1) {
            int i, j;
            cin >> i >> j;
            Node ans = query(1, 1, n, i ,j);
            int count = 0;
            for(int i = 0; i < B; i++){
                count = count + ans.on[i] * (1 << i);
            }
            cout << count << "\n";
          
        }
        else{
            int i, j, v;
            cin >> i >> j >> v;
            upd_(1, 1, n, i, j, v);
        }
    }
}
