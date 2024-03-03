#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <algorithm>
//#include <vector>

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

void MezclaVec(const int *arr1, const int *arr2, int n1, int n2, int *&ret){

    int *res = new int [n1+n2];
	int id1 = 0, id2 = 0, idr = 0;

    
    /*cout << "Primer array: ";
    for (int i = 0; i < n1; i++)    cout << arr1[i] << " ";
    cout << endl << "Segundo array: ";
    for (int i = 0; i < n2; i++)    cout << arr2[i] << " ";
    cout << endl;*/
 
	
    while ((id1 != n1) && (id2 != n2)){
        
        //cout << "Se compara: " << arr1[id1] << " pos (" << id1 << ") y " << arr2[id2] << " pos (" << id2 << ")";

		if (arr1[id1] == arr2[id2]){
			
			res[idr] = arr1[id1];
            idr++;
            id1++;
            res[idr] = arr2[id2];
			idr++;
			id2++;
            //cout << ",se añaden ambos" << endl;
		}
		
		else if (arr1[id1] < arr2[id2]){
			
            res[idr] = arr1[id1];
            //cout << " ,se añade " << arr1[id1] << endl;
			idr++;
            id1++;
		}
		
		else if (arr1[id1] > arr2[id2]){
			
			res[idr] = arr2[id2];
            //cout << " ,se añade " << arr2[id2] << endl;
			idr++;
            id2++;
		}

        if (id1 == n1)
            for (id2; id2 < n2; id2++){
                res[idr] = arr2[id2];
                idr++;
            }
        
        if (id2 == n2)
            for (id1; id1 < n1; id1++){
                res[idr] = arr1[id1];
                idr++;
            }
	}
    
    /*cout << "Resultado: ";
    for (int i = 0; i < n1+n2; i++)    cout << res[i] << " ";
    cout << endl;*/
    delete [] ret;
    ret = res;
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
/*
for (int i=0; i<k; i++) {
 for (int j=0; j<n; j++)
   cout << T[i][j] << " ";
 cout << " " << endl;
}*/

    tantes = chrono::high_resolution_clock::now();
    int tamanios [k];
    for (int i = 0; i < k; i++) tamanios[i] = n;
    int i, n_vec = k, *auxv;
    while (n_vec > 1){
        for (i = 0; i < n_vec-1; i += 2){
            
            //cout << "Tam de T: " << n_vec << endl;
            MezclaVec(T[i], T[i+1], tamanios[i], tamanios[i+1], T[i/2]);
            tamanios[i] *= 2;
            tamanios[i+1] *= 2;
        }
        
        if (i == n_vec-1){
            auxv = T[i/2];
            T[i/2] = T[n_vec-1];
            T[n_vec-1] = auxv;
            tamanios[i/2] = tamanios[n_vec-1];

            /*cout << "Entramos en el if con n_vec = " << n_vec << endl;
            for (int j = 0; j < n_vec; j++){
                for (int t = 0; t < tamanios[j]; t++) cout << T[j][t] << " ";
                cout << endl;
            }*/
            n_vec /= 2;
            n_vec ++;
            
        } 
        else n_vec /= 2;
    }
    tdespues = chrono::high_resolution_clock::now();
    transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);

    /*cout << "Resultado final:\n";
    for (int i = 0; i < n*k; i++)  cout << T[0][i] << " ";
    cout << endl;*/
    cout << "Tam: " << n*k << "\tTmp: " << transcurrido.count() << "\n";

    for(int i = 0; i < k; i++)  delete [] T[i];
    delete [] T;
}