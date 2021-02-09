#include <bits/stdc++.h>
using namespace std;
#define DEBUG false

vector<pair<unsigned, unsigned>> sasiady[100001];  // droga, miasto
unsigned biciaki[100000];                          // biciaki na drogach
unsigned droginamiasto[100000];
queue<unsigned> bfs;
struct miasto {
  unsigned parent;  // ojciec
  unsigned via;     // którą drogą do ojca
  unsigned ord;     // pozycja w sortowaniu topologicznym
  unsigned diff;    // ilość różnych biciaków do tej pory
} miasta[100001];
int main() {
  unsigned n;          // 100 000
  unsigned m, z;       // 150 000
  cin >> n >> m >> z;  // liczba miast, Biciaków, zapytań
  for(size_t i = 1; i < n; ++i) {
    unsigned a, b, c;
    cin >> a >> b >> c;  // i. droga łącząca miasto a z b i początkowo Biciak c
    biciaki[i] = c;
    sasiady[a].push_back({i, b});
    sasiady[b].push_back({i, a});
  }
  // ---
  // sasiady - jakimi drogami jest połączone dane miasto
  // ---
  bfs.push(1);
  miasta[0] = {0, 0, 0, 0};
  miasta[1] = {0, 0, 0, 0};
  sasiady[1].push_back({0, 0});
  unsigned ord = 0;
  while(!bfs.empty()) {
    unsigned aktualny = bfs.front();  // które miasto
    if(DEBUG)
      cerr << "Wzięto " << aktualny << " z kolejki\n";
    bfs.pop();
    // topologicznie
    if(DEBUG)
      cerr << "Jest to topologicznie " << ord << " miasto.\n";
    miasta[aktualny].ord = ++ord;
    // zrekonstruuj dotejpory rodzica
    unordered_set<unsigned> dotejpory;
    unsigned roznych = 0;
    if(aktualny == 1) {
      if(DEBUG)
        cerr << "Bazowy, bez rekonstrukcji...\n";
    } else {
      unsigned ilemabyc = miasta[miasta[aktualny].parent].diff;
      if(DEBUG)
        cerr << "Rekonstruowanie rodzica, ma być " << ilemabyc << '\n';
      struct miasto *aktualne = &miasta[miasta[aktualny].parent];
      while(roznych < ilemabyc) {  // idź do góry aż policzysz
        if(!dotejpory.count(biciaki[aktualne->via])) {
          dotejpory.insert(biciaki[aktualne->via]);
          ++roznych;
        }
        if(DEBUG)
          cerr << "Pojechano do " << aktualne->parent << ", złapano już "
               << roznych << '\n';
        aktualne = &miasta[aktualne->parent];
      }
      // dolicz kolejnego jeżeli się nie powtórzyło
      if(!dotejpory.count(biciaki[miasta[aktualny].via])) {
        dotejpory.insert(biciaki[miasta[aktualny].via]);
        ++roznych;
      }
      if(DEBUG)
        cerr << "Do tego miasta jest " << roznych << " biciaków.\n";
      miasta[aktualny].diff = roznych;
    }
    while(sasiady[aktualny].size() == 2) {  // jedno dziecko, przekazujemy seta
      if(DEBUG)
        cerr << "Jedno dziecko!\n";
      unsigned droga, nastepny;
      if(sasiady[aktualny][0].second == miasta[aktualny].parent) {
        droga = sasiady[aktualny][1].first;
        nastepny = sasiady[aktualny][1].second;
      } else {
        droga = sasiady[aktualny][0].first;
        nastepny = sasiady[aktualny][0].second;
      }
      if(!dotejpory.count(biciaki[droga])) {
        dotejpory.insert(biciaki[droga]);
        ++roznych;
      }
      if(DEBUG)
        cerr << "Dziedzicem przejechano do " << nastepny << " i złapano "
             << roznych << " biciaków.\n";
      droginamiasto[droga] = nastepny;
      miasta[nastepny] = {aktualny, droga, ++ord, roznych};
      aktualny = nastepny;
    }
    // ustaw dzieciom rodziców i drogi
    if(DEBUG)
      cerr << "Łapanie potomków...\n";
    for(auto m : sasiady[aktualny]) {  // weź wszystkie miasta sąsiednie
                                       // (droga,miasto) jeżeli to nie ojciec
      if(m.first != miasta[aktualny].via) {
        if(DEBUG)
          cerr << "Złapano " << m.second << ", wrzucanie na kolejkę\n";
        miasta[m.second] = {aktualny, m.first};
        droginamiasto[m.first] = m.second;
        bfs.push(m.second);
      }
    }
  }
  // ---
  //
  // ---
  while(z--) {
    char q;
    cin >> q;
    if(q == 'Z') {
      int x;
      cin >> x;
      // ile różnych Biciaków jadąc do miasta x
      if(miasta[x].ord < ord) {  // niezmienione
        cout << miasta[x].diff << '\n';
      } else {
        unordered_set<unsigned> rodzaje;
        unsigned ile = 0;
        while(x != 1) {
          if(miasta[x].ord < ord) {
            unsigned ilemabyc = miasta[x].diff;
            unordered_set<unsigned> dotejpory;
            if(DEBUG)
              cerr << "Rekonstruowanie rodzica, ma być " << ilemabyc << '\n';
            unsigned roznych = 0;
            struct miasto *aktualne = &miasta[x];
            while(roznych < ilemabyc) {  // idź do góry aż policzysz
              if(!dotejpory.count(biciaki[aktualne->via])) {
                dotejpory.insert(biciaki[aktualne->via]);
                ++roznych;
              }

              if(!rodzaje.count(biciaki[aktualne->via])) {
                rodzaje.insert(biciaki[aktualne->via]);
                ++ile;
              }
              if(DEBUG)
                cerr << "Pojechano do " << aktualne->parent << ", złapano już "
                     << roznych << '\n';
              aktualne = &miasta[aktualne->parent];
            }
            break;
          } else {
            if(!rodzaje.count(biciaki[miasta[x].via])) {
              rodzaje.insert(biciaki[miasta[x].via]);
              ++ile;
            }
          }
          x = miasta[x].parent;
        }
        cout << ile << '\n';
      }
    } else {  // q=='B'
      unsigned i, c;
      cin >> i >> c;
      // na i-tej drodze jest Biciak c
      if(biciaki[i] != c) {
        ord = min(ord, miasta[droginamiasto[i]].ord);
        biciaki[i] = c;
      }
    }
  }
}
