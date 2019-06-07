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
#include "Heap/BinaryHeap.hpp"
using namespace std;
int main(int argc, const char * argv[]) {
    // insert code here...
    IMDb i;
//    vector<string> films, casts;
    
    auto start = chrono::high_resolution_clock::now();
    i.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration = end - start;

//    string str;
//    cout << "Enter a name\n";
//    cin >> str;
//
    //    cout << str << " is related to KB through: " << i.searchDB();
    
//    cout << chrono::duration_cast<chrono::seconds>(duration).count();
//    i.buildConnections(); // build connections  person relates to other people by movies
//    i.connectToBacon(string findMe); //  function finds person's relations to Bacon
    
//    i.getCredits("George Cukor", films);
//    i.getCast("Gone with the Wind", casts);
//    for (int i = 0; i < films.size(); ++ i) {
//        cout << films[i] << "\n";
//    }
//    for (int i = 0; i < casts.size(); ++ i) {
//        cout << casts[i] << "\n";
//    }

    return 0;
}

//void func(s
