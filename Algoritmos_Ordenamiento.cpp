#include <iostream>
#include <chrono>
#include <random>
#include <ctime>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <windows.h>


#define MAX_TAMANO 1000
#define MIN_TAMANO 10
#define INCREMENTO 10
#define VECES 1000
#define NUM_ALGORITMOS 7

using namespace std;

void insercion(int A[], int n);
int aleatorio(int inicio, int fin);
void Burbuja(int A[], int n);
void OrdenamientoSeleccion(int A[], int n);
void OrdenamientoMezcla(int A[], int inicio, int fin);
void Mezcla(int A[], int inicio, int medio, int fin);
void OrdenamientoRapido(int A[], int inicio, int fin);
int Particion(int A[], int inicio, int fin);
void OrdenamientoMonticulos(int A[], int n);
void BUILD_MAX_HEAP(int A[], int n);
void MAX_HEAPIFY(int A[], int i, int n);
void OrdenamientoShell(int A[], int n);

int main(){

    srand(time(NULL));


    int Prueba[10] = { 10, 4, 2, 1, 3, 9, 5, 8, 7, 6 };
    int PruebaOriginal[10];


    //Se crea una copia del arreglo original para que se pueda comparar con los arreglos ordenados 
    std::copy(std::begin(Prueba), std::end(Prueba), std::begin(PruebaOriginal));
    
    cout<< "Por ordenar: ";

    for (int i = 0; i < 10; i++){
        cout << Prueba[i] << " ";
    }
    cout << endl;

    //Se ordena el arreglo con cada algoritmo de ordenamiento y se imprime en pantalla
    //Se imprime en pantalla el arreglo ordenado con cada algoritmo de ordenamiento
    //Se restaura el arreglo original para que se pueda ordenar con cada algoritmo de ordenamiento
    //Se muestra como se utiliza cada algoritmo de ordenamiento

    cout << "Usando Ordenamiento de Insercion: ";
    for (int i = 0; i < 10; i++){
        insercion(Prueba, 10);
        cout << Prueba[i] << " ";
    }
    std::copy(std::begin(PruebaOriginal), std::end(PruebaOriginal), std::begin(Prueba));

    cout << endl;
    cout<<"Usando Ordenamiento de Burbuja: ";
    for (int i = 0; i < 10; i++){
        Burbuja(Prueba, 10);
        cout << Prueba[i] << " ";
    }

    std::copy(std::begin(PruebaOriginal), std::end(PruebaOriginal), std::begin(Prueba));
    cout << endl;
    cout<<"Usando Ordenamiento de Seleccion: ";   
    for (int i = 0; i < 10; i++){
        OrdenamientoSeleccion(Prueba, 10);
        cout << Prueba[i] << " ";
    }
    std::copy(std::begin(PruebaOriginal), std::end(PruebaOriginal), std::begin(Prueba));
    cout << endl;
    cout<<"Usando Ordenamiento por Mezcla: ";
    for (int i = 0; i < 10; i++){
        OrdenamientoMezcla(Prueba, 0, 10);
        cout << Prueba[i] << " ";
    }
    std::copy(std::begin(PruebaOriginal), std::end(PruebaOriginal), std::begin(Prueba));
    cout << endl;
    cout<<"Usando Ordenamiento Rapido: ";
    for (int i = 0; i < 10; i++){
        OrdenamientoRapido(Prueba, 0, 10);
        cout << Prueba[i] << " ";
    }
    std::copy(std::begin(PruebaOriginal), std::end(PruebaOriginal), std::begin(Prueba));    
    cout << endl;
    cout<<"Usando Ordenamiento por Monticulos: ";
    for (int i = 0; i < 10; i++){
        OrdenamientoMonticulos(Prueba, 10);
        cout << Prueba[i] << " ";
    }
    std::copy(std::begin(PruebaOriginal), std::end(PruebaOriginal), std::begin(Prueba));
    cout << endl;
    cout<<"Usando Ordenamiento Shell: ";
    for (int i = 0; i < 10; i++){
        OrdenamientoShell(Prueba, 10);
        cout << Prueba[i] << " ";
    }
    cout << endl;
    cout << "\nA continuacion se crearan los archivos CSV con todos los algoritmos de ordenamiento" << endl;
    Sleep(4000);
    
    int A[MAX_TAMANO];
    
    //Se crean los nombres de los archivos CSV para cada algoritmo de ordenamiento
    const char* B[NUM_ALGORITMOS] = { 
        "1_Insercion_Ordenamiento.csv", 
        "2_Burbuja_Ordenamiento.csv",  
        "3_Seleccion_Ordenamiento.csv", 
        "4_Mezcla_Ordenamiento.csv", 
        "5_Rapido_Ordenamiento.csv", 
        "6_Monticulos_Ordenamiento.csv",
        "7_Shell_Ordenamiento.csv"
    };
    double tiempo[VECES][100]; 
    double suma[100];
    double prom[100];



    //Se crea un arreglo que contiene a todos los conjuntos por ordenar
    int** conjunto_numeros = new int*[100];
    for (int j= MIN_TAMANO; j <= MAX_TAMANO; j += INCREMENTO){
        int* conjunto = new int[j];
        for (int i = 0; i < j; i++){
            conjunto[i] = aleatorio(1, MAX_TAMANO);
        }
        conjunto_numeros[(j - MIN_TAMANO)/INCREMENTO] = conjunto;
    }


    for (int k = 0 ; k < NUM_ALGORITMOS ; ++k){
        //Se crea un archivo CSV para cada algoritmo de ordenamiento
        ofstream file(B[k]);

        for (int j = MIN_TAMANO ; j <= MAX_TAMANO; j += INCREMENTO){
            if (j < MAX_TAMANO) file << "Tamano " << j << " , ";
            else file << "Tamano " << j << "\n";
        }

        //Se ejecuta cada algoritmo de ordenamiento 1000 veces para cada conjunto de numeros
        for (int j = MIN_TAMANO; j <= MAX_TAMANO; j += INCREMENTO){
            suma[(j - MIN_TAMANO)/INCREMENTO] = 0;
            for (int i = 0; i < VECES; i++){

                //Se restaura el conjunto para que cada algoritmo ordene el mismo conjunto, haciendo una comparacion justa
                std::copy(conjunto_numeros[(j - MIN_TAMANO)/INCREMENTO], conjunto_numeros[(j - MIN_TAMANO)/INCREMENTO] + j, A);

                //Se mide el tiempo que tarda en ordenar el conjunto
                auto start = chrono::high_resolution_clock::now();
                switch (k){
                    case 0:
                        insercion(A, j);
                        break;
                    case 1: 
                        Burbuja(A, j);
                        break;
                    case 2: 
                        OrdenamientoSeleccion(A, j);
                        break;
                    case 3:
                        OrdenamientoMezcla(A, 0, j);
                        break;
                    case 4:
                        OrdenamientoRapido(A, 0, j);
                        break;
                    case 5:
                        OrdenamientoMonticulos(A, j);
                        break;
                    case 6:
                        OrdenamientoShell(A, j);
                        break;
                }
                auto end = chrono::high_resolution_clock::now();
                chrono::duration<double, nano > duration = end - start;
                //Se guarda el tiempo que tarda en ordenar el conjunto

                tiempo[i][(j - MIN_TAMANO)/INCREMENTO] = duration.count();
                suma[(j - MIN_TAMANO)/INCREMENTO] += tiempo[i][(j - MIN_TAMANO)/INCREMENTO];

            }

            prom[(j - MIN_TAMANO)/INCREMENTO] = suma[(j - MIN_TAMANO)/INCREMENTO] / VECES;

            //Se se trata del primer conjunto de numeros, se imprime en pantalla, para que el usuario vea que se esta trabajando con el mismo conjunto en cada algoritmo
            if (j == 10) {
                for (int c = 0; c < 10; ++c) {
                    cout << A[c] << " ";
                    Sleep(1000);
                }
            }

            //Se imprime en pantalla el algoritmo que se esta ejecutando y el tamaño del conjunto de numeros
            switch (k){
                case 0:
                cout << "Ordenamiento de Insercion, " << "Tamano = " << j << endl;
                if (j == MAX_TAMANO){
                    cout <<"Archivo CSV creado con exito."<< endl;
                    Sleep (2000);
                }
                
                    break;
                case 1: 
                cout << "Ordenamiento de Burbuja, " << "Tamano = " << j << endl;
                if (j == MAX_TAMANO){
                    cout <<"Archivo CSV creado con exito."<< endl;
                    Sleep (2000);
                }
                
                    break;
                case 2: 
                cout << "Ordenamiento de Seleccion, " << "Tamano = " << j << endl;
                if (j == MAX_TAMANO){
                    cout <<"Archivo CSV creado con exito."<< endl;
                    Sleep (2000);
                }
                
                    break;
                case 3:
                cout << "Ordenamiento de Mezcla, " << "Tamano = " << j << endl;
                if (j == MAX_TAMANO){
                    cout <<"Archivo CSV creado con exito."<< endl;
                    Sleep (2000);
                }
                
                    break;
                case 4:
                cout << "Ordenamiento Rapido, " << "Tamano = " << j << endl;
                if (j == MAX_TAMANO){
                    cout <<"Archivo CSV creado con exito."<< endl;
                    Sleep (2000);
                }
                
                    break;
                case 5:
                cout << "Ordenamiento por Monticulos, " << "Tamano = " << j << endl;
                if (j == MAX_TAMANO){
                    cout <<"Archivo CSV creado con exito."<< endl;
                    Sleep (2000);
                }
                
                    break;
                case 6:
                    cout << "Ordenamiento Shell, " << "Tamano = " << j << endl;
                    if (j == MAX_TAMANO){
                        cout <<"Archivo CSV creado con exito."<< endl;
                        Sleep (2000);
                    }

                    break;
        }
    }
        for (int i = 0; i < VECES; ++i){
            for (int j = MIN_TAMANO; j <= MAX_TAMANO; j += INCREMENTO){
                if (j < MAX_TAMANO) file << tiempo[i][(j - MIN_TAMANO)/INCREMENTO] << " , ";
                else file << tiempo[i][(j - MIN_TAMANO)/INCREMENTO] << "\n";
            }
          }

        //Se imprime en el archivo CSV los promedios de tiempo que tarda en ordenar cada conjunto de numeros
        file << "\n" <<  "Promedios:" << "\n" ;
        for(int j = 0 ; j < 100 ; ++j){
            if(j < 100) file << prom[j] << " , "  ;
      
            else  file << prom[j] << "\n" ;
      
      
          }
          file.close();
        }   
        //Se libera la memoria de los conjuntos de numeros
        for (int j = MIN_TAMANO; j <= MAX_TAMANO; j += INCREMENTO) {
            delete[] conjunto_numeros[(j - MIN_TAMANO) / INCREMENTO];
        }
        delete[] conjunto_numeros;
        
        return 0;
    }

//Funcion que genera un numero aleatorio entre un rango dado

int aleatorio (int inicio, int fin){
        return inicio + rand() % (fin - inicio + 1);
    }
    

//Algoritmos de ordenamiento

void insercion (int A[], int n){
    int i, j, aux;
    for (i = 1; i < n; i++){
        j = i;
        aux = A[i];
        while (j > 0 && aux < A[j-1]){
            A[j] = A[j-1];
            j--;
        }
        A[j] = aux;
    }
}


void Burbuja(int A[], int n){
    int i, j, temp;
    bool intercambiado = true;
    for (i = 0; i < n && intercambiado; i++){
        intercambiado = false;
        for (j = 0; j < n-1; j++){
            if (A[j] > A[j+1]){
                temp = A[j];
                A[j] = A[j+1];
                A[j+1] = temp;
                intercambiado = true;
            }
        }
    }
}

void OrdenamientoSeleccion (int A[], int n){
    int i, j, min_indx, temp;
    for (i = 0; i < n-1; i++){
        min_indx= i;
        for (j = i+1; j < n; j++){
            if (A[j] < A[min_indx]){
                min_indx = j;
            }
        }
       if (min_indx != i){
           temp = A[i];
           A[i] = A[min_indx];
           A[min_indx] = temp;
       }
    }
}

void OrdenamientoMezcla (int A[], int inicio, int fin){
    if (inicio < fin){
        int medio = inicio + (fin - inicio) / 2;
        OrdenamientoMezcla(A, inicio, medio);
        OrdenamientoMezcla(A, medio+1, fin);
        Mezcla(A, inicio, medio, fin);
    }
}

void Mezcla (int A[], int inicio, int medio, int fin){
    int i, j, k;
    int n1 = medio - inicio + 1;
    int n2 = fin - medio;
    int L[n1], R[n2];
    for (i = 0; i < n1; i++){
        L[i] = A[inicio + i];
    }
    for (j = 0; j < n2; j++){
        R[j] = A[medio + 1 + j];
    }
    i = 0;
    j = 0;
    k = inicio;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            A[k] = L[i];
            i++;
        }
        else{
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        A[k] = L[i];
        i++;
        k++;
    }
    while (j < n2){
        A[k] = R[j];
        j++;
        k++;
    }
}

void OrdenamientoRapido (int A[], int inicio, int fin){
    if (inicio < fin){
        int pivote_idx = Particion(A, inicio, fin);
        OrdenamientoRapido(A, inicio, pivote_idx - 1);
        OrdenamientoRapido(A, pivote_idx + 1, fin);
    }
}

int Particion (int A[], int inicio, int fin){
    int pivote = A[fin];
    int i = inicio - 1;
    for (int j = inicio; j <= fin - 1; j++){
        if (A[j] <= pivote){
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i+1], A[fin]);
    return i+1;
}

void OrdenamientoMonticulos (int A[], int n){
    BUILD_MAX_HEAP(A, n);
    for (int i = n - 1; i >= 1; i--){
        swap(A[0], A[i]);
        MAX_HEAPIFY(A, 0, i);
    }
}

void BUILD_MAX_HEAP (int A[], int n){
    for (int i = n / 2 - 1; i >= 0; i--){
        MAX_HEAPIFY(A, i, n);
    }
}

void MAX_HEAPIFY (int A[], int i, int n){
    int izq = 2 * i + 1;
    int der = 2 * i + 2;
    int mayor = i;
    if (izq < n && A[izq] > A[mayor]){
        mayor = izq;
    }
    if (der < n && A[der] > A[mayor]){
        mayor = der;
    }
    if (mayor != i){
        swap(A[i], A[mayor]);
        MAX_HEAPIFY(A, mayor, n);
    }
}

void OrdenamientoShell (int A[], int n){
    for (int gap = n/2; gap > 0; gap /= 2){
        for (int i = gap; i < n; i += 1){
            int temp = A[i];
            int j = i;;
            for (; j >= gap && A[j - gap] > temp; j -= gap){
                A[j] = A[j - gap];
            }
            A[j] = temp;
        }
    }
}




