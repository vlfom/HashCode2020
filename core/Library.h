//
// Created by Volodymyr Fomenko on 2020-02-20.
//

#ifndef HASHCODE2020_LIBRARY_H
#define HASHCODE2020_LIBRARY_H

#include "Book.h"
#include <vector>

class Library {
public: 
    int id;
    int t;
    int m;
    int n;
    double key;
    vector<Book> books;

    Library() {}

    Library(int t, int m, int n) {
        this->t = t;
        this->m = m;
        this->n = n;
        this->key=0;
    }
};


#endif //HASHCODE2020_LIBRARY_H
