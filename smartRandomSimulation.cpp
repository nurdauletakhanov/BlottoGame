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

const long long allSequences = 4263421511271L;
const int finalScore = 20;

vector<int> castles;
vector<vector<int> > masks;
__int128 bin[11][111];
vector<int> cur;

bool notLose(vector<int>& v){
    int score1 = 0, score2 = 0;
    for(int i = 0; i < 10; ++i){
        if(score1 >= finalScore || score2 >= finalScore) break;
        if(v[i] == 0) score1 += i + 1;
        if(v[i] == 2) score2 += i + 1;
    }
    return score1 >= score2;
}

void generateAllLoseMasks(vector<int>& cur){
    if(cur.size() == 10){
        if(notLose(cur)){
            masks.push_back(cur);
        }
        return;
    }
    for(int i = 0; i < 3; ++i){
        cur.push_back(i);
        generateAllLoseMasks(cur);
        cur.pop_back();
    }
}

__int128 binominal(int x, int y){
    if(bin[x][y] != -1) return bin[x][y];
    bin[x][y] = 1;
    for(int i = y; i >= y - x + 1; --i){
        bin[x][y] = bin[x][y] * i  / (y - i + 1);
    }
    return bin[x][y];
}

vector<vector<__int128> > calc(vector <int>& v, int sum){
    vector <vector<__int128> > dp(v.size() + 1);
    vector<vector<__int128> > prefixSum(2);
    for(int i = 0; i < 2; ++i){
        prefixSum[i].resize(101);
    }
    dp[0].resize(101);
    dp[1].resize(101);
    for(int i = 0; i <= sum; ++i){
        if(i < v[0]) dp[1][i] = 1;
        prefixSum[1][i] = dp[1][i];
        if(i) prefixSum[1][i] += prefixSum[1][i - 1];
    }
    for(int i = 2; i <= v.size(); ++i){
        dp[i].resize(101);
        for(int j = 0; j <= sum; ++j){
            prefixSum[0][j] = prefixSum[1][j];
            prefixSum[1][j] = 0;
        }
        for(int j = 0; j <= sum; ++j){
//            for(int last = 0; last < v[i - 1]; ++last){
//                if(j >= last) dp[i][j] += dp[i - 1][j - last];
//            }
            // j, j - 1, ... , j - v[i - 1] + 1
            if(v[i - 1] - 1 >= j) dp[i][j] += prefixSum[0][j];
            else dp[i][j] += prefixSum[0][j] - prefixSum[0][j - v[i - 1]];
            prefixSum[1][j] = dp[i][j];
            if(j) prefixSum[1][j] += prefixSum[1][j - 1];
        }
    }
    return dp;
}

__int128 calculateForCurrentMask(vector<int> &v, vector<int>& mask){
    int sumOfZeros = 0, cntOfTwo = 0;
    __int128 result = 0;
    vector<int> zeros;
    for(int i = 0; i < 10; ++i){
        if(mask[i] == 0){
            sumOfZeros += v[i];
            zeros.push_back(v[i]);
        }
        if(mask[i] == 2) cntOfTwo++;
    }
    int sum = sumOfZeros - cntOfTwo;
    if(cntOfTwo == 0 || sum < 0) return 0;
    vector<vector<__int128> > dp = calc(zeros, sum);
    for(int i = 0; i <= sum; ++i){
        result += binominal(cntOfTwo - 1, i + cntOfTwo - 1) * dp[(int)zeros.size()][sum - i];
    }
    return result;
}

__int128 calculateNumberOfLosingSequences(vector<int>& v){
    __int128 result = 0;
    for(int i = 0; i < masks.size(); ++i){
        result += calculateForCurrentMask(v, masks[i]);
    }
    return result;
}

int main(){
    srand(time(NULL));
    generateAllLoseMasks(cur);
    cout << masks.size() << endl;
    for(int i = 0, x; i < 10; ++i){
        cin >> x;
        castles.push_back(x);
    }
    memset(bin, -1, sizeof bin);
    for(int y = 0; y <= 110; ++y){
        for(int x = 0; x <= y && x <= 10; ++x){
            binominal(x, y);
        }
    }
    __int128 result = calculateNumberOfLosingSequences(castles);
    clock_t StartTime = clock();
    while(true){
        double duration = (clock() - StartTime) / (double)CLOCKS_PER_SEC;
        duration = duration / 60;
        cout.precision(6);
        cout << fixed << duration << endl;
        if(duration >= 30.0) break;
        int x, y;
        while(true){
            x = rand() % 10, y = rand() % 10;
            if(castles[x] == 0 || x == y) continue;
            break;
        }
        castles[x]--, castles[y]++;
        __int128 curResult = calculateNumberOfLosingSequences(castles);
        if(curResult < result){
            castles[x]++, castles[y]--;
        }else{
            result = curResult;
        }
    }
    cout << (long long)result << endl;
    for(int i = 0; i < 10; ++i){
        cout << castles[i] << " ";
    }
    cout << endl;
    cout << result * 1.0 / allSequences << endl;
}
