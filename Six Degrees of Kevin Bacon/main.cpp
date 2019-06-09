//
//  main.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <iostream>
#include <stack>
#include <chrono>
#include "IMDb.hpp"
#include <queue>
#include <string>
#include <map>
#include "Actor.hpp"
#include <utility>
using namespace std;

Actor findTarget(IMDb imdb, string person1, string person2, map<Actor,string>& dict);

int main(int argc, const char * argv[]) {
    // insert code here...
    IMDb imdb;
    vector<string> films, casts;
    
    auto start = chrono::high_resolution_clock::now();
    imdb.loadDataBase();
    auto end = chrono::high_resolution_clock::now();
    auto duration=end-start;
    
    
    
    map<Actor,string> dict;
    string person1 = "Logan Lerman";//"Emma Watson";
    string person2 = "Eddie Redmayne";//"Benedict Cumberbatch";
    Actor me = findTarget(imdb, person1, person2, dict);
    cout << me.getName() << endl;

    Actor emma("Karen Rosenfelt");
    cout << dict[emma] << endl;
    
    
    
    return 0;
}

Actor findTarget(IMDb imdb, string person1, string person2, map<Actor,string>& dict) {
    
    queue<Actor> friends;
    vector<string> _films, _casts;
    bool foundConnection = false;
    
    // Make person1 into an Actor obj a1. Put a1 into the friends queue
    Actor a1(person1);
    friends.push(a1);
    
    int loop = 0;
    // continue the loop until: 1. friend queue is exhausted or 2. person2 is found
    while ( !friends.empty() && !foundConnection) {
        // Get all of a1's films and store into _films vector
        imdb.getCredits(a1.getName(), _films);
        // Put each film into stack movieTites
        stack<string> movieTitles;
        for (int i = 0; i < _films.size(); ++i) {
            movieTitles.push(_films[i]);
        }
        // Empty out the stack of movies to read in each movie's cast for the actor
        while (!movieTitles.empty()) {
            // Get all of a1's co-casts
            imdb.getCast(movieTitles.top(), _casts);
            // Iterate throgh all the casts and push them into dictionary / queue
            for (int i = 0; i < _casts.size(); ++i) {
                // person2's name is encountered
                // skip instance where the cast is the originator himself
                Actor a2;
                a2.setName(_casts[i]);
                a2.setPrevConnection(a1);
                if (_casts[i]!=a1.getName()) {
                    //                    Actor a2;
                    //                    a2.setName(_casts[i]);
                    //                    a2.setPrevConnection(a1);
                    dict.insert(pair<Actor, string>(a2, movieTitles.top()));
                    friends.push(a2);
                }
                if (_casts[i]==person2) {
                    cout  << "found!\n";
                    //                    cout << a1.getName() <<" and " << (a1.getPrevConnection()).getName() << " konw through " << dict[a1]  << endl;
                    cout << a2 << " is connected to " << a2.getPrevConnection() << endl;
                    foundConnection = !foundConnection;
                    return a2;
                }
                
            }
            movieTitles.pop();
            
        }
        friends.pop();
        if (!friends.empty())
            a1 = friends.front();
        cout << ++loop <<  " " << a1.getName()<< endl;
    }
    
    dict.clear();
    Actor a("hihi");
    return a;
};
