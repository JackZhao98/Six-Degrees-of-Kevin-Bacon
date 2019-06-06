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
    vector<string> films,casts;
    auto start = chrono::high_resolution_clock::now();
    i.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration = end - start;
    cout << chrono::duration_cast<chrono::seconds>(duration).count();
    
    i.getCredits("Kevin Bacon", films);
    i.getCast("Star Wars: Shadows of the Empire", casts);
//    for (int i = 0; i < films.size(); ++ i) {
//        cout << films[i] << "\n";
//    }
//    for (int i = 0; i < casts.size(); ++ i) {
//        cout << casts[i] << "\n";
//    }
    return 0;
}

//void func(s