/* wordTable.h
 * date: April 19th, 2024
 * Author: Alex Dai, Aarush Ganji
 * utlns: zdai03, aganji01
 * Project 4 - Gerp
 *
 * description: wordTable is a class that stores all words inside given files,
 * meanwhile, it facilitate access of these words. Particularly, every words
 * is specified with different locations that it exist inside given files.
 *
 * Utility: provide access of different words and their locations inside files.
 *
 * This class will interact with functions of proccessing.cpp to process words
 * in files before they were stored to the table. It serve as a database for
 * search utilities of Gerp class.
 *
 * TODO: update the description
 */


#ifndef WORD_TABLE_H
#define WORD_TABLE_H

#include <string>
#include <vector>
#include <list>
#include <set>
#include <cctype>
#include <functional>
#include <utility>


class WordTable
{
  public:

    string at(int index);
    // keep updating new functionalities

  private:

    struct sensitive_words
    {
        set<string> file_info;
        set<int>    line_number;
    }

    //table that stores case-sensitive words
    vector<list<sensitive_words>>  *sensitive_table;

    //table for case-insensitive words
    vector<list<*sensitive_table>> *insensitive_table;
}




#endif