#include <bits/stdc++.h>
using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  int t;
  cin >> t;
  assert(1 <= t and t <= 40);
  while(t--) {
    int n, m, x;
    cin >> n >> m;
    assert(1 <= n and n <= 50);
    assert(1 <= m and m <= 50);
    vector<int> a;
    for(int i = 0; i < n; ++i) {
      for(int j = 0; j < m; ++j) {
        cin >> x;
        a.push_back(x);
        assert(0 <= x and x <= 100);
      }
    }
    sort(a.rbegin(), a.rend());
    int sum[2] = {0, 0};
    for(int i = 0; i < a.size(); ++i) {
      sum[i%2] += a[i];
    }
    if (sum[0] == sum[1]) {
      cout << "Draw" << "\n";
    }
    else {
      cout << "Cyborg" << "\n";
    }
  }
  return 0;
}