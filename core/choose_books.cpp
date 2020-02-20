//
// Created by Volodymyr Fomenko on 2020-02-20.
//

#include "Book.h"
#include "Library.h"

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <set>

vector <int> get_books(vector <Library> libs) {
    map<int, vector<Library>> queue;
    for (int i = 0; i < libs.size(); ++i) {
        if (queue.count(libs[i].t) == 0) {
            queue[libs[i].t] = vector<Library>();
        }
        queue[libs[i].t].push_back(libs[i]);
    }
    return libs;
}