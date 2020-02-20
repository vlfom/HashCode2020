#include "choos_libs.h"

bool cmp(Library x, Library y) {
    return x.key < y.key;
}

vector < Library > get_lib_order(int D, vector < Library > libs, double t_coef, double b_coef) {
    for (int i = 0; i < libs.size(); i++) {
        libs[i].key = t_coef * libs[i].t + b_coef * ((libs[i].n + libs[i].m - 1) / libs[i].m);
    }
    sort(libs.begin(), libs.end(), cmp);
    return libs;
}

const int N = 1e5;
const int K = 10;
vector < int > libs_with_book[N];
vector < int > ids;

bool id_cmp(int i, int j) {

}

vector < Library > get_lib_order_D(int D, int B, vector < Library > libs, int seed=123) {
    srand(seed);
    random_shuffle(libs.begin(), libs.end());
    for (int i = 0; i < libs.size(); i++) {
        for (int j = 0; j < libs[i].books.size(); j++)
            libs_with_book[libs[i].books[j].id].push_back(i);
        libs[i].key++;
    }
    vector < Library > res;
    while (!libs.empty()) {
        for (int i = 0; i < K; i++) {
            res.push_back(libs.back());
            for (int j = 0; j < libs.back().books.size(); j++)
                for (int x : libs_with_book[libs.back().books[j]])
                    libs
            res.pop_back();
        }
    }
    return res;
}