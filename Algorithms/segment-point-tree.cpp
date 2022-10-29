#include <bits/stdc++.h>
using namespace std;

constexpr size_t limit = 1 << 17;                  // the maximum number of stored elements
constexpr size_t limitBITS = log2(limit - 1) + 1;  // how many additional layers of tree do we need
static_assert(1 << limitBITS >= limit);            // base >= the number of elements
/*

# Segment (update) - Point (query) tree
src: https://github.com/Pikne-Programy/nasze-rozwiazania/blob/master/Algorithms/segment-point-tree.cpp

example (base = 8):
+-----------------------------------+
|                 1                 |
|         2               3         |
|     4       5       6       7     |
|   8   9   a   b   c   d   e   f   |
+-----------------------------------+

elements in tree are in 1..2*base-1
stored elements are indexed by 0..base-1

*/
using treeSPtype = long long;                         // type of stored elements and queries
constexpr static size_t treeSPbase = 1 << limitBITS;  // the exponent of the power of 2 exceeding the number of stored elements
constexpr static treeSPtype treeSPneutral = 1;        // the neutral element of the operation
inline treeSPtype treeSPop(const treeSPtype a, const treeSPtype b) {  // the associative operation
    return (a*b)%1000000007;
}
/******************************************/
vector<treeSPtype> treeSP(treeSPbase << 1, treeSPneutral);  // change the init value here
void treeSPset(size_t v, treeSPtype x) {
    v += treeSPbase;
    treeSP[v] = x;
}
void treeSPinit() {
    for(size_t v = treeSPbase - 1; v; --v) treeSP[v] = treeSPop(treeSP[2 * v], treeSP[2 * v + 1]);
}
treeSPtype treeSPget(size_t v) {
    v += treeSPbase;
    return treeSP[v];
}
treeSPtype treeSPquery(size_t v) {
    treeSPtype result = treeSPneutral;
    v += treeSPbase;
    while(v) {
        result = treeSPop(result, treeSP[v]);
        v >>= 1;
    }
    return result;
}
void treeSPupdate(size_t l, size_t r, treeSPtype x) {
    l += treeSPbase - 1;
    r += treeSPbase + 1;
    while(r - l > 1) {
        if(!(l & 1))  treeSP[l + 1] = treeSPop(treeSP[l + 1], x);
        if(r & 1) treeSP[r - 1] = treeSPop(treeSP[r - 1], x);
        l >>= 1;
        r >>= 1;
    }
}

int q, t, a, b, c;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> q;
    while(q--) {
        cin >> t;
        switch(t) {
            case 0: cin >> a >> b >> c; treeSPupdate(a, b, c); break;
            case 1: cin >> a; cout << treeSPquery(a) << '\n'; break;
        }
    }
}
