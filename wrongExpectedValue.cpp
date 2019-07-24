#include <functional>
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <sstream>
#include <numeric>
#include <string>
#include <vector>
#include <cstdio>
#include <bitset>
#include <cmath>
#include <ctime>
#include <queue>
#include <stack>
#include <map>
#include <set>

using namespace std;

ll dp[11][111];
ll d[22][22][11][111][111];

ll calc(int n, int s) {
    if (n == 1) return 1;
    ll &res = dp[n][s];
    if (res != -1) return res;
    res = 0;
    for (int i = 0; i <= s; i++) {
        res += calc(n-1, s-i);
    }
    return res;
}

ll f(int a, int b, int n, int s1, int s2) {
    int score = 10 - n + 1;
    if (n == 1) {
        if (s1 < s2) b += score;
        else if (s1 > s2) a += score;
        if (a >= 20) return 1;
        return 0;
    }
    ll &res = d[a][b][n][s1][s2];
    if (res != -1) return res;
    res = 0;
    for (int i = 0; i <= s1; i++) {
        ll cur = 0;
        for (int j = 0; j <= s2; j++) {
            int na = a, nb = b;
            if (i > j) na += score;
            else if (i < j) nb += score;
            if (na >= 20) cur += calc(n-1, s2-j);
            else if (nb >= 20) cur += 0;
            else cur += f(na, nb, n-1, s1-i, s2-j);
        }
        res = max(res, cur);
    }
    return res;
}

int main(){
    
    memset(dp, -1, sizeof dp);
    
    memset(d, -1, sizeof d);
    
    cout << f(0, 0, 10, 100, 100) << endl;
    
    return 0;
}
