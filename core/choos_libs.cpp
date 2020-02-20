#include "choos_libs.h"

#include <iostream>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

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
map<int, Library> libs;

vector < Library > get_lib_order_D(int D, vector < Library > libs_, int seed) {
    set<pair<int,int> > q;
    for (int i = 0; i < libs_.size(); i++) {
        int id = libs_[i].id;
        double priority = 0;
        for (int j = 0; j < libs_[i].books.size(); j++) {
            libs_with_book[libs_[i].books[j].id].push_back(id);
            priority += 1;
        }
        libs_[i].key = -priority;
        libs[id] = libs_[i];
        q.insert(make_pair(-priority,id));
    }

    vector<Library> res;
    int current_time = 0;
    while (!q.empty()) {
        pair<int,int> cur = *q.begin();
        q.erase(q.begin());
//        cout << cur.first << " " << cur.second << " " << q.size() << endl;
        int lib_id = cur.second;
        res.push_back(libs[lib_id]);
        libs.erase(lib_id);
        for(int i = 0; i < libs[lib_id].books.size(); ++i) {
            Book b = libs[lib_id].books[i];
            for (int j = 0; j < libs_with_book[b.id].size(); j++) {
                if (libs.count(libs_with_book[b.id][j]) > 0) {
                    Library temp = libs[libs_with_book[b.id][j]];
                    q.erase(make_pair(temp.key, temp.id));
                    temp.key += 1;
                    q.insert(make_pair(temp.key, temp.id));
                }
            }
        }
    }
    return res;
}