#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;
bool End;
const int width = 20;
const int height = 17;
int x, y, L, B, score;
int tailX[100], tailY[100];
int nTail=0;
char dir;
void Setup() {
    End= false;
    dir='Stop';
    x = width/2;
    y = height/2;
    L = rand()%width;
    B = rand()%height;
    score = 0;
}
void Draw() {
    system("cls");
    for (int i = 0; i < width+2; i++)
        cout <<"-";
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0)
                cout << "|";
            if (i == y && j == x)
                cout << "O";
            else if (i == B && j == L)
                cout << "X";
            else {
                bool print = false;
                for (int k = 0; k < nTail; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        cout << "O";
                        print = true;
                    }
                }
                if (!print) cout << " ";
            }

            if (j == width - 1)
                cout << "|";
        }
        cout << endl;
    }
    for (int i = 0; i < width + 2; i++)
        cout << "_";
    cout << endl;
    cout << "Score: " << score << endl;
}
void Input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                dir='L';
                break;
            case 'd':
                dir='R';
                break;
            case 'w':
                dir='U';
                break;
            case 's':
                dir='D';
                break;
            case 'x':
                End= true;
                break;
        }
    }
}
void Logic() {
    int px= tailX[0];
    int py= tailY[0];
    int p2x, p2y;
    tailX[0] = x;
    tailY[0] = y;
    for (int i = 1; i < nTail; i++) {
        p2x= tailX[i];
        p2y= tailY[i];
        tailX[i] = px;
        tailY[i] = py;
        px= p2x;
        py= p2y;
    }
    switch (dir) {
        case 'L':
            x--;
            break;
        case 'R':
            x++;
            break;
        case 'U':
            y--;
            break;
        case 'D':
            y++;
            break;
        default:
            break;
    }
    if (x >= width) x = 0; 
    else if (x < 0) x = width - 1;
    if (y >= height) y = 0; 
    else if (y < 0) y = height - 1;

    for (int i = 0; i < nTail; i++)
        if (tailX[i] == x && tailY[i] == y)
            End= true;
    if (x == L && y == B) {
        score += 1;
        L = rand() % width;
        B = rand() % height;
        nTail++;
    }
}
int main() {
    Setup();
    while (!End) {
        Draw();
        Input();
        Logic();
        Sleep(100);
    }
}
