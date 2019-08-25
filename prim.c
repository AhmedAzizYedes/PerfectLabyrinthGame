#include "prim.h"
#include <stdlib.h>
#include <time.h>

Labyrinthe *primLabyrinthe_1(int n,int m){
    Labyrinthe* laby = initialisationLabyrinthe(n,m);
    srand(time(NULL));
    int* T = (int*) malloc(sizeof(int)*n*m);
    int deb=0;
    int fin=0;
    int s0=0;
    int s1=0;
    Position pos=0;
    T[0]=rand()%(n*m);
    fin+=1;
    while (fin<n*m){
        s0=deb+rand() % (fin-deb);
        pos=rand() % 4;
        s1 = idCellule(laby,T[s0],pos);
        if (s1<0)
            continue;
        if (!estIsole(laby,s1))
            continue;
        //if (estIsole(laby,idCellule(laby,T[s],HAUT)))
        destructionMur(laby,T[s0] / laby->m,T[s0] % laby->m,pos);
        T[fin] = s1;
        fin+=1;
    }
    free(T);
    return laby;
}
Labyrinthe *primLabyrinthe(int n,int m){
    Labyrinthe* laby = initialisationLabyrinthe(n,m);
    srand(time(NULL));
    int* T = (int*) malloc(sizeof(int)*n*m);
    int deb=0;
    int fin=0;
    int s0=0;
    int s1=0;
    Position pos=0;
    T[0]=rand()%(n*m);
    fin+=1;
    while (fin<n*m){
        s0=deb+rand() % (fin-deb);
        pos=rand() % 4;
        s1 = idCellule(laby,T[s0],pos);
        if (s1<0)
            continue;
        if (!estIsole(laby,s1))
            continue;
        destructionMur(laby,T[s0] / laby->m,T[s0] % laby->m,pos);
        T[fin] = s1;
        fin+=1;
        if ((((idCellule(laby,T[s0],HAUT)<0) || !estIsole(laby,idCellule(laby,T[s0],HAUT))) && ((idCellule(laby,T[s0],BAS)<0) || !estIsole(laby,idCellule(laby,T[s0],BAS)))) && (((idCellule(laby,T[s0],GAUCHE)<0) || !estIsole(laby,idCellule(laby,T[s0],GAUCHE))) && ((idCellule(laby,T[s0],DROITE)<0) || !estIsole(laby,idCellule(laby,T[s0],DROITE))))){
            s1=T[s0];
            T[s0]=T[deb];
            T[deb]=s1;
            deb+=1;
        }
    }
    free(T);
    return laby;
}
