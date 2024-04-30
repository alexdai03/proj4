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
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <set>
#include <cctype>
#include <functional>
#include <utility>
#include <cstring>

using namespace std;

class WordTable
{
  public:

    //constructor, intializes the word table with the file passed in.
    //should it pass in a file or an istringstream?
    //every index unless filled with words, should be initialized with -1
    WordTable();
    ~WordTable();

    void add_words(string &line, int line_num, string path);

    //hash words using hash<string>{} (the string to be hashed)
    //compress using mod array size
    //keep track of the load factor with (size/capacity) < 0.7
    //
    void insensitive_search(string &word, ofstream &output);

    void sensitive_search(string &word, ofstream &output);



  private:
    const int DEFAULT_SIZE = 11;

    struct WordInfo
    {
        string word; // this is also the key
        set<string> info;

        WordInfo(string &s, string &path){
            word = s; 
            info.insert(path);
        }

        // only store once if two same words appear in the same line.
        bool contains(string s){
            return word == s;
        }
    };

    struct ICase
    {
        string key;
        //each insensitive case contain a table of sensitive cases
        vector<WordInfo> sensitive_table;

        ICase(const string s){
            key = s;
        } 

        bool equal(const string s){
            return s == key;
        }

        void init_sensitive(string &word, string &path, int num, string &line)
        {
            int size = sensitive_table.size();
            if (size == 0)
            {
                string info = path + ":" + to_string(num) + ": " + line;
                WordInfo s_case(word, info);
                sensitive_table.push_back(s_case);
            }
            else {
                bool contains = false;
                for (int i = 0; i < size; i ++)
                {
                    if (sensitive_table[i].contains(word)){
                        contains = true;
                        string info = path + ":"+ to_string(num) + ": " + line;
                        sensitive_table[i].info.insert(info); 
                    }
                }  
                if (not contains){
                    string info = path + ":" + to_string(num) + ": " + line;
                    WordInfo s_case(word, info);
                    sensitive_table.push_back(s_case);
                }
            } 
        }
    };

    list<ICase> *insensitive_table;

    int currSize;
    int capacity;

    string stripNonAlphaNum(string input);
    string to_lower(string word);
    void rehash();
    void add_for_rehash(ICase this_case);
    bool list_contains(list<ICase> list, string s);
};




#endif