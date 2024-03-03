#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
#include <vector>

#include <chrono>
using namespace std::chrono;

//generador de ejemplor para el problema de mezcla de k vectores ordenados. Para obtener k vectores ordenados de forma creciente cada uno con n elementos, genera un vector de tama�o k*n con todos los enteros entre 0 y kn-1 ordenados. Se lanzan entonces k iteraciones de un algoritmo de muestreo aleatorio de tama�o n para obtener los k vectores. Est�n ordeados porque el algoritmo de muestreo mantiene el orden

double uniforme() //Genera un n�mero uniformemente distribuido en el
                  //intervalo [0,1) a partir de uno de los generadores
                  //disponibles en C. 
{
 int t = rand();
 double f = ((double)RAND_MAX+1.0);
 return (double)t/f;
}

vector <int> ArrayaVector(int arr[], int tam){

    vector<int> ret;
    int k;
    for (int i = 0; i < tam; i++){
        k = arr[i];
        //cout << k << " ";
        ret.push_back(k);
    }
    /*for (vector<int>::iterator i = ret.begin(); i != ret.end(); ++i)
        cout << " " << *i;

    cout << endl;*/
    return ret;  
}

vector <int> MezclaVec(const vector<int> &a, const vector<int> &b){

    vector<int> ret;
    bool termina = false;
	int id1 = 0, id2 = 0;
	int n1 = a.size(), n2 = b.size();
	
	while ((id1 != n1) && (id2 != n2)){
        
        //cout << "Se compara: " << a.at(id1) << " pos (" << id1 << ") y " << b.at(id2) << " pos (" << id2 << ")" << endl;

		if (a.at(id1) == b.at(id2)){
			
			ret.push_back(a.at(id1));
            ret.push_back(b.at(id2));
			id1++;
			id2++;
            //cout << ",se añaden ambos" << endl;
		}
		
		else if (a.at(id1) < b.at(id2)){
			
            ret.push_back(a.at(id1));
            //cout << " ,se añade " << a.at(id1) << endl;
			id1++;
		}
		
		else if (a.at(id1) > b.at(id2)){
			
			ret.push_back(b.at(id2));
            //cout << " ,se añade " << b.at(id2) << endl;
			id2++;
		}

        if (id1 == n1)
            for (id2; id2 < n2; id2++)  ret.push_back(b.at(id2));
        
        if (id2 == n2)
            for (id1; id1 < n1; id1++)  ret.push_back(a.at(id1));
	}

    /*for (vector<int>::iterator i = ret.begin(); i != ret.end(); ++i)
        cout << " " << *i;
    cout << "\n";*/
    return ret;
}

int main(int argc, char * argv[])
{


  chrono::high_resolution_clock::time_point tantes, tdespues;
  chrono::duration<double> transcurrido;
  if (argc != 3)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << " <num_vect>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  int k=atoi(argv[2]);


int **T;
T =  new int * [k];
  assert(T);

 for (int i = 0; i < k; i++)
      T[i]= new int [n];

int N=k*n;
int * aux = new int[N];
  assert(aux);

srand(time(0));
//genero todos los enteros entre 0 y k*n-1
for (int j=0; j<N; j++) aux[j]=j;

//para cada uno de los k vectores se lanza el algoritmo S (sampling) de Knuth
for (int i=0; i<k; i++) {
   int t=0;
   int m=0;
   while (m<n) {
    double u=uniforme();
    if ((N-t)*u >= (n-m)) t++;
    else {
        T[i][m]=aux[t];
	t++;
	m++;
    }
  }
}

delete [] aux;

/*for (int i=0; i<k; i++) {
 for (int j=0; j<n; j++)
   cout << T[i][j] << " ";
 cout << " " << endl;
}*/
    vector<vector<int>> vectordevectores;
    for (int i = 0; i < k; i++) vectordevectores.push_back(ArrayaVector(T[i], n));

    for(int i = 0; i < k; i++)  delete [] T[i];
    delete [] T;

    vector<vector<int>> auxv;
    int siz;
    tantes = chrono::high_resolution_clock::now();
    while (vectordevectores.size() != 1){
        //cout << "a";
        siz = vectordevectores.size()-1;
        while (vectordevectores.size() > 1){

            auxv.push_back(MezclaVec(vectordevectores.at(siz), vectordevectores.at(siz-1)));
            vectordevectores.pop_back();
            vectordevectores.pop_back();
            siz -= 2;
            //cout << vectordevectores.size() << endl;
        }

        if (vectordevectores.size() == 1)   auxv.push_back(vectordevectores.front());
        vectordevectores.swap(auxv);
        auxv.clear();
    }
    tdespues = chrono::high_resolution_clock::now();
    transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);

    vector<int> resultante = vectordevectores.front();
    /*for (vector<int>::iterator i = resultante.begin(); i != resultante.end(); ++i)
        cout << " " << *i;*/

    cout << "Tam: " << resultante.size() << "\t" << transcurrido.count() << "\n";
}