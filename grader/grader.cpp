#include <bits/stdc++.h>

using namespace std;

int b, l, d, n, id, score[100001], apptime[100001], signup[100001], booksperday[100001], a, y, k1, ki;
bitset<100001> check;
bitset<100001> checkbooks;
vector<int> libraries[100001];
unordered_set<int> librarcont[100001];

int main(int argc, char** argv) {
  memset(apptime, 0, sizeof apptime);
  bool grade_mode = true;
  string infile = "input.txt";
  string outfile = "output.txt";
  if (argc >= 2) {
    infile = argv[1];
    outfile = "output-" + infile;
  }
  if (argc >= 3) {
    outfile = argv[2];
    if (outfile == "analyze")
      grade_mode = false;
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
    }
  }
  fin1.close();
  if (grade_mode) {
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
        if (ctime + k / booksperday[y] < d && !checkbooks[ki]) {
          // cerr << "Score for book " << ki << " in library " << y << ": " << score[ki] << "  " << ctime + k / booksperday[y] << " " << ctime << endl;
          totscore += score[ki];
          checkbooks[ki] = 1;
        }
        // else if (ctime + k / booksperday[y] < d) {
        //   cerr << "Already scored for book " << ki << " in library " << y << ": " << score[ki] << endl;
        // }
      }
    }
    fin2.close();
    cout << totscore << endl;
  } else {
    long double avg_signup = 0.0, avg_books = 0.0, avg_score = 0.0, avg_bpd = 0.0, avg_app = 0.0;
    long double dev_signup = 0.0, dev_books = 0.0, dev_score = 0.0, dev_bpd = 0.0, dev_app = 0.0;
    int min_signup = 100001, min_books = 100001, min_score = 100001, min_bpd = 100001, min_app = 100001,
      max_signup = 0, max_books = 0, max_score = 0, max_bpd = 0, max_app = 0;
    int totmax_score = 0; int totact_books = 0;
    for (int i = 0; i < l; i++) {
      avg_signup += signup[i]; min_signup = min(min_signup, signup[i]);
        max_signup = max(max_signup, signup[i]);
      avg_books += libraries[i].size(); min_books = min(min_books, (int) libraries[i].size());
        max_books = max(max_books, (int) libraries[i].size());
      avg_bpd += booksperday[i]; min_bpd = min(min_bpd, booksperday[i]);
        max_bpd = max(max_bpd, booksperday[i]);
    }
    avg_signup /= l;
    avg_books /= l;
    avg_bpd /= l;
    for (int i = 0; i < l; i++) {
      dev_signup += (signup[i] - avg_signup) * (signup[i] - avg_signup);
      dev_books += (libraries[i].size() - avg_books) * (libraries[i].size() - avg_books);
      dev_bpd += (booksperday[i] - avg_bpd) * (booksperday[i] - avg_bpd);
    }
    dev_signup /= l; dev_signup = sqrt(dev_signup);
    dev_books /= l; dev_books = sqrt(dev_books);
    dev_bpd /= l; dev_bpd = sqrt(dev_bpd);
    for (int i = 0; i < b; i++) {
      if (apptime[i] > 0) {
        avg_score += score[i]; min_score = min(min_score, score[i]);
          max_score = max(max_score, score[i]);
        avg_app += apptime[i]; min_app = min(min_app, apptime[i]);
          max_app = max(max_app, apptime[i]);
        totmax_score += score[i];
        totact_books++;
      }
    }
    avg_score /= totact_books;
    avg_app /= totact_books;
    for (int i = 0; i < b; i++) {
      if (apptime[i] > 0) {
        dev_score += (score[i] - avg_score) * (score[i] - avg_score);
        dev_app += (apptime[i] - avg_app) * (apptime[i] - avg_app);
      }
    }
    dev_score /= totact_books; dev_score = sqrt(dev_score);
    dev_app /= totact_books; dev_app = sqrt(dev_app);

    cout << fixed << setprecision(1);
    cout << "Number of books: " << b << ", but only " << totact_books << " do actually appear in some library" << endl;
    cout << "Number of libraries: " << l << endl;
    cout << "Days: " << d << endl;
    cout << "Average signup time: " << avg_signup << " (min: " << min_signup << ", max: " << max_signup << ", stddev: " << dev_signup << ")" << endl;
    cout << "Average number of books per library: " << avg_books << " (min: " << min_books << ", max: " << max_books << ", stddev: " << dev_books << ")" << endl;
    cout << "Average book score: " << avg_score << " (min: " << min_score << ", max: " << max_score << ", stddev: " << dev_score << ")" << endl;
    cout << "Average books per day: " << avg_bpd << " (min: " << min_bpd << ", max: " << max_bpd << ", stddev: " << dev_bpd << ")" << endl;
    cout << "Average appearance time per book: " << avg_app << " (min: " << min_app << ", max: " << max_app << ", stddev: " << dev_app << ")" << endl;
    cout << "Maximum achievable score not greater than: " << totmax_score << endl;
  }
  return 0;
}