#include <iostream>

using namespace std;

int field[100][100];
const int N = 9, M = 9, K = 10;

int main()
{
    srand(time(0));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            field[i][j] = 0;
        }
    }
    for (int i = 0; i < K; ++i) {
        while (true) {
            int x = rand() % N;
            int y = rand() % M;
            if (field[x][y] != -1) {
                field[x][y] = -1;
                break;
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] != -1) {
                field[i][j] = 0;
                for (int i2 = i - 1; i2 <= i + 1; ++i2) {
                    for (int j2 = j - 1; j2 <= j + 1; ++j2) {
                        if (i2 >= 0 && i2 < N && j2 >= 0 && j2 <= M &&
                            field[i2][j2] == -1) ++field[i][j];
                    }
                }
            }
        }
       
        
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field[i][j] == -1)cout << "*" << " ";
            else cout<< field[i][j]<<" ";
        }
        cout << endl;
    }
  
}
