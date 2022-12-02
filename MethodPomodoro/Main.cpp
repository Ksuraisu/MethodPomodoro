#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
using namespace std;

static int runtime_tomatoCount = 0;

static enum color { darkblue = 1, green, lightblue, red, purple, orange, grey, darkgrey, blue, lightgreen, turquoise, lightred, lightpurple, yellow, white, END_OF_COLOR };
string rusColor[]{ "Темно-синий", "Зеленый", "Голубой", "Красный", "Фиолетовый", "Оранжевый", "Серый", "Темно-серый", "Синий", "Светло-зеленый", "Бирюзовый", "Светло-красный", "Светло-фиолетовый", "Желтый", "Белый" };

//int total_tomatoCount, int colorConsole, "bool" animation on/off 
static int stats[3]{ 0, white, 1 };

void read() {
	ifstream fin("settings.txt");
	string input;
	int line = 0;
	for (; getline(fin, input); line++) {
		try{
			stats[line] = stoi(input);
		} catch (...){
			cout << "Произошла ошибка при чтении из файла!\n";
			return;
		}
	}
}

void save() {
	ofstream fout("settings.txt");
	for (int line = 0; line < 3; line++){
		fout << stats[line] << "\n";
	}
}

void acout(string whatToAnimate, bool endLine = true, int delay = stats[2]) {
	for (int i = 0; i < whatToAnimate.length(); i++) {
		cout << whatToAnimate[i];
		Sleep(delay);
	}
	if (endLine) cout << endl;
}

void changeColor();

void tomatoMethod();

void timerForRest() {
	int seconds;
	if (runtime_tomatoCount % 3 != 0) seconds = 600;
	else seconds = 0;
	while (true) {
		if (seconds == 900) break;
		cout << "Отдых в процессе...\n";
		Sleep(1000);
		system("cls");
		seconds++;
		cout << "Прошло: " << seconds / 60 << "м ";
		cout << seconds % 60 << 'c';
	}
}

void timerForWork(bool fiveMinutes = false) {
	int seconds;
	if (fiveMinutes) seconds = 1200;
	else seconds = 0;
	while (true) {
		if (seconds == 1500) break;
		cout << "Работа в процессе...\n";
		Sleep(1000);
		system("cls");
		seconds++;
		cout << "Прошло: " << seconds / 60 << "м ";
		cout << seconds % 60 << "с\n";
	}
	runtime_tomatoCount++;
	cout << "\a";
}

void CUI();

int main() {
	setlocale(LC_ALL, "ru-RU");
	read();
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	/*При запуске программы в VS 2022 текст изначально черный,
	однако при запуске программы из проводника, всё работает как надо*/
	SetConsoleTextAttribute(hConsole, stats[1]);
	CUI();
	save();
	return 0;
}

void errNaN() {
	acout("Вы ввели не число! Пожалуйста, будьте внимательны при вводе числа");
	acout("Если ошибка продолжает появляться, пожалуйста сообщите разработчику");
	system("pause");
	system("cls");
}

//error Number Not From List
void errNNFL() {
	acout("Вы ввели число выходящее за рамки выбора! Повторите попытку");
	system("cls");
	system("pause");
}

void CUI() {
	system("cls");

	acout("Здравствуйте! Я программа, которая поможет вам следовать методу помидора");
	acout("Пожалуйста, выберите то что вы хотите сделать: ");
	
	const int ArrStrSize = 4;
	acout("0 - Выход из программы");
	acout("1 - Старт метода");
	acout("2 - Смена цвета текста");
	acout("3 - Отключение/включение \"анимации\" текста");
	acout("Ваш выбор: ", false);

	string choose;
	int iChoose;
	cin >> choose;

	try {
		iChoose = stoi(choose);
	} catch (...) {
		errNaN();
	}

	system("cls");

	switch (iChoose)
	{
	case 0:
		stats[0] += runtime_tomatoCount;
		return;
	case 1:
		tomatoMethod();
		CUI();
		break;
	case 2:
		changeColor();
		CUI();
		break;
	case 3:
		if (stats[2] != 0) stats[2] = 0;
		else stats[2] = 1;
		CUI();
		break;
	default:
		errNNFL();
		CUI();
		break;
	}
	return;
}

void tomatoMethod() {
	system("cls");
	timerForWork();

	acout("Время работы окончено. Выберите дальнейший план действий: ");
	acout("0 - Выход в главное меню");
	acout("1 - Отдохну, а затем продолжу работу");
	acout("2 - Хочу поработать ещё 5 минут!");
	acout("3 - Ещё один помидор!");
	acout("Ваш выбор: ", false);

	string choose;
	int iChoose;
	cin >> choose;
	try {
		iChoose = stoi(choose);
	} catch (...) {
		errNaN();
	}

	system("cls");

	switch (iChoose)
	{
	case 0:
		return;
	case 1:
		timerForRest();
		system("cls");
		timerForWork();
		tomatoMethod();
		break;
	case 2:
		timerForWork(true);
		break;
	case 3:
		timerForWork();
		tomatoMethod();
		break;
	default:
		errNNFL();
		tomatoMethod();
		break;
	}
	return;
}

void changeColor() {
	color consoleColor;
	color endOfEnum = END_OF_COLOR;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	acout("Выберите цвет из списка: ");
	for (int i = 1; i < endOfEnum; i++) {
		SetConsoleTextAttribute(hConsole, i);
		string out = to_string(i) + " - " + rusColor[i - 1];
		acout(out);
	}
	acout("Ваш выбор: ", false);
	string choose;
	int iChoose;
	cin >> choose;
	try {
		iChoose = stoi(choose);
	} catch (...) {
		errNaN();
	}
	if (iChoose > endOfEnum) {
		errNNFL();
		changeColor();
		return;
	} else {
		SetConsoleTextAttribute(hConsole, iChoose);
		stats[1] = iChoose;
	}
}