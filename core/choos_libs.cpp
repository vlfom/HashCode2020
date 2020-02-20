#include "Book.h"
#include "Library.h"

bool cmp(Library x, Library y) {
    return x.key < y.key;
}

vector < int > get_lib_order(vector < Library > libs, double t_coef = 1, double b_coef = 0) {
    for (int i = 0; i < libs.size(); i++) {
        libs[i].key = t_coef * libs[i].t + b_coef * ((libs[i].n + libs[i].m - 1) / libs[i].m);
    }
    sort(libs.begin(), libs.end(), cmp);
    vector < int > res;
    for (int i = 0; i < libs.size(); i++)
        res.push_back(libs[i].id);
    return res;
}