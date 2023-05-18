#include <iostream>
#include<conio.h>
#include <Windows.h>
using namespace std;
char rowLabel = 64;
int num = 1;
const int s = 10;
int X = 0;
int Y = 0;
int game[s][s]{};
bool isEmpty(int x, int y, int size, int HorOrVer) {
	if (HorOrVer == 0) {
		// X oxu
		if (x + size > s) {
			return false;
		}

		for (int i = x; i < x + size; i++) {
			if (game[i][y] != 0 || (y > 0 && game[i][y - 1] != 0) || (y < s - 1 && game[i][y + 1] != 0) ||
				(i > 0 && game[i - 1][y] != 0) || (i < s - 1 && game[i + 1][y] != 0) ||
				(y > 0 && game[i][y - 1] != 0) || (y < s - 1 && game[i][y + 1] != 0) ||
				(i > 0 && y > 0 && game[i - 1][y - 1] != 0) || (i > 0 && y < s - 1 && game[i - 1][y + 1] != 0) ||
				(i < s - 1 && y > 0 && game[i + 1][y - 1] != 0) || (i < s - 1 && y < s - 1 && game[i + 1][y + 1] != 0)) {
				return false;
			}
		}
	}
	else {
		// Y oxu 
		if (y + size > s) {
			return false;
		}

		for (int i = y; i < y + size; i++) {
			if (game[x][i] != 0 || (x > 0 && game[x - 1][i] != 0) || (x < s - 1 && game[x + 1][i] != 0) ||
				(i > 0 && game[x][i - 1] != 0) || (i < s - 1 && game[x][i + 1] != 0) ||
				(x > 0 && game[x - 1][i] != 0) || (x < s - 1 && game[x + 1][i] != 0) ||
				(x > 0 && i > 0 && game[x - 1][i - 1] != 0) || (x > 0 && i < s - 1 && game[x - 1][i + 1] != 0) ||
				(x < s - 1 && i > 0 && game[x + 1][i - 1] != 0) || (x < s - 1 && i < s - 1 && game[x + 1][i + 1] != 0)) {
				return false;
			}
		}
	}

	return true;
}


void PlaceShip(int size) {
	cout << size << " uzunlugunda gemi ucun koordinant daxil edin ..(once setir sonra sutun...mes : a 1 ) :  ";
	char row, column;
	row = _getch();
	cout << row << " ";
	X = row - 96;
	column = _getch();
	cout << column << " ";
	Y = column - 49;
	cout << endl << endl;
	cout << "Geminin X oxu uzre yoxsa Y oxu uzre yerlesdirilmesini secin (X oxu uzre -> 0   , Y oxu uzre -> 1 )  : ";
	int HorOrVer;
	cin >> HorOrVer;

	if (isEmpty(X, Y, size, HorOrVer)) {
		if (HorOrVer == 0) {
			// X oxu uzre
			for (int i = Y; i < Y + size; i++) {
				game[X][i] = 2;
			}
		}
		else {
			// Y oxu uzre 
			for (int i = X; i < X + size; i++) {
				game[i][Y] = 2;
			}
		}
		cout << "Gemi ugurla yerlestirildi" << endl;
	}
	else {
		cout << "Yanlis pozisiya, Bu koordinanta gemi yerlestirile bilmez..." << endl;
		PlaceShip(size);
	}
	system("cls");
}


void GetRandomPlacedShip() {
	int shipCount[4] = { 4, 3, 2, 1 };
	srand(time(0));

	for (int i = 4; i > 0; i--) {
		for (int j = 0; j < shipCount[i - 1]; j++) {
			bool validPosition = false;

			while (!validPosition) {
				int x = rand() % s;
				int y = rand() % s;
				int HorOrVer = rand() % 2;

				if (HorOrVer == 0 && y + i <= s) {
					validPosition = isEmpty(x, y, i, HorOrVer);
				}
				else if (HorOrVer == 1 && x + i <= s) {
					validPosition = isEmpty(x, y, i, HorOrVer);
				}

				if (validPosition) {
					if (HorOrVer == 0) {
						// X oxu uzre
						for (int k = x; k < x + i; k++) {
							game[k][y] = 2;
						}
					}
					else {
						// Y oxu uzre
						for (int k = y; k < y + i; k++) {
							game[x][k] = 2;
						}
					}
				}
			}
		}
	}
}
void ShowGame(char rowLabel, int num) {
	for (size_t i = 0; i < s; i++) {
		if (i != 0)
			cout << rowLabel << " ";

		for (size_t k = 0; k < s; k++) {
			if (i == 0) {
				if (num == 1)
					cout << "   " << num << "  ";
				else
					cout << num << "  ";
			}
			else {
				if (game[i][k] == 1)
					cout << " x ";
				else if (game[i][k] == 2)
					cout << " 0 ";
				else if (game[i][k] == -2)
					cout << " U ";
				else if (game[i][k]==-3)
					cout << " R ";
				else
					cout << " - ";
			}
			num++;
		}

		cout << endl;
		rowLabel++;
	}
}
void ComputerAttack() {
	int x, y;
	static int previousHitX = -1; 
	static int previousHitY = -1;
	bool successfulHit = false;
	bool smartMove = false;
	if (previousHitX != -1 && previousHitY != -1 && game[previousHitX][previousHitY] == 2) {
		smartMove = true;

		
		int direction = rand() % 4; 

		switch (direction) {
		case 0: 
			if (previousHitY > 0 && game[previousHitX][previousHitY - 1] >= 0) {
				x = previousHitX;
				y = previousHitY - 1;
			}
			else {
				
				direction = (direction + 1) % 4;
				smartMove = false;
			}
			break;

		case 1: 
			if (previousHitY < s - 1 && game[previousHitX][previousHitY + 1] >= 0) {
				x = previousHitX;
				y = previousHitY + 1;
			}
			else {
				
				direction = (direction + 1) % 4;
				smartMove = false;
			}
			break;

		case 2: 
			if (previousHitX > 0 && game[previousHitX - 1][previousHitY] >= 0) {
				x = previousHitX - 1;
				y = previousHitY;
			}
			else {
				
				direction = (direction + 1) % 4;
				smartMove = false;
			}
			break;

		case 3: 
			if (previousHitX < s - 1 && game[previousHitX + 1][previousHitY] >= 0) {
				x = previousHitX + 1;
				y = previousHitY;
			}
			else {
				
				direction = (direction + 1) % 4;
				smartMove = false;
			}
			break;
		}
	}

	if (!smartMove) {
		do {
			x = rand() % s;
			y = rand() % s;
		} while (game[x][y] < 0);
	}

	if (game[x][y] == 0) {
		cout << "Robotun vurusu ugursuz oldu! (" << char(x + 96) << " " << y + 1 << ")" << endl;
		game[x][y] = -1;
		previousHitX = -1;
		previousHitY = -1;
	}
	else if (game[x][y] == 2) {
		cout << "Robotun vurusu ugurlu oldu ! (" << char(x + 96) << " " << y + 1 << ")" << endl;
		game[x][y] = -3;
		previousHitX = x;
		previousHitY = y;
	}
	else if (game[x][y] == -1) {
		cout << "Robot eyni yere tekrar vurdu  (" << char(x + 96) << " " << y + 1 << ")" << endl;
	}
}

void PlayGame() {
	srand(time(0));
	bool userTurn = true;

	while (true) {
		if (userTurn) {
			
			system("cls");
			ShowGame(rowLabel, num);
			char row, column;
			cout << "Vurmaq istediyiniz koordinanti girin (mes: a1): ";
			cin >> row >> column;
			int x = row - 96;
			int y = column - 49;

			if (game[x][y] == 0) {

				cout << "Atis ugursuz oldu! (" << row << " " << column << ")" << endl;
				game[x][y] = -1;
			}
			else if (game[x][y] == 2) {
				cout << "Atis ugurlu oldu! Bir gemi vurdunuz! (" << row << " " << column << ")" << endl;
				game[x][y] = -2;
			}
			else if (game[x][y] < 0) {
				cout << "Bu koordinanta daha önce atis edildi ,yeniden cehd edin." << endl;
				continue;
			}
			userTurn = false;
			
		}
		else {
			
			ComputerAttack();
			userTurn = true;
			
		}

		
		bool allShipsSunk = true;
		for (int i = 0; i < s; i++) {
			for (int j = 0; j < s; j++) {
				if ((userTurn && game[i][j] != -2) || (!userTurn && game[i][j] == 2)) {
					allShipsSunk = false;
					break;
				}
			}
			if (!allShipsSunk) {
				break;
			}
		}

		if (allShipsSunk) {
			if (userTurn) {
				cout << "Tebrikler! Butun gemileri vurdunuz ve qazandiniz." << endl;
			}
			else {
				cout << "Teessufki Butun gemileriniz vuruldu." << endl;
			}
			break;
		}
		system("pause");
	}
}


void main() {
	srand(time(0));
	char rowLabel = 64;
	int num = 1;

	cout << "Oyuna baslamaq ucun bir secim secin :" << endl;
	cout << "1. Auto Mod" << endl;
	cout << "2. Manual Mod" << endl;
	char choice = '0';
	cin >> choice;

	if (choice == '1') {
		GetRandomPlacedShip();
		PlayGame();


	}
	else if (choice == '2') {
		int ships[10] = { 4, 3, 3, 2, 2, 2, 1, 1, 1, 1 };

		for (int i = 0; i < 10; i++) {
			ShowGame(rowLabel, num);
			PlaceShip(ships[i]);
		}

		system("cls");
		ShowGame(rowLabel, num);

		PlayGame();
	}

	cout << endl << endl << endl; cin.get();

}

