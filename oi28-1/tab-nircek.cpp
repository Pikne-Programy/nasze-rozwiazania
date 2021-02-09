#include <iostream>
using namespace std;
uint8_t t[1000][1000];
int q, s;
void rysuj(int x, int y) {
    if(x==-1||y==-1)
        return;
    if(t[x][y]) {
      --s;
      t[x][y] = 0;
    } else {
      ++s;
      t[x][y] = 1;
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> q >> q >> q; // n, m nie są potrzebne
    while(q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        x1 -= 2;
        y1 -= 2;
        --x2;
        --y2;
        rysuj(x1, y1);
        rysuj(x1, y2);
        rysuj(x2, y1);
        rysuj(x2, y2);
        cout << s << '\n';
    }
    return 0;
}
