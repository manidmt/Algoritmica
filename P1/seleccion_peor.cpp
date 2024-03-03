/**
   @file Ordenaci�n por selecci�n
*/

   
#include <iostream>
using namespace std;
#include <ctime>
#include <cstdlib>
#include <climits>
#include <cassert>
#include <chrono>
using namespace std::chrono;






/* ************************************************************ */ 
/*  M�todo de ordenaci�n por selecci�n  */

/**
   @brief Ordena un vector por el m�todo de selecci�n.

   @param T: vector de elementos. Debe tener num_elem elementos.
             Es MODIFICADO.
   @param num_elem: n�mero de elementos. num_elem > 0.

   Cambia el orden de los elementos de T de forma que los dispone
   en sentido creciente de menor a mayor.
   Aplica el algoritmo de selecci�n.
*/
inline static 
void seleccion(int T[], int num_elem);



/**
   @brief Ordena parte de un vector por el m�todo de selecci�n.

   @param T: vector de elementos. Tiene un n�mero de elementos 
                   mayor o igual a final. Es MODIFICADO.
   @param inicial: Posici�n que marca el incio de la parte del
                   vector a ordenar.
   @param final: Posici�n detr�s de la �ltima de la parte del
                   vector a ordenar. 
		   inicial < final.

   Cambia el orden de los elementos de T entre las posiciones
   inicial y final - 1de forma que los dispone en sentido creciente
   de menor a mayor.
   Aplica el algoritmo de selecci�n.
*/
static void seleccion_lims(int T[], int inicial, int final);



/**
   Implementaci�n de las funciones
**/

void seleccion(int T[], int num_elem)
{
  seleccion_lims(T, 0, num_elem);
}

static void seleccion_lims(int T[], int inicial, int final)
{
  int i, j, indice_menor;
  int menor, aux;
  for (i = inicial; i < final - 1; i++) {
    indice_menor = i;
    menor = T[i];
    for (j = i; j < final; j++)
      if (T[j] < menor) {
	indice_menor = j;
	menor = T[j];
      }
    aux = T[i];
    T[i] = T[indice_menor];
    T[indice_menor] = aux;
  };
}



int main(int argc, char * argv[])
{

  if (argc != 2)
    {
      cerr << "Formato " << argv[0] << " <num_elem>" << endl;
      return -1;
    }

  int n = atoi(argv[1]);
  double time_total = 0;

  high_resolution_clock::time_point tantes, tdepues, tantes_vacio, tdespues_vacio;
  duration<double> transcurrido;

  int * T = new int[n];
  assert(T);

    for (int i = 0; i < n; i++)
      {
        T[i] = n - i;
      };


    const int TAM_GRANDE = 2000;
    const int NUM_VECES = 100;

    if (n > TAM_GRANDE)
      {
        tantes = high_resolution_clock::now();
        
        seleccion(T, n);
        
        tdepues = high_resolution_clock::now();
    
        transcurrido = duration_cast<duration<double>>(tdepues - tantes);

        time_total = transcurrido.count();
      } else {
        int * U = new int[n];
        assert(U);

        for (int i = 0; i < n; i++)
            U[i] = T[i];
        
        tantes_vacio = high_resolution_clock::now();
        for (int veces = 0; veces < NUM_VECES; veces++)
    {
      for (int i = 0; i < n; i++)
        U[i] = T[i];
    }
        tdespues_vacio = high_resolution_clock::now();

        tantes = high_resolution_clock::now();
        for (int veces = 0; veces < NUM_VECES; veces++)
    {
      for (int i = 0; i < n; i++)
        U[i] = T[i];
      seleccion(U, n);
    }
      tdepues = high_resolution_clock::now();

      transcurrido = duration_cast<duration<double>>((tdepues - tantes) - (tdespues_vacio - tantes_vacio));

      time_total = transcurrido.count();

        delete [] U;
      }

  cout << n << " " << time_total << endl;

  delete [] T;

  return 0;
};
