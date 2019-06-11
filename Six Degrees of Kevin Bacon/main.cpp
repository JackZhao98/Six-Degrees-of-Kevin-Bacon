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
const int MAX_BACON_LEVEL = 5;
void prompt(string& src, string& dest);
Actor findTarget(IMDb& imdb, string src, string dest);

int main(int argc, const char * argv[]) {
    
    IMDb imdb;
    imdb.loadDataBase();
    
    
    string a1 = "";                   // src actor name
    string a2 = "";                   // dest ctor name
    prompt(a1, a2);                   // ask users to pick the names
    cout << findTarget(imdb, a1, a2); // bsf calculation for shortest path
    // error: the bacon number returns incorrectly here but not in the findTarget fxn
    
    return 0;
}

// Breadth Search First
Actor findTarget(IMDb& imdb, string a1, string a2) {
    
    vector<string> films, casts; // vectors to contain all the films and casts
    // assoc. with an actor and film respectfully
    AVLTree<Actor> actorTree;    // tree to contain visited actors (no duplicates)
    AVLTree<Movie> movieTree;    // tree to contain visited movies (no duplicates)
    queue<string> qu;            // queue to contain actor (names) assoc. with
    // a1 (no duplicates)
    
    qu.push(a1);                 // push a1 into the queue whose movies we want to
    // extract/examine to find a2
    Actor src(a1, "", "");       // construct a src actor object
    actorTree.insertWithReturnPointer(src); // put src actor object in actorTree
    
    bool found = false;          // boolean that breaks and returns if a2 is found
    
    while (!qu.empty() && !found) {
        string currentActor = qu.front(); // currentActor is actor (name) used to
        // explore movie paths leading to other actors
        imdb.getCredits(currentActor, films);  // query films and load into films vector
        
        for(int i=0;i<films.size();++i) {
            // go through each film. Use film to find deeper actor/film connections and
            // sort them into respective trees IFF not already in the trees
            if (!movieTree.searchAVL(Movie(films[i]))) {
                // load movie to tree and then query casts and load into casts vector
                movieTree.insertWithReturnPointer(Movie(films[i]));
                imdb.getCast(films[i], casts);
                
                for (int j=0; j<casts.size(); ++j) {
                    // Skip/Avoid examining actor in the movie casts who is myself
                    if ( casts[j]!=currentActor) {
                        Actor act, prevAct; // create temp actor objects
                        // Sort actors into the actorTree IFF not already in tree
                        if (!actorTree.searchAVL(Actor(casts[j]))) {
                            // add actor to tree
                            act = actorTree.insertWithReturnPointer(Actor(casts[j], films[i], currentActor))->getData();
                            // Update added actor's path to accont for prev. connection
                            prevAct = actorTree.searchAVL(Actor(currentActor))->getData();
                            act.addConnection(prevAct.getPath(), prevAct.getPrevious());
                            // Push actor (name) into queue of actors for examining paths
                            qu.push(casts[j]);
                        }
                        // Return if target is found
                        if (casts[j] == a2) {
                            act.addBaconLevel(); // Round up a level of bacon number
                            cout << act;
                            return act;
                        }
                        // Stop looking if target is more than 5 levels deep
                        if (act.getBaconLevel() > MAX_BACON_LEVEL) {
                            return Actor();
                        }
                    } // end of actorTree sorting
                } // end of loop for extraditing actor from the film
            } // end of detecting a unique film and putting it in a tree
        } // end of loop for querrying the films of an actor
        qu.pop();
    }// end of loop for examining all viable actor candidates in 5 Bacon levels
    return Actor();
}

void prompt(string& src, string& dest) {
    
    cout << "Please choose an actor: ";
    getline(cin, src);
    cout << "Please choose anctor as target: ";
    getline(cin, dest);
    
    cout << "Please wait while I load...\n";
}
