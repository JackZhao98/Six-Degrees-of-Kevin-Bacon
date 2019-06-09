//
//  main.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <iostream>       // std::cout
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
    
    //    imdb.getCredits("George Cukor", films);
    //    imdb.getCast("Gone with the Wind", casts);
    //    for (int i = 0; i < films.size(); ++ i) {
    //        cout << films[i] << "\n";
    //    }
    //    for (int i = 0; i < casts.size(); ++ i) {
    //        cout << casts[i] << "\n";
    //    }
    
    map<Actor,string> dict;
    string person1 = "Logan Lerman";//"Emma Watson";
    string person2 = "Eddie Redmayne";//"Benedict Cumberbatch";
    Actor me = findTarget(imdb, person1, person2, dict);
    //    if (me.empty())
    cout << me.getName() << endl;
    //    cout << me.getPrevConnection();
    //    cout << dict[me.getPrevConnection()] << endl;
    //    while (me.getName()!=person1) {
    //        cout << dict[me.getPrevConnection()] << endl;
    //        me.getName() = me.getPrevConnection();
    string name = me.getName();
    while (name != person1) {
        cout << me.getName() << " knows " << me.getPrevConnection()<< endl;

    }
    //    }
    return 0;
}

Actor findTarget(IMDb imdb, string person1, string person2, map<Actor,string>& dict) {
    queue<string> friends;
    vector<string> _films, _casts;
    string previousConnection = person1;
    bool foundConnection = false;
    // put person1 into the queue
    friends.push(person1);
    // if person is not in the dictionary
    int loop =0;
    while ( !friends.empty() || !foundConnection) {
        // Get all of person1's films and store into _films vector
        imdb.getCredits(person1, _films);
        // Put each film into stack movieTites
        stack<string> movieTitles;
        for (int i = 0; i < _films.size(); ++i) {
            movieTitles.push(_films[i]);
        }
        // Empty out the stack of movies
        while (!movieTitles.empty()) {
            // Get all of person1's co-casts
            imdb.getCast(movieTitles.top(), _casts);
            // Iterate throgh all the casts and push them into dictionary / queue
            Actor a;
            for (int i = 0; i < _casts.size(); ++i) {
                if (_casts[i]!=person1) {
                    a.setName(_casts[i]);
                    a.setPrevConnection(person1);
                    dict.insert(pair<Actor, string>(a, movieTitles.top() ));
                    friends.push(_casts[i]);
                }
                if (_casts[i]==person2) {
                    //                    cout << a.getName() << " and " << a.getPrevConnection() << " know each other through movie \""<< dict[a] << "\""<< endl;
                    foundConnection = !foundConnection;
                    return a;
                }
            }
            movieTitles.pop();
        }
        friends.pop();
        if (!friends.empty())
            person1=friends.front();
        //        cout << ++loop <<  " " << person1<< endl;
    }
    
    dict.clear();
    Actor a("hihi");
    return a;
};
