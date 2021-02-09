#include <bits/stdc++.h>
using namespace std;

struct row {
  unsigned d;
  size_t id;
  unsigned dd, dp, dr;
  bool operator<(const struct row n) const { return d > n.d; }
};

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  size_t N;
  cin >> N;
  unsigned long long S = 0;
  bool D = false, P = false, R = false;
  priority_queue<struct row> pq[3];
  for(size_t id = 0; id < N; ++id) {
    unsigned d, p, r;
    cin >> d >> p >> r;
    D = D || d;
    P = P || p;
    R = R || r;
    unsigned dpr[] = {d, p, r};
    unsigned m = max({d, p, r});
    unsigned s = min({d + p, p + r, r + d});
    S += s;
    for(size_t w = 0; w < 3; ++w) {
      pq[w].push({m - (dpr[w]), id, m - d, m - p, m - r});
      if(pq[w].size() == 4)
        pq[w].pop();
    }
  }
  set<size_t> ids;
  vector<array<unsigned, 3>> dpr;
  for(size_t w = 0; w < 3; ++w) {
    while(!pq[w].empty()) {
      if(!ids.count(pq[w].top().id)) {
        dpr.push_back({pq[w].top().dd, pq[w].top().dp, pq[w].top().dr});
        ids.insert(pq[w].top().id);
      }
      pq[w].pop();
    }
  }
  vector<size_t> sel;
  size_t l = 0;
  for(array<unsigned, 3> e : dpr) {
    ++l;
    size_t q = -1;
    for(size_t w = 3; w != -1; --w)
      if(!e[w])
        q = w;
    sel.push_back(q);
  }
  array<bool, 3> exists = {!D, !P, !R};
  unsigned sum = 0;
  for(size_t w = 0; w < 3; ++w)
    if(!exists[w]) {
      for(size_t e : sel) {
        if(e == w) {
          exists[w] = true;
          ++sum;
          break;
        }
      }
    } else {
      ++sum;
    }
  if(sum == 2) {
    size_t missing = -1;
    while(exists[++missing])
      ;
    size_t id = -1;
    unsigned iv = -1;
    for(size_t i = 0; i < l; ++i)
      if(dpr[i][missing] <= iv) {
        id = i;
        iv = dpr[i][missing];
      }
    size_t old = missing;
    swap(sel[id], old);
    exists = {!D, !P, !R};
    sum = 0;
    for(size_t w = 0; w < 3; ++w)
      if(!exists[w]) {
        for(size_t e : sel) {
          if(e == w) {
            exists[w] = true;
            ++sum;
            break;
          }
        }
      } else
        ++sum;

    if(sum == 3) {
      S += iv;
    } else {
      exists[missing] = false;
      sel[id] = old;
      --sum;
    }
  }
  if(sum == 1) {
    size_t a = -1;
    while(exists[++a])
      ;
    size_t b = a;
    while(exists[++b])
      ;
    priority_queue<pair<unsigned, size_t>> pqa, pqb, r;
    for(size_t i = 0; i < l; ++i) {
      pqa.push(make_pair(dpr[i][a], i));
      pqb.push(make_pair(dpr[i][b], i));
      if(pqa.size() == 3)
        pqa.pop();
      if(pqb.size() == 3)
        pqb.pop();
    }
    unsigned av2 = pqa.top().first, bv2 = pqb.top().first;
    unsigned ai2 = pqa.top().second, bi2 = pqb.top().second;
    pqa.pop();
    pqb.pop();
    if(pqa.top().second != pqb.top().second) {
      S += pqa.top().first + pqb.top().first;
    } else {
      unsigned s1 = pqa.top().second == bi2 ? INT_MAX : pqa.top().first + bv2;
      unsigned s2 = pqb.top().second == ai2 ? INT_MAX : pqb.top().first + av2;
      S += min(s1, s2);
    }
  }
  cout << S;
  return 0;
}
