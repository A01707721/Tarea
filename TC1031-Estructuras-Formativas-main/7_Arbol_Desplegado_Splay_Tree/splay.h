/*
 * splay.h
 *
 *  Created on: 04/11/2024
 *      Author: Adrian Marquez
 */
#ifndef SPLAY_H_
#define SPLAY_H_

#include <string>
#include <sstream>
#include <iostream>

template <class T> class SplayTree;

template <class T>
class Node{
    private:
    Node<T> *left;
    Node<T> *right;
    Node<T> *parent;
    T value;
    Node<T>* successor();
    Node<T>* rot_right(Node<T>*);
    Node<T>* rot_left(Node<T>*);
    void preorder_n(std::stringstream& aux) const;
    void inorder_n(std::stringstream& aux) const;
    void print_tree_n(std::stringstream& aux) const;
    public:
    Node(T);
    Node(T, Node<T>*, Node<T>*, Node<T>*);
    Node<T>* add(T);
    Node<T>* find(T);
    Node<T>* remove(T);
    void removeChilds();
    Node<T>* splay(Node<T>*,Node<T>*);
    friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val){
    value=val;
    left=0;
    right=0;
    parent=0;
}

template <class T>
Node<T>::Node(T val, Node<T>* l, Node<T>* r, Node<T>* p){
    value=val;
    left=l;
    right=r;
    parent=p;
}

template <class T>
Node<T>* Node<T>::successor(){
    Node<T> *le, *ri;

	le = left;
	ri = right;

	if (right->left == 0) {
		right = right->right;
		ri->right = 0;
		return ri;
	}

	Node<T> *parent, *child;
	parent = right;
	child = right->left;
	while (child->left != 0) {
		parent = child;
		child = child->left;
	}
	parent->left = child->right;
	child->right = 0;
	return child;
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
    Node<T> *y = x->left;
	x->left = y->right;
	if(y->right)
		y->right->parent = x;
	y->right = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;

}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
    Node<T> *y = x->right;
	x->right = y->left;
	if(y->left)
		y->left->parent = x;
	y->left = x;
	y->parent = x->parent;
	x->parent = y;
	if(y->parent){
		if(y->parent->left && y->parent->left->value == x->value)
			y->parent->left = y;
		else
			y->parent->right = y;
	}
	return y;
}

template <class T>
void Node<T>::print_tree_n(std::stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent->value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left->value;
	if (right != 0)
		aux << " right " << right->value;
	aux << "\n";

	if (left != 0) {
		left->print_tree_n(aux);
	}
	if (right != 0) {
		right->print_tree_n(aux);
	}
}


template <class T>
void Node<T>::inorder_n(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder_n(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder_n(aux);
	}
}

template <class T>
void Node<T>::preorder_n(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder_n(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder_n(aux);
	}
}

template <class T>
Node<T>* Node<T>::add(T val){
    if (val < value) {
		if (left != 0)
			return left->add(val);
		else {
			left = new Node<T>(val, 0, 0, this);
			return left;
		}
	} else {
		if (right != 0)
			return right->add(val);
		else {
			right = new Node<T>(val, 0, 0, this);
			return right;
		}
	}
}

template <class T>
Node<T>* Node<T>::find(T val){
    if (val == value){
		return this;
    }
	else if (val < value) {
		if (left != 0){
			return left->find(val);
        }
		else{
			return this;
        }
	} 
    else {
		if (right != 0){
			return right->find(val);
        }
		else{
			return this;
        }
	}
}

template <class T>
Node<T>* Node<T>::remove(T val) {
    Node<T>* aux = find(val);
	Node<T>* child;

    if (aux == 0 || aux->value != val)
        return 0;

    Node<T>* par = aux->parent;   
    if (aux->left == 0 && aux->right == 0) {
        if (par) {
            if (par->left == aux)
				par->left = 0;
            else
				par->right = 0;
        }
        delete aux;
        return par;
    }else if (aux->left == 0 || aux->right == 0) {
		if (aux->right != 0)
			child = aux->right;
		else{
			child = aux->left;
        }
		if (child != 0)
			child->parent = par;

		if (par != 0) {
			if (par->left == aux)
				par->left = child;
			else
				par->right = child;
		}
	}
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
    while(x->parent != 0){

		if(x->parent->value == root->value){
			if(x->parent->left && x->parent->left->value == x->value){
				rot_right(x->parent);
			}else{
				rot_left(x->parent);
			}
		}else{
			Node<T>*p = x->parent;
			Node<T>*g = p->parent;
			if(p->left && g->left &&
				x->value == p->left->value && p->value == g->left->value){
				rot_right(g);
				rot_right(p);
			}else if(p->right && g->right &&
				x->value == p->right->value && p->value == g->right->value){
				rot_left(g);
				rot_left(p);
			}else	if(p->left && g->right &&
				x->value == p->left->value && p->value == g->right->value){
				rot_right(p);
				rot_left(g);
			}else{
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}


template <class T>
class SplayTree{
    private:
    Node<T>* root;
    public:
    SplayTree():root(0){};
    ~SplayTree(){
        remove_all();
    }
    void add(T);
    bool find(T);
    void remove(T);
    void remove_all();
    std::string inorder() const;
	std::string print_tree() const;
	std::string preorder() const;
};

template <class T>
void SplayTree<T>::add(T val){
    if(root!=0){
        Node<T>* aux = root->add(val);

        root=root->splay(root,aux);
    }
    else{
         root=new Node<T>(val);
    }
}

template <class T>
bool SplayTree<T>::find(T val){
   if (root != 0) {
		Node<T>* aux = root->find(val);
		root = root->splay(root,aux);
		return (root->value == val);
	} 
    else{
        return false;
    }
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root->value) {
			Node<T> *succ = root->successor();
			if (succ != 0) {
					succ->left = root->left;
					succ->right = root->right;
					succ->parent = 0;
					if(succ->left)
						succ->left->parent = succ;
					if(succ->right)
						succ->right->parent = succ;
			}
			delete root;
			root = succ;
		} 
        else{
			Node<T>* p = root->remove(val);
			root = root->splay(root,p);
		}
	}
}

template <class T>
void SplayTree<T>::remove_all(){
    if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
std::string SplayTree<T>::inorder() const {
	std::stringstream aux;

	aux << "[";
	root->inorder_n(aux);
	aux << "]";
	return aux.str();
}

template <class T>
std::string SplayTree<T>::print_tree() const {
	std::stringstream aux;

	aux << "\n ================================ ";
		root->print_tree_n(aux);
	aux << " ================================ \n";
	return aux.str();
}



template <class T>
std::string SplayTree<T>::preorder() const {
	std::stringstream aux;

	aux << "[";
		root->preorder_n(aux);
	aux << "]";
	return aux.str();
}

#endif
