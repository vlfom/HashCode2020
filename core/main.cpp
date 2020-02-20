#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "Book.h"
#include "Library.h"

using namespace std;

void read_input (string filename,  vector<Library>& libs) {
    int B, L, D;

    ifstream fin(filename);

    unordered_map<int, int> books;

    fin >> B >> L >> D;
    
    for (int i = 0; i < B; i++) {
        int book_sc;
        fin>>book_sc;
        books[i] = book_sc;
    }

    for (int i = 0; i < L; i++) {
        int Ni, Ti, Mi;

        fin >> Ni >> Ti >> Mi;
        
        Library lib(Ti, Mi, Ni);
        
        for (int j = 0; j < Ni; j++) {
            int book_id;
            fin >> book_id;
            lib.books.push_back(Book(book_id, books[book_id]));
        }

        libs.push_back(lib);
    }
}

int main(int argc, char **argv) {
    vector<Library> libs;
    read_input(argv[1], libs);
}