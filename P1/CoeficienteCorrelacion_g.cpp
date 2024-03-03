/*
	Autor: Aarón Jerónimo Fernández y Enrique López García

	Descripción: Dada una función de ajuste calcula el coeficiente de determinación.

	USO: "./CoeficienteCorrelación Arg1 Arg2 (Arg3) Arg4*"
	Arg1: Archivo del que extraer los datos.
	Arg2: Tipo de función a elegir entre lineal, superlineal, polinómica...
	(Arg3): Grado de la función polinómica. Este argumento es opcional-
	Arg4*: Constantes de la función. Pueden variar dependiendo de la función escogida.
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

vector <double> constantes,x,y;
double (*funcion)(double x) = nullptr;

double polinomica(double x) {
	double output = 0;
	for (int i = 0; i<constantes.size(); i++) {
		output += constantes[i]*pow(x,constantes.size()-i-1);
	}
	return output;
}

double superlineal(double x) {
    double aux =(constantes.at(0)*x*(log(constantes.at(1)*x)/log(2))+constantes.at(2)*x+constantes.at(3));
	return aux;
}

double exponencial(double x) {
	return (constantes.at(0)*exp(constantes.at(1)*x)+constantes.at(2));
}

double exponencial2(double x) {
	return (constantes.at(0)*pow(2,constantes.at(1)*x)+constantes.at(2));
}

double VarRes() {
	double output = 0;
	for (int i = 0; i < y.size(); i++) {
		//cout << "i:" << i << " "<< y.at(i)-funcion(x.at(i)) << " " << pow(y.at(i)-funcion(x.at(i)),2) << endl;
		output += pow(y.at(i)-funcion(x.at(i)),2);
		//cout << "i:" << i << " " << output << endl;
	}
	return output/y.size();
}

double VarExp() {
	double media = 0;
	for (int i = 0; i < y.size(); i++)
		media += y.at(i);
	media /= y.size();

	double output = 0;
	for (int i = 0; i < y.size(); i++)
		output += pow(funcion(x.at(i))-media,2);

	return output/y.size();
}

int main (int argc, char *argv[]) {

	if (argc < 3) {
		cout << "USO: \"./r Arg1 Arg2 (Arg3) Arg4*\"" << endl
		     << "Arg1: Archivo del que extraer los datos." << endl
		     << "Arg2: Tipo de función a elegir entre: p(polinómica), s(superlineal), e(exponencial), e2 (exponencial en base 2)" << endl
		     << "(Arg3): Grado de la función polinómica. Este argumento es opcional-" << endl
		     << "Arg4*: Constantes de la función. Pueden variar dependiendo de la función escogida." << endl;
		exit(1);
	}

	// cout << "Leyendo tipo de función: " << argv[2] << endl;

	double aux;
	string comp = argv[2];
	string file = argv[1];

	//cout << "Leyendo constantes" << endl;

	if (comp == "p") {

		int grado = atoi(argv[3]);
		
		if (3+1+grado+1 != argc) {
			cout << "Grado " << grado << " nArg " << argc << endl;
			cout << "Error en constantes" << endl;
			return -1;
		}
		
		for (int i=0; i<=grado; i++)
			constantes.push_back(atof(argv[4+i]));

		funcion = polinomica;

	}
	else if (comp == "s") {

		if (3+4 != argc) {
			cout << "Error en constantes" << endl;
			return -1;
		}

		for (int i=0; i<4; i++)
			constantes.push_back(atof(argv[3+i]));		

		funcion = superlineal;

	}
	else if (comp == "e") {

		if (3+3 != argc) {
			cout << "Error en constantes" << endl;
			return -1;
		}

		for (int i=0; i<3; i++)
			constantes.push_back(atof(argv[3+i]));

		funcion = exponencial2;

	} else {
		cout << "Tipo de función incorrecto" << endl;
		return -1;
	}

	/*
	for (int i=0; i<constantes.size(); i++)
		cout << constantes.at(i) << "\t";
	cout << endl;
	*/	

	// cout << "Leyendo archivo " << file << endl;

	fstream fi;

	fi.open(file);

	if (!fi) {
		cout << "Error al abrir el archivo" << file << endl;
		return -1;
	} 

	int contador = 0;

	while (fi >> aux) {
		//cout << aux << " " << funcion(aux) << " ";
		x.push_back(aux);
		fi >> aux;
		//cout << aux << endl;
		y.push_back(aux);
	}

	fi.close();

	double var_exp = VarExp();
	double var_res = VarRes();
	//cout << "Varianzas: Explicativa " << var_exp << " Residual " << var_res << endl;
	cout << "Coeficiente de correlación: " << var_exp/(var_exp+var_res) << endl;

	return 0;
}
