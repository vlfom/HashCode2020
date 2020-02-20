#include <iostream>
#include <vector>
#include "Book.h"
#include "Library.h"

using namespace std;

void read_input (string filename) {
    int B, L, D;

    cin >> B >> L >> D;
    vector<Book> books(B);
    
    for (int i = 0; i < B; i++) {
        int book_sc;
        cin>>book_sc;

        books.push_back(Book(i, book_sc));
    }

    for (int i = 0; i < L; i++) {
        int Ni, Ti, Mi;

        cin >> Ni >> Ti >> Mi;
        
        Library lib(Ti, Mi, Ni);
        
        for (int j = 0; j < Ni; j++) {
            int book_id;
            cin >> book_id;
            lib.books.push_back(Book(book_id));
        }
    }
}

int main() {

}