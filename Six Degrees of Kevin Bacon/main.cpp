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
#include "Movie.hpp"
using namespace std;

//Actor findTarget(IMDb imdb, string person1, string person2, map<Actor,string>& dict);

void findTarget();
int main(int argc, const char * argv[]) {
    
    
    //    auto start = chrono::high_resolution_clock::now();
    
    //    auto end = chrono::high_resolution_clock::now();
    //    auto duration=end-start;
    
    
    //    Actor d = actorTree.insertWithReturnPointer(src)->getData();
    //    cout << d.getPath() << endl;
    //    cout << actorTree.getSize() << endl;
    //    cout << movieTree.getSize() << endl;
    findTarget();
    cout << "\n";
    return 0;
}

void findTarget() {
    IMDb imdb;
    imdb.loadDataBase();
    vector<string> films, casts;
    string a1 = "Martin Freeman";
    string a2 = "Alan Rickman";
    AVLTree<Actor> actorTree;
    AVLTree<Movie> movieTree;
    string path =  "";
    string previous = "";
    
    queue<string> qu; // front of the person
    qu.push(a1);
    Actor src(a1, path, previous);
    actorTree.insertWithReturnPointer(src);
    string lastPath;
    bool found = false;
    while (!qu.empty() && !found) {
        
        string currentActor = qu.front();
        
        imdb.getCredits(currentActor, films);
        for (int i = 0; i< films.size(); ++i) {
            
            if (!movieTree.searchAVL(Movie(films[i]))) {
                
                // TESTING
                lastPath = currentActor + " " + films[i]; // construct a lastPath string
                
                // query film & put into tree iff not there. If film already there, break
                movieTree.insertWithReturnPointer(Movie(films[i]));
                
                imdb.getCast(films[i], casts); // query casts & put into tree iff not there
                
                for (int j = 0; j<casts.size(); ++j) {
                    
                    if ( casts[j]!=currentActor)  {
                        Actor act;
                        Actor prevAct;
                        if (!actorTree.searchAVL(Actor(casts[j]))) {
                            // if Actor is not already in the tree, add it to the tree
                            act = actorTree.insertWithReturnPointer(Actor(casts[j], films[i], currentActor))->getData();
                            // update the path
                            prevAct = actorTree.searchAVL(Actor(currentActor))->getData();
                            act.addConnection(prevAct.getPath(), prevAct.getPrevious());
//                            cout << act;
                            qu.push(casts[j]); // push into queue of actors to examine
                        } else {
                            // Actor has already appeared before. Do nothing
                        }
                        if (casts[j] == a2) {
                            cout << "found!\n" << act;
                            return ;
                            
                        }
                    }
                }
            }
            
        }
        
        qu.pop();
        
    }
}
