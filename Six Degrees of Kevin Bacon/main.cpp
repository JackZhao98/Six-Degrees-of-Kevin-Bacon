//
//  main.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 5/30/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include <iostream>
#include <chrono>
#include <queue>
#include <string>
#include "IMDb.hpp"
#include "Actor.hpp"
#include "Movie.hpp"
using namespace std;

void prompt(string& src, string& dest);
Actor findTarget(IMDb& imdb, string& src, string& dest);


int main(int argc, const char * argv[]) {
    
    IMDb imdb;
    imdb.loadDataBase();
    
    char exit;
    do {
        
        string a1, a2;
        prompt(a1, a2);
        
        cout << findTarget(a1, a2);
        cout << "Press Q to quit\n";
        cin >> exit;
    } while (exit!=tolower('Q'));
    
    return 0;
}

Actor findTarget(IMDb& imdb, string& a1, string& a2) {
    
    vector<string> films, casts; // vectors to contain all the films and casts
                                 // assoc. with an actor and film respectfully
    AVLTree<Actor> actorTree;    // tree to contain visited actors (no duplicates)
    AVLTree<Movie> movieTree;    // tree to contain visited movies (no duplicates)
    queue<string> qu;            // queue to contain actor (names) assoc. with
                                 // a1 (no duplicates)
    
    qu.push(a1);                 // push a1 into the queue whose movies we want to
                                 // extract/examine to find a2
    Actor src(a1, "", "");      // construct a src actor object
    actorTree.insertWithReturnPointer(src); // put src actor object in actorTree
    
    bool found = false;
    while (!qu.empty() && !found) {
        
        string currentActor = qu.front();
        
        imdb.getCredits(currentActor, films);
        
        for (int i = 0; i<films.size(); ++i) {
            
            if (!movieTree.searchAVL(Movie(films[i]))) {
                
                // query film & put into tree iff not there. If film already there, break
                movieTree.insertWithReturnPointer(Movie(films[i]));
                
                imdb.getCast(films[i], casts); // query casts & put into tree iff not there
                
                for (int j=0; j<casts.size(); ++j) {
                    
                    // sorting actors into the actorTree
                    if ( casts[j]!=currentActor) {
                        Actor act;
                        Actor prevAct;
                        if (!actorTree.searchAVL(Actor(casts[j]))) {
                            // if Actor is not already in the tree, add it to the tree
                            act = actorTree.insertWithReturnPointer(Actor(casts[j], films[i], currentActor))->getData();
                            // and update its path to include the previous connecting actor
                            prevAct = actorTree.searchAVL(Actor(currentActor))->getData();
                            act.addConnection(prevAct.getPath(), prevAct.getPrevious());
                            // cout << act;
                            qu.push(casts[j]); // push into queue of actors to examine
                        }
                        // checking if target is found
                        if (casts[j] == a2) {
                            //cout << act;
                            act.addBaconLevel(); // bump up bacon number
                            return act;
                        }
                        // if target is deeper than 5 levels, stop looking
                        if (act.getBaconLevel() > 5) {
                            return Actor();
                        }
                    } // end of actorTree sorting
                    // keep track of bacon number
                } // end of the loop for extraditing actor from the film
            } // end of detecting a unique film and putting it in a tree
        } // end of the loop for querrying the films of an actor
        qu.pop();
    }
    return Actor();
}

void prompt(string& src, string& dest) {
    
    cout << "Please choose an actor: ";
    getline(cin, src);
    cout << "Please choose anctor as target: ";
    getline(cin, dest);
    
    cout << "Please wait while I load...\n";
}
