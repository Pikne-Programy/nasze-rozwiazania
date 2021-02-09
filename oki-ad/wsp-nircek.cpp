#include <iostream>
using namespace std;
size_t n, k;
uint64_t m[1 << 13];
int main() {
  ios::sync_with_stdio(0);
  cout.tie(0);
  cin.tie(0);
  cin >> n >> k;
  while(n--) {
    string a;
    cin >> a;
    uint16_t b = 0;
    for(size_t i = 0; i < k; ++i)
      b = (b << 1) + a[i] - '0';
    ++m[b];
  }
  uint64_t w = 0;
  for(size_t i = 1; i < 1 << k; ++i) {
    w += m[i] * (m[i] - 1) / 2;
    for(size_t j = i + 1; j < 1 << k; ++j)
      if(i & j)
        w += m[i] * m[j];
  }
  cout << w;
}
