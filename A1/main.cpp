#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

using std::abs;
using std::cin;
using std::cout;
using std::hypot;
using std::istream;
using std::mt19937;
using std::ofstream;
using std::pair;
using std::random_device;
using std::string;
using std::uniform_real_distribution;
using std::vector;

struct circle {
  double x = 0;
  double y = 0;
  double r = 0;

  bool ok(double dot_x, double dot_y) {
    if (hypot(abs(x - dot_x), abs(y - dot_y)) <= r) {
      return true;
    }
    return false;
  }
};

istream &operator>>(istream &in, circle &c) {
  in >> c.x >> c.y >> c.r;
  return in;
}

circle circle_gen(int seed) {
  mt19937 gen(seed);
  uniform_real_distribution<> urd(0, 1);
  circle res;
  res.x = urd(gen);
  res.y = urd(gen);
  res.r = urd(gen);
  return res;
}

double test(int seed, int points, circle c1, circle c2, circle c3, double lb,
            double ub) {
  mt19937 gen(seed);
  uniform_real_distribution<> urd(lb, ub);
  int n = 0;
  for (int i = 0; i < points; i++) {
    double x = urd(gen);
    double y = urd(gen);
    n += (c1.ok(x, y) && c2.ok(x, y) && c3.ok(x, y));
  }

  double res = (double)n * (ub - lb) * (ub - lb) / points;
  return res;
}

vector<pair<int, double>> tester(int seed, circle c1, circle c2, circle c3,
                                 bool small_size = false) {
  vector<pair<int, double>> res;
  res.reserve(2000);
  double lb = 0;
  double ub = 3.3;
  if (small_size) {
    lb = 0.85;
    ub = 2.1;
  }
  for (int pnts = 100; pnts < 1000; pnts += 100) {
    res.push_back({pnts, test(seed, pnts, c1, c2, c3, lb, ub)});
  }
  for (int pnts = 1000; pnts <= 100000; pnts += 500) {
    res.push_back({pnts, test(seed, pnts, c1, c2, c3, lb, ub)});
  }
  return res;
}

template <typename T, typename V>
void print_vector(vector<pair<T, V>> &v, std::ofstream &fout) {
  for (pair<T, V> i : v) {
    fout << i.first << ' ' << i.second << '\n';
  }
}

int main() {
  circle c1 = {1, 1, 1};
  circle c2 = {1.5, 2, std::sqrt(5) / 2};
  circle c3 = {2, 1.5, std::sqrt(5) / 2};
  for (int seed = 0; seed < 10; seed++) {
    auto res = tester(seed, c1, c2, c3);
    string name1 = "output_seed_" + std::to_string(seed) + "_big.txt";
    ofstream fout1(name1);
    print_vector(res, fout1);
    res = tester(seed, c1, c2, c3, true);
    string name2 = "output_seed_" + std::to_string(seed) + "_small.txt";
    ofstream fout2(name2);
    print_vector(res, fout2);
  }
}