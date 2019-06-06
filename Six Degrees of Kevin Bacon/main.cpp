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
#include "path.hpp"
using namespace std;
void render();
string userInput(const string& hint, const IMDb& i);
int main(int argc, const char * argv[]) {
    render();
    return 0;
}

void render() {
    IMDb i;
    path p;
    vector<string> films,casts;
    
    auto start = chrono::high_resolution_clock::now();
    i.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration = end - start;
    cout << "\n\tDatabase loaded, elapsed time: "<< chrono::duration_cast<chrono::seconds>(duration).count() << "s\n\n";
    
    while (true) {
        string start = userInput("Actor name: ", i);
        string target = userInput("Another Actor name: ", i);
        if (target == start) {
            cout << "Degree of 0, Nice try\n";
        } else if (start == "" || target == ""){
            break;
        }
        else {
            auto Pstart = chrono::high_resolution_clock::now();
            
            if (!p.buildPath(start, target, i))
                cout << "No path found between " << start << " and " << target << "\n";
            auto Pend = chrono::high_resolution_clock::now();
            auto Pduration = Pend - Pstart;
            cout << chrono::duration_cast<chrono::milliseconds>(Pduration).count() << "ms\n";
        }
        
       
    }
}

string userInput(const string& hint, const IMDb& i) {
    string input;
    while (true) {
        vector<string> credits;
        cout << hint << " (press Enter to exit): ";
        getline(cin, input);
        
        if (input == "")
            break;
        if (i.getCredits(input, credits))
            break;
        
        cout << "Unable to find \"" << input << "\" in the IMDb database. "<< "Please try again." << endl;
    }
    return input;
}
