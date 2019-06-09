//
//  IMDb.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/5/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef IMDb_hpp
#define IMDb_hpp

#include <fstream>
#include <sstream>
#include <utility>
#include "Tree/AVL Tree.hpp"
#include "data.hpp"

class IMDb {
private:
    std::ifstream db;
    std::string dbPath;
    AVLTree<data> _actor;
    AVLTree<data> _movie;

    
public:
    IMDb();
    ~IMDb();
    IMDb(const IMDb& other);
    IMDb& operator=(const IMDb& other);
    
    void loadDataBase();
    
    void searchDataBase(string name);
    
    bool getCredits(const string& actorName, vector<string>& films)const;
    bool getCast(const string& movieTitle, vector<string>& casts)const;
    
};

#endif /* IMDb_hpp */
