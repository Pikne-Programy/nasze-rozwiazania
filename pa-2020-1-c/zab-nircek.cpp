// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/414890/source/
#include <iostream>
using namespace std;
int t[2][2][26];
void wczyt(size_t n, size_t i) {
  bool s = 0;
  while(n--) {
    char c;
    cin >> c;
    ++t[i][s][c - 'a'];
    s ^= 1;
  }
}
bool porownaj() {
  for(size_t i = 0; i < 26; ++i)
    if(t[0][0][i] != t[1][0][i] || t[0][1][i] != t[1][1][i])
      return false;
  return true;
}
int main() {
  size_t n;
  cin >> n;
  wczyt(n, 0);
  wczyt(n, 1);
  if(porownaj())
    cout << "TAK\n";
  else
    cout << "NIE\n";
}
