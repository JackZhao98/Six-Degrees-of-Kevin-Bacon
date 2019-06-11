//
//  AVL Tree.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/5/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef AVL_Tree_hpp
#define AVL_Tree_hpp

#include "Tree Functions.cpp"
#include <iostream>
#include "Actor.hpp"
using namespace std;
template <class T>
class AVLTree {
private:
    TreeNode<T>* _root;
    unsigned int _size;
    bool searchAVL(const T& target, TreeNode<T>*& found) const;
    string _path;
//    vector<Actor> connection;
    // Boolean, return true if the node has been found.
public:
    AVLTree();
    AVLTree(const T* sorted, unsigned int size);
    ~AVLTree();
    AVLTree(const AVLTree& OTHER);
    AVLTree& operator =(const AVLTree& RHS);
    void setPath(string path);
    const TreeNode<T>*& getRoot() {return _root;}
    // Access the root. (const type)
    TreeNode<T>*& root() {return _root;}
    // Access the root and modifie it.
    const unsigned int getSize() {return _size;}
    const T getData() {return _root->getData();}
    // Access the size of the tree.
    bool insert(const T& INS_THIS);
    
    TreeNode<T>* insertWithReturnPointer(const T& INS_THIS);
    // Insert node to the avl tree.
    bool erase(const T& DEL_THIS);
    // Erase a node with given T type content.
    TreeNode<T>* searchAVL(const T& FIND_THIS) const;
    // Search AVL tree, return the "found" key node.
    void clear();
    // Extraction operator.
    AVLTree& operator << (const T& Data) {
        insert(Data);
        return *this;
    }
    
    // Friend insertion/extration operator
    friend
    std::ostream& operator <<(std::ostream& outs, const AVLTree<T>& tree){
        return print(tree._root, outs);
    }
    friend
    std::istream& operator >>(std::istream& ins, AVLTree<T>& tree){
        T temp;
        ins >> temp;
        tree.insert(temp);
        return ins;
    }
    
};

template <class T>
inline AVLTree<T>::AVLTree(): _root(nullptr), _size(0), _path("") {}

template <class T>
inline AVLTree<T>::AVLTree(const T* sorted, unsigned int size): _root(nullptr) {
    _root = list_to_tree(sorted, size);
    _size = size;
    _path = "";
}

template <class T>
inline AVLTree<T>::~AVLTree() {
    clear();
}

template <class T>
inline AVLTree<T>::AVLTree(const AVLTree& OTHER) {
    _root = copyTree(OTHER._root);
}

template <class T>
inline AVLTree<T>& AVLTree<T>::operator =(const AVLTree& RHS) {
    if (this != &RHS) {
        clear();
        _root = copyTree(RHS._root);
        _size = RHS._size;
    }
    return *this;
}

//template <class T>
//inline void AVLTree<T>::setPath(string path) {
//    path += " -> ";
//    _path += path;
//}

template <class T>
inline bool AVLTree<T>::insert(const T& INS_THIS) {
    bool success = avl::insert(_root, INS_THIS);
    !(success)||(++_size);
    // True: insert new node.
    // False: Node already exists, count number incremented.
    return success;
}

template <class T>
TreeNode<T>* AVLTree<T>::insertWithReturnPointer(const T& INS_THIS) {
    _size ++;
    return avl::insertWithReturnPointer(_root, INS_THIS);
}

template <class T>
inline bool AVLTree<T>::erase(const T& DEL_THIS) {
    bool success = avl::erase(_root, DEL_THIS);
    if (success)
        --_size;
    return success;
}

template <class T>
inline TreeNode<T>* AVLTree<T>::searchAVL(const T& FIND_THIS)const {
    return search(_root, FIND_THIS);
}

template <class T>
inline bool AVLTree<T>::searchAVL(const T& target, TreeNode<T>*& found)const {
    return search(_root, target, found);
}

template <class T>
inline void AVLTree<T>::clear() {
    clearTree(_root);
}



#endif /* AVL_Tree_hpp */
