#include <bits/stdc++.h>
using namespace std;

constexpr size_t limit = 1 << 17;                  // the maximum number of stored elements
constexpr size_t limitBITS = log2(limit - 1) + 1;  // how many additional layers of tree do we need
static_assert(1 << limitBITS >= limit);            // base >= the number of elements
/*

# Point (update) - Segment (query) tree
src: https://github.com/Pikne-Programy/nasze-rozwiazania/blob/master/Algorithms/point-segment-tree.cpp

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
using treePStype = int;                               // type of stored elements and queries
constexpr static size_t treePSbase = 1 << limitBITS;  // the exponent of the power of 2 exceeding the number of stored elements
constexpr static treePStype treePSneutral = INT_MIN;  // the neutral element of the operation
inline treePStype treePSop(const treePStype a, const treePStype b) {  // the associative operation
    return max(a, b);
}
/******************************************/
vector<treePStype> treePS(treePSbase << 1, treePSneutral);  // change the init value here
void treePSset(size_t v, treePStype x) {
    v += treePSbase;
    treePS[v] = x;
}
void treePSinit() {
    for(size_t v = treePSbase - 1; v; --v) treePS[v] = treePSop(treePS[2 * v], treePS[2 * v + 1]);
}
treePStype treePSget(size_t v) {
    v += treePSbase;
    return treePS[v];
}
void treePSupdate(size_t v, treePStype x) {
    v += treePSbase;
    treePS[v] = x;
    v >>= 1;
    while(v) {
        treePS[v] = treePSop(treePS[2 * v], treePS[2 * v + 1]);
        v >>= 1;
    }
}
treePStype treePSquery(size_t l, size_t r) {
    treePStype result = treePSneutral;
    l += treePSbase - 1;
    r += treePSbase + 1;
    while(r - l > 1) {
        if(!(l & 1)) result = treePSop(result, treePS[l + 1]);
        if(r & 1) result = treePSop(result, treePS[r - 1]);
        l >>= 1;
        r >>= 1;
    }
    return result;
}

int q, t, a, b;

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    cin >> q;
    while(q--) {
        cin >> t >> a >> b;
        switch(t) {
            case 0: treePSupdate(a, b); break;
            case 1: cout << treePSquery(a, b) << '\n'; break;
        }
    }
}
