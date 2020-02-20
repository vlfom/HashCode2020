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
map<int, Library> libs;

struct Lib {
public:
    int lib_id;
    int priority;
};

bool operator ==(const LibLib& a, const LibLib& b) {
    return a.priority == b.priority && a.lib_id == b.lib_id;
}

bool operator <(const LibLib& a, const LibLib& b) {
    return a.priority > b.priority || a.priority == b.priority && a.lib_id > b.lid_id;
}

bool comp(LibLib a, LibLib b) {
    return a.priority > b.priority;
}

vector < Library > get_lib_order_D(int D, int B, vector < Library > libs_, int seed=123) {
    libs = libs_;

    set<Lib> q;
    for (int i = 0; i < libs_.size(); i++) {
        Lib temp;
        temp.lib_id = libs_[i].id;
        libs[libs_[i].id] = libs_[i];
        temp.priority = 0;
        for (int j = 0; j < libs_[i].books.size(); j++) {
            libs_with_book[libs_[i].books[j].id].push_back(libs_[i].id);
            temp.priority += 1;
        }
        q.insert(temp);
    }

    vector<Library> res;
    int current_time = 0;
    while (!q.empty()) {
        Lib cur = *q.begin();
        q.erase(q.begin());
        for(int i = 0; i < libs[cur.lib_id].books.size(); ++i) {
            Book b = libs[cur.lib_id].books[i];
            for (int j = 0; j < libs_with_book[b.id]; j++) {
                Lib temp = libs[libs_with_book[b.id][j]];
                q.erase(temp);
                temp.priority -= 1;
                q.insrt(temp);
            }
        }
    }
    return res;
}