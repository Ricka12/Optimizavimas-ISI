#include <iostream>
#include <fstream>
using namespace std;

ofstream R("Octave.txt");
/////////////////////////////////////////////////////////////////////////////////////////////////
struct duKint {
	double xNaujas1, xNaujas2;
};
/////////////////////////////////////////////////////////////////////////////////////////////////
bool hessePatikra(double x2, double x3)
{
	return 2 * x3 >= 0 && 2 * x2 + 2 * x3 - 1 >= 0 && 2 * x2 >= 0;//grazina 1 jei hesse matrica teigiamai apibrezta
}

double tiksloFunkcija(double x2, double x3)
{
	return (x2 * x2 * x3 + x2 * x3 * x3 - x2 * x3) / 8;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
duKint gradientas(duKint x)
{
	duKint a;
	a.xNaujas1 = (2 * x.xNaujas1 * x.xNaujas2 + x.xNaujas2 * x.xNaujas2 - x.xNaujas2) / 8;
	a.xNaujas2 = (x.xNaujas1 * x.xNaujas1 + 2 * x.xNaujas1 * x.xNaujas2 - x.xNaujas1) / 8;

	return a;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void gradientinisNusileidimas(duKint a)
{
	duKint zingsnis = a;
	double gamma = 0.1;
	int pabaiga = 0;
	while (pabaiga != 1)
	{
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
// 
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
	R << "% Taskas(0, 0)" << endl;// 
	gradientinisNusileidimas(a);
	R << "% Taskas(1, 1) " << endl;// 
	gradientinisNusileidimas(b);
	R << "% Taskas(0.2, 0.4) " << endl;// 
	gradientinisNusileidimas(c);
	////////////////////////////////////////////////////////////////////////////////////greiciausiasNusileidimas

	////////////////////////////////////////////////////////////////////////////////////deformuotasSimplekso

}