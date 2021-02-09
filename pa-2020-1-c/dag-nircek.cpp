// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/424102/source/
#include <bits/stdc++.h>
#define N 75
using namespace std;
size_t conn[N];           // dodatkowe powiązania
size_t traceback[N + 1];  // kolejne ilości dróg, ostatnia ma być jeden
set<pair<size_t, size_t>> hopki;  // -dokąd, skąd
vector<size_t> majahopki;
void init() { traceback[N] = 1; }
bool ma_hopke(const size_t a) { return conn[a] > a + 1; }
void usun_losowa_hopke() {
  size_t r = rand() % majahopki.size();              // wylosuj
  hopki.erase({-conn[majahopki[r]], majahopki[r]});  // wyrzuć połączenie
  conn[majahopki[r]] = 0;                            // usuń hopkę
  swap(majahopki[r], *(majahopki.end() - 1));        // zapomnij
  majahopki.pop_back();
}
void nadpisz_hopke(size_t a, size_t b) {
  if(ma_hopke(a)) {  // musimy usunąć stary
    hopki.erase({-conn[a], a});
  } else {
    majahopki.push_back(a);
  }
  conn[a] = b;
  hopki.insert({-b, a});
}
void zmien_losowa_hopke() {
  size_t a = rand() % (N - 2);
  size_t b = 2 + a + rand() % (N - a - 2);
  nadpisz_hopke(a, b);
}
size_t policz_sciezki() {
  set<pair<size_t, size_t>>::iterator it = hopki.begin();
  for(size_t i = N - 1; i != (size_t) -1; --i) {
    if(ma_hopke(i))
      traceback[i] += traceback[i + 1];
    else
      traceback[i] = traceback[i + 1];
    while(it != hopki.end() && it->first == -i) {
      traceback[it->second] = traceback[i];
      ++it;
    }
  }
  return traceback[0];
}
int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  size_t sciezek, aktualnie;
  cin >> sciezek;
  init();
  while((aktualnie = policz_sciezki()) != sciezek)
    if(aktualnie < sciezek)
      zmien_losowa_hopke();
    else
      usun_losowa_hopke();
  cout << N << '\n';
  for(size_t i = 0; i < N - 1; ++i)
    cout << i + 2 << ' ' << (ma_hopke(i) ? (int) (conn[i] + 1) : -1) << '\n';
  cout << "-1 -1\n";
  return 0;
}


