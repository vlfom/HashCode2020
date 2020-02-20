#include <bits/stdc++.h>

using namespace std;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef pair<long double, int> di;
typedef pair<long double, ii> dii;

int b, l, d, n, id, score[100001], apptime[100001], signup[100001], booksperday[100001], libscur[100001], a, y, k1, ki;
bitset<100001> check;
bitset<100001> checkbooks;
vector<int> libraries[100001];
unordered_set<int> librarcont[100001];
vector<int> apploc[100001];

int grade(const vector<int>& libs, const vector< vector<int> >& bks) {
  check.reset(); checkbooks.reset();
  a = libs.size();
  int totscore = 0;
  int ctime = 0;
  for (int i = 0; i < a; i++) {
    y = libs[i]; k1 = bks[i].size();
    if (y >= l) {
      cerr << "Error: invalid library id " << y << "." << endl;
      return 0;
    }
    if (check[y]) {
      cerr << "Error: listed library " << y << " twice." << endl;
      return 0;
    }
    check[y] = 1;
    ctime += signup[y];
    for (int k = 0; k < k1; k++) {
      ki = bks[i][k];
      if (librarcont[y].find(ki) == librarcont[y].end()) {
        cerr << "Error: library " << y << " does not contain book " << ki << "." << endl;
        return 0;
      }
      if (ctime + k / booksperday[y] < d && !checkbooks[ki]) {
        totscore += score[ki];
        checkbooks[ki] = 1;
      }
    }
  }
  return totscore;
}

long double calc_score(const unordered_set<int>& booksused, int lib, int ctime, vector<ii>& bookids, bool pushtovec = false) {
  long double totscore = 0.0;
  vector<ii> bscores;
  for (int i = 0; i < libraries[lib].size(); i++) {
    int cb = libraries[lib][i];
    if (booksused.find(cb) == booksused.end()) {
      bscores.push_back(ii(-score[cb], cb));
    }
  }
  sort(bscores.begin(), bscores.end());
  for (int i = 0; i < bscores.size(); i++) {
    if (pushtovec) bookids.push_back(ii(bscores[i].second, 0));
    if (ctime + signup[lib] + i / booksperday[lib] < d) {
      if (pushtovec) bookids.back().second = 1;
      // totscore -= bscores[i].first;
    }
    if (signup[lib] + i / booksperday[lib] < (d - ctime) * 180 / 100) {
      totscore -= bscores[i].first;
    }
  }
  return totscore / signup[lib];
}

int main(int argc, char** argv) {
  memset(apptime, 0, sizeof apptime);
  memset(libscur, 0, sizeof libscur);
  string infile = "input.txt";
  string outfile = "output.txt";
  if (argc >= 2) {
    infile = argv[1];
    outfile = "output-" + infile;
  }
  if (argc >= 3) {
    outfile = argv[2];
  }
  ifstream fin1(infile);
  fin1 >> b >> l >> d;
  for (int i = 0; i < b; i++)
    fin1 >> score[i];
  for (int i = 0; i < l; i++) {
    fin1 >> n >> signup[i] >> booksperday[i];
    for (int k = 0; k < n; k++) {
      fin1 >> id;
      libraries[i].push_back(id);
      librarcont[i].insert(id);
      apptime[id]++;
      apploc[id].push_back(i);
    }
  }
  fin1.close();

  unordered_set<int> used; int ctime = 0;
  priority_queue<dii> pq; vector<ii> bookids; vector<ii> bookids2;
  for (int i = 0; i < l; i++) {
    pq.push(dii(calc_score(used, i, ctime, bookids2), ii(i, 0)));
  }
  vector<int> libs;
  vector< vector<int> > bks;
  while (!pq.empty()) {
    dii best = pq.top(); pq.pop();
    int clib = best.second.first; int lidx = best.second.second;
    if (lidx == libscur[clib]) {
      long double sc = calc_score(used, clib, ctime, bookids, true);
      libscur[clib] = -1;
      ctime += signup[clib];
      libs.push_back(clib);
      bks.push_back(vector<int>());
      for (int i = 0; i < bookids.size(); i++) {
        int bkid = bookids[i].first;
        bks.back().push_back(bkid);
        if (bookids[i].second) // book can be scanned
          used.insert(bkid);
      }
      for (int i = 0; i < bookids.size(); i++) {
        int bkid = bookids[i].first;
        if (bookids[i].second) { // book can be scanned
          for (int k = 0; k < apploc[bkid].size(); k++) {
            int blib = apploc[bkid][k];
            if (libscur[blib] >= 0) {
              libscur[blib]++;
              pq.push(dii(calc_score(used, blib, ctime, bookids2), ii(blib, libscur[blib])));
            }
          }
        }
      }
      bookids.clear();
    }
  }

  int solscore = grade(libs, bks);
  cout << solscore << endl;

  ofstream fout(outfile);
  int cntlibs = 0;
  for (int i = 0; i < libs.size(); i++) {
    if (bks[i].size() > 0)
      cntlibs++;
  }
  fout << cntlibs << endl;
  a = libs.size();
  for (int i = 0; i < a; i++) {
    if (bks[i].size() > 0) {
      fout << libs[i] << " " << bks[i].size() << endl;
      y = libs[i]; k1 = bks[i].size();
      for (int k = 0; k < k1; k++) {
        if (k > 0) fout << " ";
        ki = bks[i][k];
        fout << ki;
      }
      fout << endl;
    }
  }
  fout.close();

  return 0;
}