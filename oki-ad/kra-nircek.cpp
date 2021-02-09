#include <iostream>
using namespace std;
size_t n, m;
struct xd {
  uint32_t pref;
  uint64_t kombinacje = 0;
} * maski;
uint32_t pref[19];
uint32_t a, b;
int main() {
  cin >> n >> m;
  maski = new struct xd[1 << n];
  while(m--) {
    cin >> a >> b;
    pref[a - 1] |= (1 << (b - 1));
  }
  maski[0].pref = 0;
  maski[0].kombinacje = 1;
  for(uint32_t maska = 0; maska < 1 << n; ++maska) {
    for(size_t i = 0; i < n; ++i) {
      uint32_t m = (1 << i);
      if(!(m & maski[maska].pref)) {  // jeżeli się nie pokłócą
        m |= maska;
        if(maska != m) {
          maski[m].pref = maski[maska].pref | pref[i];
          maski[m].kombinacje += maski[maska].kombinacje;
        }
      }
    }
  }
  cout << maski[(1 << n) - 1].kombinacje;
}
