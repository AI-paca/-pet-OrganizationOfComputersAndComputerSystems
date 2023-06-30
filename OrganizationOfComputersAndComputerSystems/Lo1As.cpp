#include <iostream> // потоковый ввод/вывод 
using namespace std;
//функция вычисления выражения (4*a-99-3*b)/(10*c*c-5/d);
int calc(int a, int b, int c, int d) {
	int result = 0;
	__asm {
		mov eax, a
		mov ebx, b
		mov ecx, c
		mov edx, d
		imul ebx, 3; <ebx> = b * 3
		imul eax, 4; <eax> = a * 4
		sub eax, ebx; <eax> = a * 4 - b * 3
		sub eax, 99; <eax> = a * 4 - b * 3 - 99
		push eax; в стеке a * 4 - b * 3 - 99
		imul ecx, ecx; <ecx:ecx> = c * c
		imul ecx, 10; <ecx> = c * c * 10
		mov eax, -5; <eax> = -5
		mov ebx, d
		cdq; eax ==> edx:eax;
		idiv ebx; eax: = 5 / d
			add ecx, eax; <eax> = c * c * 10 - 5 / d
			pop eax;  <eax> = a * 4 - b * 3 - 99
			cdq; eax ==> <edx:eax>
			idiv ecx; <eax> = (a * 4 - b * 3 - 99) / (c * c * 10 - 5 / d)
			mov result, eax; result = eax
	}
	return result; // возвращаем результат вычисления выражения 
}

int calc_cpp(int a, int b, int c, int d) {
	return  (4 * a - 99 - 3 * b) / (10 * c * c - 5 / d);
}

int Lo1As() {
	setlocale(LC_ALL, "rus");
	cout << "Лабораторная работа №1. Выполнил студент Аверкина Виктория группы 6104 Варисант 91" << endl << "Вычислить выражение (4 * a - 99 - 3 * b) / (10 * c * c - 5 / d)" << endl;
	int a, b, c, d;
	cout << "a = "; cin >> a; // потоковый ввод/вывод
	cout << "b = "; cin >> b;
	cout << "c = "; cin >> c;
	cout << "d = "; cin >> d;
	if ((d == 0) || ((10 * c * c - 5 / d) == 0)) {
		cout << "Ошибка! деление на 0" << endl;
	}
	else {
		cout << "Резудьтат на asm: " << calc(a, b, c, d) << endl;
		cout << "результат на c++: " << calc_cpp(a, b, c, d) << endl;
	}
	system("PAUSE");
	return 0;
}