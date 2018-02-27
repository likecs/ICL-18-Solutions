#include <bits/stdc++.h>
using namespace std;

const int LIM = 26;

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
  int t, n, k;
  string s;
  cin >> t;
  assert(1 <= t and t <= 100);
  while(t--) {
    cin >> n >> k >> s;
    assert(1 <= n and n <= 1000);
    assert(1 <= k and k <= 1000);
    for(int i = 0; i < n; ++i) {
      assert('a' <= s[i] and s[i] <= 'z');
    }
    vector<int> freq(LIM, 0);
    for(int i = 0; i < n; ++i) {
      freq[s[i] - 'a'] += 1;
    }
    //ans = n - 2*f + s/k
    int cnt_ch = n;
    int cnt_dig = 0;
    int sum = 0;
    for(int i = 0; i < LIM; ++i) {
       if ((i+1) > k * 2) {
         cnt_ch -= freq[i];
         cnt_dig += freq[i];
         sum += (i+1) * freq[i];
       }
    }
    int num = k * (cnt_ch - cnt_dig) + sum;
    int den = k;
    int d = gcd(num, den);
    num /= d;
    den /= d;
    cout << num << " " << den << "\n";
  }
  return 0;
}
