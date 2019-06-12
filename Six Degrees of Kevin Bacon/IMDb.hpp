//  IMDb.hpp
//  Six Degrees of Kelvin Bacon
#ifndef IMDb_hpp
#define IMDb_hpp
#include <fstream>
#include <sstream>
#include "Tree/AVL Tree.hpp"
#include "data.hpp"
/*
 * IMDb class
 * Process the local database and load everything into the tree.
 */
class IMDb {
    
private:
    std::ifstream db;
    std::string dbPath;
    AVLTree<data> actor;
    AVLTree<data> movie;

public:
    IMDb();
    ~IMDb();
    IMDb(const IMDb& other);
    IMDb& operator=(const IMDb& other);
    
    void loadDataBase();
    /* Loads all the local data from a *.tsv formatted database.
     * The data will be loaded into two trees, [actor] and [movie]
     * Each node contains necessary information for path finding.
     */
    bool getCredits(const string& actorName, vector<string>& films)const;
    /* Takes an actor name as a string in parameter, and a vector of films,
     * then replace the films with actual film list that the specified actor has involved with
     * Return true if the actor has been founded, return false if not found.
     */
    bool getCast(const string& movieTitle, vector<string>& casts)const;
    /* Takes a movie name as a string in parameter, and a vector of casts,
     * then replace the casts with actual cast list that the specified movie has involved with
     * Return true if the movie has been founded, return false if not found.
     */
    string accessActor(const string& huffmanCode = "", int index = 0);
    /* Find an actor using the huffman code.
     *  start from the tree root, go right if the char is 1, go left if 0.
     *  i.e. "01101", left,right,right,left,right
     * This function will be used to "randomly" choose an actor for testing purposes.
     */
};

#endif /* IMDb_hpp */
