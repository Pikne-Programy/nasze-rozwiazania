// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/416407/source/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>
using namespace std;
long long s[500001];
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  size_t n;
  cin >> n;
  for(size_t i = 1; i <= n; ++i) {
    long long a;
    cin >> a;
    s[i] = s[i - 1] + a;
  }
  if(s[n] < 0) {
    cout << -1 << '\n';
    return 0;
  }
  vector<pair<long long, size_t>> punkty;  // suma, max droga
  for(size_t i = 0; i <= n; ++i)
    if(0 <= s[i] && s[i] <= s[n])
      punkty.push_back({s[i], (size_t) -1});
  size_t len = punkty.size();
  for(size_t i = len - 1; i != (size_t) -1; --i) {
    size_t m = 0;
    long long w = LLONG_MAX;
    for(size_t j = i + 1; j < len; ++j)
      if(punkty[j].first >= punkty[i].first && punkty[j].first < w) {
        w = punkty[j].first;
        m = max(m, punkty[j].second + 1);
      }
    punkty[i].second = m;
  }
  cout << n - punkty[0].second << '\n';
  return 0;
}
