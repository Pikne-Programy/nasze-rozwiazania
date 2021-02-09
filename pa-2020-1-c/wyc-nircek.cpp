// https://sio2.mimuw.edu.pl/c/pa-2020-1/s/421359/source/
// A C++ Program to implement A* Search Algorithm
// modified https://www.geeksforgeeks.org/a-search-algorithm/
#include <bits/stdc++.h>
using namespace std;
#define ROW 2001
#define COL 2001
int M, N;
typedef struct Pair {
  int first;
  int second;
  bool operator<(const struct Pair &other) const {
    return (first != other.first) ? (first < other.first)
                                  : (second < other.second);
  }
} Pair;
typedef struct pPair {
  double first;
  Pair second;
  bool operator<(const struct pPair &other) const {
    return (first != other.first) ? (first < other.first)
                                  : (second < other.second);
  }
} pPair;
int SRC_F = 0, SRC_S = 0, DEST_F, DEST_S;
char grid[ROW][COL];

struct cell {
  int parent_i, parent_j;
  double f, g, h;
};

bool isValid(int row, int col) {
  return (row >= 0) && (row < M) && (col >= 0) && (col < N);
}

bool isUnBlocked(int row, int col) { return grid[row][col] == '.'; }

bool isDestination(int row, int col) { return row == DEST_F && col == DEST_S; }
double calculateHValue(int row, int col) {
  return ((double) sqrt(
      (row - DEST_F) * (row - DEST_F) + (col - DEST_S) * (col - DEST_S)));
}

unsigned long long tracePath(cell *cellDetails[]) {
  int row = DEST_F;
  int col = DEST_S;
  unsigned long long l = 0;
  while(!(cellDetails[row][col].parent_i == row &&
          cellDetails[row][col].parent_j == col)) {
    ++l;
    int temp_row = cellDetails[row][col].parent_i;
    int temp_col = cellDetails[row][col].parent_j;
    row = temp_row;
    col = temp_col;
  }
  return l;
}

unsigned long long aStarSearch() {
  if(isValid(SRC_F, SRC_S) == false) {
    return 0;
  }

  if(isValid(DEST_F, DEST_S) == false) {
    return 0;
  }

  if(isUnBlocked(SRC_F, SRC_S) == false ||
      isUnBlocked(DEST_F, DEST_S) == false) {
    return 0;
  }

  if(isDestination(SRC_F, SRC_S) == true) {
    return 0;
  }
  bool closedList[ROW][COL];
  memset(closedList, false, sizeof(closedList));

  cell *cellDetails[ROW];
  for(unsigned long long i = 0; i < ROW; ++i)
    cellDetails[i] = new cell[COL];

  int i, j;

  for(i = 0; i < ROW; i++) {
    for(j = 0; j < COL; j++) {
      cellDetails[i][j].f = FLT_MAX;
      cellDetails[i][j].g = FLT_MAX;
      cellDetails[i][j].h = FLT_MAX;
      cellDetails[i][j].parent_i = -1;
      cellDetails[i][j].parent_j = -1;
    }
  }

  i = SRC_F, j = SRC_S;
  cellDetails[i][j].f = 0.0;
  cellDetails[i][j].g = 0.0;
  cellDetails[i][j].h = 0.0;
  cellDetails[i][j].parent_i = i;
  cellDetails[i][j].parent_j = j;

  set<pPair> openList;

  openList.insert({0.0, {i, j}});

  bool foundDest = false;

  while(!openList.empty()) {
    pPair p = *openList.begin();

    openList.erase(openList.begin());

    i = p.second.first;
    j = p.second.second;
    closedList[i][j] = true;

    double gNew, hNew, fNew;

    if(isValid(i - 1, j)) {
      if(isDestination(i - 1, j)) {
        cellDetails[i - 1][j].parent_i = i;
        cellDetails[i - 1][j].parent_j = j;
        return tracePath(cellDetails);
      } else if((!closedList[i - 1][j]) && isUnBlocked(i - 1, j)) {
        gNew = cellDetails[i][j].g + 1.0;
        hNew = calculateHValue(i - 1, j);
        fNew = gNew + hNew;
        if(cellDetails[i - 1][j].f == FLT_MAX ||
            cellDetails[i - 1][j].f > fNew) {
          openList.insert({fNew, {i - 1, j}});
          cellDetails[i - 1][j].f = fNew;
          cellDetails[i - 1][j].g = gNew;
          cellDetails[i - 1][j].h = hNew;
          cellDetails[i - 1][j].parent_i = i;
          cellDetails[i - 1][j].parent_j = j;
        }
      }
    }

    if(isValid(i + 1, j)) {
      if(isDestination(i + 1, j)) {
        cellDetails[i + 1][j].parent_i = i;
        cellDetails[i + 1][j].parent_j = j;
        return tracePath(cellDetails);
      } else if((!closedList[i + 1][j]) && isUnBlocked(i + 1, j)) {
        gNew = cellDetails[i][j].g + 1.0;
        hNew = calculateHValue(i + 1, j);
        fNew = gNew + hNew;
        if(cellDetails[i + 1][j].f == FLT_MAX ||
            cellDetails[i + 1][j].f > fNew) {
          openList.insert({fNew, {i + 1, j}});
          cellDetails[i + 1][j].f = fNew;
          cellDetails[i + 1][j].g = gNew;
          cellDetails[i + 1][j].h = hNew;
          cellDetails[i + 1][j].parent_i = i;
          cellDetails[i + 1][j].parent_j = j;
        }
      }
    }
    if(isValid(i, j + 1) == true) {
      if(isDestination(i, j + 1)) {
        cellDetails[i][j + 1].parent_i = i;
        cellDetails[i][j + 1].parent_j = j;
        return tracePath(cellDetails);
      } else if((!closedList[i][j + 1]) && isUnBlocked(i, j + 1)) {
        gNew = cellDetails[i][j].g + 1.0;
        hNew = calculateHValue(i, j + 1);
        fNew = gNew + hNew;
        if(cellDetails[i][j + 1].f == FLT_MAX ||
            cellDetails[i][j + 1].f > fNew) {
          openList.insert({fNew, {i, j + 1}});
          cellDetails[i][j + 1].f = fNew;
          cellDetails[i][j + 1].g = gNew;
          cellDetails[i][j + 1].h = hNew;
          cellDetails[i][j + 1].parent_i = i;
          cellDetails[i][j + 1].parent_j = j;
        }
      }
    }
    if(isValid(i, j - 1)) {
      if(isDestination(i, j - 1)) {
        cellDetails[i][j - 1].parent_i = i;
        cellDetails[i][j - 1].parent_j = j;
        return tracePath(cellDetails);
      } else if((!closedList[i][j - 1]) && isUnBlocked(i, j - 1)) {
        gNew = cellDetails[i][j].g + 1.;
        hNew = calculateHValue(i, j - 1);
        fNew = gNew + hNew;
        if(cellDetails[i][j - 1].f == FLT_MAX ||
            cellDetails[i][j - 1].f > fNew) {
          openList.insert({fNew, {i, j - 1}});
          cellDetails[i][j - 1].f = fNew;
          cellDetails[i][j - 1].g = gNew;
          cellDetails[i][j - 1].h = hNew;
          cellDetails[i][j - 1].parent_i = i;
          cellDetails[i][j - 1].parent_j = j;
        }
      }
    }
  }
  return -1;
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  unsigned long long n;
  cin >> M >> N >> n;
  cin.get();
  DEST_F = M - 1;
  DEST_S = N - 1;
  for(unsigned long long i = 0; i < M; ++i)
    cin.getline(grid[i], COL);
  unsigned long long droga = aStarSearch();
  vector<pair<int, int>> friends;
  unsigned long long a, b;
  unsigned long long min_wejsc = M + N - 2;
  unsigned long long zejsc = (droga - min_wejsc) / 2;
  unsigned long long wejsc = min_wejsc + zejsc;
  unsigned long long m = ULLONG_MAX, mm = 0;  // value, ilość
  unsigned long long value;
  while(n--) {
    cin >> a >> b;
    value = a * wejsc + b * zejsc;
    if(value == m)
      ++mm;
    else if(value < m) {
      m = value;
      mm = 1;
    }
  }
  cout << m << ' ' << mm << '\n';
  return 0;
}
