#include <iostream>

#include <vector>
#include <algorithm>

#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

using namespace std;

int generador(vector<int> &contenedores, int &max_capacidad){

    srand (time(NULL));

    int VALOR_MAX_CAPACIDAD = 1000000;
    int VALOR_MAX_N_CONTENEDORES = 498000;
    int VALOR_MIN_N_CONTENEDORES = 2000;
    max_capacidad = rand() % VALOR_MAX_CAPACIDAD;
    int num_contenedores = rand() % VALOR_MAX_N_CONTENEDORES + VALOR_MIN_N_CONTENEDORES;

    for (int i = 0; i < num_contenedores; i++)

        contenedores.push_back(rand() % VALOR_MAX_N_CONTENEDORES);

    return num_contenedores;
}

vector<int> algoritmo(vector<int> contenedores, int max_capacidad, bool maxtoneladas,int &capacidad_cubierta){

    vector<int> solucion;
    if(maxtoneladas)
        sort(contenedores.begin(), contenedores.end(), greater<int>());      // Ordenamos en orden descendente (max toneladas)
    else    
        sort(contenedores.begin(), contenedores.end());                      // Ordenamos en orden ascendente  (max contenedores)

    int c = 0, peso_actual = 0;
    while(c < contenedores.size() && peso_actual != max_capacidad){

        if (peso_actual + contenedores[c] <= max_capacidad){

            peso_actual += contenedores[c];
            solucion.push_back(contenedores[c]);
        }
        c++;
    }

    capacidad_cubierta = peso_actual;
    return solucion;
}

void printSolucion (vector<int> sol, int num_contenedores, int max_capacidad, int capacidad_cubierta){

    cout << "Se han cargado un total de " << sol.size() << " contenedores de los " << num_contenedores
         << " posibles, en un barco con capacidad para " << max_capacidad 
         << " toneladas de carga, de las que se han utilizado " << capacidad_cubierta 
         << "\nLos contenedores utilizados han sido:\n";
    
    for (int i = 0; i < sol.size(); i++){
        cout << sol[i];
        if (i % 10 == 0 && i != 0)    cout << endl;
        else                cout << " ";
    }
    cout << endl;
}

int main(){

    int max_capacidad, capacidad_cubierta_MaxToneladas, capacidad_cubierta_MaxNumCont;
    vector<int> contendedores;

    int num_contenedores = generador(contendedores, max_capacidad);
    vector<int> solMaxNumCont = algoritmo(contendedores, max_capacidad, false, capacidad_cubierta_MaxNumCont);
    vector<int> solToneladas  = algoritmo(contendedores, max_capacidad, true, capacidad_cubierta_MaxToneladas);

    cout << "/**********************  Maximizar el número de contenedores en el barco (óptima)    **********************/\n";
    printSolucion(solMaxNumCont, num_contenedores, max_capacidad, capacidad_cubierta_MaxNumCont);

    cout << endl;
    cout << "/*************************  Maximizar la carga de toneladas utilizada del barco    ************************/\n";
    printSolucion(solToneladas, num_contenedores, max_capacidad, capacidad_cubierta_MaxToneladas);

    return 0;
}




