#include "header.h"
#include "glut.h"
using namespace std;

int main()
{
	system("color F2");
	system("cls");
	moveCurs (40, 10);
	cout << "WELCOME TO OUR GAME!" << endl;
	moveCurs(40,10);
	_getch();
	menu(250);

	return 0;
}
