//
// Created by Volodymyr Fomenko on 2020-02-20.
//

#ifndef HASHCODE2020_BOOK_H
#define HASHCODE2020_BOOK_H


class Book {
public:
    int id;
    int score;

    Book() {

    }

    Book(int id, int score) {
        this->id = id;
        this->score = score;
    }
};


#endif //HASHCODE2020_BOOK_H
