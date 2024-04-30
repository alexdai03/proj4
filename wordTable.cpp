/* wordTable.cpp
 * date: April 19th, 2024
 * Author: Alex Dai, Aarush Ganji
 * utlns: zdai03, aganji01
 * Project 4 - Gerp
 *
 * description: This file contains implementations of WordTable class
 */

#include "wordTable.h"


WordTable::WordTable(){
    currSize = 0;
    capacity = DEFAULT_SIZE;
    insensitive_table = new list<ICase>[capacity];
}

WordTable::~WordTable(){
    delete [] insensitive_table;
}

void WordTable::insensitive_search(string &word, ofstream &output){
    bool contains = false;
    int hashcode = hash<string>{}(to_lower(word)) % capacity;

    list<ICase> *whichTable = &insensitive_table[hashcode];
    ICase *thisTable;

    list<ICase>::iterator it = whichTable->begin();
    for (it; not (it == whichTable->end()); it ++){
        if (it->equal(to_lower(word))){
            *thisTable = *it;
            contains = true;
        }
    }
    if (contains){
        int size = thisTable->sensitive_table.size();
        for (int i = 0; i < size; i ++){
            set<string>::iterator ir;
            ir = thisTable->sensitive_table[i].info.begin();
            for (ir; not (ir == it->sensitive_table[i].info.end()); ir ++){
                output << *ir << endl;
            }
        }
    }
    else {
        output << word << "Not Found." << endl;
    }
}   

void WordTable::sensitive_search(string &word, ofstream &output){
    bool contains = false;
    bool found = false;
    int hashcode = hash<string>{}(to_lower(word)) % capacity;

    list<ICase> *whichTable = &insensitive_table[hashcode];
    ICase *thisTable;
    set<string> *this_info;

    list<ICase>::iterator it = whichTable->begin();
    for (it; not (it == whichTable->end()); it ++){
        if (it->equal(to_lower(word))){
            *thisTable = *it;
            contains = true;
        }
    }
    int size = thisTable->sensitive_table.size();
    for (int i = 0; i < size; i++){
        if (thisTable->sensitive_table[i].contains(word)){
            *this_info = thisTable->sensitive_table[i].info;
            found = true;
        }
    }
    if (contains and found){
        set<string>::iterator i = this_info->begin();
        for (i; not (i == this_info->end()); i ++){
            output << *i << endl;
        }
    }
    else{
        output << word << "Not Found. Try with @insensitive or @i." << endl;
    }
}

void WordTable::add_words(string &line, int line_num, string path){
    istringstream input(line);
    string word;
    int ikey, key;
    
    while ((not input.eof()) and (input >> word)){
        bool contains = false;
        word = stripNonAlphaNum(word);
    
        ikey = hash<string>{}(to_lower(word)) % capacity;
        list<ICase> *whichTable = &insensitive_table[ikey];

        list<ICase>::iterator it = whichTable->begin();
        for (it; not (it == whichTable->end()); it ++){
            if (it->equal(to_lower(word))){
                contains = true;
                it->init_sensitive(word, path, line_num, line);
            }
        } 
        if (not contains){
            ICase this_case(to_lower(word));
            this_case.init_sensitive(word, path, line_num, line);
            whichTable->push_back(this_case);
            currSize ++;
        }
        if (currSize/capacity > 0.7){
            rehash();
        }
    }
}



void WordTable::rehash(){
    list<ICase> *old_table = insensitive_table;
    int old_capacity = capacity;
    capacity = 2 * capacity;
    insensitive_table = new list<ICase>[capacity];
    currSize = 0;
    
    // insert old elements into new structure
    for(int i = 0; i < old_capacity; i++) {
        list<ICase> *whichTable = &old_table[i];
        list<ICase>::iterator it = whichTable->begin();
        for (it; not (it == whichTable->end()); it ++){
            add_for_rehash(*it);
        }
    }
    delete [] old_table;
}

void WordTable::add_for_rehash(ICase this_case){

    int ikey = hash<string>{}(to_lower(this_case.key)) % capacity;

    list<ICase> *whichTable = &insensitive_table[ikey];

    if (whichTable->size() == 0){
        whichTable->push_back(this_case);
        currSize ++;
    }

    string word = this_case.key;
    list<ICase>::iterator it = whichTable->begin();
    for (it; not (it == whichTable->end()); it ++)
    {
        if (not (it->equal(word)))
        {
            whichTable->push_back(this_case);
            currSize ++;
        }
    }
}


string WordTable::stripNonAlphaNum(string input){
    size_t start = 0, end = input.size();

    // Find the first alphanumeric character
    while (start < end and not(input[start] >= '0' and input[start] <= '9' or
                               input[start] >= 'A' and input[start] <= 'Z' or
                               input[start] >= 'a' and input[start] <= 'z')) {
        start++;
    }

    // Find the last alphanumeric character
    while (end > start and not(input[end - 1] >= '0' and input[end - 1] <= '9' 
                        or input[end - 1] >= 'A' and input[end - 1] <= 'Z' 
                        or input[end - 1] >= 'a' and input[end - 1] <= 'z')) {
        end--;
    }

    // Return the substring from start to end
    return input.substr(start, end - start);
}

string WordTable::to_lower(string word){

    istringstream iss(word);
    char c;
    iss.get(c);
    string lower = "";

    while (not iss.eof()){
        c = char(tolower(c));
        lower += string(1, c);
        iss.get(c);
    }

    return lower;
}