/*
 * sorts.h
 *
 *  Created on: 03/09/2024
 *      Author: Adrian Marquez
 */

#ifndef SORTS_H_
#define SORTS_H_

#include <vector>
#include <list>

using namespace std;

template <class T>
class Sorts {
    private:
    void swap(vector<T>&, int, int);
    void copyArray(vector<T>&, vector<T>&, int, int);
	void mergeSplit(vector<T>&, vector<T>&, int, int);
    void mergeArray(vector<T>&, vector<T>&, int, int, int);
    public:
    void ordenaSeleccion(vector<T>&);
    void ordenaBurbuja(vector<T>&);
    void ordenaMerge(vector<T>&);
    int busqSecuencial(vector<T>&, int);
    int busqBinaria(vector<T>&, int);
};

template <class T>
void Sorts<T>::swap(vector<T> &v, int a, int b){
    int aux=v[a];
    v[a]=v[b];
    v[b]=aux;
}

template <class T>
void Sorts<T>::ordenaSeleccion(vector<T> &v){
    for(int i=0; i < v.size(); i++){
        int pos=i;
        for(int j=i; j < v.size(); j++){
            if(v[pos] > v[j]){
                pos=j;
            }
        }
        swap(v,pos,i);
    }
}

template <class T>
void Sorts<T>::ordenaBurbuja(vector<T> &v){
    for(int i=0; i < v.size(); i++){
        for(int j=0; j < (v.size()-i)-1; j++){
            if(v[j] > v[j+1]){
                swap(v,j,j+1);
            }
        }
    }
}

template <class T>
void Sorts<T>::ordenaMerge(vector<T> &v){
    int low,high;
    low=0;
    high=v.size()-1;
    vector<T> temp(v.size());
    mergeSplit(v,temp,low,high);
}

template <class T>
void Sorts<T>::copyArray(vector<T> &A, vector<T> &B, int low, int high){
    for(int i=low; i <= high; i++){
        A[i]=B[i];
    }
}

template <class T>
void Sorts<T>::mergeArray(vector<T> &A, vector<T> &B, int low, int mid, int high){
    int i,j,k;
    i=low;
    j=mid+1;
    k=low;
    while(i <= mid && j <= high){
        if(A[i]>A[j]){
            B[k]=A[j];
            j++;
        }
        else{
            B[k]=A[i];
            i++;
        }
        k++;
    }
    if(i>mid){
        for(;j <= high; j++){
            B[k++]=A[j];
        }
    }
    else{
        for(;i <= mid; i++){
            B[k++]=A[i];
        }
    }
}

template <class T>
void Sorts<T>::mergeSplit(vector<T> &A, vector<T> &B, int low, int high){
    int mid;
    if(high-low < 1){
        return;
    }
    else{
        mid=(high+low)/2;
        mergeSplit(A,B,low,mid);
        mergeSplit(A,B,mid+1,high);
        mergeArray(A,B,low,mid,high);
        copyArray(A,B,low,high);
    }
}



template <class T>
int Sorts<T>::busqSecuencial(vector<T> &v, int a){\
    int cond=0;
    for(int i=0; i < v.size(); i++){
        if(v[i]==a){
            return i;
        }
    }
    return -1;
}

template <class T>
int Sorts<T>::busqBinaria(vector<T> &v, int a){
    int high=v.size()-1;
    int low=0;
    while(low<=high){
        int mid=(high+low)/2;
        if(v[mid]<a){
            low=mid+1;
        }
        if(v[mid]>a){
            high=mid-1;
        }
        if(v[mid]==a){
            return mid;
        }
    }
    return -1;
}

#endif /* SORTS_H_ */
