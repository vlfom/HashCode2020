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

void reset() {
  b = l = d = n = id = a = y = k1 = ki = 0;
  memset(score, 0, sizeof score);
  memset(apptime, 0, sizeof apptime);
  memset(signup, 0, sizeof signup);
  memset(booksperday, 0, sizeof booksperday);
  memset(libscur, 0, sizeof libscur);
  check.reset(); checkbooks.reset();
  for (int i = 0; i < 100001; i++) {
    libraries[i] = vector<int>();
    librarcont[i] = unordered_set<int>();
    apploc[i] = vector<int>();
  }
}

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
    if (signup[lib] + i / booksperday[lib] < (d - ctime) * 150 / 100) {
      totscore -= bscores[i].first;
    }
  }
  return totscore / signup[lib];
}

int calc_sol(vector<int>& libs, vector< vector<int> >& bks) {
  int rellibs = 0;
  unordered_set<int> used; int ctime = 0;
  priority_queue<dii> pq; vector<ii> bookids; vector<ii> bookids2;
  for (int i = 0; i < l; i++) {
    pq.push(dii(calc_score(used, i, ctime, bookids2), ii(i, 0)));
  }
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
        if (bookids[i].second) { // book can be scanned
          used.insert(bkid);
          rellibs = libs.size();
        }
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
  return rellibs;
}

void assign_books(vector<int>& libs, vector< vector<int> >& bks) {
  unordered_set<int> used; int ctime = 0;
  vector<ii> bookids;
  for (int i1 = 0; i1 < libs.size(); i1++) {
    if (i1 >= bks.size()) bks.push_back(vector<int>());
    bks[i1].clear();
    int clib = libs[i1];
    long double sc = calc_score(used, clib, ctime, bookids, true);
    ctime += signup[clib];
    for (int i = 0; i < bookids.size(); i++) {
      int bkid = bookids[i].first;
      bks[i1].push_back(bkid);
      if (bookids[i].second) // book can be scanned
        used.insert(bkid);
    }
    bookids.clear();
  }
}

int main(int argc, char** argv) {
  cout << fixed << setprecision(2);
  const bool siman = true;
  const int numin = 6;
  const string inps[] = {"a", "b", "c", "d", "e", "f"};
  bool recalc[] = {false, false, false, false, false, false};
  for (int i = 1; i < argc; i++) {
    for (int k = 0; k < numin; k++) {
      if (inps[k] == argv[i])
        recalc[k] = true;
    }
  }
  
  int total = 0;

  for (int k2 = 0; k2 < numin; k2++) {
    reset();
    vector<int> libs; vector< vector<int> > bks;
    ifstream fin1("..\\input\\" + inps[k2] + ".txt");
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

    int oldscore = 0, solscore = 0;
    ifstream fin2(inps[k2] + "-res.txt");
    if (fin2.is_open()) {
      fin2 >> a;
      for (int i = 0; i < a; i++) {
        fin2 >> y >> k1; libs.push_back(y); bks.push_back(vector<int>());
        for (int k = 0; k < k1; k++) {
          fin2 >> ki;
          bks[i].push_back(ki);
        }
      }
      fin2.close();
      oldscore = grade(libs, bks);
    }

    if (recalc[k2]) {
      libs.clear(); bks.clear();
      int rellibs = calc_sol(libs, bks);
      solscore = grade(libs, bks);

      if (siman) { // simulated annealing
        // cout << "relevant libraries: " << rellibs << " out of " << libs.size() << endl;
        vector<int> bestlibs = libs;
        const int steps = 1000;
        int cscore = solscore;
        for (int time = 0; time < steps; time++) {
          long double temp = 100.0 * pow(2.0, -time / (long double) (steps - 1));
          vector<int> libsb = libs;
          int shufflei = 0, shufflej = 0;
          while (shufflei == shufflej) {
            shufflei = floor(rand() / (1.0 + (long double) RAND_MAX) * rellibs);
            shufflej = rellibs + floor(rand() / (1.0 + (long double) RAND_MAX) * (min((int) libs.size(), rellibs + 250) - rellibs));
          }
          for (int i = shufflei; i < rellibs - 1; i++)
            libsb[i] = libs[i + 1];
          libsb[rellibs - 1] = libs[shufflej];
          // libsb[shufflei] = libs[shufflej];
          libsb[shufflej] = libs[shufflei];
          assign_books(libsb, bks);
          int newscore = grade(libsb, bks);
          if (newscore > cscore || (pow(2.0, (newscore - cscore) / temp) > (rand() / (long double) RAND_MAX))) {
            cscore = newscore;
            libs = libsb;
            if (newscore > solscore) {
              solscore = newscore;
              bestlibs = libs;
            }
          }
          cout << "\rSimulated annealing: " << (100.0 * time / (long double) (steps - 1)) << "%, current: " << cscore << ", best: " << solscore;
          if (solscore > oldscore) cout << "  IMPROVEMENT!";
        }
        libs = bestlibs;
        assign_books(libs, bks);
      }
      cout << "\r                                                                              \r";

      if (solscore > oldscore) {
        ofstream fout(inps[k2] + "-res.txt");
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
      }
    }
    cout << inps[k2] << " - old: " << oldscore << " -> new: " << solscore;
    if (solscore > oldscore) {
      cout << "  IMPROVEMENT!";
    }
    cout << endl;
    total += max(solscore, oldscore);
  }

  cout << "Total score: " << total << endl;

  return 0;
}