#include <iostream>
#include <fstream>
using namespace std;

ofstream R("Octave.txt");
/////////////////////////////////////////////////////////////////////////////////////////////////
struct duKint { //Vartotojo apibreztas kintamasis kad galima butu perduoti 2 kintamuosius
	double xNaujas1, xNaujas2;
};
/////////////////////////////////////////////////////////////////////////////////////////////////
bool hessePatikra(double x2, double x3) //gal implementuosiu dar nezinau ar reikia !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
{
	return 2 * x3 >= 0 && 2 * x2 + 2 * x3 - 1 >= 0 && 2 * x2 >= 0;//grazina 1 jei hesse matrica teigiamai apibrezta
}

double tiksloFunkcija(double x2, double x3) //tikslo funkcija su kuria yra dirbama
{
	return (x2 * x2 * x3 + x2 * x3 * x3 - x2 * x3) / 8;
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
double skaiciuojamFunkcija(double x)
{
	return ((x * x - 2) * (x * x - 2)) / 4 - 1;
}
////////////////////// Kaip pasiskaiciuot gamma?? kas yra gama siuo atveju?? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
void intervaloPusiau()
{
	int pabaiga = 0, skaiciavimuKiekisDalijimoPusiau = 0, iteracijuSkDalPus = 0;
	double l = 0, r = 10;
	double xm = (l + r) / 2;
	double L = r - l;
	double x1, x2;
	double fxm, fx1, fx2;
	fxm = skaiciuojamFunkcija(xm);
	skaiciavimuKiekisDalijimoPusiau++;
	while (pabaiga != 1)
	{
		iteracijuSkDalPus++;
		x1 = l + L / 4;
		x2 = r - L / 4;
		fx1 = skaiciuojamFunkcija(x1);
		fx2 = skaiciuojamFunkcija(x2);
		skaiciavimuKiekisDalijimoPusiau += 2;
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
		if (zingsnis.xNaujas1 - a.xNaujas1 <= 0.0000000001 && zingsnis.xNaujas2 - a.xNaujas2 <= 0.0000000001)//Iki kokio min zingsnio turi eiti?? !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		{
			pabaiga = 1;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void greiciausiasNusileidimas(duKint a)
{
	duKint zingsnis = a;
	double gamma;
	int pabaiga = 0;
	srand(time(NULL));
	while (pabaiga != 1)
	{
		gamma = rand()%1+1; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
		zingsnis.xNaujas1 = a.xNaujas1;
		zingsnis.xNaujas2 = a.xNaujas2;
		R << "plot3(" << a.xNaujas1 << ", " << a.xNaujas2 << ", " << tiksloFunkcija(a.xNaujas1, a.xNaujas2) << ",'ro', 'MarkerSize', 5)" << endl;// Vizualizcijai su octave
		a.xNaujas1 = a.xNaujas1 - gamma * gradientas(a).xNaujas1;
		a.xNaujas2 = a.xNaujas2 - gamma * gradientas(a).xNaujas2;
		if (zingsnis.xNaujas1 - a.xNaujas1 <= 0.0000000001 && zingsnis.xNaujas2 - a.xNaujas2 <= 0.0000000001)//Iki kokio min zingsnio turi eiti??
		{
			pabaiga = 1;
		}
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
	R << "xlabel('X-axis')" << endl;
	R << "ylabel('Y-axis')" << endl;
	R << "zlabel('Z-axis')" << endl;

	R << "hold on" << endl;
	////////////////////////////////////////////////////////////////////////////////////gradientinisNusileidimas
	duKint a{0,0};
	duKint b{ 1,1 };
	duKint c{0.2,0.4};
	R << "% Taskas(0, 0)" << endl;
	gradientinisNusileidimas(a);
	R << "% Taskas(1, 1) " << endl;
	gradientinisNusileidimas(b);
	R << "% Taskas(0.2, 0.4) " << endl;
	gradientinisNusileidimas(c);
	////////////////////////////////////////////////////////////////////////////////////greiciausiasNusileidimas
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