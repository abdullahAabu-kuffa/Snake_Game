// Snake_Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <ctime>
#include <conio.h>
#include<windows.h>
using namespace std;
void shift_right(int arr[], int size) {
    for(int i = size-2; i >= 0; i--){
        arr[i + 1] = arr[i];
    }
}
// properties ...................................................
enum direction { Top = 1, Donw, Right, Left };
struct map { int width, height, fruitx, fruity; };
struct snake { int headx, heady, tail_n,tailx[50],taily[50]; direction dir; };
struct player { int score; bool lose; };

map map1; snake snake1; player player1;
void generate_fruit() {
    srand(time(NULL));
    map1.fruitx = rand() % (map1.width - 2) + 1;
    map1.fruity = rand() % (map1.height - 2) + 1;
}
void starting() {
    map1.height =40 ;
    map1.width = 40;
    generate_fruit();

    snake1.headx = map1.width / 2;
    snake1.heady = map1.height / 2;
    snake1.tail_n = 0;

    player1.score = 0;
    player1.lose = false;
}
void draw() {
    system("cls");
    for (int i = 0; i < map1.height; i++){
        for (int j = 0; j < map1.width; j++){
            if (i == 0 || i == map1.height - 1)cout << "*";
            else if (j == 0 || j == map1.width - 1)cout << "*";
            else if (i == snake1.heady && j == snake1.headx) cout << "O";
            else if (i == map1.fruity && j == map1.fruitx) cout << "$";
            else {
                bool p = 0;
                for (int k = 0; k < snake1.tail_n; k++) {
                    if (snake1.tailx[k] == j && snake1.taily[k] == i) {
                        cout << "o";
                        p = 1;
                        break;
                    }
                }
                if (!p)cout << " ";
            }
        }
        cout << endl;
    }
   
    cout << "the score of player : " << player1.score << endl;
}
void command() {
    if (_kbhit()) {
        char c = _getch();   
        switch (c) {
        case 'w':snake1.dir = Top; break;
        case 's':snake1.dir = Donw; break;
        case 'd':snake1.dir = Right; break;
        case 'a':snake1.dir = Left; break;
        case 'x':exit(0);
        }
    }
}
void move() {
    shift_right(snake1.tailx, 50);
    shift_right(snake1.taily, 50);
    snake1.tailx[0] = snake1.headx;
    snake1.taily[0] = snake1.heady;

    switch (snake1.dir) {
    case Top:snake1.heady--; break;
    case Donw:snake1.heady++; break;
    case Right:snake1.headx++; break;
    case Left:snake1.headx--; break;
    }
    if (snake1.heady > map1.height || snake1.heady < 0 || snake1.headx >= map1.width || snake1.headx < 0)
        player1.lose = true;
    if (snake1.heady == map1.fruity && snake1.headx == map1.fruitx) {
        generate_fruit();
        player1.score += 5;
    snake1.tail_n++;
    }
}
int main() {
    starting();
    while (!player1.lose) {
        draw();
        command();
        move();
        Sleep(50);
    }
    cout << "you are loser." << endl;
   // std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
