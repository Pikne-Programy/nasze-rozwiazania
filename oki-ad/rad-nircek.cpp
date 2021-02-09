#include <iostream>
using namespace std;
bool s1[360];
bool s2[360];
int main() {
  size_t n;
  cin >> n;
  s2[0] = true;
  while(n--) {
    swap(s2, s1);
    int a;
    cin >> a;
    for(size_t i = 0; i < 360; ++i)
      s2[i] = false;
    for(size_t i = 0; i < 360; ++i)
      if(s1[i]) {
        s2[(i + a) % 360] = true;
        s2[(360 + i - a) % 360] = true;
      }
  }
  if(s2[0])
    cout << "TAK";
  else
    cout << "NIE";
  return 0;
}
