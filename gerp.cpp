/* gerp.cpp
 * date: April 19th, 2024
 * Author: Alex Dai, Aarush Ganji
 * utlns: zdai03, aganji01
 * Project 4 - Gerp
 *
 * description: This file contains implementations for gerp class
 */

#include "gerp.h"


void Gerp::run(const string &input, const string &output){

    //declare and initalize the table
    traverseDirectory(input);

    implement_command(cin, output);

    cout << "Goodbye! Thank you and have a nice day." << endl;

}

void Gerp::implement_command(istream &iss, const string &output){
    ofstream outstream;
    open_or_die(outstream, output);

    string command;
    bool quit = false;
    while ((not quit) and (iss >> command)){
        cout << "Query? ";
        if (command == "@i" or command == "@insensitive"){
            iss >> command;
            table->insensitive_search(command, outstream);
        }
        else if (command == "@f"){
            iss >> command;
            outstream.close();
            open_or_die(outstream, command);
        }
        else if (command == "@q" or command == "@quit"){
            quit = true;
        }
        else {
            table->sensitive_search(command, outstream);
        }
    }

    outstream.close();
}



void Gerp::traverseDirectory(string directory){
    FSTree tree(directory);
    DirNode *root = tree.getRoot();
    string path = "";

    recursive_traversal(root, path);
}

void Gerp::recursive_traversal(DirNode *curr, string path){

    path += curr->getName() + "/";

    if (curr->hasFiles())
    {
        int numFiles = curr->numFiles();
        for (int i = 0; i < numFiles; i++)
        {
            fill_table(curr->getFile(i), path + curr->getFile(i));
        }
    }
    if (not (curr->hasSubDir()))
    {
        return;
    }

    int numDirs = curr->numSubDirs();
    for (int i = 0; i < numDirs; i ++)
    {
        recursive_traversal(curr->getSubDir(i), path);
    } 
    return;
}

void Gerp::fill_table(string infile, string file_path){

    ifstream instream;
    open_or_die(instream, infile);

    int line_num = 1;
    string str;
    getline(instream, str);

    while (not instream.eof())
    {
        table->add_words(str, line_num, file_path);
        getline(instream, str);
        line_num ++;
    }

    instream.close();
}


/*
 * name:      open_or_die
 * purpose:   open a file or throw a runtime error if unable to open
 * arguments: stream: reference to the file stream to open
 *            file_name: name of the file to open
 * returns:   none
 * effects:   may throw a runtime error if unable to open the file
 */
template <typename streamtype>
void Gerp::open_or_die(streamtype &stream, string file_name)
{
    stream.open(file_name);
    if (not stream.is_open()){
        throw runtime_error("Unable to open file " + file_name);
    }
}