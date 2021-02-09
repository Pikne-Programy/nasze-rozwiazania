// 70/100
#include <iostream>
using namespace std;
size_t n;
long long t[20];
struct xd {
  long long suma;
  int kombinacje = 0;
} *maski;
int main() {
  cin >> n;
  maski = new struct xd[1 << n];
  maski[0].suma = 0;
  maski[0].kombinacje = 1;
  for(size_t i = 0; i < n; ++i)
    cin >> t[i];
  for(uint32_t maska = 0; maska < 1 << n; ++maska) {
    if(maski[maska].suma >= 0) {
      for(size_t i = 0; i < n; ++i) {
        uint32_t m = maska | (1 << i);
        if(maska != m) {
          maski[m].suma = maski[maska].suma + t[i];
          if(maski[m].suma >= 0) {
            maski[m].kombinacje += maski[maska].kombinacje;
            maski[m].kombinacje %= 1000000007;
          }
        }
      }
    }
  }
  cout << maski[(1 << n) - 1].kombinacje;
}
