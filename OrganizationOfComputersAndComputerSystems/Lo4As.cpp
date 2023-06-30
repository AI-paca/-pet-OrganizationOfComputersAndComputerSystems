#include <iostream>
#include <cmath>
using namespace std;
//X=-91*π -sin(π*a)-cos(b)-tg(a)+ctg(-a)+ π/(a*a+b)/(91*a-b)
const double getpi()
{
	double pi;
	__asm
	{
		finit; инициализировать процессор FPU(подготовка для операций с плавающей точкой)
		fldpi; загрузить π(встроенную константу) в стек FPU
		fstp pi; извлечь из стека π и сохранить в pi
	}
	return pi;
}
const double pi = getpi();


double calc(double a, double b) {
	double result = 0;
	const double c91 = 91;
	__asm
	{
		; st0 st1 st2 st3 st4 - регистры для double(чисел с плавающей точкой)
		//X=-91*π -sin(π*a)-cos(b)-tg(a)+ctg(-a)+ π/(a*a+b)/(91*a-b)
		finit; инициализировать процессор FPU(подготовка для операций с плавающей точкой)
		fld a; st0 = a /*a*/
		fld st(0); st0 = a /*a a*/

		fchs; st0 = -a  /*-a a*/
		fptan; st0 = 1 st1 = -tan(a) /*-tan(a) a*/
		fdiv st(0), st(1); st0 = cot(-a) /*cot(-a) -tan(a) a*/  
			//jp	exit_l; //divbyzero
		faddp st(1), st(0); st0 = cot(-a) /*-tan(a)+cot(-a) a*/

		fldpi; st0 = pi /*pi -tan(a)+cot(-a) a*/
		fmul st(0), st(2); st0 = pi * a /*pi*a -tan(a)+cot(-a) a*/
		fsin; st0 = sin(pi * a) /*sin(π*a) -tan(a)+cot(-a) a*/
		fsubp st(1), st(0); st0 = cot(-a) - tan(a) - sin(pi * a) /*-sin(π*a)-tan(a)+cot(-a) a*/

		fld b; st0 = b /*b -sin(π*a)-tan(a)+cot(-a) a*/
		fld st(0); st0 = b /*b b -sin(π*a)-tan(a)+cot(-a) a*/
		fcos; st0 = cos(b) /*cos(b) b -sin(π*a)-tan(a)+cot(-a) a*/
		fsubp st(2), st(0); st1 = cot(-a) - tan(a) - sin(pi * a) - cos(b)  /*b -cos(b)-sin(π*a)-tan(a)+cot(-a) a*/

		fld c91; st0=91  /*91 b -cos(b)-sin(π*a)-tan(a)+cot(-a) a*/
		fmul st(0), st(3); st0 = 91 * a /*91*a b -cos(b)-sin(π*a)-tan(a)+cot(-a) a*/
		fsub st(0), st(1); st0 = 91 * a-b /*91*a-b b -cos(b)-sin(π*a)-tan(a)+cot(-a) a*/
		fxch st(3); st0 = a st2 = cot(-a) - tan(a) - sin(pi * a) - cos(b) /*a b -cos(b)-sin(π*a)-tan(a)+cot(-a) 91*a-b*/
		fmul st(0), st(0); st3 = a * a/*a*a b -cos(b)-sin(π*a)-tan(a)+cot(-a) 91*a-b*/
		faddp st(1), st(0);  st0 = a * a + b /*a*a+b -cos(b)-sin(π*a)-tan(a)+cot(-a) 91*a-b*/
		fldpi; st0 = pi  /*π a*a+b -cos(b)-sin(π*a)-tan(a)+cot(-a) 91*a-b*/
		fdivrp st(1), st(0); st(0)= pi/ a * a + b /*π/(a*a+b) -cos(b)-sin(π*a)-tan(a)+cot(-a)* 91*a-b*/
		fdivrp st(2), st(0); st(1) = (pi / a * a + b)/(91 * a - b) /*π/(a*a+b)/(91*a-b) -cos(b)-sin(π*a)-tan(a)+cot(-a)*/
			jo	exit_l; //divbyzero
		faddp st(1), st(0); st(0) = cot(-a) - tan(a) - sin(pi * a) - cos(b) + (pi / a * a + b) / (91 * a - b) /*-cos(b)-sin(π*a)-tan(a)+cot(-a)+π/(a*a+b)/(91*a-b) */
		fldpi; st0 = pi /*π -cos(b)-sin(π*a)-tan(a)+cot(-a)+π/(a*a+b)/(91*a-b) */
		fld c91; st0 = 91 /*91 π -cos(b)-sin(π*a)-tan(a)+cot(-a)+π/(a*a+b)/(91*a-b) */
		fchs;  st0 = -91  /*-91 π -cos(b)-sin(π*a)-tan(a)+cot(-a)+π/(a*a+b)/(91*a-b) */
		fmulp st(1), st(0); st0 = -91*pi /*-91*π -cos(b)-sin(π*a)-tan(a)+cot(-a)+π/(a*a+b)/(91*a-b) */
		faddp st(1), st(0); st(0) = -91 * pi + cot(-a) - tan(a) - sin(pi * a) - cos(b) + (pi / a * a + b) / (91 * a - b) /*-91*π-cos(b)-sin(π*a)-tan(a)+cot(-a)+π/(a*a+b)/(91*a-b) */
		fstp result;
	exit_l:
		finit;
	}
	return result;
}

double calc_cpp(double a, double b) {
	return -91 * pi - sin(pi * a) - cos(b) - tan(a) + 1/tan(-a) + pi / (a * a + b) / (91 * a - b);
}

int Lo4As()
{
	setlocale(LC_ALL, "rus");
	cout << "Лабораторная работа №4. Выполнил студент Аверкина Виктория группы 6104 Варисант 91" << endl << "Вычислить X=-91*pi-sin(pi*a)-cos(b)-tg(a)+ctg(-a)+pi/(a*a+b)/(91*a-b)" << endl;
	double a, b;
	cout << "a = "; cin >> a; // потоковый ввод/вывод
	cout << "b = "; cin >> b;
	if ((91 * a - b) != 0 && (a * a + b) != 0 && a != 0) {
		cout << "результат на c++: " << calc_cpp(a, b) << endl;
		cout << "Резудьтат на asm: " << calc(a, b) << endl;
	}
	else
		cout << "Ошибка! деление на 0" << endl;
	system("PAUSE");
	return 0;
}