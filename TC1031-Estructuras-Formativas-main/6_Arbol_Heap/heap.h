#ifndef HEAP_H_
#define HEAP_H_

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

template <class T>
class Heap {
private:
	T *data;
	unsigned int sze;
	unsigned int count;
    void heapify(unsigned int);
	unsigned int parent(unsigned int) const;
	unsigned int left(unsigned int) const;
	unsigned int right(unsigned int) const;
	void swap(unsigned int, unsigned int);

public:
	Heap(unsigned int) ;
	~Heap();
	bool empty();
	void push(T) ;
    unsigned int size();
	void pop();
    T top();
	string toString() const;
};

template <class T>
Heap<T>::Heap(unsigned int s){
    sze=s;
    data=new T[sze];
    count=0;
}

template <class T>
Heap<T>::~Heap(){
    delete [] data;
    sze=0;
    data=0;
    count=0;
}

template <class T>
bool Heap<T>::empty(){
    if(count==0){
        return true;
    }
    else{
        return false;
    }
}

template <class T>
void Heap<T>::heapify(unsigned int index){
    unsigned int l=left(index);
    unsigned int r=right(index);
    unsigned int minimun=index;
    if(l<=count && data[l]<data[minimun]){
        minimun=l;
    }
    else if(r<=count && data[r]<data[minimun]){
        minimun=r;
    }
    if(index!=minimun){
        swap(index,minimun);
        heapify(minimun);
    }
}

template <class T>
unsigned int Heap<T>::parent(unsigned int index) const{
    unsigned int pos=(index-1)/2;
    return pos;
}

template <class T>
unsigned int Heap<T>::left(unsigned int index) const{
    unsigned int pos=(index*2)+1;
    return pos;
}

template <class T>
unsigned int Heap<T>::right(unsigned int index) const{
    unsigned int pos=(index*2)+2;
    return pos;
}

template <class T>
void Heap<T>::swap(unsigned int x, unsigned int y){
    T z=data[x];
    data[x]=data[y];
    data[y]=z;
}

template <class T>
void Heap<T>::push(T val){
    unsigned int index;
	index = count;
	count++;
	while (index > 0 && val < data[parent(index)]) {
		data[index] = data[parent(index)];
		index = parent(index);
	}
	data[index] = val;
}

template <class T>
unsigned int Heap<T>::size(){
    return count;
}

template <class T>
void Heap<T>::pop(){
    data[0]=data[--count];
    heapify(0);
}

template <class T>
T Heap<T>::top(){
    return data[0];
}

template <class T>
string Heap<T>::toString() const {
	stringstream aux;
	aux << "[";	for (unsigned int i = 0; i < count; i++) {
		if (i != 0) {
			aux << " ";
		} aux << data[i];
	} aux << "]";
	return aux.str();
}

#endif
