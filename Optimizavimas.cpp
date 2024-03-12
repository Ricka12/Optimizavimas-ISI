// Optimizavimas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
using namespace std;
double skaiciuojamFunkcija(double x) 
{
	return ((x * x - 2) * (x * x - 2)) / 4 - 1;
}
double skaiciuojamFunkcijosIsvestine(double x)
{
	return x * x * x - 2 * x;
}
double skaiciuojamFunkcijosDvigubaIsvestine(double x)
{
	return 3 * x * x - 2;
}
int main()
{
	ofstream R("Octave.txt");
	R << "hold off" << endl;
	R << "grid on" << endl;
	R << "x = linspace(0,7,50)" << endl;
	R << "y=(x.^2 - 2).^2 / 4 - 1" << endl;
	R << "plot(x,y, \"b\")" << endl;
	R << "hold on" << endl;
	//////////////////////////////////////////////////////////////////////////////////////
	//Intervalo dalijimo pusiau metodas
	//////////////////////////////////////////////////////////////////////////////////////

	int pabaiga = 0, skaiciavimuKiekisDalijimoPusiau=0, iteracijuSkDalPus=0;
	double l=0, r=10;
	double xm = (l + r) / 2;
	double L = r - l;
	double x1, x2;
	double fxm, fx1, fx2;
	fxm = skaiciuojamFunkcija(xm);
	skaiciavimuKiekisDalijimoPusiau++;
	while (pabaiga != 1)
	{
		R << "plot(" << xm << ", " << fxm << ", \"r+\")" << endl;
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
	cout << "Intervalo dalijimo pusiau metodas" << endl << "Minimumas x : " << xm << " y : " << fxm << " skaiciavimu kiekis : " << skaiciavimuKiekisDalijimoPusiau << " Zingsniu skaicius : " << iteracijuSkDalPus << endl;
	//////////////////////////////////////////////////////////////////////////////////////
	//Auksinio pjuvio algoritmas 
	//////////////////////////////////////////////////////////////////////////////////////
	int skaiciavimuKiekisAuksinisPjuvis=0,iteracijuSkAukPjuv=0;
	double fibinacioSkaicius = 0.61803;
	pabaiga = 0;
	l = 0, r = 10;
	L = r - l;
	x1 = r - fibinacioSkaicius * L;
	x2 = l + fibinacioSkaicius * L;
	fx1 = skaiciuojamFunkcija(x1);
	fx2 = skaiciuojamFunkcija(x2);
	skaiciavimuKiekisAuksinisPjuvis += 2;
	while (pabaiga != 1)
	{
		iteracijuSkAukPjuv++;
		R << "plot(" << x2 << ", " << fx2 << ", \"g+\")" << endl;
		if (fx2 < fx1)
		{
			l = x1;
			L = r - l;
			x1 = x2;
			fx1 = fx2;
			x2 = l + fibinacioSkaicius * L;
			fx2 = skaiciuojamFunkcija(x2);
			skaiciavimuKiekisAuksinisPjuvis++;
		}
		else {
			r = x2;
			L = r - l;
			x2 = x1;
			fx2 = fx1;
			x1 = r - fibinacioSkaicius * L;
			fx1 = skaiciuojamFunkcija(x1);
			skaiciavimuKiekisAuksinisPjuvis++;
		}
		if (L < 0.0001)
		{
			pabaiga = 1;
		}
	}
	cout << endl << "Auksinio pjuvio metodas" << endl << "Minimumas: " << x2 << " y : " << fx2 << " skaiciavimu kiekis : " << skaiciavimuKiekisAuksinisPjuvis << " Zingsniu skaicius : " << iteracijuSkAukPjuv << endl;
	//////////////////////////////////////////////////////////////////////////////////////
	//Niutono metodas
	//////////////////////////////////////////////////////////////////////////////////////
	double xNiutono = 5, zingsniuIlgis;
	int iteracijuSkNiutono = 0, skaiciavimuKiekisNiutono = 0;
	pabaiga = 0;
	while (pabaiga != 1)
	{
		R << "plot(" << xNiutono << ", " << skaiciuojamFunkcija(xNiutono) << ", \"m+\")" << endl; //sio neskaiciuoju i bendra skaiciavimu kieki nes cia tik visualizacijai
		zingsniuIlgis = xNiutono;
		iteracijuSkNiutono++;
		xNiutono = xNiutono - skaiciuojamFunkcijosIsvestine(xNiutono) / skaiciuojamFunkcijosDvigubaIsvestine(xNiutono);
		skaiciavimuKiekisNiutono += 2;
		if (zingsniuIlgis-xNiutono <= 0.0001)
		{
			pabaiga = 1;
		}
	}

	cout << endl << "Niutono metodas" << endl << "Minimumas: " << xNiutono << " y : " << skaiciuojamFunkcija(xNiutono) << " skaiciavimu kiekis : " << skaiciavimuKiekisNiutono << " Zingsniu skaicius : " << iteracijuSkNiutono << endl;
}

