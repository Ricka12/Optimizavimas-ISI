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
double tiksloFunkcija(duKint a) //tikslo funkcija su kuria yra dirbama
{
	return (a.xNaujas1 * a.xNaujas1 * a.xNaujas2 + a.xNaujas1 * a.xNaujas2 * a.xNaujas2 - a.xNaujas1 * a.xNaujas2) / 8.0;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
duKint gradientas(duKint x) // skaiciuojamas gradientas nuo tasku
{
	duKint a;
	a.xNaujas1 = (2 * x.xNaujas1 * x.xNaujas2 + x.xNaujas2 * x.xNaujas2 - x.xNaujas2) / 8;
	a.xNaujas2 = (x.xNaujas1 * x.xNaujas1 + 2 * x.xNaujas1 * x.xNaujas2 - x.xNaujas1) / 8;
	return a;
}
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
void gradientinisNusileidimas(duKint a)
{
	duKint taskai = a; //kad nepakeistu pradinio tasko
	duKint zingsnis = taskai;
	double epsilon = 0.0000000001;
	double gamma = 0.75;
	int pabaiga = 0;
	while (pabaiga != 1)
	{
		zingsnis.xNaujas1 = taskai.xNaujas1;
		zingsnis.xNaujas2 = taskai.xNaujas2;
		R << "plot3(" << taskai.xNaujas1 << ", " << taskai.xNaujas2 << ", " << tiksloFunkcija(taskai) << ",'ro', 'MarkerSize', 10)" << endl;// Vizualizcijai su octave
		taskai.xNaujas1 = taskai.xNaujas1 - gamma * gradientas(taskai).xNaujas1;
		taskai.xNaujas2 = taskai.xNaujas2 - gamma * gradientas(taskai).xNaujas2;
		if (zingsnis.xNaujas1 - taskai.xNaujas1 <= epsilon && zingsnis.xNaujas2 - taskai.xNaujas2 <= epsilon)
		{
			pabaiga = 1;
		}
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////
// Gradientinio nusileidimo optimizavimo
duKint gammosFormule(double gamma, duKint x, duKint grad) {
	double xNaujas1 = x.xNaujas1 - gamma * grad.xNaujas1;
	double xNaujas2 = x.xNaujas1 - gamma * grad.xNaujas2;
	return { xNaujas1, xNaujas2 };
}
double gammosFormule(duKint x, duKint grad, double gamma) {
	double xNaujas1 = x.xNaujas1 - gamma * grad.xNaujas1;
	double xNaujas2 = x.xNaujas1 - gamma * grad.xNaujas2;
	return tiksloFunkcija({ xNaujas1, xNaujas2 });
}
/////////////////////////////////////////////////////////////////////////////////////////////////Intervalo dalijimo pusiau metodas optimizuoti gamma

double intervaloPusiau(duKint Xi, duKint grad)
{
	int pabaiga = 0;
	double l = 0, r = 5;
	double xm = (l + r) / 2;
	double L = r - l;
	double x1, x2;
	double fxm, fx1, fx2;
	fxm = gammosFormule(Xi, grad, xm);
	while (pabaiga != 1)
	{
		x1 = l + L / 4;
		x2 = r - L / 4;

		fx1= gammosFormule(Xi, grad, x1);
		fx2= gammosFormule(Xi, grad, x2);
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
	return xm;
}
/////////////////////////////////////////////////////////////////////////////////////////////////
void greiciausiasNusileidimas(duKint X0)
{
	duKint X;
	duKint grad;
	double gamma, naujaReiksme;
	duKint xNaujas;
	double epsilon = 0.00000000000000001;
	X = X0;
	double Xreiksme = tiksloFunkcija(X);
	for (int i = 0; i < 100000; i++)
	{
		R << "plot3(" << X.xNaujas1 << ", " << X.xNaujas2 << ", " << tiksloFunkcija(X) << ",'bo', 'MarkerSize', 10)" << endl;
		grad = gradientas(X);
		if (grad.xNaujas1 == 0 && grad.xNaujas2 == 0) {
			break;
		}
		else {
			gamma = intervaloPusiau(X, grad);
			xNaujas = gammosFormule(gamma, X, grad);
			naujaReiksme = tiksloFunkcija(xNaujas);
		}
		if (sqrt(grad.xNaujas1 * grad.xNaujas1 + grad.xNaujas2 * grad.xNaujas2) < epsilon || abs(naujaReiksme - Xreiksme) < epsilon) {
			break;
		}
		else {
			X = xNaujas;
			Xreiksme = naujaReiksme;
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
	R << "xlabel('X2-axis')" << endl;
	R << "ylabel('X3-axis')" << endl;
	R << "zlabel('Fx-axis')" << endl;

	R << "hold on" << endl;
	////////////////////////////////////////////////////////////////////////////////////gradientinisNusileidimas
	duKint a{ 0,0 };
	duKint b{ 1,1 };
	duKint c{ 0.2,0.4 };
	R << "% Gradientinis nusileidimas" << endl;
	R << "% Taskas(0, 0)" << endl;
	gradientinisNusileidimas(a);
	R << "% Taskas(1, 1) " << endl;
	gradientinisNusileidimas(b);
	R << "% Taskas(0.2, 0.4) " << endl;
	gradientinisNusileidimas(c);

	////////////////////////////////////////////////////////////////////////////////////greiciausiasNusileidimas
	R << "% Greičiausias nusileidimas" << endl;
	R << "% Taskas(0, 0)" << endl;
	greiciausiasNusileidimas(a);
	R << "% Taskas(1, 1) " << endl;
	greiciausiasNusileidimas(b);
	R << "% Taskas(0.2, 0.4) " << endl;
	greiciausiasNusileidimas(c);
	////////////////////////////////////////////////////////////////////////////////////deformuotasSimplekso

}