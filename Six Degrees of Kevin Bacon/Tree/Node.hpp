//
//  Node.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/5/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef Node_hpp
#define Node_hpp
#include <iostream>
#include <string>
#include <sstream>
template <class T>
class TreeNode {
private:
    T _T_TYPE_DATA;
    TreeNode* _SMALLER_NODE; // Left node
    TreeNode* _GREATER_NODE; // Right node
    int _count;
    // Node duplicates count.
    int _height;
    void getChildrenHeight(int& smaller_height, int& greater_height)const;
    // Access the children's node height.
public:
    // Constructor
    TreeNode(const T& new_data = T(),
             TreeNode* init_small = nullptr,
             TreeNode* init_great = nullptr,
             int height = 0, int count = 1);
    // Tree Operation
    int balance_factor();
    // This function calculates the balance factor
    //  based on its children's height and return the factor
    int calculate_height();
    // Calculate the node height.
    int update_height();
    // Updatae node height.
    
    // Mutator
    T& data();
    // Access and modify the data.
    TreeNode*& greaterNode();
    // Access and modify the smaller (left) node.
    TreeNode*& smallerNode();
    // Access and modify the greater (right) node.
    void set_data(const T& new_data);
    // Modify the data.
    void set_small(TreeNode* new_left);
    // Change the left node.
    void set_great(TreeNode* new_right);
    // Change the right node.
    
    void incr_count() {_count ++;}
    // Increment the count number (of a node)
    void decr_count() {_count --;}
    // Decrease the count number
    
    // Accessor
    const T& getData() {
        std::stringstream ss;
//        ss.str(_T_TYPE_DATA);
//        std::cout << _T_TYPE_DATA.str() << std::endl;
        return _T_TYPE_DATA;}
    // Access data.
    TreeNode*& getGreaterNode() {return _GREATER_NODE;}
    // Access greater node.
    TreeNode*& getSmallerNode() {return _SMALLER_NODE;}
    // Access smaller node.
    const int getHeight() {return _height;}
    // Access the height of a node.
    const int getCount() {return _count;}
    // Access the count of a node.
    
    // Boolean
    bool is_leaf() const;
    // Return true if the node is a leaf (no children)
    
    
    template <class S>
    friend std::ostream& operator<<(const TreeNode<S>*& node, std::ostream& out) {
        std::string data = node->_T_TYPE_DATA;
        out << data;
        return out;
    }

};

template <class T>
TreeNode<T>::TreeNode(const T& new_data, TreeNode* init_small, TreeNode* init_great, int height, int count): _count(count) {
    _SMALLER_NODE = init_small;
    _GREATER_NODE = init_great;
    _T_TYPE_DATA = new_data;
    _height = height;
}
template <class T>
T& TreeNode<T>::data() {
    return _T_TYPE_DATA;
}
template <class T>
TreeNode<T>*& TreeNode<T>::greaterNode() {
    return _GREATER_NODE;
}
template <class T>
TreeNode<T>*& TreeNode<T>::smallerNode() {
    return _SMALLER_NODE;
}
template <class T>
void TreeNode<T>::set_data(const T& new_data) {
    _T_TYPE_DATA = new_data;
}
template <class T>
void TreeNode<T>::set_small(TreeNode* new_left) {
    _SMALLER_NODE = new_left;
}
template <class T>
void TreeNode<T>::set_great(TreeNode* new_right) {
    _GREATER_NODE = new_right;
}
template <class T>
bool TreeNode<T>::is_leaf() const {
    return !_SMALLER_NODE && !_GREATER_NODE;
}

template <class T>
int TreeNode<T>::balance_factor() {
    int left, right= 0;
    getChildrenHeight(left, right);
    return right - left;
}
template <class T>
inline int TreeNode<T>::calculate_height() {
    int left, right = 0;
    // Get maximum height of children nodes.
    getChildrenHeight(left, right);
    return (std::max(left, right) + 1);
}
template <class T>
inline int TreeNode<T>::update_height() {
    return _height = calculate_height();
}
template <class T>
void TreeNode<T>::getChildrenHeight(int& smaller_height, int& greater_height)const  {
    if (!_SMALLER_NODE)
        smaller_height = -1;
    else
        smaller_height = _SMALLER_NODE -> _height;
    if (!_GREATER_NODE)
        greater_height = -1;
    else
        greater_height = _GREATER_NODE -> _height;
}

#endif /* Node_hpp */
