#include <iostream>
using namespace std;
//В одномерном массиве A = { a[i] } целых чисел вычислить количество 
//ненулевых элементов с нечетными номерами.

int calc(int* arr, int len){
	int result = 0;
	__asm {
		xor esi, esi; подготовим регистр индекса в массиве
		xor edi, edi; счётчик количества элементов
		mov	ebx, arr; ebx указывает на начало массива
		mov	ecx, len; счётчик цикла по всем элементам массива
		jcxz exit_1; завершить если длина массива 0
	begin_loop:
		mov	eax, [ebx + esi * 4]; определяем текущий элемент
		cmp	eax, 0;	сравнение a[i] и 0
			je	end_loop;	если элемент нулевой
		inc	edi;	элемент удовлетворяет условию, увеличиваем счётчик
	end_loop :
		add	esi, 2; переходим к следующему элементу
		sub ecx, 2;
		jg begin_loop; повторяем цикл для всех элементов массива
	exit_1 : 
		mov	eax, edi; возвращаем количество элементов  удовлетворяет условию
		mov result, eax; result = eax
	}
}

int calc_cpp(int* arr, int len) {
	int count = 0;
	for (int i = 0; i < len; i += 2)
		if (arr[i] != 0)
			count += 1;
	return count;
}

int Lo3As()
{
	setlocale(LC_ALL, "rus");
	cout << "Лабораторная работа №3." << endl << "В одномерном массиве A = { a[i] } целых чисел вычислить количество ненулевых элементов с нечетными номерами." << endl;
	int len;
	cout << "Введите длину массива = "; cin >> len;
	int* arr = new int[len];
	for (int i = 0; i < len; i++)
		cin >> arr[i];
	cout << "Резудьтат на asm: " << calc(arr, len) << endl;
	cout << "результат на c++: " << calc_cpp(arr, len) << endl;
	system("PAUSE");
	return 0;
}