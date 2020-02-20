//
// Created by Volodymyr Fomenko on 2020-02-20.
//

#include "choose_books.h"

bool comp(Book a, Book b) {
    return a.score > b.score;
}

vector < bool > used_books;
vector < int > cnt_books;

const int S0 = 100;
const int S1 = 30;

bool alt_comp(Book a, Book b) {
    a.score + (cnt_books[a.id] == 0 ? S0 : 0) + (cnt_books[a.id] == 1 ? S1 : 0) >
        b.score + (cnt_books[b.id] == 0 ? S0 : 0) + (cnt_books[b.id] == 1 ? S1 : 0);
}

vector <Library> get_books(int D, vector <Library> libs, int B = -1) {
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

    if (B == -1) {
        for (int i = 0; i < libs.size(); ++i) {
            sort(libs[i].books.begin(), libs[i].books.end(), &comp);
        }
    } else {
        used_books.assign(B, false);
        cnt_books.assign(B, 0);
        int time = D, i = 0;
        for ( ; i < libs.size(); i++) {
            time -= libs[i].t;
            if (time <= 0) {
                i--;
                break;
            }
            for (int j = 0; j < libs[i].books.size(); j++)
                cnt_books[libs[i].books[j].id]++;
        }
        for ( ; i >= 0; i--) {
            for (int j = 0; j < libs[i].books.size(); j++)
                cnt_books[libs[i].books[j].id]--;
            sort(libs[i].books.begin(), libs[i].books.end(), &alt_comp);
        }
    }

    return libs;
}