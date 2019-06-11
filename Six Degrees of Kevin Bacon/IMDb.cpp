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
    if (!db.good()) {
        cout << "File Not in Path. ";
        exit(1);
    }
}

IMDb::~IMDb() {
    db.close();
}

IMDb::IMDb(const IMDb& other): dbPath(other.dbPath), _actor(other._actor), _movie(other._movie) {
    db.close();
    db.open(dbPath);
}

IMDb& IMDb::operator=(const IMDb& other) {
    if (this != &other) {
        dbPath = other.dbPath;
        _actor = other._actor;
        _movie = other._movie;
        db.close();
        db.open(dbPath);
    }
    return *this;
}

void IMDb::loadDataBase() {
    string line, movieTitle, actorName, prevActor, prevMovie;
    
    while (db) {
        string connection;
        getline(db,line);
        stringstream ss;
        ss.str(line);
        getline(ss,movieTitle,'\t');
        getline(ss,actorName,'\t');
        
        _actor.insertWithReturnPointer(data(actorName)) -> data().addConnection(movieTitle);
        _movie.insertWithReturnPointer(data(movieTitle)) -> data().addConnection(actorName);
    }
}

bool IMDb::getCredits(const string& actorName, vector<string>& films)const {
    TreeNode<data>* temp = _actor.searchAVL(data(actorName));
    if (!temp)
        return false;
    
    films.clear();
    for (int i = 0; i < temp->data().getConnection().size(); ++i) {
        films.push_back(temp->data().getConnection()[i]);
    }
    return true;
}

bool IMDb::getCast(const string& movieTitle, vector<string>& casts)const {
    TreeNode<data>* temp = _movie.searchAVL(data(movieTitle));
    if (!temp)
        return false;
    
    casts.clear();
    for (int i = 0; i < temp->data().getConnection().size(); ++i) {
        casts.push_back(temp->data().getConnection()[i]);
    }
    return true;
}


