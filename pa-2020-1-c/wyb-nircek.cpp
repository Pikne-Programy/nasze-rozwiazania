// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/411116/source/
#include <iostream>
using namespace std;

/*
19
3B 4B 5B 4C 5C 3C 1A 5A 5C 3A 5A 2C 1B 2A 5B 5C 2B 1C 4A

20
2B 4B 4C 5A 5C 5C 4A 1B 3A 4A 2A 3B 1B 1C 1A 5A 2C 1B 5B 3C
*/
int t[5][3];
int main() {
  int n;
  cin >> n;
  int s = 15;
  while(n--) {
    size_t i;
    char z;
    cin >> i >> z;
    int p = (i == 5 ? 2 : 1);
    if((++t[i - 1][z - 'A']) == p){
      //cerr << t[i - 1][z - 'A'] << ' ';
      --s;
    }
    //cerr << i << z << s << endl;
  }
  //cerr << s << '\n';
  cout << (s ? "NIE\n" : "TAK\n");
  return 0;
}
