// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/413097/source/
#include <iostream>
#include <set>
#define DEBUG false
using namespace std;
class Zbior {
  size_t n;
  set<pair<size_t, size_t>> przedzialy;

 public:
  Zbior(size_t n) { this->n = n; }
  Zbior(size_t n, set<pair<size_t, size_t>> przedzialy) {
    this->n = n;
    this->przedzialy = przedzialy;
  }
  set<pair<size_t, size_t>>::iterator nastepny(size_t x) {
    return przedzialy.upper_bound({x, -1});
  }
  set<pair<size_t, size_t>>::iterator zawierajacy(size_t x) {
    auto xx = nastepny(x);
    if(xx == przedzialy.begin())
      return przedzialy.end();
    else
      --xx;
    if(xx->first <= x && x <= xx->second)
      return xx;
    return przedzialy.end();
  }
  void usun(size_t a, size_t b) {
    auto prawy = zawierajacy(b);
    if(prawy != przedzialy.end()) {
      size_t dopelnienie = prawy->second;
      przedzialy.erase(prawy);
      if(b != dopelnienie)
        przedzialy.insert({b + 1, dopelnienie});
    }
    auto lewy = zawierajacy(a);
    if(lewy != przedzialy.end()) {
      size_t dopelnienie = lewy->first;
      przedzialy.erase(lewy);
      if(dopelnienie != a)
        przedzialy.insert({dopelnienie, a - 1});
      if(DEBUG)
        cerr << "Obięto lewy koniec\n";
    }
    lewy = prawy = nastepny(a);
    while(prawy != przedzialy.end() && prawy->second <= b)
      ++prawy;
    przedzialy.erase(lewy, prawy);
  }
  Zbior &dodaj(size_t a, size_t b) {
    if(b < a)
      return *this;
    auto lewy = zawierajacy(a - 1);
    if(lewy != przedzialy.end())
      a = lewy->first;  // rozszerzamy do lewej
    auto prawy = zawierajacy(b + 1);
    if(prawy != przedzialy.end())
      b = prawy->second;  // rozszerzamy do prawej
    usun(a, b);           // usuwamy wszystkie w przedziale
    przedzialy.insert({a, b});
    return *this;
  }
  Zbior negacja() {
    set<pair<size_t, size_t>> nowy;
    size_t poprzedni = 0;
    for(auto e : przedzialy) {
      if(e.first != 0) {
        size_t nastepny = e.first - 1;
        if(nastepny >= poprzedni)
          nowy.insert({poprzedni, nastepny});
      }
      poprzedni = e.second + 1;
    }
    if(n - 1 >= poprzedni)
      nowy.insert({poprzedni, n - 1});
    return Zbior(n, nowy);
  }
  Zbior iloczyn(Zbior &inny) {
    Zbior wynikowy(n);
    for(auto e : przedzialy) {
      auto brzeg = e.first;
      while(brzeg <= e.second) {
        auto lewy = inny.zawierajacy(brzeg);
        if(lewy != inny.przedzialy.end()) {
          auto nastepny = min(e.second, lewy->second);
          wynikowy.dodaj(brzeg, nastepny);
          brzeg = lewy->second + 1;
        } else {
          auto nastepny = inny.nastepny(brzeg);
          brzeg = nastepny == inny.przedzialy.end() ? n : nastepny->first;
        }
      }
    }
    return wynikowy;
  }
  size_t dlugosc() {
    size_t s = 0;
    for(pair<size_t, size_t> e : przedzialy) {
      s += e.second - e.first + 1;
    }
    return s;
  }
};
int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  size_t n, m;
  cin >> n >> m;  // puszki, operacje
  Zbior zolty(n), niebieski(n), czerwony(n);
  while(m--) {
    size_t l, r, k;
    cin >> l >> r >> k;
    --l;
    --r;
    switch(k) {
      case 1:
        zolty.dodaj(l, r);
        break;
      case 2:
        niebieski.dodaj(l, r);
        break;
      case 3:
        czerwony.dodaj(l, r);
        break;
    }
  }
  cout << czerwony.negacja().iloczyn(zolty).iloczyn(niebieski).dlugosc()
       << '\n';
  return 0;
}
