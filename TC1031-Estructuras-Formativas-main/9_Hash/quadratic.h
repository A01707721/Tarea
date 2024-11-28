/*
*  autor: Adrian Marquez
*  fecha: 25/11/2024
*/
#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>
#include <sstream>

using namespace std;

template <class Key, class Value>
class Quadratic {
private:
	unsigned int (*func) (const Key);
	unsigned int size;
	unsigned int count;
	Key *keys;
	Key initialValue;
	Value *values;
	long indexOf(const Key) const;
public:
	Quadratic(unsigned int, Key, unsigned int (*f) (const Key)) ;
	~Quadratic();
	bool full() const;
	void put(Key, Value);
	Value get(const Key) ;
	string toString() const;
};

template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key k, unsigned int (*f) (const Key))  {
	size = sze;
	keys = new Key[size];
    if (keys == 0) {
		delete keys;
	}
	initialValue = k;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = k;
	}
	values = new Value[size];
	for (int i = 0; i  < sze; i++){
        values[i] = 0;
    }

	func = f;
	count = 0;
}

template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	delete [] keys;
	delete [] values;
	keys = 0;
	values = 0;
	size = 0;
	func = 0;
	count = 0;

}

template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	bool cond=count>size;
	return (cond);
}

template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;
	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	} while (start != i);
	return -1;
}

template <class Key, class Value>
void Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int start, j = 0;
	long pos;
    pos = indexOf(k);
    if (pos != -1) {
        values[pos] = v;
		return;
    }
    start = func(k) % size;
    unsigned int i = start;
    do {
        i = (start + j * j) % size;
        if (keys[i] == initialValue) {
            keys[i] = k;
            values[i] = v;
            count++;
			return;
        }
        j++;
    } while (j < size);
	return;
}

template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k)  {
	long pos;

	pos = indexOf(k);
	if (pos != -1) {
		return values[pos];
	}
    return 0;
}

template <class Key, class Value>
string Quadratic<Key, Value>::toString() const {
	stringstream aux;
	for (int i = 0; i < size; i++){
			if (keys[i] != initialValue){
				aux << "(" << i << " ";
			  aux << keys[i] << " : " << values[i] << ") ";
			}
	}
	return aux.str();
}
#endif
