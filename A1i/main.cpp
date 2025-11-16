#include <iostream>
#include <cmath>
#include <random>

using std::mt19937;
using std::cin;
using std::cout;
using std::istream;

struct circle {
  double x = 0;
  double y = 0;
  double r = 0;

  bool ok(double dot_x, double dot_y) {
    if (std::hypot(std::abs(x - dot_x), std::abs(y - dot_y)) <= r) {
      return true;
    }
    return false;
  }
};

istream &operator>>(istream& in, circle &c) {
  in >> c.x >> c.y >> c.r;
  return in;
}

int main() {
  circle c1;
  circle c2;
  circle c3;
  cin >> c1 >> c2 >> c3;

  std::random_device rd;
  mt19937 gen(rd());
  std::uniform_real_distribution<> urd(-1, 2);

  int n = 0;
  for (size_t i = 0; i < 1000000; i++) {
    double x = urd(gen);
    double y = urd(gen);
    n += (c1.ok(x, y) && c2.ok(x, y) && c3.ok(x, y));
  }

  cout << std::fixed;
  cout.precision(3);
  cout << (double) n * 9 / 1000000;
}