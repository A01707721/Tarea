/*
 * list.h
 *
 *  Created on: 23/09/2024
 *      Author: Adrian Marquez
 */
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

template <class T> class List;

template <class T>
class Link{
    private:
    Link(T);
	Link(T, Link<T>*);
	Link(const Link<T> &);
    T value;
    Link<T> *next;
    friend class List<T>;
};

template <class T>
Link<T>::Link(T val): value(val), next(0){};

template <class T>
Link<T>::Link(T val, Link<T> *p): value(val), next(p){};

template <class T>
Link<T>::Link(const Link<T> &original): value(original.value), next(original.next){};

template <class T>
class List{
    private:
    Link<T> *head;
    int size;
    public:
    List();
    ~List();
    void clear();
    void insertion(T);
    int search(T);
    void update(int, T);
    void deleteAt(int);
    std::string toString();
    void operator= (const List&) ;
};

template <class T>
List<T>::List(): head(0), size(0){};

template <class T>
List<T>::~List(){
    clear();
}

template <class T>
void List<T>::clear() {
	Link<T> *p, *q;

	p = head;
	while (p != 0) {
		q = p->next;
		delete p;
		p = q;
	}
	head = 0;
	size = 0;
}

template <class T>
void List<T>::insertion(T val){
    Link<T> *p;
    Link<T> *newLink= new Link<T>(val);
    if(head==0){
        head=newLink;
    }
    else{
        p=head;
        while(p->next!=0){
            p=p->next;
        }
        newLink->next=0;
        p->next=newLink;
    }
    
    size++;

}

template <class T>
int List<T>::search(T val){
    int index=0;
    Link<T> *p=head;
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
void List<T>::update(int i, T val){
    Link<T> *p=head;
    int index=0;
    while(index != i){
        p=p->next;
        index++;
    }
    p->value=val;

}

template <class T>
void List<T>::deleteAt(int i){
    Link<T> *p,*q;
    p=head;
    int index=0;
    if(i==0){
        p=p->next;
        delete head;
        head=p;
    }
    else{
        while(index < i-1){
        p=p->next;
        index++;
    }
    q=p->next;
    p->next=q->next;
    delete q;
    }
    size--;
    
}

template <class T>
std::string List<T>::toString() {
	std::stringstream aux;
	Link<T> *p;

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
void List<T>::operator=(const List<T> &original)  {
	Link<T> *p, *q;

	clear();
	p = original.head;
	head = new Link<T>(p->value);
	q = head;
    p = p->next;
	while(p != 0) {
		q->next = new Link<T>(p->value);
		p = p->next;
		q = q->next;
		}
		size = original.size;
}
