#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

template <class T> class DList;

template <class T>
class DLink{
    private:
    DLink(T);
	DLink(T, DLink<T>*, DLink<T>*);
	DLink(const DLink<T> &);
    T value;
    DLink<T> *next;
    DLink<T> *previous;
    friend class DList<T>;
};

template <class T>
DLink<T>::DLink(T val): value(val), next(0), previous(0){};

template <class T>
DLink<T>::DLink(T val, DLink<T> *p, DLink<T> *q): value(val), next(p), previous(q){};

template <class T>
DLink<T>::DLink(const DLink<T> &original): value(original.value), next(original.next), previous(original.previous){};

template <class T>
class DList{
    private:
    DLink<T> *head;
    DLink<T> *tail;
    int size;
    public:
    DList();
    ~DList();
    void clear();
    void insertion(T);
    int search(T);
    void update(int, T);
    void deleteAt(int);
    string toStringForward();
    string toStringBackward();
};

template <class T>
DList<T>::DList(): head(0), tail(0), size(0){};

template <class T>
DList<T>::~DList(){
    clear();
}

template <class T>
void DList<T>::clear() {
	DLink<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	tail = 0;
	size = 0;
}

template <class T>
void DList<T>::insertion(T val){
    DLink<T> *p;
    DLink<T> *newLink= new DLink<T>(val);
    if(head==0){
        head=newLink;
        tail=newLink;
    }
    else{
        tail->next=newLink;
        newLink->previous=tail;
        tail=newLink;
    }
    
    size++;

}

template <class T>
int DList<T>::search(T val){
    int index=0;
    DLink<T> *p=head;
    while(p !=0 && p->value != val){
        p=p->next;
        index++;
    }
    if(p==0){
        return -1;
    }
    else{
        return index;
    }
    
    
    
}

template <class T>
void DList<T>::update(int i, T val){
    DLink<T> *p=head;
    int index=0;
    while(index != i){
        p=p->next;
        index++;
    }
    p->value=val;

}

template <class T>
void DList<T>::deleteAt(int i){
    DLink<T> *p,*q;
    p=head;
    int index=0;
    if(i==0){
        p=p->next;
        p->previous=0;
        delete head;
        head=p;
    }
    else if(i==size){
        p=tail;
        q=p->previous;
        q->next=0;
        delete p;
        tail=q;
    }
    else{
        while(index != i){
            p=p->next;
            index++;
        }
        q=p->next;
        q->previous=p->previous;
        p->previous->next=q;
        delete p;
    }
    size--;
}

template <class T>
string DList<T>::toStringForward(){
	stringstream aux;
	DLink<T> *p;

	p = head;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->next != 0) {
			aux << ", ";
		}
		p = p->next;
	}
	aux << "]";
	return aux.str();
}

template <class T>
string DList<T>::toStringBackward(){
	stringstream aux;
	DLink<T> *p;

	p = tail;
	aux << "[";
	while (p != 0) {
		aux << p->value;
		if (p->previous != 0) {
			aux << ", ";
		}
		p = p->previous;
	}
	aux << "]";
	return aux.str();
}
