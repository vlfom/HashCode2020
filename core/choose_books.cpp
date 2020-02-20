//
// Created by Volodymyr Fomenko on 2020-02-20.
//

#include "choose_books.h"

bool comp(Book a, Book b) {
    return a.score > b.score;
}

vector <Library> get_books(int D, vector <Library> libs) {
//    map<int, vector<Library>> queue;
//    set<pair<int, int>> books;
//
//    int current_time_min = 0;
//    for (int i = 0; i < libs.size(); ++i) {
//        if (current_time_min + libs[i].t >= D) {
//            break;
//        }
//
//        if (queue.count(libs[i].t) == 0) {
//            queue[libs[i].t] = vector<Library>();
//        }
//        queue[libs[i].t].push_back(libs[i]);
//
//        sort(libs[i].books.begin(), libs[i].books.end(), &comp);
//
//        current_time_min += libs[i].t;
//    }

    for (int i = 0; i < libs.size(); ++i) {
        sort(libs[i].books.begin(), libs[i].books.end(), &comp);
    }
    

    return libs;
}