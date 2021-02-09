// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/422584/source/
#include <iostream>
using namespace std;
#define M 11460  // do m=213
#define DEBUG false
#define MEMTEST false
char wspolczynniki[2 * M - 2][2 * M - 2];
unsigned long long linia1[2 * M - 2];
unsigned long long linia2[2 * M - 2];
unsigned long long n, m, prime;
size_t l, l2, p, p2;
void addmodto(unsigned long long &a, unsigned long long b) {
  a += b;
  while(a >= prime)
    a -= prime;
}
int main() {
  ios_base::sync_with_stdio(0);
  cout.tie(0);
  cin.tie(0);
  cin >> n >> m >> prime;
  size_t i = 0, j = 0;
  if(MEMTEST) {
    for(l = (m - 1) / 2; l != (size_t) -1; --l)
      for(p = l; l + p < m; ++p)
        ++i;
    cout << i;
    return 0;
  }
  for(l = (m - 1) / 2; l != (size_t) -1; --l)
    for(p = l; l + p < m; ++p) {
      if(DEBUG)
        cerr << '(' << l << ',' << p << ")[" << i << "] -> ";
      j = 0;
      for(l2 = (m - 1) / 2; l2 != (size_t) -1; --l2)
        for(p2 = l2; l2 + p2 < m; ++p2) {
          if(DEBUG)
            cerr << '(' << l2 << ',' << p2 << ")[" << j << "]: ";
          if((l2 <= l && l <= p2) || (l <= l2 && l2 <= p)) {
            if(l2 + p2 == m - 1) {
              wspolczynniki[i][j] = 1;
              if(DEBUG)
                cerr << 1 << endl;
            } else {
              if(m - 1 - p2 <= p) {
                wspolczynniki[i][j] = 2;
                if(DEBUG)
                  cerr << 2 << endl;
              } else {
                wspolczynniki[i][j] = 1;
                if(DEBUG)
                  cerr << 1 << endl;
              }
            }
          } else {
            if(DEBUG)
              cerr << 0 << endl;
          }
          ++j;
        }
      ++i;
    }
  size_t N = i;
  unsigned long long *bufor1 = linia1;
  unsigned long long *bufor2 = linia2;
  for(i = 0; i < N; ++i)
    bufor1[i] = 1;
  while(n--) {
    for(i = 0; i < N; ++i) {
      unsigned long long b = 0;
      for(j = 0; j < N; ++j) {
        if(DEBUG)
          cerr << (int) wspolczynniki[i][j] << '*' << bufor1[j] << ' ';
        addmodto(b, bufor1[j] * wspolczynniki[i][j]);
      }
      if(DEBUG)
        cerr << " = " << b << endl;
      bufor2[i] = b;
    }
    if(DEBUG)
      cerr << string('-', 37) << endl;
    swap(bufor1, bufor2);
  }
  cout << bufor1[N - 1] << '\n';
  return 0;
}
