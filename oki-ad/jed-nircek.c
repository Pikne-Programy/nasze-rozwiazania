#include <stdio.h>
unsigned n, x = 0, a;
int main() {
  scanf("%d", &n);
  while(n--) {
    scanf("%d", &a);
    x ^= a;
  }
  printf("%d", x);
  return 0;
}
