#include <bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;

#define fi first
#define sec second

const int MAX = 1e5 + 5;
const int LIM = 20;

struct fenwick {
  int n;
  int bit[MAX];
  void clear(int _n) {
    n = _n;
    for(int i = 0; i <= n; ++i) {
      bit[i] = 0;
    }
  }
  void update(int x, int v) {
    while(x < n) {
      bit[x] += v;
      x += x & (-x);
    }
  }
  int query(int x) {
    int res = 0;
    while(x > 0) {
      res += bit[x];
      x -= x & (-x);
    }
    return res;
  }
};

int n, m;
char a[MAX];
char b[MAX];
set<int> g[LIM];
fenwick freq[LIM];
LL mask_cnt[1 << LIM];

void update(int x, int code, LL add) {
  int mask;
  vector<pii> events_low, events_high;
  for(int i = 0; i < LIM; ++i) {
    if (i == code) {
      continue;
    }
    auto it = g[i].lower_bound(x);
    if (it != g[i].end()) {
      assert((*it) > x);
      events_high.push_back({*it, i});
    }
    if (it != g[i].begin()) {
      --it;
      assert((*it) < x);
      events_low.push_back({*it, i});
    }
  }
  sort(events_low.begin(), events_low.end());
  events_low.push_back({x, 0});
  sort(events_high.begin(), events_high.end());
  events_high.push_back({m, 0});
  mask = 1 << code;
  vector<pii> mask_low;
  for(int i = events_low.size()-2; i >= 0; --i) {
    mask_low.push_back({mask, events_low[i+1].fi - events_low[i].fi});
    mask |= 1 << events_low[i].sec;
  }
  mask_low.push_back({mask, events_low[0].fi + 1});
  mask = 1 << code;
  for(int i = 0; i+1 < events_high.size(); ++i) {
    mask |= 1 << events_high[i].sec;
  }
  vector<pii> mask_high;
  for(int i = events_high.size()-2; i >= 0; --i) {
    mask_high.push_back({mask, events_high[i+1].fi - events_high[i].fi});
    mask ^= 1 << events_high[i].sec;
  }
  if (events_high[0].fi != (x+1)) {
    mask_high.push_back({mask, events_high[0].fi - x - 1});
  }
  for(int i = 0; i < mask_low.size(); ++i) {
    assert(mask_low[i].sec >= 1);
    mask_cnt[mask_low[i].fi] += add * mask_low[i].sec;
  }
  for(int i = 0; i < mask_low.size(); ++i) {
    for(int j = 0; j < mask_high.size(); ++j) {
      int new_mask = mask_low[i].fi | mask_high[j].fi;
      mask_cnt[new_mask] += add * mask_low[i].sec * mask_high[j].sec;
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  char y;
  int t, q, type, l, r, x;
  cin >> t;
  assert(1 <= t and t <= 20);
  int SUM_N = 0, SUM_M = 0;
  while(t--) {
    cin >> a >> b;
    n = strlen(a);
    m = strlen(b);
    SUM_N += n;
    SUM_M += m;
    assert(1 <= n and n <= 100000);
    assert(1 <= m and m <= 100000);
    for(int i = 0; i < n; ++i) {
      assert('a' <= a[i] and a[i] <= 't');
    }
    for(int i = 0; i < m; ++i) {
      assert('a' <= b[i] and b[i] <= 't');
    }
    for(int i = 0; i < LIM; ++i) {
      freq[i].clear(n+1);
    }
    for(int i = 0; i < n; ++i) {
      freq[a[i] - 'a'].update(i + 1, 1);
    }
    for(int i = 0; i < LIM; ++i) {
      g[i].clear();
    }
    for(int i = 0; i < m; ++i) {
      g[b[i] - 'a'].insert(i);
    }
    for(int i = 0; i < (1 << LIM); ++i) {
      mask_cnt[i] = 0ll;
    }
    for(int i = 0; i < m; ++i) {
      vector<pii> events;
      for(int j = 0; j < LIM; ++j) {
        auto it = g[j].lower_bound(i);
        if (it != g[j].end()) {
          assert((*it) >= i);
          events.push_back({*it, j});
        }
      }
      sort(events.begin(), events.end());
      events.push_back({m, 0});
      int mask = 0;
      for(int j = 0; j+1 < events.size(); ++j) {
        mask |= 1 << events[j].sec;
        mask_cnt[mask] += events[j+1].fi - events[j].fi;
      }
    }
    const LL INF = 1LL * m * (m+1) / 2;
    cin >> q;
    assert(1 <= q and q <= 100000);
    while(q--) {
      cin >> type;
      if (type == 1) {
        cin >> x >> y;
        assert(1 <= x and x <= n);
        assert('a' <= y and y <= 't');
        x -= 1;
        freq[a[x] - 'a'].update(x + 1, -1);
        a[x] = y;
        freq[a[x] - 'a'].update(x + 1, 1);
      }
      else if (type == 2) {
        cin >> x >> y;
        assert(1 <= x and x <= m);
        assert('a' <= y and y <= 't');
        x -= 1;
        update(x, b[x] - 'a', -1);
        g[b[x] - 'a'].erase(x);
        b[x] = y;
        g[b[x] - 'a'].insert(x);
        update(x, b[x] - 'a', 1);
      }
      else if (type == 3) {
        cin >> l >> r;
        assert(1 <= l and l <= r);
        assert(l <= r and r <= n);
        int mask = 0;
        for(int i = 0; i < LIM; ++i) {
          int cnt = freq[i].query(r) - freq[i].query(l - 1);
          if (cnt > 0) {
            mask |= 1 << i;
          }
        }
        cout << mask_cnt[mask] << "\n";
        assert(0 <= mask_cnt[mask] and mask_cnt[mask] <= INF);
      }
    }
  }
  assert(1 <= SUM_N and SUM_N <= 200000);
  assert(1 <= SUM_M and SUM_M <= 200000);
  return 0;
}
