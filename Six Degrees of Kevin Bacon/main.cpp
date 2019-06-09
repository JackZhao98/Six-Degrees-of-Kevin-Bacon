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

bool findTarget(IMDb imdb, string person1, string person2, map<Actor,string>& dict);

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
    
//    map<string,string> dict;
//    string person1 = "Kevin Bacon";
//    string person2 = "Benedict Cumberbatch";
//    stack<string> movieTitles;
//    map<string, string> actorMoviePair; // first stores actor name, then store title
//    queue<string> qu; //
//    //    queue<Actor> friends; // a queue of actor called "friends"
//
//    // query from imdb all of person1's films
//    imdb.getCredits(person1, films);
//
//    // go thru all of person1's films, push them into stack movieTites, and get ea/film's cast
//    for (int i = 0; i < films.size(); ++i) {
//        movieTitles.push(films[i]);
//        imdb.getCast(movieTitles.top(), casts);
//    }
//
//    // iterate throgh all the the movies to extract ea/movie's cast
//    while (!movieTitles.empty()) {
//        imdb.getCast(movieTitles.top(), casts);
//        for (int i = 0; i < casts.size(); ++i) {
//
//            qu.push(casts[i]);
//            // put ea/ actor as an obj in friend queue / map
//            if (casts[i]!=person1) {
//                actorMoviePair.insert(pair<string, string>(casts[i], movieTitles.top()));
//            }
//
//        }
//        movieTitles.pop();
//    }
//    cout  <<  endl;
//    cout << qu.size() << endl;
    
    //    while (!qu.empty()) {
    //        cout << qu.front()  << endl;
    //        qu.pop();
    //    }
    //    int i = 0;
    //    for(map<string, string>::const_iterator it = actorMoviePair.begin(); it != actorMoviePair.end(); ++it) {
    //        cout <<  ++i << " " << it->first << " in " << it->second << "\n";
    //    }
    //
    map<Actor,string> dict;
    cout << findTarget(imdb, "Kevin Bacon", "Alan Rickman", dict) << endl;
    return 0;
}

bool findTarget(IMDb imdb, string person1, string person2, map<Actor,string>& dict) {
//    map<string,string>::iterator it = dict.find(person2);
    queue<string> friends;
    vector<string> _films, _casts;
    string previousConnection = person1;
    
    // put person1 into the queue
    friends.push(person1);
    // if person is not in the dictionary
    while (!friends.empty()) {
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
            // Iterate throgh all the cast and push them into dictionary / queue
            Actor a;
            for (int i = 0; i < _casts.size(); ++i) {
                if (_casts[i]!=person1) {
                    a.setName(_casts[i]);
                    a.setPrevConnection(person1);
//                    Actor a(_casts[i], person1);
//                    cout << a.getName() << " is connected to " << a.getPrevConnection() << endl ;
                    dict.insert(pair<Actor, string>(a, movieTitles.top() ));
//                    cout << dict[a] << endl;
//                    cout << _casts[i] << " is conneced to " << person1<< endl;
//                    dict[a] = movieTitles.top();
//                    dict[Actor(_casts[i], person1)] = movieTitles.top();
                    friends.push(_casts[i]);
                }
                if (_casts[i]==person2) {
                    cout << a.getName() << " and " << a.getPrevConnection() << " know each other through movie \""<< dict[a] << "\""<< endl;
                    return true;
                }
            }
            movieTitles.pop();
        }
        person1=friends.front();
        friends.pop();
    }
    
    return false;
};
