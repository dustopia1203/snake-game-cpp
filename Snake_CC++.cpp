#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <iomanip>

using namespace std;

const int height = 20;
const int width = 100;
bool gameOver;
int x, y, fruit_x, fruit_y, score, maxScore;
int tail_x[100], tail_y[20];
int pre_x, pre_y, pre__x, pre__y;
char direction, head, selection;

void Setup()
{
	srand(time(0));
	score = 0;
	head = 'O';
	direction = ' ';
    gameOver = false;
    x = width / 2;
    y = height / 2;
	fruit_x = rand() % (width - 1) + 1;
    fruit_y = rand() % (height - 1) + 1;
    selection = 'Y';
}

void Draw()
{
    system("CLS");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
                cout << "#";
            else if (i == y && j == x)
                cout << "O";
            else if (i == fruit_y && j == fruit_x)
                cout << "*";
            else
            {
            	bool print = false;
            	for (int k = 0; k < score; k++)
            	{
            		if (i == tail_y[k] && j == tail_x[k])
            		{
            			cout << "o";
            			print = true;
            		}
				}
				if (!print)
					cout << " ";
			}
        }
        cout << endl;
    }
	cout << "Your score: " << score << endl << "Current Direction: " << head << endl;;
}

void Input()
{
	char tmp = direction;
	if (kbhit())
	{
		direction = getch();
		if (tmp == 'w' && direction == 's' || tmp == 's' && direction == 'w' || tmp == 'a' && direction == 'd' || tmp == 'd' && direction == 'a')
			direction = tmp;
	}
		
}

void Logic()
{
	pre_x = tail_x[0];
	pre_y = tail_y[0];
	tail_x[0] = x;
	tail_y[0] = y;
	for (int i = 1; i < score; i++)
	{
		pre__x = tail_x[i];
		pre__y = tail_y[i];
		tail_x[i] = pre_x;
		tail_y[i] = pre_y;
		pre_x = pre__x;
		pre_y = pre__y;
	}
	switch(direction) 
	{
		case 'w':
			head = '^';
			y--;
			break;
		case 'a':
			head = '<';
			x--;
			break;
		case 's':
			head = 'v';
			y++;
			break;
		case 'd':
			head = '>';
			x++;
			break;
		default:
			break;
	}
	for (int i = 0; i < score; i++)
		if (x == tail_x[i] && y == tail_y[i])
			gameOver = true;
	if (x == 0 || y == 0 || x == width - 1 || y == height - 1)
		gameOver = true;
	if (x == fruit_x && y == fruit_y)
	{
		++score;
		maxScore = (maxScore < score) ? score : maxScore;
		fruit_x = rand() % width;
    	fruit_y = rand() % height;
	}	
}

int main()
{
	// Hide cursor on console
	HANDLE hStdOut = NULL;
    CONSOLE_CURSOR_INFO curInfo;
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleCursorInfo(hStdOut, &curInfo);
    curInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hStdOut, &curInfo);

	cout << "-----------------------------Snake Game----------------------------\n";
	cout << "               Tutorial: W-up, A-left, S-down, D-right             \n";
	cout << "---------------------Press any button to start.--------------------\n";
	getch();
	while (selection != 'N') 
	{
		Setup();
		while (!gameOver)
    	{
        	Draw();
        	Input();
        	Logic();
        	Sleep(20);
		}
    	cout << "Game Over!" << endl;
    	cout << "Your record: " << maxScore << endl;
    	cout << "Do you want to restart? (Y/N): ";
    	cin >> selection;
    	selection = toupper(selection);
    	if (selection == 'N')
    		cout << "Thanks for playing!" << endl;
    	else if (selection == 'Y')
    		continue;
    	else 
    	{
    		cout << "Wrong request! The game will be closed!" << endl;
    		break;
		}
	}
    return 0;
}
