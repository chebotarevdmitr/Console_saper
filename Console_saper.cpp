#include <iostream>

using namespace std;

int field[100][100];
// -1 mine (mina)
// 0-8 cell (kletka)

// pole igrorka  ->(field_p)<-
int field_p[100][100];
// -2  -clous
// -1  -flag
// 0-8 -opened    
/* funkciya kotoraya chistit i vivodit pole na ekran 
   -> print_field <- (){system("cls");for()...}
*/
const int N = 5, M = 5, K = 5;
void print_field() {
    system("cls");
    cout << "  ";
    for (int i = 0; i < M; ++i) {
        cout << " " << i + 1;
        if (i + 1 < 10)cout << ' ';
    }
    cout << endl;
    for (int i = 0; i < N; i++) {
        cout << i + 1 << " ";
        if (i + 1 < 10)cout << ' ';
        for (int j = 0; j < M; j++) {
            if (field_p[i][j] == -2)cout << "_  ";
            else if (field_p[i][j] == -1)cout << "f  ";
            else if (field_p[i][j] == -3)cout << "*  ";
            else cout << field_p[i][j] << "  ";
        }
        cout << endl;
    }
    cout << endl << endl << endl << endl;
}

//funkciya ->dfs<- "obhod v glubinu"(DIIP FIRST SEARCH)
//pri otkritii pustoy kletki otkrivautsya sosednie 
//bezopastnie kletki

void dfs(int x, int y) {
    if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y]> -2) return;
    field_p[x][y] = field[x][y];
    if (field[x][y] > 0)return;
    for (int i2 = x - 1; i2 <= x + 1; ++i2) {
        for (int j2 = y - 1; j2 <= y + 1; ++j2) {
            if (i2 != x || j2 != y) dfs(i2, j2);
        }
    }
}

//funkciya otkritiya kletki ->open_cell<-
//true ne vzorvalis
bool open_cell(int x, int y) {
    if (field[x][y] == -1) return false;
    if (field[x][y] == 0) {
        field_p[x][y] = field[x][y];
        return true;
    }
    dfs(x, y);
}

//funkciya -> is_win <- proverka viigrali ili net
bool is_win() {
    int opened = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if (field_p[i][j] >= 0) opened++;
        }
    }
    return(N * M - K == opened);
}

int main()
{
    while (true) {
        srand(time(0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                field[i][j] = 0;
                field_p[i][j] = -2;
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

        while (true)
        {
            print_field();
            cout << "Enter comand:";
            /*
              \o (X Y) open
              \f (X Y) flag
              \n new game
              \q finish the game
            */
            string comand;
            cin >> comand;
            if (comand == "\\o") {
                // Vvod koordinat
                int x, y;
                cin >> x >> y;
                --x; --y;
                // otkroem kletki
                if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
                if(! open_cell(x, y)) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            if (field_p[i][j] == -1)field_p[i][j] = -2;
                            if (field[i][j] == -1) field_p[x][y] = -3;
                        }
                    }
                    print_field();
                    cout << " Vi proigrali,\nchtob nacat novuyu igru vvedite lyubuyu stroku";
                    string s;
                    cin >> s;
                    break;
                }
                if (is_win()) {
                    for (int i = 0; i < N; i++) {
                        for (int j = 0; j < M; j++) {
                            if (field_p[i][j] == -1)field_p[i][j] = -2;
                            if (field[i][j] == -1) field_p[x][y] = -3;
                        }
                    }
                    print_field();
                    cout << " Vi viigrali!!!!!,\nchtob nacat novuyu igru vvedite lyubuyu stroku";
                    string s;
                    cin >> s;
                    break;
                }
            }
            else if (comand == "\\f") {
                // Vvod koordinat
                int x, y;
                cin >> x >> y;
                --x; --y;
                if (x < 0 || x >= N || y < 0 || y >= M || field_p[x][y] >= 0) continue;
                //put flag
                if (field_p[x][y] == -1)  field_p[x][y] == -2;
                else field_p[x][y] = -1;
            }

            else if (comand == "\\n") {
                break;
            }
            else if (comand == "\\q") {
                return 0;
            }
        }
    }
    system("pause>0");
}
