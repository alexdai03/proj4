/*
 *  CharArrayList.h
 *  Alex Dai
 *  Jan 26th
 *
 *  COMP 15 HW 1 Cheshire ConCATenation
 *
 *  Keep track of all the methods in the class arraylist and the member
 *  variables in the list
 *
 */
#ifndef CHAR_ARRAY_LIST_H
#define CHAR_ARRAY_LIST_H

#include <iostream>
#include <string>
#include <stdexcept>

class CharArrayList {
public:
    CharArrayList();
    CharArrayList(char c);
    CharArrayList(char *arr, int size);
    CharArrayList(const CharArrayList &other);
    ~CharArrayList();
    CharArrayList &operator=(const CharArrayList &other);

    bool isEmpty() const;
    void clear();
    int size() const;
    char first() const;
    char last() const;
    char elementAt(int index) const;
    std::string toString() const;
    std::string toReverseString() const;
    void pushAtBack(char c);
    void pushAtFront(char c);
    void insertAt(char c, int index);
    void insertInOrder(char c);
    void popFromFront();
    void popFromBack();
    void removeAt(int index);
    void replaceAt(char c, int index);
    void concatenate(CharArrayList *other);

private:
    int vSize;
    int capacity;
    char *buffer;

    void expand();
};



#endif
