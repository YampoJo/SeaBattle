 #define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <math.h>
#include <time.h>
#include <Windows.h>
#include <iomanip>
#include <string>
#include <stdio.h>
#include <dos.h>

enum ConsoleColor 
{
	Black, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
	LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

void SetColor (int text, int background) 
{
	HANDLE hStdOut = GetStdHandle (STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute (hStdOut, (WORD) ((background << 4) | text));
}

enum Keys 
{
	ArDown = 80,
	ArRight = 77,
	ArLeft = 75,
	ArUp = 72,
	Enter = 13
};

void GotoXY(int X, int Y)
{
	HANDLE hConsole;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { X, Y };
	SetConsoleCursorPosition(hStdOut, coord);
}


enum Symbols
{
	Sea, Ship, Hit, ShipZone, HitWater, Stroke
};

struct Cell 
{
	int symbol = Symbols::Sea;
	//bool is_selected = false;
};

void profiles ();

void menu();

void initMap();

void clearmap (Cell **ar);

void winscreen();

void printmapLeft(Cell **ar);

void printmapRight(Cell** ar);

void set_diag();

void set_ships(Cell **ar, int diag, int count_for_print_ship, int y, int x, int corab);

bool hit_to_ships(Cell** ar, int y, int x, bool n);

bool chekwin (Cell **ar, int y, int x);

void design_pack(int number, int x, int y, int color);

void count_and_logic_ships(int *corab, int *count_for_print_ship);

void diag_func(int* diag);

void _next ();

using namespace std;


Cell** map;
Cell** map_enemy;

string player_1;
string player_2;

int count_4 = 1;
int count_3 = 2;
int count_2 = 3;
int count_1 = 4;

int raiting_1 = 0;
int raiting_2 = 0;
int raiting_hit_1 = 0;
int raiting_hit_2 = 0;

int count_spawned_ships = 0;
int layouts = 0;
int player = 1;

int main()
{	
	setlocale (LC_ALL, "ru");
	srand(time(NULL));
	profiles();
	menu();
	return 0;
}

void profiles () 
{
	system ("cls");
	cout << "Игрок 1, введите ваше имя >> "; cin >> player_1; cout << endl;
	system ("cls");
	cout << "Игрок 2, введите ваше имя >> "; cin >> player_2; cout << endl;
}

void menu()
{
	initMap();
	system ("cls");
	layouts++;
	set_diag();
	
}


void initMap()
{
	map = new Cell *[12];
	map_enemy = new Cell *[12];
	for (int i = 0; i < 12; i++)
	{
		map[i] = new Cell[12];
		map_enemy[i] = new Cell[12];
	}

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			Cell sym;
			sym.symbol = Symbols::Sea;
			map[i][j] = sym;
			map_enemy[i][j] = sym;

			if (i == 0)
			{
				sym.symbol = Symbols::Stroke;
				map[i][j] = sym;
				map_enemy[i][j] = sym;
			}

			if (i == 11)
			{
				sym.symbol = Symbols::Stroke;
				map[i][j] = sym;
				map_enemy[i][j] = sym;
			}

			if (j == 0)
			{
				sym.symbol = Symbols::Stroke;
				map[i][j] = sym;
				map_enemy[i][j] = sym;
			}

			if (j == 11)
			{
				sym.symbol = Symbols::Stroke;
				map[i][j] = sym;
				map_enemy[i][j] = sym;
			}
		}
	}
}

void printmapLeft(Cell **ar)
{
	int cellX = 2, cellY = 1;

	for (int i = 0; i < 12; i++)
	{
		design_pack(3, cellX, cellY, 12);
		cellX = cellX + 4;
	}
	cellX = 2;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{ 
			switch (ar[i][j].symbol)
			{
			case 0: 
				design_pack(0, cellX, cellY, 15); 
				break;
			case 1: 
				design_pack(1, cellX, cellY, 11);
				break;
			case 2: 
				design_pack(2, cellX, cellY, 4);
				break;
			case 3:
				switch (layouts) 
				{
				case 1:
					design_pack (5, cellX, cellY, 7);
					break;
				case 2:
					design_pack (0, cellX, cellY, 7);
					break;
				}
				break;
			case 4:
				design_pack(2, cellX, cellY, 1);
				break;
			case 5:
				switch (player) 
				{
				case 1:
					design_pack (6, cellX, cellY, 5);
					break;
				case 2:
					design_pack (6, cellX, cellY, 10);
					break;
				}
				
				break;
			}
			cellX = cellX + 4;
			cout << " ";
		}
		cellX = 2;
		cellY = cellY + 2;
		cout << endl;
	}
}

void printmapRight(Cell** ar)
{
	int cellX = 60, cellY = 1;

	for (int i = 0; i < 12; i++)
	{
		design_pack(3, cellX, cellY, 12);
		cellX = cellX + 4;
	}
	cellX = 60;

	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			switch (ar[i][j].symbol)
			{
			case 0:
				design_pack(0, cellX, cellY, 15);
				break;
			case 1:
				design_pack(0, cellX, cellY, 11);
				break;
			case 2:
				design_pack(2, cellX, cellY, 4);
				break;
			case 3:
				design_pack(0, cellX, cellY, 7);
				break;
			case 4:
				design_pack(2, cellX, cellY, 1);
				break;
			case 5:
				switch (player) 
				{
				case 1:
					design_pack (6, cellX, cellY, 10);
					break;
				case 2:
					design_pack (6, cellX, cellY, 5);
					break;
				}
				break;
			}
			cellX = cellX + 4;
			cout << " ";
		}
		cellX = 60;
		cellY = cellY + 2;
		cout << endl;
	}
}

void set_diag()
{
	int diag;
	int corab = 0;
	int count_for_print_ship = 0;
	bool n = false;
	bool _chekwin = false;

	for (int key = 0, cellX = 6, cellY = 3, x = 1, y = 1; true; key = _getch ()) 
	{
		if (key == ArDown) 
		{
			cellY += 2;
			y += 1;
			if (y > 10)
			{
				cellY = 3;
				y = 1;
			}
		}
		if (key == ArUp) 
		{
			cellY -= 2;
			y -= 1;
			if (y < 1)
			{
				cellY = 21;
				y = 10;
			}
		}
		if (key == ArRight) 
		{
			cellX += 4;
			x += 1;
			if (x > 10)
			{
				cellX = 6;
				x = 1;
			}
		}
		if (key == ArLeft) 
		{
			cellX -= 4;
			x -= 1;
			if (x < 1)
			{
				cellX = 42;
				x = 10;
			}
		}
		if (key == Enter) 
		{
			switch (layouts)
			{
			case 1:
				diag_func(&diag);
				count_and_logic_ships(&corab, &count_for_print_ship);

				switch (player)
				{
				case 1:
					set_ships(map, diag, count_for_print_ship, y, x, corab);
					if (count_spawned_ships == 10)
					{
						player = 2;
						count_spawned_ships = 0;
						count_4 = count_4 + 1;
						count_3 = count_3 + 2;
						count_2 = count_2 + 3;
						count_1 = count_1 + 4;
						_next ();
					}
					break;
				case 2:
					
					set_ships(map_enemy, diag, count_for_print_ship, y, x, corab);
					if (count_spawned_ships == 10)
					{
						player = 1;
						layouts = 2;
						count_spawned_ships = 0;
						_next ();
					}
					break;
				}
				break;

			case 2:
				switch (player)
				{
				case 1:
					n = hit_to_ships(map_enemy, y, x, n);

					if (n == true) player = 1;
					else {player = 2; _next ();}

					_chekwin = chekwin (map_enemy, 1, 1);
					break;
				case 2:
					n = hit_to_ships(map, y, x, n);

					if (n == true) player = 2;
					else {player = 1; _next ();}

					_chekwin = chekwin (map, 1, 1);
					break;
				}
				
				

				/*cout << "_chekwin" << _chekwin << " ";
				system ("pause >> 0");*/

				if (_chekwin == true)
				{
					winscreen();
					clearmap (map);
					clearmap (map_enemy);
					menu();
				}
				
				break;
			}
		}
		system("cls");
		switch (player)
		{
		case 1:
			printmapLeft(map);
			SetColor (5, 0);
			GotoXY (2, 26);
			cout << "ПОЛЕ ИГРОКА: " << player_1;
			if (layouts == 2)
			{
				printmapRight(map_enemy);
				SetColor (10, 0);
				GotoXY (60, 26);
				cout << "ПОЛЕ ИГРОКА: " << player_2;
			}
			break;

		case 2:
			printmapLeft(map_enemy);
			SetColor (10, 0);
			GotoXY (2, 26);
			cout << "ПОЛЕ ИГРОКА: " << player_2;
			if (layouts == 2)
			{
				printmapRight (map);
				SetColor (4, 0);
				GotoXY (60, 26);
				cout << "ПОЛЕ ИГРОКА: " << player_1;
			}
			break;
		}
		switch (layouts)
		{
		case 1:
			design_pack(4, cellX, cellY, 14);
			break;
		case 2:
			design_pack(4, cellX + 58, cellY, 14);
			break;
		}
		
	}
}

void set_ships(Cell **ar, int diag, int count_for_print_ship, int y, int x, int corab)
{
	int mojno_count = 0;

	for (int i = 0, checky = y, checkx = x; i < count_for_print_ship; i++) 
	{
		if (ar[checky][checkx].symbol == Symbols::Sea)
		{
			mojno_count++;
			/*cout << "sea" << endl;
			system("pause >> 0");*/
		}

		if (ar[checky][checkx].symbol != Symbols::Sea)
		{
			mojno_count--;
			/*cout << "ship or shipZone or Stroke" << endl;
			system("pause >> 0");*/
		}

		switch (diag)
		{
		case 1:
			checkx += 1;
			break;
		case 2:
			checky += 1;
			break;
		}
	}

	if (mojno_count == count_for_print_ship)
	{
		int wallX = x;
		int wallY = y;
		int shipX = x;
		int shipY = y;
		switch (diag) 
		{
		case 1:
			for (int i = 0, y = shipY, x = shipX; i < count_for_print_ship; i++, x++)
			{
				if (ar[y + 1][x].symbol == Symbols::Sea)
				{
					ar[y + 1][x].symbol = Symbols::ShipZone;
				}
				if (ar[y - 1][x].symbol == Symbols::Sea)
				{
					ar[y - 1][x].symbol = Symbols::ShipZone;
				}
				ar[y][x].symbol = Symbols::Ship;
			}

			if (ar[wallY][wallX - 1].symbol == Symbols::Sea) ar[wallY][wallX - 1].symbol = Symbols::ShipZone;

			if (ar[wallY + 1][wallX - 1].symbol == Symbols::Sea) ar[wallY + 1][wallX - 1].symbol = Symbols::ShipZone;

			if (ar[wallY - 1][wallX - 1].symbol== Symbols::Sea) ar[wallY - 1][wallX - 1].symbol = Symbols::ShipZone;

			if (ar[wallY][wallX + count_for_print_ship].symbol == Symbols::Sea) ar[wallY][wallX + count_for_print_ship].symbol = Symbols::ShipZone;

			if (ar[wallY + 1][wallX + count_for_print_ship].symbol == Symbols::Sea) ar[wallY + 1][wallX + count_for_print_ship].symbol = Symbols::ShipZone;

			if (ar[wallY - 1][wallX + count_for_print_ship].symbol == Symbols::Sea) ar[wallY - 1][wallX + count_for_print_ship].symbol = Symbols::ShipZone;
			break;
		case 2:
			for (int i = 0, y = shipY, x = shipX; i < count_for_print_ship; i++, y++)
			{
				if (ar[y][x + 1].symbol == Symbols::Sea)
				{
					ar[y][x + 1].symbol = Symbols::ShipZone;
				}
				if (ar[y][x - 1].symbol == Symbols::Sea)
				{
					ar[y][x - 1].symbol = Symbols::ShipZone;
				}
				ar[y][x].symbol = Symbols::Ship;
			}

			if (ar[wallY - 1][wallX].symbol == Symbols::Sea) ar[wallY - 1][wallX].symbol = Symbols::ShipZone;

			if (ar[wallY - 1][wallX + 1].symbol == Symbols::Sea) ar[wallY - 1][wallX + 1].symbol = Symbols::ShipZone;

			if (ar[wallY - 1][wallX - 1].symbol == Symbols::Sea) ar[wallY - 1][wallX - 1].symbol = Symbols::ShipZone;

			if (ar[wallY + count_for_print_ship][wallX].symbol == Symbols::Sea) ar[wallY + count_for_print_ship][wallX].symbol = Symbols::ShipZone;

			if (ar[wallY + count_for_print_ship][wallX - 1].symbol == Symbols::Sea) ar[wallY + count_for_print_ship][wallX - 1].symbol = Symbols::ShipZone;

			if (ar[wallY + count_for_print_ship][wallX + 1].symbol == Symbols::Sea) ar[wallY + count_for_print_ship][wallX + 1].symbol = Symbols::ShipZone;
			break;
		}
		count_spawned_ships = count_spawned_ships + 1;
		
	}
	if (mojno_count < count_for_print_ship)
	{
		if (corab == 1) count_4 = count_4 + 1;
		if (corab == 2) count_3 = count_3 + 1;
		if (corab == 3) count_2 = count_2 + 1;
		if (corab == 4) count_1 = count_1 + 1;

		system ("pause >> 0");
		set_diag ();
	}
}

bool hit_to_ships(Cell** ar, int y, int x, bool n)
{
	if (ar[y][x].symbol == Symbols::Sea or ar[y][x].symbol == Symbols::ShipZone)
	{
		ar[y][x].symbol = Symbols::HitWater;

		n = false;
		switch (player) 
		{
		case 1:
			raiting_hit_1 = raiting_hit_1 - 1;
			raiting_1 = raiting_1 - 5;
			break;
		case 2:
			raiting_hit_2 = raiting_hit_2 - 1;
			raiting_1 = raiting_1 - 5;
			break;
		}
	}

	if (ar[y][x].symbol == Symbols::HitWater or ar[y][x].symbol == Symbols::Hit)
	{
		switch (player) 
		{
		case 1:
			raiting_1 = raiting_1 - 5;
			break;
		case 2:
			raiting_1 = raiting_1 - 5;
			break;
		}
		n = false;
	}

	if (ar[y][x].symbol == Symbols::Ship)
	{
		ar[y][x].symbol = Symbols::Hit;
		switch (player) 
		{
		case 1:
			raiting_hit_1 = raiting_hit_1 + 1;
			if (raiting_hit_1 < 5)
			{
				raiting_1 = raiting_1 + 5;
			}
			if (raiting_hit_1 > 10) 
			{
				raiting_1 = raiting_1 + 10;
			}
			if (raiting_hit_1 > 15) 
			{
				raiting_1 = raiting_1 + 15;
			}
			
			break;
		case 2:
			raiting_hit_2 = raiting_hit_2 + 1;
			break;
		}
		n = true;
	}
	return n;
}

bool chekwin (Cell **ar, int y, int x) 
{
	int count_ship_cells = 0;
	bool win = false;

	for (int i = y; i < 11; i++) 
	{
		for (int j = x; j < 11; j++) 
		{
			if(ar[i][j].symbol == Symbols::Hit)
			{
				count_ship_cells++;
				/*GotoXY (30, 60);
				cout << "count_ship_cells" << count_ship_cells <<" ";
				system ("pause >> 0");*/
			}
		}
	}
	if(count_ship_cells == 20)
	{
		win = true;
		/*cout << "win" << win << " ";
		system ("pause >> 0");*/
		return win;
	}

	return win;
}

void clearmap(Cell **ar)
{
	for (int i = 0; i < 12; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			Cell sym;
			sym.symbol = Symbols::Sea;
			map[i][j] = sym;
			map_enemy[i][j] = sym;
		}
	}
}

void winscreen () 
{
	system ("cls");
	SetColor (15, 0);
	cout << "Победил игрок " << player << endl;
	switch (player) 
	{
	case 1:
		cout << "Ваш рейтинг = " << raiting_1;
		break;
	case 2:
		cout << "Ваш рейтинг = " << raiting_2;
		break;
	}

	cout << endl <<"Чтобы продолжить нажмите любую клавишу";
	
	count_4 = 1;
	count_3 = 2;
	count_2 = 3;
	count_1 = 4;

	player_1 = "";
	player_2 = "";
	raiting_1 = 0;
	raiting_2 = 0;
	raiting_hit_1 = 0;
	raiting_hit_2 = 0;
	count_spawned_ships = 0;
	layouts = 0;
	player = 1;

	system ("pause >> 0");
}

void design_pack(int number, int x, int y, int color)
{
	//////////////////////////////////////////////////

	string graphic_line(37, '_'); //1
	string graphic_line_window(3, '_');//2

	//////////////////////////////////////////////////

	switch (number)
	{
	case 0:
		SetColor(15, 0);
		GotoXY(x - 1, y - 1 + 1);
		cout << "|   |" << endl;
		GotoXY(x - 1, y - 1 + 2);
		cout << "|" << graphic_line_window << "|";
		break;
	case 1:
		GotoXY(x - 1, y - 1 + 1);
		SetColor(15, 0); cout << "|"; SetColor(color, 0); cout << "###"; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		GotoXY(x - 1, y - 1 + 2);
		SetColor(15, 0); cout << "|"; SetColor(color, 0); cout << "###"; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		break;
	case 2:
		SetColor(15, 0);
		GotoXY(x - 1, y - 1 + 1);
		SetColor(15, 0); cout << "|"; SetColor(color, 0); cout << "\\_/"; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		GotoXY(x - 1, y - 1 + 2);
		SetColor(15, 0); cout << "|"; SetColor(color, 0); cout << "/ \\"; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		break;
	case 3:
		SetColor(15, 0);
		GotoXY(x - 1, y - 1);
		cout << " " << graphic_line_window << endl;
		break;
	case 4:
		SetColor (15, 0);
		GotoXY (x - 1, y - 1 + 1);
		SetColor (15, 0); cout << "|"; SetColor (color, 0); cout << "+ >"; SetColor (15, 0); cout << "|"; SetColor (4, 0); cout << endl;
		GotoXY (x - 1, y - 1 + 2);
		SetColor (15, 0); cout << "|"; SetColor (color, 0); cout << "v"; SetColor (15, 0); cout << "__|"; SetColor (4, 0); cout << endl;
		break;
	case 5:
		SetColor(15, 0);
		GotoXY(x - 1, y - 1 + 1);
		SetColor(15, 0); cout << "|"; SetColor(15, color); cout << "   "; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		GotoXY(x - 1, y - 1 + 2);
		SetColor(15, 0); cout << "|"; SetColor(15, color); cout << "___"; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		break;
	case 6:
		SetColor(15, 0);
		GotoXY(x - 1, y - 1 + 1);
		SetColor(15, 0); cout << "|"; SetColor(color, 0); cout << "==="; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		GotoXY(x - 1, y - 1 + 2);
		SetColor(15, 0); cout << "|"; SetColor(color, 0); cout << "==="; SetColor(15, 0); cout << "|"; SetColor(4, 0); cout << endl;
		break;
	}
}

void count_and_logic_ships(int *corab, int *count_for_print_ship)
{
	do 
	{
		cout << "Плизки выберите корабль" << endl;
		cout << "1.Четырка = " << count_4 << " " << "2.Трешка = " << count_3 << " " << "3.Двушка = " << count_2 << " " << "4.Однушка = " << count_1 << " " << endl;
		cout << ">> "; cin >> *corab; cout << endl;
	} while (*corab < 1 or *corab > 4);

	switch (*corab) 
	{ 
	case 1:
		if (count_4 == 0) set_diag ();
		else { count_4--; *count_for_print_ship = 4;}  break;
	case 2:
		if (count_3 == 0) set_diag ();
		else {count_3--; *count_for_print_ship = 3;} break;
	case 3:
		if (count_2 == 0) set_diag ();
		else {count_2--; *count_for_print_ship = 2;} break;
	case 4:
		if (count_1 == 0) set_diag ();
		else {count_1--; *count_for_print_ship = 1;} break;
	}

	/*cout << *count_for_print_ship << endl;
	system ("pause >> 0");*/
}

void diag_func(int* diag)
{

	GotoXY(2, 28);
	SetColor(15, 0);
	do
	{
		GotoXY(2, 27);
		SetColor(15, 0);
		cout << "Плизки выберите диагональ" << endl;
		cout << "1.Горизонтально" << endl; cout << "2.Вертикально" << endl;
		cout << ">> "; cin >> *diag; cout << endl;

	} while (*diag < 1 or *diag > 2);
	
}

void _next () 
{
	system("cls");
	SetColor (15, 0);
	cout << "Поменяйтесь с противником" << endl;
	cout << "Для продолжения нажмите enter" << endl;
	system ("pause >> null");
}

