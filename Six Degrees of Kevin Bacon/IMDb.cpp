//
//  IMDb.cpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/5/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#include "IMDb.hpp"

IMDb::IMDb(): dbPath("IMDb.tsv") {
    db.open(dbPath);
    if (!db.good())
        exit(1);
}

IMDb::~IMDb() {
    db.close();
}

IMDb::IMDb(const IMDb& other): dbPath(other.dbPath), actor(other.actor), movie(other.movie) {
    db.close();
    db.open(dbPath);
}

IMDb& IMDb::operator=(const IMDb& other) {
    if (this != &other) {
        dbPath = other.dbPath;
        actor = other.actor;
        movie = other.movie;
        db.close();
        db.open(dbPath);
    }
    return *this;
}

void IMDb::loadDataBase() {
    string line, _movie, _actor;
    int count = 0;
    while (db) {
        getline(db,line);
        stringstream ss;
        ss.str(line);
        getline(ss,_movie,'\t');
        getline(ss,_actor,'\t');
        
        actor.insertWithReturnPointer(data(_actor)) -> data().addConnection(_movie);
        movie.insertWithReturnPointer(data(_movie)) -> data().addConnection(_actor);
        
        if (!(count%110542)) {
            cout << count/110542 << "0%...";
        }
        ++ count;
    }
    cout << "Done!";
    
}

bool IMDb::getCredits(const string& actorName, vector<string>& films)const {
    TreeNode<data>* temp = actor.searchAVL(data(actorName));
    if (!temp)
        return false;
    
    films.clear();
    for (int i = 0; i < temp->data().getConnected().size(); ++i) {
        films.push_back(temp->data().getConnected()[i]);
    }
    return true;
}

bool IMDb::getCast(const string& movieTitle, vector<string>& casts)const {
    TreeNode<data>* temp = movie.searchAVL(data(movieTitle));
    if (!temp)
        return false;
    
    casts.clear();
    for (int i = 0; i < temp->data().getConnected().size(); ++i) {
        casts.push_back(temp->data().getConnected()[i]);
    }
    return true;
}

string IMDb::accessActor(const string& huffmanCode, int index) {
    TreeNode<data>* walker = actor.root();
    while (index < huffmanCode.size()) {
        if (huffmanCode[index] == '1') {
            if (walker -> getGreaterNode())
                walker = walker -> greaterNode();
            else
                break;
        }
        else {
            if (walker -> getSmallerNode())
                walker = walker -> smallerNode();
            else
                break;
        }
        ++ index;
    }
    return walker -> data().getString();
}
