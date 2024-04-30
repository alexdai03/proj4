/* gerp.h
 * date: April 19th, 2024
 * Author: Alex Dai, Aarush Ganji
 * utlns: zdai03, aganji01
 * Project 4 - Gerp
 *
 * description: this class initilizes the gerp object. Gerp is a simple word
 * search tool that instantaneously locates a user provided word in all user
 * provided files.
 
 * Utilities:
 * 1) case-sensitive search, implemented by directly typing the word as the
 *    query 
 * 2) case-insensitive search, implemented using: @i [word] or 
 *    @insensitive [word]. 
 * 3) change the ourput file using: @f [FileName]
 * 4) terminate search using: @q or @quit
 *
 * Gerp class interacts with functions in processing.cpp and wordTable class to
 * store locations and information of all unique words in files that the user
 * provide.
 * 
 * TODO: complete the description
 */

#ifndef GERP_H
#define GERP_H

#include "wordTable.h"
#include "FSTree.h"
#include "DirNode.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


using namespace std;

class Gerp
{
  public:

    void run(const string &input, const string &output);
    // keep updating new functionalities

  private:

    template<typename streamtype>
    void open_or_die(streamtype &stream, string file_name);
    void traverseDirectory(string directory);
    void recursive_traversal(DirNode *curr, string path);
    void fill_table(string infile, string file_path);
    void implement_command(istream &iss, const string &output);
 


    // should it be a pointer?
    WordTable *table;
};




#endif