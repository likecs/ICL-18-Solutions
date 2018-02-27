#include <bits/stdc++.h>
using namespace std;

const int MAX = 5e4 + 4;
const int LIM = 1 << 16;

int n, q;
int bit = 0, N2 = 1;
vector<int> files;
vector<int> precompute[LIM + 1];

void gen(int idx, int bit) {
  if (bit == 0) {
    files.push_back(1);
    if (idx == 1) {
      files.push_back(2);
    }
    return ;
  }
  int mid = 1 << bit;
  if (idx <= mid) {
    gen(idx, bit - 1);
    int sz = files.size();
    for(int i = 0; i < sz; ++i) {
      if (files[i] + mid <= n) {
        files.push_back(files[i] + mid);
      }
      else {
        break;
      }
    }
  }
  else {
    gen(idx - mid, bit - 1);
  }
}

int get(int &l, int &r) {
  r %= N2;
  if (r == 0) {
    r = N2;
  }
  int low = 0, high = precompute[r].size()-1, ans = -1;
  while(low <= high) {
    int mid = (low + high)/2;
    if (precompute[r][mid] + l - 1 <= n) {
      ans = mid;
      low = mid + 1;
    }
    else {
      high = mid - 1;
    }
  }
  assert(ans != -1);
  return ans;   //0-based indexing.
}

int main() {
  ios_base::sync_with_stdio(false);
  cin >> n >> q;
  assert(1 <= n and n <= 50000);
  assert(1 <= q and q <= 300000);
  while(N2 < n) {
    bit += 1;
    N2 *= 2;
  }
  assert((1 << bit) == N2);
  for(int day = 1; day <= (1 << bit); ++day) {
    files.clear();
    gen(day, bit);
    precompute[day] = files;
  }
  int type, l, r, k;
  while(q--) {
    cin >> type;
    if (type == 1) {
      cin >> l >> r;
      assert(1 <= l and l <= n);
      assert(0 <= r and r <= 1000000000);
      int ans = get(l, r);
      cout << (n - ans - 1) << "\n";
    }
    else {
      cin >> l >> r >> k;
      assert(1 <= l and l <= n);
      assert(0 <= r and r <= 1000000000);
      assert(1 <= k and k <= n);
      int ans = get(l, r);
      if (k > ans+1) {
        cout << "-1" << "\n";
      }
      else {
        assert(1 <= k and k <= precompute[r].size());
        cout << (precompute[r][k-1] + l - 1) << "\n";
      }
    }
  }
  return 0;
}
