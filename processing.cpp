#include "processing.h"
#include "FSTree.h"
#include "DirNode.h"


string stripNonAlphaNum(string input){
    istringstream iss(input);
    char c;
    iss.get(c);
    int leading = 0;
    int trailing = 0;
    
    while (not ((int(c) > 47 and int(c) < 58) or 
                (int(c) > 64 and int(c) < 91) or
                (int(c) > 96 and int(c) < 123)))
    {  
        leading ++;
        iss.get(c);
    }

    for (int i = input.length() - 1; i >= 0; i --){
        c = input[i];
        if (not ((int(c) > 47 and int(c) < 58) or 
                 (int(c) > 64 and int(c) < 91) or
                 (int(c) > 96 and int(c) < 123)))
        {
            trailing ++;
        } 
        else
        {
            i = 0;
        }
    }

    return input.substr(leading, input.length() - trailing);
}


void traverseDirectory(string directory){
    FSTree tree(directory);
    DirNode *root = tree.getRoot();
    int numDirs = root->numSubDirs();
    
    for (int i = 0; i < numDirs; i++)
    {
        if (root->hasFiles())
        {
            int numFiles = root->numFiles();
            for (int i = 0; i < numFiles; i++)
            {
                cout << root->getName() << "/";
                cout << root->getFile(i) << endl;
            }
        }
        cout << root->getName() << "/";
        root = root->getSubDir(i);
    }
}