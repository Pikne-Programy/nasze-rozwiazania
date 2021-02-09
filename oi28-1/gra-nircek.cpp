#include <bits/stdc++.h>
using namespace std;

#define P static_cast<size_t>(1e5)
#define H static_cast<size_t>(2e6)

#define DEBUG false

struct hole {
  size_t i;
  size_t p;
  size_t v = UINT_MAX;
} holes[H + P + 2], *platforms[P + 2], *mem;

array<size_t, P + 2> results;

struct _IndexComp {
  bool operator()(const struct hole &left, const struct hole &right) {
    return left.i < right.i;
  }
  bool operator()(const size_t &left, const struct hole &right) {
    return left < right.i;
  }
} IndexComp;

typedef pair<size_t, struct hole *> PAIR;
priority_queue<PAIR, vector<PAIR>, std::greater<PAIR>> pq;

size_t start = 0, n, z;
void write(struct hole *hole, size_t value) {
  if(DEBUG)
    cerr << "trying to write p" << hole->p << 'i' << hole->i << 'v' << hole->v
         << " value " << value << ".\n";
  if(hole->v > value) {
    if(DEBUG)
      cerr << "written\n";
    hole->v = value;
    pq.push({value, hole});
  }
}
void write_range(size_t platform, size_t a, size_t b, size_t value) {
  if(DEBUG)
    cerr << "trying to range p" << platform << 'a' << a << 'b' << b << 'v'
         << value << ".\n";
  struct hole *h1a =
      upper_bound(platforms[platform], platforms[platform + 1], a, IndexComp);
  if(DEBUG)
    cerr << "got a=p" << h1a->p << 'i' << h1a->i << 'v' << h1a->v << " and ";
  struct hole *h1b =
      upper_bound(platforms[platform], platforms[platform + 1], b, IndexComp);
  if(DEBUG)
    cerr << "got b=p" << h1b->p << 'i' << h1b->i << 'v' << h1b->v << ".\n";
  while(h1a != h1b)
    write(h1a++, value);
  if(DEBUG)
    cerr << "Ended range.\n";
}
void write_prev(size_t platform, size_t index, size_t value) {
  if(platform > n) {
    if(DEBUG)
      cerr << "Skipping prev...\n";
    return;
  }
  if(DEBUG)
    cerr << "Writting previous of p" << platform << 'i' << index << 'v' << value
         << ".\n";
  struct hole *prev = upper_bound(platforms[platform], platforms[platform + 1],
                          index, IndexComp) -
                      1;
  write(prev, value + 1);
  write_range(platform - 1, prev->i, index, value);
  if(DEBUG)
    cerr << "Ended previous\n";
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  results.fill(UINT_MAX);
  cin >> n >> z >> z;  // X is useless
  mem = holes;
  platforms[0] = mem++;
  for(size_t p = 1; p <= n; ++p) {
    size_t k, ki;
    cin >> k;
    if(DEBUG)
      cerr << "Platform p" << p << '(' << k << ',' << mem << "): ";
    if(k == 0) {
      if(DEBUG)
        cerr << "truncating...";
      start = p;
    }
    mem->p = p;
    mem->i = 0;
    platforms[p] = mem++;
    if(DEBUG)
      cerr << "0 ";
    while(k--) {
      mem->p = p;
      cin >> mem->i;
      if(DEBUG)
        cerr << mem->i << ' ';
      ++mem;
    }
    if(DEBUG)
      cerr << '\n';
  }
  if(DEBUG)
    cerr << '\n';
  mem->p = n + 1;
  mem->i = 0;
  platforms[n + 1] = mem++;
  mem->p = n + 2;
  mem->i = 0;
  platforms[n + 2] = mem;
  for(size_t p = n; p != start; --p) {
    struct hole *last = platforms[p + 1] - 1;
    write(last, 1);
    write_range(p - 1, last->i, UINT_MAX, 0);
    if(DEBUG)
      cerr << '\n';
  }
  while(z--) {
    size_t k;
    cin >> k;
    if(k <= start) {
      cout << "0\n";
    } else {
      while(results[k] == UINT_MAX) {
        pair<size_t, struct hole *> a = pq.top();
        pq.pop();
        struct hole *h = a.second;
        if(a.first == h->v) {
          if(DEBUG)
            cerr << "Got from pq p" << h->p << 'i' << h->i << 'v' << h->v
                 << ".\n";

          if(h->i == 0) {
            if(DEBUG)
              cerr << "Got result for platform " << h->p << ": " << h->v - 1
                   << '\n';
            results[h->p] = h->v - 1;
          } else {
            write_range(h->p - 1, (h - 1)->i, h->i, h->v);
            write(h - 1, h->v + 1);
            write_prev(h->p + 1, h->i, h->v);
          }
          if(DEBUG)
            cerr << '\n';
        } else if(DEBUG)
          cerr << "Skip from pq p" << h->p << 'i' << h->i << 'v' << h->v
               << " with value " << -a.first << ".\n\n";
      }
      cout << results[k] << '\n';
    }
  }
  return 0;
}
