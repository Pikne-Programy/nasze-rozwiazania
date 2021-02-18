#include <bits/stdc++.h>
using namespace std;
constexpr int limit = 20; // 100?
bitset<limit> sq[limit];  // ściana to 0
int N, K;                 // celuje w 5, a potem w 10
uint64_t _reku(size_t i, size_t j)
{
    if(i+1==N && j+1==N)
        return 1;
    uint64_t suma = 0;
    if (i+1!=N&&sq[i + 1][j])
        suma += _reku(i + 1, j);
    if (j+1!=N&&sq[i][j + 1])
        suma += _reku(i, j + 1);
    return suma;
}
uint64_t reku(size_t i = 0, size_t j = 0)
{
    if (sq[0][0] && sq[N - 1][N - 1])
        return _reku(i, j);
    return 0;
}
void randomise()
{
    for (size_t i = 0; i < N; ++i)
        for (size_t j = 0; j < N; ++j)
            sq[i][j] = rand() & 3;
}
void randomise_diagonal()
{
    for (size_t i = 0; i < N; ++i)
        sq[i][N - i - 1] = rand() & 1;
}
void randomise_row(size_t j = 1)
{
    for (size_t i = j ? 0 : 1; i < N; ++i)
        sq[i][j] = rand() & 1;
}
void init()
{
    for (size_t i = 0; i < N; ++i)
        sq[i].set();
}
void print()
{
    cout << N << '\n';
    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            cout << (sq[i][j] ? '.' : '#');
        }
        cout << '\n';
    }
}

int randix[] = {0, 0, 0, 0, 0, 0, 0, 10000, 30000, 15000, 45000, 50000};
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    srand(2);
    cin >> K;
    for (N = 0; N < 12; ++N)
    {
        init();
        while (randix[N]--)
        {
            randomise_diagonal();
            if (K == reku())
            {
                print();
                return 0;
            }
            for (size_t j = 0; j < (N + 1) / 2; ++j)
            {
                randomise_row(j);
                if (K == reku())
                {
                    print();
                    return 0;
                }
            }
        }
    }
    N = 9;
    while (true)
    {
        randomise();
        if (K == reku())
        {
            print();
            return 0;
        }
    }
    return 0;
}
