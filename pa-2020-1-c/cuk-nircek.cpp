// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/423855/source/
#include <bits/stdc++.h>
#define prime 1000000009
#define DEBUG false
using namespace std;

int64_t gcdExtended(int64_t a, int64_t b, int64_t *x, int64_t *y) {
  if(a == 0) {
    *x = 0, *y = 1;
    return b;
  }
  int64_t x1, y1;
  int64_t gcd = gcdExtended(b % a, a, &x1, &y1);
  *x = y1 - (b / a) * x1;
  *y = x1;
  return gcd;
}
int64_t modInverse(int64_t b) {
  ////////////////////////////////////////// b^(p-2) !!!!!!!!!!!!!!!!!!!!!!!!!!!
  int64_t x, y;
  int64_t g = gcdExtended(b, prime, &x, &y);
  if(g != 1)
    return -1;
  return (x % prime + prime) % prime;
}
uint64_t modDivide(uint64_t a, uint64_t b) {
  a = a % prime;
  int64_t inv = modInverse(b);
  if(DEBUG)
  cerr << "[INWERSJA DLA " << b << ": " << inv << ']';
  if(inv == -1) {
    cerr << "DIVISION ERR";
    return -1;
  }
  return (inv * a) % prime;
}
uint64_t modMultiply(uint64_t a, uint64_t b) {
  uint64_t r = 0;
  while(a != 0) {
    if(a & 1)
      r = (r + b) % prime;
    a >>= 1;
    b = (b << 1) % prime;
  }
  return r;
}
uint64_t modAdd(uint64_t a, uint64_t b) {
  a += b;
  if(a >= prime)
    a %= prime;
  return a;
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  size_t n;
  cin >> n;
  int a;
  vector<int> t;
  while(n--) {
    cin >> a;
    t.push_back(a);
  }
  sort(t.begin(), t.end());
  uint64_t jedynek = 0;
  while(jedynek < n && t[jedynek] == 1)
    ++jedynek;
  if(DEBUG)
    cerr << "Wykryto " << jedynek << " jedynek, usuwanie...\n";
  t.erase(t.begin(), t.begin() + jedynek);
  if(DEBUG)
    cerr << "Generowanie trójkąta pascala\n";
  uint64_t pascal[jedynek + 1];
  pascal[0] = 1;
  for(uint64_t i = 0; i < jedynek; ++i) {
    uint64_t a;
    pascal[i + 1] = modDivide(a = modMultiply(pascal[i], jedynek - i), i + 1);
    if(DEBUG)
      cerr << pascal[i] << '*' << jedynek - i << "=" << a << endl;
    if(DEBUG)
      cerr << a << '/' << i + 1 << "=" << pascal[i + 1] << endl;
  }
  if(DEBUG){
    cerr << '1';
  for(uint64_t i = 0; i < jedynek; ++i) {
    cerr << ' ' << pascal[i + 1];
  }
  cerr << '\n';
  }
  uint64_t kombinacje = 0;
  uint64_t maxkombinacji = 1 << t.size();
  for(uint64_t wziete_jedynki = 1; wziete_jedynki <= jedynek;
      ++wziete_jedynki) {
    if(DEBUG)
      cerr << "Dla " << wziete_jedynki << " jedynek:\n";
    uint64_t tekombinacje = 0;
    if(DEBUG)
      cerr << "(max kombnacji: " << maxkombinacji << ")\n";
    for(uint64_t komb = 0; komb < maxkombinacji; ++komb) {
      uint64_t ckomb = komb;
      bool test = true;
      uint64_t suma = wziete_jedynki + 1;
      uint64_t j = 0;
      while(ckomb) {
        if(ckomb & 1) {
          if(DEBUG)
          cerr << t[j] << ' ';
          if(suma < t[j]) {
            if(DEBUG)
              cerr << "ERR";
            test = false;
            break;
          }
          suma += t[j];
        }
        ++j;
        ckomb >>= 1;
      }
      if(DEBUG)
      cerr << endl;
      if(test)
        ++tekombinacje;
    }
    kombinacje =
        modAdd(kombinacje, modMultiply(pascal[wziete_jedynki], tekombinacje));
  }
  cout << kombinacje << '\n';
  return 0;
}
