#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <chrono>
#include <thread>

using namespace std;

const int width = 20;
const int height = 20;
int initialSpeed = 200;  // Начальная скорость падения фруктов (в миллисекундах)
bool gameOver;
int catcherX, fruitX, fruitY, score, speed;
bool fruitEaten = false;

void Setup();

void Speed ();

void PrintBorder();

void Draw();

void UpdateScore();

void Input();

void Logic();

void ShowMenu();

void Levels ();

bool CheckRestart();

int main()
{
    srand(time(0)); //  Генератор случайного место нахождения фруктов.
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

        Levels();

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

void Levels ()
{
    speed = initialSpeed;
    int choice;
    cout << "Choose gaming mode\n" << "1.Easy mode\n" << "2.Normal mode\n" << "3.Hard mode" << endl;
    cin >> choice;
    if (choice == 1)
       speed = 500;
    else if (choice == 2)
        speed = 350;
    else if (choice == 3)
        speed = 200;

}

void Setup()
{
    gameOver = false;
    catcherX = width / 2;
    fruitX = rand() % width;
    fruitY = 0;
    score = 0;
}

void PrintBorder()
{
    cout << string(width + 2, '#') << endl;
}

void UpdateScore()
{
    cout << "Score: " << score << endl;
}

void Draw()
{
    system("cls"); // Обновление екрана (Каждое движение)

    PrintBorder();

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
                cout << "#";
            if (i == fruitY && j == fruitX)
            {
                // Изменяем цвет фрукта на желтый (ANSI)
                cout << "\x1b[33mO\x1b[0m";
            }

            else if (i == height - 1 && j == catcherX)
            {
                // Изменяем цвет кетчера на зеленый (ANSI)
                cout << "\x1b[32m^\x1b[0m";
            }
            else
                cout << " ";
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    PrintBorder();
    UpdateScore();
}

//void Input()
//{
//    if (_kbhit())
//    {
//        switch (_getch())
//        {
//            case 'a':
//                if (catcherX > 0)
//                    catcherX--;
//                break;
//            case 'd':
//                if (catcherX < width - 1)
//                    catcherX++;
//                break;
//            case 'x':
//                gameOver = true;
//                break;
//        }
//    }
//}

void Input()
{
    if (_kbhit())
    {
        char input = (_getch());

        if (input == 'a')
        {
            if (catcherX > 0)
                catcherX--;
        }
        else if (input == 'd')
        {
            if (catcherX < width - 1)
                catcherX++;
        }
        else if (input == 'x')
        {
            gameOver = true;
        }
    }
}

void Speed ()
{
    if (score % 2 == 0)
    {
        speed -= 10;  // Увеличение скорости падения фруктов на 10 миллисекунд
        if (speed <= 0)
            speed = 1;  // Ограничение минимальной скорости в 1 миллисекунду
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
       Speed();
    }
    else if (fruitY >= height)
    {
        gameOver = true;
    }
}
void ShowMenu()
{
    cout << "=== Fruit Catcher Game ===" << endl;
    cout << "Press Enter to choice game mode or X to exit." << endl;
}

bool CheckRestart()
{
    char choice;
    cout << "Do you want to play again? (Y/N): ";
    cin >> choice;
    return (choice == 'Y' || choice == 'y');
}

