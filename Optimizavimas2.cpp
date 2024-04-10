#include <iostream>
#include <fstream>
using namespace std;

ofstream R("Octave.txt");
/////////////////////////////////////////////////////////////////////////////////////////////////
struct duKint { //Vartotojo apibreztas kintamasis kad galima butu perduoti 2 kintamuosius
	double xNaujas1, xNaujas2;
};
/////////////////////////////////////////////////////////////////////////////////////////////////
bool hessePatikra(double x2, double x3) 
{
	return 2 * x3 >= 0 && 2 * x2 + 2 * x3 - 1 >= 0 && 2 * x2 >= 0;//grazina 1 jei hesse matrica teigiamai apibrezta
}
/////////////////////////////////////////////////////////////////////////////////////////////////
double tiksloFunkcija(double x2, double x3) //tikslo funkcija su kuria yra dirbama
{
	return (x2 * x2 * x3 + x2 * x3 * x3 - x2 * x3) / 8;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
double minimizuojamGamma(double gamma, double x1, double x2, double a1, double a2)
{
	if (x1 - gamma * a1 < x2 - gamma * a2 && gamma >= 0)
	{
		return x1 - gamma * a1;
	}
	else if (x1 - gamma * a1 > x2 - gamma * a2 && gamma >= 0)
	{
		return x2 - gamma * a2;
	}
	else {
		return 0;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
duKint gradientas(duKint x) // skaiciuojamas gradientas nuo tasku
{
	duKint a;
	a.xNaujas1 = (2 * x.xNaujas1 * x.xNaujas2 + x.xNaujas2 * x.xNaujas2 - x.xNaujas2) / 8;
	a.xNaujas2 = (x.xNaujas1 * x.xNaujas1 + 2 * x.xNaujas1 * x.xNaujas2 - x.xNaujas1) / 8;

	return a;
}
/////////////////////////////////////////////////////////////////////////////////////////////////Intervalo dalijimo pusiau metodas
double intervaloPusiau(double gamma, duKint a)
{
	int pabaiga = 0;
	double l = 0, r = 10;
	double xm = (l + r) / 2;
	double L = r - l;
	double x1, x2;
	double fxm, fx1, fx2;
	fxm = minimizuojamGamma(xm, a.xNaujas1, a.xNaujas2, gradientas(a).xNaujas1, gradientas(a).xNaujas2);
	while (pabaiga != 1)
	{
		x1 = l + L / 4;
		x2 = r - L / 4;
		
		fx1 = minimizuojamGamma(x1, a.xNaujas1, a.xNaujas2, gradientas(a).xNaujas1, gradientas(a).xNaujas2);
		fx2 = minimizuojamGamma(x2, a.xNaujas1, a.xNaujas2, gradientas(a).xNaujas1, gradientas(a).xNaujas2);
		if (fx1 < fxm)
		{
			r = xm;
			xm = x1;
			fxm = fx1;
		}
		else if (fx2 < fxm)
		{
			l = xm;
			xm = x2;
			fxm = fx2;

		}
		else {
			l = x1;
			r = x2;
		}
		L = r - l;
		if (L < 0.0001)
		{
			pabaiga = 1;
		}
	}
	if (fx1 <= fxm && fx1 <= fx2)
	{
		return fx1;
	}
	else if (fxm <= fx1 && fxm <= fx2)
	{
		return fxm;
	}
	else {
		return fx2;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void gradientinisNusileidimas(duKint a)
{
	duKint zingsnis = a;
	double gamma = 0.75;
	int pabaiga = 0;
	while (pabaiga != 1)
	{
		zingsnis.xNaujas1 = a.xNaujas1;
		zingsnis.xNaujas2 = a.xNaujas2;
		R << "plot3(" << a.xNaujas1 << ", " << a.xNaujas2 << ", " << tiksloFunkcija(a.xNaujas1, a.xNaujas2) << ",'ro', 'MarkerSize', 5)" << endl;// Vizualizcijai su octave
		a.xNaujas1 = a.xNaujas1 - gamma * gradientas(a).xNaujas1;
		a.xNaujas2 = a.xNaujas2 - gamma * gradientas(a).xNaujas2;
		if (zingsnis.xNaujas1 - a.xNaujas1 <= 0.0000000001 && zingsnis.xNaujas2 - a.xNaujas2 <= 0.0000000001)
		{
			pabaiga = 1;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void greiciausiasNusileidimas(duKint a)
{
	duKint zingsnis = a;
	double gamma = 1;
	int pabaiga = 0;
	srand(time(NULL));
	while (pabaiga != 1)
	{
		zingsnis.xNaujas1 = a.xNaujas1;
		zingsnis.xNaujas2 = a.xNaujas2;
		R << "plot3(" << a.xNaujas1 << ", " << a.xNaujas2 << ", " << tiksloFunkcija(a.xNaujas1, a.xNaujas2) << ",'bo', 'MarkerSize', 5)" << endl;// Vizualizcijai su octave
		a.xNaujas1 = a.xNaujas1 - gamma * gradientas(a).xNaujas1;
		a.xNaujas2 = a.xNaujas2 - gamma * gradientas(a).xNaujas2;
		if (zingsnis.xNaujas1 - a.xNaujas1 <= 0.0000000001 && zingsnis.xNaujas2 - a.xNaujas2 <= 0.0000000001)
		{
			pabaiga = 1;
		}
		gamma = intervaloPusiau(gamma, a);
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	//////////////////////////////////////////////////////////////////////////////////// Funkcijos vizualizacija
	R << "hold off" << endl;
	R << "grid on" << endl;
	R << "x2 = linspace(0,1,100)" << endl;
	R << "x3 = linspace(0,1,100)" << endl;
	R << "[x2, x3] = meshgrid(x2, x3)" << endl;
	R << "fx = 1/8 * (x2.^2 .* x3 + x2 .* x3.^2 - x2 .* x3)" << endl;
	R << "surf(x2, x3, fx)" << endl;
	R << "title('Funkcijos vizualizacija')" << endl;
	R << "xlabel('X2-axis')" << endl;
	R << "ylabel('X3-axis')" << endl;
	R << "zlabel('Fx-axis')" << endl;

	R << "hold on" << endl;
	////////////////////////////////////////////////////////////////////////////////////gradientinisNusileidimas
	duKint a{ 0,0 };
	duKint b{ 1,1 };
	duKint c{ 0.2,0.4 };
	/*R << "% Gradientinis nusileidimas" << endl;
	R << "% Taskas(0, 0)" << endl;
	gradientinisNusileidimas(a);
	R << "% Taskas(1, 1) " << endl;
	gradientinisNusileidimas(b);
	R << "% Taskas(0.2, 0.4) " << endl;
	gradientinisNusileidimas(c);*/
	////////////////////////////////////////////////////////////////////////////////////greiciausiasNusileidimas
	R << "% Greičiausias nusileidimas" << endl;
	R << "% Taskas(0, 0)" << endl;
	greiciausiasNusileidimas(a);
	R << "% Taskas(1, 1) " << endl;
	greiciausiasNusileidimas(b);
	R << "% Taskas(0.2, 0.4) " << endl;
	greiciausiasNusileidimas(c);
	////////////////////////////////////////////////////////////////////////////////////deformuotasSimplekso
	/*
	Sudaromas pradinis simpleksas ir visose jo viršun¯ ese ˙
apskaiciuojamos tikslo funkcijos reikšm ˇ es. Simplekso dydi˛ ˙
reguliuoja parametras α. a parenkamas pacio zmogaus??
*/
}