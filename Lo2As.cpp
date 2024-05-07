#include <iostream> // потоковый ввод/вывод 
using namespace std;
//{a / (b + 8)              ;a > b
//- 49a                     ;a = b
//(7a * a - 10b) / (a + b)  ;a < b}

int calc(int a, int b) {
	int result = 0;
	__asm {
		mov	ecx, a; < eсx >= a
		mov	ebx, b; < ebx >= b
		cmp	ecx, ebx; сравнение a и b
		jg	l_bigger; переход если a > b
		jl	l_smaller; переход если a < b
		mov	eax, ecx; < eax >= a
		imul eax, -49; <eax> = a * -49
		jmp	exit_l; переход на конец программы		
	l_bigger:
		add ebx, 8; <ebx> = b+8
		or ebx, ebx; сравнение (b+8) и 0
			je	error; ошибка деление на ноль
		mov	eax, ecx; < eax >= a
		cdq; eax ==> edx:eax;
		idiv ebx; <eax> = a / (b+8)
		jmp	exit_l; переход на конец программы
	l_smaller:
		mov	eax, ecx; < eax >= a
		mov ecx, ebx; < ecx >= b
		add ebx, eax; <eax> = b + a
		or ebx, ebx; сравнение b и 0
			je	error; ошибка деление на ноль
		imul eax, eax; <edx:eax> = a * a
		imul eax, 7; < eax >= 7 * a * a
		imul ecx , 10; < ecx >= 10 * b
		sub	eax, ecx; < eax > = 7 * a * a - 10*b
		cdq; eax ==> edx:eax;
		idiv ebx; <eax> = (7 * a * a - 10 * b) / (b + a)
	exit_l:
		mov result, eax; result = eax
	error :
	}
	return result; // возвращаем результат вычисления выражения 
}

int calc_cpp(int a, int b) {
	if (a > b)
		return a / (b + 8);
	else if (a < b)
		return  (7*a * a - 10*b) / (a + b);
	else
		return -49*a;
}

int Lo2As() {
	setlocale(LC_ALL, "rus");
	cout << "Лабораторная работа №2." << endl << "Вычислить выражение: \n|a / (b + 8)               ;a > b\n{- 49a                     ;a = b\n|(7a * a - 10b) / (a + b)  ;a < b" << endl;
	int a, b;
	cout << "a = "; cin >> a; // потоковый ввод/вывод
	cout << "b = "; cin >> b;
	cout << "Резудьтат на asm: " << calc(a, b) << endl;
	if (((b + 8 == 0) && (a > b)) || ((a < b) && (a + b) == 0))
		cout << "Ошибка! деление на 0" << endl;
	else 
		cout << "результат на c++: " << calc_cpp(a, b) << endl;
	system("PAUSE");
	return 0;
}