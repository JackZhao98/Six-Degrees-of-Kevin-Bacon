//
//  Tree Functions.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/5/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include "Node.hpp"
// Print white space when printing the tree.
template <class T>
TreeNode<T>* search(TreeNode<T>* root, const T& findThis);
// Search for const T type data, and return its node pointer.
template <class T>
bool search(TreeNode<T>* root, const T& findThis, TreeNode<T>*& targetPtr);
// Search for const T type data, and return a boolean if it exists.
template <class T>
std::ostream& print(TreeNode<T>* root, std::ostream& out, int level = 0);
// Print the tree exactly how it looks. (horizontal)
template <class T>
void clearTree(TreeNode<T>*& root);
// Clear the tree, delete all nodes.
template <class T>
TreeNode<T>* copyTree(TreeNode<T>* root);
// Copy the tree and return the new root pointer.
template <class T>
TreeNode<T>* list_to_tree(const T* a, int size);
// Convert a sorted list to a tree.

template <class T>
TreeNode<T>* search(TreeNode<T>* root, const T& findThis) {
    if (!root)
        return nullptr;
    if (findThis == root -> getData())
        return root;
    if (findThis < root -> getData())
        return search(root -> smallerNode(), findThis);
    else
        return search(root -> greaterNode(), findThis);
}

template <class T>
void printData(TreeNode<T>* root) {
    if (!root)
        return ;
    printData(root -> getGreaterNode());
    std::cout << "[" << root<< "]" << std::endl;
    printData(root -> getSmallerNode());

}

template <class T>
bool search(TreeNode<T>* root, const T& findThis, TreeNode<T>*& targetPtr) {
    targetPtr = search(root, findThis);
    return targetPtr;
}

template <class T>
std::ostream& print(TreeNode<T>* root, std::ostream& out, int level) {
    if (!root)
        return out;
    print(root -> getGreaterNode(), out, level + 1);
    out << std::string(8*level, ' ') << root -> getCount() << "*" << "[" << root -> getData() << "]" << std::endl;
    print(root -> getSmallerNode(), out, level + 1);
    return out;
}

template <class T>
void clearTree(TreeNode<T>*& root) {
    if (!root)
        return;
    if (root -> getSmallerNode())
        clearTree(root -> smallerNode());
    if (root -> getGreaterNode())
        clearTree(root -> greaterNode());
    delete root;
    root = nullptr;
}

template <class T>
TreeNode<T>* copyTree(TreeNode<T>* root) {
    if (!root)
        return nullptr;
    return new TreeNode<T>(root->getData(), copyTree(root -> getSmallerNode()), copyTree(root -> getGreaterNode()), root -> getHeight(), root -> getCount());
}

template <class T>
TreeNode<T>* list_to_tree(const T* a, int size) {
    if (size < 1)
        return nullptr;
    int midPoint = size / 2;
    TreeNode<T>* root = new TreeNode<T> (*(a+midPoint));
    int leftSize = midPoint;
    int rightSize = size - 1 - midPoint;
    root -> set_small(list_to_tree(a, leftSize));
    root -> set_great(list_to_tree(a+midPoint+1, rightSize));
    root -> update_height();
    return root;
}

namespace avl {
    template <class T>
    bool insert(TreeNode<T>*& root, const T& T_TYPE_DATA);
    // Insert data to the tree.
    template <class T>
    TreeNode<T>* insertWithReturnPointer(TreeNode<T>*& root, const T& T_TYPE_DATA);
    template <class T>
    bool erase(TreeNode<T>*& root, const T& REMOVE_THIS);
    //Erase a node with REMOVE_THIS as its data.
    template <class T>
    void replace_left_max(TreeNode<T>*& root, T& max);
    // Find the max node on the smaller side, and swap with root.
    template <class T>
    void addTrees(TreeNode<T>*& dest, TreeNode<T>* source, unsigned int& destSize);
    // Combine two trees together.
    template <class T>
    TreeNode<T>* rotate(TreeNode<T>*& root);
    // Rotate the root based on its balance factor.
    template <class T>
    TreeNode<T>* rotate_left(TreeNode<T>*& root);
    // Rotate left.
    template <class T>
    TreeNode<T>* rotate_right(TreeNode<T>*& root);
    // Rotate right
    template <class T>
    std::ostream& in_order_print(TreeNode<T>*& root, std::ostream& out);
    // Print the tree in order.
    
    template <class T>
    bool insert(TreeNode<T>*& root, const T& T_TYPE_DATA) {
        bool success = false;
        if (!root) {
            root = new TreeNode<T>(T_TYPE_DATA);
            return true;
        }
        if (root -> getData() == T_TYPE_DATA) {
            root -> incr_count();
            return false;
        }
        if (T_TYPE_DATA < root -> getData())
            success = insert(root -> smallerNode(), T_TYPE_DATA);
        else
            success = insert(root -> greaterNode(), T_TYPE_DATA);
        
        root -> update_height();
        rotate(root);
        
        return success;
    }
    
    template <class T>
    TreeNode<T>* insertWithReturnPointer(TreeNode<T>*& root, const T& T_TYPE_DATA) {
        if (!root) {
            root = new TreeNode<T>(T_TYPE_DATA);
            return root;
        }
        if (root -> getData() == T_TYPE_DATA) {
            root -> incr_count();
            return root;
        }
        TreeNode<T>* temp = root;
        if (T_TYPE_DATA < root -> getData())
            temp = insertWithReturnPointer(root -> smallerNode(), T_TYPE_DATA);
        else
            temp = insertWithReturnPointer(root -> greaterNode(), T_TYPE_DATA);
        
        root -> update_height();
        rotate(root);
        
        return temp;
    }
    
    template <class T>
    bool erase(TreeNode<T>*& root, const T& REMOVE_THIS) {
        bool success = false;
        if (!root)
            return false;
        
        if (REMOVE_THIS < root -> data()) {
            if ((success = erase(root -> smallerNode(), REMOVE_THIS))) {
                root -> update_height();
                //rotate(root)
                rotate(root);
            }
            return success;
        }
        
        else if (REMOVE_THIS > root -> data()) {
            if ((success = erase(root -> greaterNode(), REMOVE_THIS))) {
                root -> update_height();
                //rotate
                rotate(root);
            }
            return success;
        }
        
        else {
            if (!root -> getSmallerNode()) {
                TreeNode<T>* temp = root;
                root = root -> greaterNode();
                delete temp;
            }
            else {
                replace_left_max(root -> smallerNode(), root -> data());
            }
            // Must use if because a leaf might have been deleted
            if (root) {
                root -> update_height();
                //rotate
                rotate(root);
            }
        }
        return true;
    }
    
    template <class T>
    void addTrees(TreeNode<T>*& dest, TreeNode<T>* source, unsigned int& destSize) {
        if (!source)
            return;
        if (insert(dest, source->data()))
            ++destSize;
        addTrees(dest, source -> smallerNode(), destSize);
        addTrees(dest, source -> greaterNode(), destSize);
    }
    
    template <class T>
    void replace_left_max(TreeNode<T>*& root, T& max) {
        if (root -> greaterNode()) {
            replace_left_max(root -> greaterNode(), max);
            root -> update_height();
            // rotate.
            rotate(root);
        } else {
            max = root -> data();
            TreeNode<T>* temp = root;
            root = root -> smallerNode();
            delete temp;
        }
    }
    
    template <class T>
    TreeNode<T>* rotate(TreeNode<T>*& root) {
        if (!root)
            return nullptr;
        
        if (root -> balance_factor() == 2) {
            if (root ->greaterNode()-> balance_factor() == -1) {
                rotate_right(root -> greaterNode());
                return rotate_left(root);
            }
            return rotate_left(root);
        }
        else if (root -> balance_factor() == -2) {
            if (root -> smallerNode() -> balance_factor() == 1) {
                rotate_left(root -> smallerNode());
                return rotate_right(root);
            }
            return rotate_right(root);
        }
        root -> update_height();
        return root;
    }
    
    template <class T>
    TreeNode<T>* rotate_left(TreeNode<T>*& root) {
        assert(root && root->greaterNode());
        TreeNode<T>* rightChild = root -> greaterNode();
        root -> greaterNode() = root -> greaterNode() -> smallerNode();
        root -> update_height();
        rightChild -> smallerNode() = root;
        rightChild -> update_height();
        root = rightChild;
        return root;
    }
    
    template <class T>
    TreeNode<T>* rotate_right(TreeNode<T>*& root) {
        assert(root && root->smallerNode());
        TreeNode<T>* leftChild = root -> smallerNode();
        root -> smallerNode() = root -> smallerNode() -> greaterNode();
        root -> update_height();
        leftChild -> greaterNode() = root;
        leftChild -> update_height();
        root = leftChild;
        return root;
    }
    
    template <class S>
    std::ostream& in_order_print(TreeNode<S>*& root, std::ostream& out) {
        while (root) {
            TreeNode<S>* tempWalker = root;
            while (tempWalker -> smallerNode())
                tempWalker = tempWalker -> smallerNode();

            S temp = tempWalker -> getData();

            out << temp << "  " << tempWalker -> getCount() << std::endl;
            if (erase(root, temp)) {}
        }

        return out;
    }
}
