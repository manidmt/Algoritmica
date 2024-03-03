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
/*
void ResizeT(int **arr, int tam, int n){

    cout << "Entro en ResizeT " << endl;
    int **T =  new int * [tam];
    for (int i = 0; i < tam; i++)
        T[i]= new int [n];

    for (int i = 0; i < tam; i++)
        for (int j = 0; j < n; j++){
            T[i][j] = arr[i][j];
            cout << T[i][j] << " ";
        }
    cout << endl;
    arr = T;
    for(int i = 0; i < tam; i++)  delete [] T[i];
    delete [] T;
}
*/
void Copy(int *arr, int *copiar, int n){

    for (int i = 0; i < n; i++) arr[i] = copiar[i];
}

void ResizeV(int *arr, int anttam,int tam){
    
    cout << "Entro en ResizeV " << endl;
    int * newArr = new int [tam];
    Copy(newArr, arr, anttam);
    //cout << endl;
    arr = newArr;
    delete [] newArr;
}

void MezclaArr(int const *arr1, int const *arr2, int *res, int n1, int n2, int nr){

    ResizeV(res, nr, (n1+n2));
    int id1 = 0, id2 = 0, idr = 0;
/*
    cout << "Primer array: ";
    for (int i = 0; i < n1; i++)    cout << arr1[i] << " ";
    cout << endl << "Segundo array: ";
    for (int i = 0; i < n1; i++)    cout << arr2[i] << " ";
    cout << endl;
 */

    while ((id1 != n1) && (id2 != n2)){
        
        cout << "Se compara: " << arr1[id1] << " pos (" << id1 << ") y " << arr2[id2] << " pos (" << id2 << ")";

		if (arr1[id1] == arr2[id2]){
			
			res[idr] = arr1[id1];
            idr++;
            id1++;
            res[idr] = arr2[id2];
			idr++;
			id2++;
            cout << ",se añaden ambos" << endl;
		}
		
		else if (arr1[id1] < arr2[id2]){
			
            res[idr] = arr1[id1];
            cout << " ,se añade " << arr1[id1] << endl;
			idr++;
            id1++;
		}
		
		else if (arr1[id1] > arr2[id2]){
			
			res[idr] = arr2[id2];
            cout << " ,se añade " << arr2[id2] << endl;
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
                res[idr] = arr2[id1];
                idr++;
            }
	}
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

for (int i=0; i<k; i++) {
 for (int j=0; j<n; j++)
   cout << T[i][j] << " ";
 cout << " " << endl;
}

/*
    int *p1 = new int [5];
    int *p2 = new int [5];
    int *pr = new int [0];

    for (int i = 0; i < 5; i++){

        p1[i] = i;
        p2[4-i] = i;
    }

    MezclaArr(p1, p2, pr, 5, 5, 0);

    for (int i = 0; i < 10; i++)
        cout << pr[i] << " ";*/

    int * auxv = new int [n];
    tantes = chrono::high_resolution_clock::now();
    int sizT = k-1;
    int sizA = n;
    Copy(auxv, T[sizT], n); 
    while (sizT != 0){
        sizT--;
        MezclaArr(auxv, T[sizT], auxv, sizA, n, sizA);
        sizA += n;
    }
    tdespues = chrono::high_resolution_clock::now();
    transcurrido = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);
    cout << "Resultado final:\n";
    for (int i = 0; i < sizA; i++)  cout << auxv[i] << " ";
    cout << endl;
    cout << "Tam: " << sizA << "\tTmp: " << transcurrido.count() << "\n";
}