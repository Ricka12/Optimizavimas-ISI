#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//////////////////////////////////////////////////////////////////////////////////// Funkcijos vizualizacija
	ofstream R("Octave.txt");
	R << "hold off" << endl;
	R << "grid on" << endl;
	R << "x2 = linspace(0,1,100)" << endl;
	R << "x3 = linspace(0,1,100)" << endl;
	R << "[x2, x3] = meshgrid(x2, x3)" << endl;

	R << "fx = 1/8 * (x2.^2 .* x3 + x2 .* x3.^2 - x2 .* x3)" << endl;
	R << "surf(x2, x3, fx)" << endl;
	R << "xlabel('X-axis')" << endl;
	R << "ylabel('Y-axis')" << endl;
	R << "zlabel('Z-axis')" << endl;
	R << "title('Funkcijos vizualizacija')" << endl;
	R << "hold on" << endl;

	////////////////////////////////////////////////////////////////////////////////////gradientinisNusileidimas
	////////////////////////////////////////////////////////////////////////////////////greiciausiasNusileidimas
	////////////////////////////////////////////////////////////////////////////////////deformuotasSimplekso

}