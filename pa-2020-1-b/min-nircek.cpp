// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/420058/source/
#include <bits/stdc++.h>
using namespace std;
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  size_t n;
  cin >> n;
  vector<long long> odpala[n];
  map<long long, size_t> miny_wstecz;         // coord, index
  set<pair<long long, size_t>> pole_razenia;  // coord, index
  for(size_t i = 0; i < n; ++i) {
    long long a, r;
    cin >> a >> r;
    for(auto it = pole_razenia.lower_bound({a, 0}); it != pole_razenia.end();
        ++it)  // wszystkie, które nas obejmują
      odpala[it->second].push_back(i);
    for(auto it = miny_wstecz.lower_bound(a - r); it != miny_wstecz.end();
        ++it)  // wszystkie, które my obejmujemy
      odpala[i].push_back(it->second);

    pole_razenia.insert({a + r, i});
    miny_wstecz[a] = i;
  }
  unsigned long long x;
  unsigned long long end = 1 << n;
  unsigned long long s = 1;
  for(unsigned long long c = 1; c && (c < end); ++c) {
    bool failed = false;
    for(size_t i = 0; i < n; ++i) {
      if(c & (1 << i)) {
        for(auto e : odpala[i]) {
          if(!(c & (1 << e))){
            failed = true;
            break;
          }
        }
      }
      if(failed)
        break;
    }
    if(!failed)
      ++s;
  }
  cout << s%1000000007 << '\n';
  return 0;
}
