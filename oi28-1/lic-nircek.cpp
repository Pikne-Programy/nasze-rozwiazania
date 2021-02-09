#include <algorithm>
#include <iostream>
using namespace std;
int n;  // długość wyświetlacza
int z;  // operacje
string wew, zew, suma;
void zmien_suma(int i, bool gora) {
  if(gora) {
    while(suma[i] == 9) {
      suma[i] = 0;
      --i;
    }
    ++suma[i];
  } else {
    while(suma[i] == 0) {
      suma[i] = 9;
      --i;
    }
    --suma[i];
  }
}
void zmien(string &z, int i, int c) {
  int d = c - z[n - i];
  z[n - i] = c;
  int nn = suma[n - i];
  nn += d;
  if(nn < 0) {
    suma[n - i] = nn + 10;
    zmien_suma(n - i - 1, false);
  } else if(nn > 9) {
    suma[n - i] = nn - 10;
    zmien_suma(n - i - 1, true);
  } else {
    suma[n - i] = nn;
  }
}
int main() {
  cin >> n >> z;
  cin >> wew >> zew;
  wew = "0" + wew;
  zew = "0" + zew;
  int carry = false;
  for(int i = n - 1; i > -1; --i) {
    wew[i] -= '0';
    zew[i] -= '0';
    char s = wew[i] + zew[i] + carry;
    if(carry = (s > 9))
      s -= 10;
    suma += s;
  }
  reverse(suma.begin(), suma.end());
  for(size_t i = 0; i < n; ++i)
    suma[i] += '0';
  for(size_t i = 0; i < n; ++i)
    suma[i] -= '0';
  while(z--) {
    char q;
    int i, c;
    cin >> q;
    if(q == 'S') {
      cin >> i;
      cout << (char)(suma[n - i] + '0') << '\n';
    } else {
      cin >> i >> c;
      zmien(q == 'W' ? wew : zew, i, c);
    }
  }
}

