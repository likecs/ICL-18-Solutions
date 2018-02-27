#include <bits/stdc++.h>
using namespace std;

const int inf = 1e9;

int gcd(int a, int b) {
  while(b) {
    int r = a % b;
    a = b;
    b = r;
  }
  return a;
}

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  assert(1 <= t and t <= 100000);
  while(t--) {
    int n, m, a, b, c, d, P;
    cin >> n >> m;
    // North, South, East, West
    cin >> a >> b >> c >> d;
    cin >> P;
    assert(1 <= n and n <= 1000);
    assert(1 <= m and m <= 1000);
    assert(1 <= a and a <= 1000);
    assert(1 <= b and b <= 1000);
    assert(1 <= c and c <= 1000);
    assert(1 <= d and d <= 1000);
    assert(1 <= P and P <= 1000000);
    // N - S = m, E - W = n
    // Na + Sb + Ec + Wd = P
    int A = a + b;
    int B = c + d;
    int C = P + m * b + n * d;
    // N * A + E * B = C
    // Constraints:
    // N >= m, E >= n
    int g = gcd(A, B);
    if (C % g != 0) {
      cout << "-1" << "\n";
      continue;
    }
    int ans = inf;
    int till = C / A;
    for(int N = m; N <= till; ++N) {
      int E = (C - N * A);
      if (E % B != 0) {
        continue;
      }
      E /= B;
      if (E < n) {
        break;
      }
      int S = N - m, W = E - n;
      ans = min(ans, N + S + E + W);
    }
    if (ans == inf) {
      ans = -1;
    }
    else {
      assert(ans >= n + m);
    }
    cout << ans << "\n";
  }
  return 0;
}
