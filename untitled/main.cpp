#include <stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>
#include<time.h>
#include<sys/time.h>
#include <iostream>
#include <vector>
#include <thread>

using namespace std;
#define NUM_HILOS 4

vector <vector<double> > matriz1;
vector <vector<double> > matriz2;
vector <vector<double> > matriz3;

struct datos {
    long thread_id;
    int num_filas1;
    int num_columnas1;
    int num_filas2;
    int num_columnas2;
};

datos datos_pasar[NUM_HILOS];

void allocar_memoria(int filas1, int columnas1, int filas2, int columnas2);
void imprimir_matrix(int filas, int columnas, int filas2, int columnas2);
void llenar_numeros(int filas, int columnas, int filas2, int columnas2);

void* multiplicar_paralelo(void* parametros) {
    int j, filas1, columnas1, r, filas2, columnas2;
    long i, lim_inf, lim_sup, k;
    long t;
    struct datos* mis_datos;
    mis_datos=(struct datos*)parametros;
    t = mis_datos->thread_id;
    filas1 = mis_datos->num_filas1;
    columnas1 = mis_datos->num_columnas1;
    filas2 = mis_datos->num_filas2;
    columnas2 = mis_datos->num_columnas2;
    if(filas1%NUM_HILOS != 0 && t==NUM_HILOS-1 )
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS) +1;
    }
    else
    {
        lim_inf = t * (filas1 / NUM_HILOS);
        lim_sup = (t + 1) * (filas1 / NUM_HILOS);
    }

    double sum=0;
    printf("Hilo %ld, LIM inf %ld LIM sup %ld\n", t, lim_inf, lim_sup);
    for (i = lim_inf; i < lim_sup; i++) {
        for (int j = 0; j < columnas2; j++) {
            for (int z = 0; z < columnas1; z++) {
                sum += matriz1[i][z] * matriz2[z][j];
            }
            matriz3[i].push_back(sum);
            sum = 0;
        }
    }

    pthread_exit(NULL);
}

int main() {
    int m1,n1,m2,n2,rc;
    long t;
    void* status;

    struct timeval start;
    struct timeval finish;
    long compiletime;
    double Time;


    pthread_t hilos[NUM_HILOS];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Multiplicacion de Matrices\n");
    printf("¿Cuantas filas tiene la matriz 1?\n");
    scanf("%d",&m1);
    printf("¿Cuantas columnas tiene la matriz 1?\n");
    scanf("%d",&n1);

    printf("¿Cuantas filas tiene la matriz 2?\n");
    scanf("%d",&m2);
    printf("¿Cuantas columnas tiene la matriz 2?\n");
    scanf("%d",&n2);
    if (n1 == m2) {
        printf("La Matriz 1 es %d x %d \n", m1, n1);
        printf("La Matriz 2 es %d x %d \n", m2, n2);
        printf("La Matriz 3 es %d x %d \n", m1, n2);

        allocar_memoria(m1, n1, m2, n2);
        llenar_numeros(m1, n1, m2, n2);

        gettimeofday(&start, 0);
        for (t = 0;t < NUM_HILOS; t++) {
            datos_pasar[t].thread_id=t;
            datos_pasar[t].num_filas1=m1;
            datos_pasar[t].num_columnas1=n1;
            datos_pasar[t].num_filas2=m2;
            datos_pasar[t].num_columnas2=n2;
            printf("Creando el hilo %ld \n",t);
            rc = pthread_create(&hilos[t],&attr,multiplicar_paralelo,(void*)&datos_pasar[t]);
            if (rc) {
                printf("ERROR codigo %d \n",rc);
                exit(-1);
            }
        }

        pthread_attr_destroy(&attr);

        for(t=0;t<NUM_HILOS;t++) {
            rc = pthread_join(hilos[t],&status);
            if (rc) {
                printf("ERROR,codigo %d \n",rc);
                exit(-1);
            }
            printf("En la funcion main, ya acabo el hilo %ld con status %ld \n",t,(long)status);
        }
        gettimeofday(&finish, 0);
        compiletime = (finish.tv_sec - start.tv_sec)*1000000;
        compiletime = compiletime+(finish.tv_usec-start.tv_usec);
        Time = (double)compiletime;

        printf("Despues de multiplicar con hilos:\n");
        printf("El programa se demoro: %lf segundos.\n", (double)Time/1000000.0);
        imprimir_matrix(m1,n1,m2,n2);

        printf("Fin del programa \n");
        pthread_exit(NULL);

    } else {
        printf("No se pueden multiplicar las matrices (%d no es igual a %d)\n", n1, m2);
    }

    return 0;
}

void allocar_memoria(int filas1,int columnas1, int filas2, int columnas2) {

    for(int i=0;i<filas1;i++)
    {
        vector<double> a = {};
        matriz1.push_back(a);
    }

    for(int i=0;i<filas2;i++)
    {
        vector<double> a = {};
        matriz2.push_back(a);
    }

    for(int i=0;i<filas1;i++)
    {
        vector<double> a = {};
        matriz3.push_back(a);
    }
}

void imprimir_matrix(int filas1, int columnas1, int filas2, int columnas2) {

    int i, j;
    printf("MATRIZ 1\n");
    for (i=0;i<filas1;i++) {
        for (j=0;j<columnas1;j++) {
            printf("%lf \t",matriz1[i][j]);
        }
        printf("\n");
    }
    printf("MATRIZ 2\n");
    for (i=0;i<filas2;i++) {
        for (j=0;j<columnas2;j++) {
            printf("%lf \t",matriz2[i][j]);
        }
        printf("\n");
    }
    printf("MATRIZ 3\n");
    for (i=0;i<filas1;i++) {
        for (j=0;j<columnas2;j++) {
            printf("%lf \t",matriz3[i][j]);
        }
        printf("\n");
    }
}

void llenar_numeros(int filas1, int columnas1, int filas2, int columnas2) {
    int i,j;

    for (i = 0;i < filas1; i++) {
        for (j = 0; j < columnas1; j++) {
            //matriz1[i][j] = j*3+2*(rand()%15);
            //std::cout<<"Hola"<<std::endl;
            matriz1[i].push_back(5);
        }
    }
    for (i = 0;i < filas2; i++) {
        for (j = 0;j < columnas2; j++) {
            //matriz2[i][j] = j*3+2*(rand()%15);
            //std::cout<<"Holanda"<<std::endl;
            matriz2[i].push_back(1);
        }
    }
}