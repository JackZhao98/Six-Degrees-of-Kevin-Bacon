//
//  BinaryHeap.hpp
//  Heap
//
//  Created by Winnie Jeng on 5/14/19.
//  Copyright © 2019 Winnie Jeng. All rights reserved.
//

#ifndef BinaryHeap_hpp
#define BinaryHeap_hpp

#include <stdio.h>
#include <vector>
#include "heapFxns.hpp"

template <typename T>
class Heap : public heapFxns<T> {
    
private:
    vector<T> v;
    
public:
    Heap() {v.push_back("\000000");}
    ~Heap() {}
    Heap(const Heap& other) {}
//    Heap operator=(const Heap& other);
    
    void insert(T data) {
        heapFxns<T>::insert(v, data);
    }
    T remove() {
        return heapFxns<T>::remove(v);
    }
    void print() {
        heapFxns<T>::print(v);
    }
    
};

#endif /* BinaryHeap_hpp */
