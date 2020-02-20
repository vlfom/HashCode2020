#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include "Book.h"
#include "Library.h"
#include "choos_libs.h"
#include "choose_books.h"


using namespace std;

void read_input (string filename,  vector<Library>& libs, int& D) {
    int B, L;

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
        
        Library lib(i, Ti, Mi, Ni);
        
        for (int j = 0; j < Ni; j++) {
            int book_id;
            fin >> book_id;
            lib.books.push_back(Book(book_id, books[book_id]));
        }

        libs.push_back(lib);
    }
}

void write_output (string filename, vector<Library>& libs) {
    ofstream fout(filename);

    cout << libs.size() << "\n";

    for (int i = 0; i < libs.size(); i++) {
        cout << libs[i].id << " " << libs[i].books.size() << "\n";
        for (int j = 0; j < libs[i].books.size(); j++) {
            cout << libs[i].books[j].id << " ";
        }
        cout<<"\n";
    }
}

int main(int argc, char **argv) {
    vector<Library> libs;
    int D;

    read_input(argv[1], libs, D);

    vector<Library> res = get_books(D, get_lib_order(D, libs));

    write_output(argv[2], res);

}