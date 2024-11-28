/*
 * funciones.h
 *
 *  Created on: 19/08/2024
 *      Author: Adrian Marquez
 */

#include <iostream>

class Funciones{
    public:
    int sumaIterativa(int n){
        int acum=0;
        for(int i=1;i<=n;i++){
            acum=acum+i;
        }
        return acum;
    }
    int sumaRecursiva(int n){
        if(n==0){
            return 0;
        }
        else{
            return sumaRecursiva(n-1)+n;
        }
        
    }
    int sumaDirecta(int n){
        int res=(n*(n+1))/2;
        return res;
    }
};
