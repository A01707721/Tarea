/*
 * bst.h
 *
 *  Created on: 07/10/2024
 *      Author: Adrian Marquez
 */
#include <string>
#include <sstream>
#include <iostream>
#ifndef BST_H
#define BST_H

template <class T> class BST;

template <class T>
class TreeNode{
    private:
    TreeNode<T> *left;
    TreeNode<T> *right;
    T value;
    void preorder(std::stringstream& aux);
    void inorder(std::stringstream& aux);
    void postorder(std::stringstream& aux);
    void levelbylevel(std::stringstream& aux);
    public:
    TreeNode(T);
    TreeNode(T, TreeNode<T>*, TreeNode<T>*);
    void add(T);
    int height();
    void removeChilds();

    friend class BST<T>;
};

template <class T>
TreeNode<T>::TreeNode(T val){
    value=val;
    left=0;
    right=0;
}

template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T>* l, TreeNode<T>* r ){
    value=val;
    left=l;
    right=r;
}

template <class T>
void TreeNode<T>::preorder(std::stringstream& aux) {
    aux << value;
    if (left != 0) {
        aux << " ";
        left->preorder(aux);
    }
    if (right != 0) {
        aux << " ";
        right->preorder(aux);
    }
}

template <class T>
void TreeNode<T>::inorder(std::stringstream& aux) {
    if (left != 0){
        left ->inorder(aux);
        aux << " ";
    }
    aux << value;

    if (right != 0){
        aux << " ";
        right -> inorder(aux);
    }
}

template <class T>
void TreeNode<T>::postorder(std::stringstream& aux) {
    if (left != 0){
        left -> postorder(aux);
        aux << " ";
    }
    if (right != 0){
        right -> postorder(aux);
        aux << " ";
    }
    aux << value;
}

template <class T>
void TreeNode<T>::levelbylevel(std::stringstream& aux) {
    aux << value;
    if (left != 0){
        aux << " ";
        left->levelbylevel(aux);
    }
    if(right != 0){
        aux << " ";
        right -> levelbylevel(aux);
    }
}
    
template <class T>
void TreeNode<T>::add(T val){
    if(val < value){
        if(left==0){
            left=new TreeNode<T>(val);
        }
        else{
            left->add(val);
        }
    }
    else{
        if(right==0){
            right=new TreeNode<T>(val);
        }
        else{
            right->add(val);
        }
    }
}

template <class T>
int TreeNode<T>::height(){
    int height_r=0;
    int height_l=0;
    if(left!=0){
        height_l=left->height();
    }
    if(right!=0){
        height_r=right->height();
    }
    if(height_l > height_r){
        return height_l+1;
    }
    else{
        return height_r+1;
    }

}

template <class T>
void TreeNode<T>::removeChilds(){
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
class BST{
    private:
    TreeNode<T>* root;
    public:
    BST(): root(0){};
    ~BST(){
        remove();
    }
    int height();
    void remove();
    void add(T);
    std::string visit();
    std::string ancestors(T);
    int whatlevelamI(T);
};

template <class T>
int BST<T>::height(){
    return root->height();
}

template <class T>
void BST<T>::remove(){
    if(root!=0){
        root->removeChilds();
    }
    delete root;
    root=0;

}


template <class T>
void BST<T>::add(T val){
    if(root!=0){
        root->add(val);
    }
    else{
        root=new TreeNode<T>(val);
    }
}

template <class T>
std::string BST<T>::visit(){
    std::stringstream aux;
    aux << "[";
    root->preorder(aux);
    aux << "]";
    aux << "\n";
    aux << "[";
    root->inorder(aux);
    aux << "]";
    aux << "\n";
    aux << "[";
    root->postorder(aux);
    aux << "]";
    aux << "\n";
    aux << "[";
    root->levelbylevel(aux);
    aux << "]";
    return aux.str();
}

template <class T>
std::string BST<T>::ancestors(T val){
    std::stringstream aux;
    TreeNode<T>* ptr=root;
    int validation=0;
    aux << "[";
    while (ptr != 0 && val != ptr->value) {
        if(validation!=0){
            aux << " ";
        }
        aux << ptr->value;
        if (val < ptr->value){
            ptr = ptr->left;
        }
        else{
            ptr = ptr->right;
        }
        validation++;
    }
        if (ptr == 0){
            return "[]";
        }
        aux << "]";
        return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val){
    TreeNode<T> *ptr=root;
    int level = 1;
    while(val != ptr->value){
        if (val < ptr->value) {
            level++;
            ptr = ptr->left;
        } else if (val > ptr->value) {
            level++;
            ptr = ptr->right;
        }
    }
    return level;
}

#endif
