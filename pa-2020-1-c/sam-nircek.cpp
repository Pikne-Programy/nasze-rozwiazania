// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/417612/source/
#include <bits/stdc++.h>
using namespace std;
int main() {
  size_t n;
  cin >> n;
  map<int, size_t> pionowe;
  map<int, size_t> poziome;
  while(n--) {
    int r, w, t;
    cin >> r >> w >> t;
    switch(r) {
      case 1:
        ++pionowe[w - t];
        break;
      case 2:
        ++poziome[w - t];
        break;
    }
  }
  if(pionowe.size()>poziome.size())
    swap(pionowe, poziome);
  size_t s = 0;
  for(auto it = pionowe.begin(); it != pionowe.end(); ++it)
    s += min(it->second, poziome[it->first]);
  cout << s << endl;
}
