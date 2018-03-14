#include <iostream>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <time.h>
#include <fstream>

void moveCurs(int x, int y);
void menu(int _speed);
void field();
void food();
void drawField();
bool isFoodField();
bool dead();
void game(int speed_);
void gameOver();
void drawRecords();
int Complexity(int Speed);
void Bonusfood();
bool isBonusFoodField();
void Pause();
void drawPauseField();
void exit();
void extra();
void resetRecords();
void about();