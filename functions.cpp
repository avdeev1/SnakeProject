#include "header.h"
#include "mmsystem.h"
#include "glut.h"

DWORD fdwSound = SND_ASYNC | SND_FILENAME;

using namespace std;

ifstream fin;
fstream fout;

// ��������� �������� ������
const int DIR_RIGHT = 1;		
const int DIR_LEFT = -1;
const int DIR_UP = 2;
const int DIR_DOWN = -2;


char a[400][400]; //������ ����
char b[400][400];
int co_x[400], co_y[400], foodx, foody, bfoodx, bfoody; //���������� ������ � ���
const int height = 30, width = 70; // ������ � ������
int num = 3; // ��������� ����� ������
int n; // ��� ������ ������������� �����
string winner; // ��� ����� ����������
string name;
int direction = 1; //���������� �������� ���������� �������
int score = 0; // ���������� ��������� �����
const int EasySpeed = 250;
const int MediumSpeed = 200;
const int HardSpeed = 150;
const int FatalSpeed = 100;
int mspeed = 250;
int _speed;
int coy = 10;				// ���������� �, ����������� ��� ����������� ������� � ����


void moveCurs(int x, int y) //������� ����������� ������� � �������� �����
{
		COORD coord;
		coord.X = x;
		coord.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void menu(int _speed)			
{
	coy = 10;
	//������� ����
	system("cls");
	//Form1->MediaPlayer1->FileName = "C:\\Users\\����\\Documents\\Visual Studio 2012\\Projects\\Project\\Project\\Mario_Theme.ogg";
	//Form1->MediaPlayer1->Open();
	//Form1->MediaPlayer1->Play();
	moveCurs (40, 10);
	cout << "PLAY" << endl;						// ����
	moveCurs (40, 11);
	if (_speed == 250)
		cout << "COMPLEXITY (EASY)" << endl;	// ���������
	else if (_speed == 200)
		cout << "COMPLEXITY (MEDIUM)" << endl;
	else if (_speed == 150)
		cout << "COMPLEXITY (HARD)" << endl;
	else if (_speed == 100)
		cout << "COMPLEXITY (FATAL)" << endl;
	moveCurs (40, 12);
	cout << "TABLE OF RECORDS" << endl;			// ������� ��������
	moveCurs (40, 13);
	cout << "EXTRA" << endl;					// ���������
	moveCurs (40,14);
	cout << "EXIT" << endl;						// ����� �� ����

	moveCurs(40,10);
	while (_getch()!=13)			// ����������� ������� � ������� ����
	{
		int kb_ = _getch();
		switch (kb_)
		{
		case 80: 
			coy++;
			coy == 15 ? moveCurs(40,10),coy = 10 : moveCurs(40, coy);		// �������� ������� ��� ������� ������� ����
			break;

		case 72:
			coy--;
			coy == 9 ? moveCurs(40,14),coy = 14 : moveCurs(40, coy);		// ���������� ������� ��� ������� ������� �����
			break;
		}
	}

	//int kb = _getch();
	switch (coy)					// ����� ������� �� ���������� �
	{
	case 10:
		field();						// ����
		drawField();
		game(_speed);
		break;
	case 11:
		mspeed = Complexity(_speed);	// ���������
		coy = 10;
		menu(mspeed);
		break;
	case 12:
		drawRecords();					// ������� �������� 
		coy = 10;
		menu(_speed);
		break;
	case 13:
		extra();						// �������������� �����������
		menu(_speed);
		break;
	case 14:
		exit(0);						// �����
		break;
	}
}

void field()			//����������� ����� ����
{
	// ��������� ����������� ���� � ������
	for (int i = 0; i <= height; ++i) 
            for (int j = 0; j <= width; ++j)
                a[i][j] = (i == 0 || j == 0 || i == height || j == width ? '#' : ' ');
	
	// ����������� ���� ����� �����
	for (int i = 0; i <= height; ++i) 
            for (int j = 0; j <= width; ++j)
                b[i][j] = (i == 0 || j == 0 || i == height || j == width ? '#' : ' ');
	
	//��������� ������
	num = 3;

	co_x[0] = 1;
	co_y[0] = 1;
	co_x[1] = 2;
	co_y[1] = 1;
	co_x[2] = 3;
	co_y[2] = 1;

	a[1][1] = 'o';
	a[1][2] = 'o';
	a[1][3] = 'o';

	foodx = 0;
	foody = 0;
	direction = 1;
	score = 0;
}

void food()	//��������� ���
{
	srand(time(NULL));
	foody = rand()%29+1;
	foodx = rand()%69+1;

	moveCurs(foodx, foody);
	cout << "O";

	int l = rand()%100+1;		// ��������� �������� ���
	if (l==100)
	{
	bfoody = rand()%29+1;
	bfoodx = rand()%69+1;

	moveCurs(bfoodx, bfoody);
	cout << "$";
	}
}

void Bonusfood()	// �������� ���
{
	srand(time(NULL));
	bfoody = rand()%29+1;
	bfoodx = rand()%69+1;

	moveCurs(bfoodx, bfoody);
	cout << "$";
}

void drawPauseField()		// ����������� ������ ����� �����
{
	int i,j;

	system ("cls");

	for (i=0; i<=height; ++i)
	{
		for (j=0; j<= width; ++j)
			cout << b[i][j];
		cout << endl;
	}

	food();
}

void drawField()		// ����������� ���� �� ��������� ������ ����
{
	int i,j;

	system ("cls");

	for (i=0; i<=height; ++i)
	{
		for (j=0; j<= width; ++j)
			cout << a[i][j];
		cout << endl;
	}

	food();

}


bool isFoodField()		// ��������: ���� �� ������� ���, ���� ��, �� ���������� ����� ���
{	
	if ((co_x[num] == foodx) && (co_y[num]==foody))
	{
		foodx=NULL;
		foody=NULL;
		score++;
		return true;
	}
	return false;
}

bool isBonusFoodField()	// �������� �� �������� ���
{
	if ((co_x[num] == bfoodx) && (co_y[num]==bfoody))
	{
		bfoodx=NULL;
		bfoody=NULL;
		score+=2;
		return true;
	}
	return false;
}

bool dead()		// ������ ������
{
	int i;
	//���� ������ ������ �� �������
	if(co_x[num-1] == width)
		return true;
	if (co_x[num-1] == 0)
		return true;
	if (co_y[num-1] == height)
		return true;
	if (co_y[num-1] == 0)
		return true;

	// ���� ������ ������ ���� �� ����
	for (i=0; i< num-3; ++i)
		if ((co_x[i] == co_x[num-1]) && (co_y[i] == co_y[num-1]))
			return true;
	return false;
}

void game(int speed_)		// ����, ���������� � ������ ���������� �� ���������
{
	//PlaySound("Mario_Theme.ogg",NULL, SND_FILENAME | SND_ASYNC);
	char input;
	int speed = speed_;
	int temp_dir = direction;
	do{
		
		if (kbhit()) input = _getch();
		else input=0;

		switch (input)
		{
		case 'P':
			if (direction == DIR_UP) break;
            temp_dir=DIR_DOWN; 
			break;
		 case 'H': 
                    if (direction==DIR_DOWN) break;
                    temp_dir=DIR_UP;
                    break;
         case 'K':
                    if (direction==DIR_RIGHT) break;
                    temp_dir= DIR_LEFT; 
                    break;
         case 'M': 
                    if (direction==DIR_LEFT) break;
                    temp_dir= DIR_RIGHT; 
                    break;
		 case 27:
			 Pause();			// ����������� ��������� �� ����� ��� ������� escape 
			 coy = 10;
			 drawPauseField();
			 break;
		default:
			break;
		}

		direction=temp_dir;
 
            switch (temp_dir) 
            {
				case DIR_RIGHT:
                    co_x[num] = co_x[num-1]+1;
                    co_y[num] = co_y[num-1];
                    break;
				case DIR_LEFT:
                    co_x[num] = co_x[num-1]-1;
                    co_y[num] = co_y[num-1];
                    break;
				case DIR_UP:
                    co_y[num] = co_y[num-1]-1;
                    co_x[num] = co_x[num-1];
                    break;
				case DIR_DOWN:
                    co_y[num] = co_y[num-1]+1;
                    co_x[num] = co_x[num-1];
                    break;
                default:
                    break;
            }


			if (isFoodField())
			{
				moveCurs(co_x[num], co_y[num]);
				cout << "o";
				++num;
				speed-=5;
				food();
			}

			else if (isBonusFoodField())
				{
					moveCurs(co_x[num], co_y[num]);
					cout << "o";
					num++;
					speed-=5;
				}
			else 
				{
					moveCurs (co_x[0],co_y[0]);
					cout << ' ';
 
					for (int i = 0; i < num; i++)
					{
						co_x[i] = co_x[i+1];
						co_y[i] = co_y[i+1];
					} 
 
					moveCurs (co_x[num], co_y[num]);
					cout << "o";
				}

			if (dead())			// ���� ������, �� ����� ����
			{
				gameOver();
				break;
			}
			moveCurs(1,32);
            cout <<"Score : "<< score <<endl;
			Sleep(speed);
			
	}while(1>0);
}


void gameOver() // �����
{
	fin.open("C:\\Users\\Admin\\Documents\\Visual Studio 2012\\Projects\\Project\\Project\\in.txt");

	int score1[6];
	string name1[6];

	for (int i=0; i<6; ++i)
	{
		fin >> name1[i];
		fin >> score1[i];
	}
	
	fin.close();

	int j=10;

	for (int i=0; i<6; i++)
		if (score > score1[i])
		{
			j=i;
			break;
		}

	system("cls");
	moveCurs (40, 14);	
	cout << "\a GAME OVER!!!" << endl;
	moveCurs (40, 15);
	cout << "ENTER YOUR NAME: ";
	cin >> name;

	fout.open("C:\\Users\\Admin\\Documents\\Visual Studio 2012\\Projects\\Project\\Project\\in.txt");

	if (j!=10)
	{
		for (int i=5; i>j; --i)
		{
			name1[i] = name1[i-1];
			score1[i] = score1[i-1];
		}	
		score1[j] = score;
		name1[j] = name;

		for (int i=0; i<6; ++i)
			fout << name1[i] << "\t" << score1[i] << endl;
	}

	fout.close();

	system("cls");
	moveCurs (40, 14);
	cout << name << ", YOUR SCORE IS " << score << endl;
	moveCurs (40,15);
	cout << "THE BEST SCORE IS " << score1[0] << " BY " << name1[0] << endl;
	_getch();
	//moveCurs (40,16);
	//cout << "IF YOU WANT TRY AGAIN PRESS ENTER" << endl;
	
	system("cls");
	moveCurs(40,10);
	cout << "NEW GAME" << endl;
	moveCurs(40,12);
	cout << "MENU" << endl;
	
	moveCurs(40,10);
	int co_y = 10;
	while (_getch()!=13)
	{
		int kb  = _getch();
		switch (kb)
		{
		case 80: 
			co_y+=2;
			co_y == 14 ? moveCurs(40,10),co_y = 10 : moveCurs(40, co_y);
			break;

		case 72:
			co_y-=2;
			co_y == 8 ? moveCurs(40,12),co_y = 12 : moveCurs(40, co_y);
			break;
		}

	}
	switch (co_y)
	{
	case 12:
		menu(mspeed);			// ��� ������� �� escape ���������� ������� ����
		break;
	case 10:
		system ("cls");
		field();				// �� enter ���������� ����� ���� � ����� �� ������� ���������
		drawField();
		game(mspeed);
		break;
	}
}

void drawRecords()				// ������� ������ ������� �������� � ������� ����
{
	int score[6];
	string name[6];

	system("cls");
	fin.open("C:\\Users\\Admin\\Documents\\Visual Studio 2012\\Projects\\Project\\Project\\in.txt");
	
	for (int i=0; i<6; ++i)
	{
		fin >> name[i];
		fin >> score[i];
	}

	fin.close();

	cout << "Exit: escape" << endl;
	moveCurs(40,10);
	cout << "NAME\t" << "  RESULT" << endl;
	for (int i=0; i<6; ++i)
	{
		moveCurs(40,11+i);
		cout << name[i] << "\t    " << score[i] << endl;
	}
	moveCurs(40,10);
	while (_getch()!=27)
	{
		continue;
	}
	system("cls");
	coy = 10;
}

int Complexity(int Speed)			// ������� ������ ���������
{
	coy = 10;
	system("cls");
	moveCurs(40,10);
	cout << "EASY" << endl;
	moveCurs(40,11);
	cout << "MEDIUM" << endl;
	moveCurs(40,12);
	cout << "HARD" << endl;
	moveCurs(40,13);
	cout << "FATAL" << endl;


	moveCurs(40,10);
	while (_getch()!=13)
	{
		int kb_ = _getch();
		switch (kb_)
		{
		case 80: 
			coy++;
			coy == 14 ? moveCurs(40,10),coy = 10 : moveCurs(40, coy);
			break;

		case 72:
			coy--;
			coy == 9 ? moveCurs(40,13),coy = 13 : moveCurs(40, coy);
			break;
		}
	}


	switch (coy)
	{
	case 10:
		Speed = EasySpeed;
		break;
	case 11:
		Speed = MediumSpeed;
		break;
	case 12:
		Speed = HardSpeed;
		break;
	case 13:
		Speed = FatalSpeed;
		break;
	}
	system("cls");
	return Speed;
}


void Pause()						// ������� ����� ����� �� ����� ����
{
	system("cls");
	moveCurs(40,10);
	cout << "CONTINUE" << endl;		// ����������
	moveCurs(40,12);
	cout << "NEW GAME" << endl;		// ����� ���� �� ��� �� ������ ��������� 
	moveCurs(40,14);
	cout << "MENU" << endl;			// ����� � ����
	moveCurs(40,16);
	cout << "EXIT" << endl;			// ����� �� ����
	
	moveCurs(40,10);
	while (_getch()!=13)
	{
		int kb_ = _getch();
		switch (kb_)
		{
		case 80: 
			coy+=2;
			coy == 18 ? moveCurs(40,10),coy = 10 : moveCurs(40, coy);
			break;

		case 72:
			coy-=2;
			coy == 8 ? moveCurs(40,16),coy = 16 : moveCurs(40, coy);
			break;
		}
	}

	switch (coy)
	{
	case 10:				// ����������� ����
		break;
	case 12:
		coy = 10;			// ����� ����
		system("cls");
		field();
		drawField();
		game(mspeed);
		break;
	case 14:				// ����� � ����
		coy = 10;
		menu(mspeed);
		break;
	case 16:				// ����� �� ����
		coy = 10;
		exit();
		break;
	}

	system("cls");
}

void exit()				// ������� ������ �� ����
{
	system("cls");
	moveCurs(40, 10);
	cout << "ARE YOU SURE?" << endl;
	moveCurs(40, 12);
	cout << "YES" << endl;
	moveCurs(40, 14);
	cout << "NO" << endl;
	
	int co_y = 12;
	moveCurs(40,12);
	while (_getch()!=13)
	{
		int kb_ = _getch();
		switch (kb_)
		{
		case 80: 
			co_y+=2;
			co_y == 16 ? moveCurs(40,12),co_y = 12 : moveCurs(40, co_y);
			break;

		case 72:
			co_y-=2;
			co_y == 10 ? moveCurs(40,14),co_y = 14 : moveCurs(40, co_y);
			break;
		}
	}

	switch (co_y)
	{
	case 12:
		exit(0);
		break;
	case 14:
		Pause();
		break;
	}

}


void extra()
{
	system("cls");
	moveCurs(40,10);
	cout << "RESET RECORDS" << endl;
	moveCurs(40,12);
	cout << "ABOUT" << endl;
	moveCurs(40,14);
	cout << "BACK" << endl;

	int co_y = 10;
	moveCurs(40,10);
	while (_getch()!=13)
	{
		int kb_ = _getch();
		switch (kb_)
		{
		case 80: 
			co_y+=2;
			co_y == 16 ? moveCurs(40,10),co_y = 10 : moveCurs(40, co_y);
			break;

		case 72:
			co_y-=2;
			co_y == 8 ? moveCurs(40,14),co_y = 14 : moveCurs(40, co_y);
			break;
		}
	}

	switch (co_y)
	{
	case 10:
		resetRecords();
		break;
	case 12:
		about();
		break;
	}
}


void resetRecords()
{
	system("cls");
	moveCurs(40,10);
	cout << "ARE YOU SURE?" << endl;
	moveCurs(40,12);
	cout << "YES" << endl;
	moveCurs(40,14);
	cout << "NO" << endl;

	int co_y = 12;
	moveCurs(40,12);
	while (_getch()!=13)
	{
		int kb_ = _getch();
		switch (kb_)
		{
		case 80: 
			co_y+=2;
			co_y == 16 ? moveCurs(40,12),co_y = 12 : moveCurs(40, co_y);
			break;

		case 72:
			co_y-=2;
			co_y == 10 ? moveCurs(40,14),co_y = 14 : moveCurs(40, co_y);
			break;
		}
	}

	switch (co_y)
	{
	case 12:
		fout.open("C:\\Users\\Admin\\Documents\\Visual Studio 2012\\Projects\\Project\\Project\\in.txt");
		for (int i=1; i<=6; ++i)
			fout << "player" << i << "\t" << 0 << endl;
		fout.close();
		extra();
		break;
	case 14:
		extra();
		break;
	}
}

void about()
{
	system("cls");
	moveCurs(40,10);
	cout << "CREATED BY AVDEEV" << endl;
	moveCurs(40,14);
	cout << "4/14/2017" << endl;
	_getch();
	extra();
}
