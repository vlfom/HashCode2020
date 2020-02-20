#include <bits/stdc++.h>

using namespace std;

int b, l, d, n, id, score[100001], signup[100001], booksperday[100001], a, y, k1, ki;
bitset<100001> check;
vector<int> libraries[100001];
unordered_set<int> librarcont[100001];

int main(int argc, char** argv) {
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
    }
  }
  fin1.close();
  ifstream fin2(outfile);
  fin2 >> a;
  int totscore = 0;
  int ctime = 0;
  for (int i = 0; i < a; i++) {
    fin2 >> y >> k1;
    if (y >= l) {
      cout << "Error: invalid library id " << y << "." << endl;
      return 1;
    }
    if (check[y]) {
      cout << "Error: listed library " << y << " twice." << endl;
      return 1;
    }
    check[y] = 1;
    ctime += signup[y];
    for (int k = 0; k < k1; k++) {
      fin2 >> ki;
      if (librarcont[y].find(ki) == librarcont[y].end()) {
        cout << "Error: library " << y << " does not contain book " << ki << "." << endl;
        return 1;
      }
      if (ctime + (k + 1) / booksperday[y] <= d) {
        totscore += score[ki];
      }
    }
  }
  fin2.close();
  cout << totscore << endl;
  return 0;
}