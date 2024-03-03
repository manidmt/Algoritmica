#include "iostream"
#include "vector"
#include "algorithm"
#include "iterator"
#include <chrono>

using namespace std;

/*******************************************/
/* Heap sort
/******************************************/
 
 void swap (int & a, int & b); // Función de intercambio de posición

 
 
 void Heap (int *array, int length, int index); // Algoritmo de clasificación de montón (big top heap)

 
 
 void HeapSort (int *array, int size); // Función de ordenación del montón


/*******************************************/
/* Algoritmo bruto
/******************************************/

/**
 * @brief Ordena los @p k vectores de @p n elementos en el vector @p resultado
 * 
 * Los une todos en @p resultado y luego le realiza heapsort
 * 
 * @param vectores vector de vectores a ordear
 * @param resultado vector resultado 
 * @param k número de vectores
 * @param n número de elementos por vectores
 * 
 * @pre Se supone que @p resultado tiene memoria reservada para n*k enteros
 * @pre Los vectores de @p vectores están ordenados
 */
void algoritmoBruto (int **vectores, int *resultado, int k, int n) ;

/*******************************************/
/* Algoritmo otro
/******************************************/

/**
 * @brief Ordena los @p k vectores de @p n elementos en el vector @p resultado
 * 
 * Los va uniendo en el vector @p resultado buscando el mínimo de cada vector en @p vectores
 * e insertándolo, de forma que queden ordenados 
 * 
 * @param vectores vector de vectores a ordear 
 * @param resultado vector resultado 
 * @param k número de vectores
 * @param n número de elementos por vectores
 * 
 * @pre Se supone que @p resultado tiene memoria reservada para n*k enteros
 * @pre Los vectores de @p vectores están ordenados
 */
void algoritmoOtro (int **vectores, int *resultado, int k, int n) ;

/*******************************************/
/* Algoritmo nuestro
/******************************************/

/**
 * @brief Ordena los @p k vectores de @p n elementos en el vector @p resultado
 * 
 * Los une de dos en dos ordenadamente hasta obtener el resultado
 * 
 * @param vectores vector de vectores a ordear
 * @param k número de vectores
 * @param n número de elementos por vectores
 * 
 * @pre Se supone que @p resultado tiene memoria reservada para n*k enteros
 * @pre Los vectores de @p vectores están ordenados
 * @post El resultado se obtiene en @p vectores[0]
 */
void algoritmoNuestro (int **vectores, int k, int n);

void MezclaVec(const int *arr1, const int *arr2, int n1, int n2, int *&ret);

/*******************************************/
/* Algoritmo nuestro
/******************************************/

/**
 * @brief Ordena los @p k vectores de @p n elementos en el vector @p resultado
 * 
 * Se unen los dos primeros vectores y al resultante se le añade el tercero. Así 
 * sucesivamente hasta obtener el resultado
 * 
 * @param vectores vector de vectores a ordear
 * @param k número de vectores
 * @param n número de elementos por vectores
 * 
 * @pre Se supone que @p resultado tiene memoria reservada para n*k enteros
 * @pre Los vectores de @p vectores están ordenados
 * @post El resultado se obtiene en @p vectores[0]
 */
void algoritmoPropuesto (int **vectores, int k, int n);


/*******************************************/
/* Generador vectores
/******************************************/

// Genera un numero uniformemente distribuido en el intervalo [0,1) a partir de uno 
// de los generadores disponibles en C.
double uniforme() ;

void generadorvectores(int** vectores, int k, int n) ;


/*******************************************/
/* Función principal
/******************************************/

int main (int argc, char* argv[]) {

    // Comprobamos y guardamos argumentos
    if (argc != 3)
    {
      cerr << "Uso: " << argv[0] << " <num_vectores>" << " <num_elementos>" << endl;
      return -1;
    }

    // Informamos de la salida
    /*
    cout << "Salida: <k> <n> <t_algPropuesto> <t_algNuestro> <t_algBruto> <t_algOtro>"
    */
    int k = atoi(argv[1]);
    int n = atoi(argv[2]);
    //int n = 3158, k = 131580;
    int iteraciones = 1;

    // Inicializamos el cronómetro
    chrono::high_resolution_clock::time_point tantes, tdespues;
    chrono::duration<double> transcurrido[4];

    // Reservamos la memoria para vectores y resultado
    int **vectores =  new int *[k];

    for (int i = 0; i < k; i++)
        vectores[i]= new int [n];

    int *resultado = new int [n*k];

    /*************************************************************/

    for (int i=0; i<iteraciones; ++i) {

        // Inicializamos vectores
        generadorvectores(vectores, k, n);

        /*
        cout << "Imprimiendo vectores" << endl;

        for (int i=0; i<k; ++i) {
            cout << "Vector " << i << ":  ";
            for (int j=0; j<n; ++j)
                cout << vectores[i][j] << " ";
            cout << endl;
        }
        cout << endl;
        */

        /*************************************************************/
        //cout << "1" << endl;

        // Hacemos una copia porque algoritmo propuesto cambia los vectores
        int **vectoresCopia =  new int *[k];

        for (int i = 0; i < k;  i++)
            vectoresCopia[i]= new int [n];

        for (int i = 0; i < k; i++)
            for (int j=0; j<n; ++j)
                vectoresCopia[i][j] = vectores[i][j];

        tantes = chrono::high_resolution_clock::now();
        algoritmoPropuesto(vectoresCopia, k, n);
        tdespues = chrono::high_resolution_clock::now();
        transcurrido[0] = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);

        // Imprimimos el vector resultado
        /*
        cout << "Resultado = ";
        for (int i=0; i<n*k; ++i)
            cout << vectoresCopia[0][i] << " ";

        cout << endl << endl;
        */
       
       // Liberamos la copia
        for(int i = 0; i < k-1; i++)  
            delete [] vectoresCopia[i];
        delete [] vectoresCopia;        
      
        // Imprimimos el tiempo
        cout << k << " " << n << " " << transcurrido[0].count();

        /*************************************************************/
        //cout << "2" << endl;

        // Hacemos una copia porque algoritmo propuesto cambia los vectores
        vectoresCopia =  new int *[k];

        for (int i = 0; i < k; i++)
            vectoresCopia[i]= new int [n];

        for (int i = 0; i < k; i++)
            for (int j=0; j<n; ++j)
                vectoresCopia[i][j] = vectores[i][j];

        tantes = chrono::high_resolution_clock::now();
        algoritmoNuestro(vectoresCopia, k, n);
        tdespues = chrono::high_resolution_clock::now();
        transcurrido[1] = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);

        
        // Imprimimos el vector resultado
        /*
        cout << "Resultado = ";
        for (int i=0; i<n*k; ++i)
            cout << vectoresCopia[0][i] << " ";

        cout << endl << endl;
        */
       
       // Liberamos la copia
        for(int i = 0; i < k; i++)  
            delete [] vectoresCopia[i];
        delete [] vectoresCopia;
    
        // Imprimimos el tiempo
        cout << " " << transcurrido[1].count();

        /*************************************************************/
        //cout << "3" << endl;

        tantes = chrono::high_resolution_clock::now();
        algoritmoBruto(vectores, resultado, k, n);
        tdespues = chrono::high_resolution_clock::now();
        transcurrido[2] = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);

        // Imprimimos el vector resultado
        /*
        cout << "Resultado = ";
        for (int i=0; i<n*k; ++i)
            cout << resultado[i] << " ";

        cout << endl << endl;
        */
       
        // Imprimimos el tiempo
        cout << " " << transcurrido[2].count() ;

    /*************************************************************/
        //cout << "4" << endl;

        tantes = chrono::high_resolution_clock::now();
        algoritmoOtro(vectores, resultado, k, n);
        tdespues = chrono::high_resolution_clock::now();
        transcurrido[3] = chrono::duration_cast<chrono::duration<double>>(tdespues-tantes);

        // Imprimimos el vector resultado
        /* 
        cout << "Resultado = ";
        for (int i=0; i<n*k; ++i)
            cout << resultado[i] << " ";

        cout << endl << endl;
        */
       
        // Imprimimos el tiempo
        cout << " " << transcurrido[3].count() << endl;
    
    }
    
   /*************************************************************/


    // Liberamos memoria de vectores y resultado
    for (int i=0; i<k; ++i)
        delete[] vectores[i];
    
    delete[] vectores;
    delete[] resultado;

    return 0;
}

/*******************************************/
/* Implementaciones
/******************************************/

void swap (int & a, int & b) // Función de intercambio de posición
{
	int temp = a;
	a = b;
	b = temp;
}
 
 
 void Heap (int *array, int length, int index) // Algoritmo de clasificación de montón (big top heap)
{
	 int left = 2 * index + 1; // left array index
	 int right = 2 * index + 2; // El índice de la matriz de nodos derecha
	 int max = index; // index es el nodo padre
 
	 if (left <length && array [left]> array [max]) // El nodo izquierdo se compara con el nodo padre
	{
		max = left;
	}
	
	 if (right <length && array [right]> array [max]) // El nodo derecho se compara con el nodo padre
	{
		max = right;
	}
 
	if (array[index] != array[max])
	{
		swap(array[index], array[max]);
		 Heap (array, length, max); // Llamada recursiva
	}
}
 
 
 void HeapSort (int *array, int size) // Función de ordenación del montón
{
	 for (int i = size / 2-1; i>= 0; i--) // crea un montón
	{
		Heap(array, size, i);
	}
 
	for (int i = size - 1; i >= 1; i--)
	{
		 swap (array [0], array [i]); // Coloque el valor máximo de array [0] en la posición de array [i], el valor máximo se inclina hacia atrás
		 Heap (array, i, 0); // Llame al algoritmo de ordenación del montón para comparar
	}
}

/*************************************************************/

void algoritmoBruto (int **vectores, int *resultado, int k, int n) {
    
    // Concatenamos los vectores
    for(int i=0; i<n*k; ++i)
        resultado[i] = vectores[i/n][i%n];

    // Ordenamos el vector usando HeapSort
    HeapSort(resultado, n*k);
}

/*************************************************************/

void algoritmoOtro (int **vectores, int *resultado, int k, int n) {
    
    int i, vector_min;

    int pos_vector[k] = {0};
    bool final[k] = {false};    // final[i] = true  si pos_vector[i] está en la posición n+1 

    // Ordenamos los vectores en resultado
    for (i=0; i<n*k; ++i) {

        // Bucamos el mínimo
        vector_min = 0;
        while(vector_min<k && final[vector_min])  
            vector_min++; // Pasamos al siguiente hasta que encontremos un vector que no se haya recorrido entero 

        for (int j=vector_min+1; j<k; ++j)
            if (!final[j] && vectores[vector_min][pos_vector[vector_min]] > vectores[j][pos_vector[j]])
                vector_min = j;

        // Insertamos el mínimo y pasamos al siguiente
        resultado[i] = vectores[vector_min][pos_vector[vector_min]];
        
        if (pos_vector[vector_min] == n)
            final[vector_min] = true;
        else
            pos_vector[vector_min]++;

    }

}

/*************************************************************/

void algoritmoNuestro (int **vectores, int k, int n) {
    int tamanios [k];   // Tamaños de cada vector
    for (int i = 0; i < k; i++) tamanios[i] = n;
    int i, n_vec = k, *auxv;
    while (n_vec > 1){
        for (i = 0; i < n_vec-1; i += 2){
            
            //cout << "Tam de T: " << n_vec << endl;
            MezclaVec(vectores[i], vectores[i+1], tamanios[i], tamanios[i+1], vectores[i/2]);
            tamanios[i/2] = tamanios[i] + tamanios[i+1];
        }
        
        if (i == n_vec-1){
            // Ponemos el último vector al final de los vectores unidos
            auxv = vectores[i/2];
            vectores[i/2] = vectores[n_vec-1];
            vectores[n_vec-1] = auxv;
            // Actualizamos el tamaño
            tamanios[i/2] = tamanios[n_vec-1];

            /*cout << "Entramos en el if con n_vec = " << n_vec << endl;
            for (int j = 0; j < n_vec; j++){
                for (int t = 0; t < tamanios[j]; t++) cout << T[j][t] << " ";
                cout << endl;
            }*/
            n_vec = i/2 + 1;
        } 
        else n_vec = i/2;
    }
}

/*************************************************************/

void algoritmoPropuesto (int **vectores, int k, int n) {
    int *auxv = vectores[k-1];
    int sizA = n;
    for (int i = k-2; i >= 0; i--){
        
        MezclaVec(auxv, vectores[i], sizA, n, auxv);
        sizA += n;
    }
}

void MezclaVec(const int *arr1, const int *arr2, int n1, int n2, int *&ret){

    int *res = new int [n1+n2];
	int id1 = 0, id2 = 0, idr = 0;

    /*
    cout << "Primer array: ";
    for (int i = 0; i < n1; i++)    cout << arr1[i] << " ";
    cout << endl << "Segundo array: ";
    for (int i = 0; i < n2; i++)    cout << arr2[i] << " ";
    cout << endl;
    */
	
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
    
    delete [] ret;
    ret = res;
}

/*************************************************************/

double uniforme() {
    int t = rand();
    double f = ((double)RAND_MAX+1.0);
    return (double)t/f;
}


void generadorvectores(int** vectores, int k, int n) {

    
    int N=k*n;
    int *aux = new int[N];

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
                vectores[i][m]=aux[t];
            t++;
            m++;
            }
        }
    }

    delete [] aux;
    /*
    for (int i=0; i<k; i++) {
        for (int j=0; j<n; j++)
            cout << vectores[i][j] << " ";
        cout << " " << endl;
    }
    */

}