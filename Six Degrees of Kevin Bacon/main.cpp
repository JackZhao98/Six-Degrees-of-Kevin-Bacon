//
//  main.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <iostream>
#include <chrono>
#include "IMDb.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    IMDb i;
//    vector<string> films, casts;
    
    auto start = chrono::high_resolution_clock::now();
    i.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration = end - start;
    cout << chrono::duration_cast<chrono::seconds>(duration).count();
//    i.getCredits("George Cukor", films);
//    i.getCast("Gone with the Wind", casts);
//    for (int i = 0; i < films.size(); ++ i) {
//        cout << films[i] << "\n";
//    }
//    for (int i = 0; i < casts.size(); ++ i) {
//        cout << casts[i] << "\n";
//    }
    vector<string> v;
    for (int i = 0; i < 10000000; i++) {
        v.push_back("What is the longest name I can think of?");
    }
    cout << v.size() << endl;
    return 0;
}

//void func(s
