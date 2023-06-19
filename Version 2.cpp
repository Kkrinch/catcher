#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

const int width = 20;
const int height = 20;
const int initialSpeed = 200;  // Начальная скорость падения фруктов (в миллисекундах)

bool gameOver;
int catcherX, fruitX, fruitY, score, speed;

void Setup()
{
    gameOver = false;
    catcherX = width / 2;
    fruitX = rand() % width;
    fruitY = 0;
    score = 0;
    speed = initialSpeed;
}

void Draw()
{
    system("cls");
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == fruitY && j == fruitX)
            {
                // Изменяем цвет фрукта на желтый
                cout << "\x1b[33mF\x1b[0m";
            }
            else if (i == height - 1 && j == catcherX)
            {
                // Изменяем цвет кетчера на зеленый
                cout << "\x1b[32mC\x1b[0m";
            }
            else
                cout << " ";
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    if (_kbhit())
    {
        switch (_getch())
        {
            case 'a':
                if (catcherX > 0)
                    catcherX--;
                break;
            case 'd':
                if (catcherX < width - 1)
                    catcherX++;
                break;
            case 'x':
                gameOver = true;
                break;
        }
    }
}

void Logic()
{
    fruitY++;
    if (fruitY == height - 1 && fruitX == catcherX)
    {
        score++;
        fruitX = rand() % width;
        fruitY = 0;
        if (score % 2 == 0)
        {
            speed -= 10;  // Увеличение скорости падения фруктов на 10 миллисекунд
            if (speed <= 0)
                speed = 1;  // Ограничение минимальной скорости в 1 миллисекунду
        }
    }
    else if (fruitY >= height)
    {
        gameOver = true;
    }
}

void ShowMenu()
{
    cout << "=== Fruit Catcher Game ===" << endl;
    cout << "Press Enter to start the game or X to exit." << endl;
}

bool CheckRestart()
{
    char choice;
    cout << "Do you want to play again? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

int main()
{
    srand(time(0));
    bool restart = true;

    while (restart)
    {
        Setup();
        ShowMenu();
        char menuChoice = _getch();

        if (menuChoice == 'x' || menuChoice == 'X')
        {
            restart = false;
            continue;
        }

        while (!gameOver)
        {
            Draw();
            Input();
            Logic();
            this_thread::sleep_for(chrono::milliseconds(speed));
        }

        cout << "Game Over!" << endl;
        cout << "Your Score: " << score << endl;
        restart = CheckRestart();
    }

    cout << "Thanks for playing!" << endl;
    return 0;
}
