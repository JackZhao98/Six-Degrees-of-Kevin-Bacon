//
//  path.hpp
//  Six Degrees of Kelvin Bacon
//
//  Created by Jack Zhao on 6/6/19.
//  Copyright © 2019 Jack Zhao. All rights reserved.
//

#ifndef path_hpp
#define path_hpp
#include <string>
#include <iostream>
#include <vector>
#include "IMDb.hpp"

struct edge {
    std::string movieTitle;
    std::string actorName;
    
    edge(const std::string& movie = "", const std::string& actor = ""): movieTitle(movie), actorName(actor){}
};

class path {
private:
    std::string startActor;
    std::vector<edge> links;
    
public:
    path(const std::string& _startActor= "Kevin Bacon");
    ~path();
    path(const path& other);
    path& operator=(const path& other);
    
    bool buildPath(const std::string& startActor, const std::string& targetActor, const IMDb& database);
    
    int getLength() const;
    void addConnection(const std::string& movie, const std::string& actor);
    void removeLastConnection();
    const std::string& getLastKnownActor() const;
    
    void reversePath();
    
    friend
    std::ostream& operator<<(std::ostream& out, const path& print);
};

#endif /* path_hpp */
