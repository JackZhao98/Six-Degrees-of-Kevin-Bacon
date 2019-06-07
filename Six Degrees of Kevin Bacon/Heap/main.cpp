//
//  main.cpp
//  Heap
//
//  Created by Winnie Jeng on 5/14/19.
//  Copyright © 2019 Winnie Jeng. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <cstdlib>
#include "BinaryHeap.hpp"
using namespace std;

int main(int argc, const char * argv[]) {
    
    Heap<int> h;
    int arr[] = {98, 97,86,57,88,75,70,36,20,29,44};
    for (int i = 0; i < 11; ++i) {
        h.insert(arr[i]);
//        h.print();
    }
    for (int i = 0; i < 11; ++i) {
        cout << h.remove() << "\n";
    }
    
    
    return 0;
}
