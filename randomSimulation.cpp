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

int n, k, lastScore;
pair <int, vector <int> > castle[555];
vector <int> myCastle;

vector<int> generate(){
    int sum = 100;
    vector<int> result;
    for(int i = 0; i < 9; ++i){
        if(sum == 0) result.push_back(0);
        else{
            int val = rand() % sum;
            result.push_back(val);
            sum -= val;
        }
    }
    result.push_back(sum);
    return result;
}

pair <int, int> play(int x){
    int score1 = 0, score2 = 0;
    for(int i = 0; i < 10; ++i){
        if(score1 >= 20 || score2 >= 20) break;
        if(myCastle[i] > castle[x].second[i]){
            score1 += i + 1;
        }
        if(myCastle[i] < castle[x].second[i]){
            score2 += i + 1;
        }
    }
    return make_pair(score1, score2);
}

int main(){
    srand(time(NULL));
    n = 50, k = 100000;
    for(int i = 0; i < 10; ++i){
        myCastle.push_back(0);
    }
    myCastle[4] = 25;
    myCastle[5] = 25;
    myCastle[6] = 25;
    myCastle[7] = 25;
    for(int i = 0; i < n; ++i){
        castle[i].second = generate();
    }
    for(int i = 0; i < n; ++i){
        pair <int, int> result = play(i);
        lastScore += result.first;
        castle[i].first += result.second;
    }
    for(int step = 0; step < k; ++step){
        int x, y;
        while(true){
            x = rand() % 10, y = rand() % 10;
            if(myCastle[x] == 0 || x == y) continue;
            break;
        }
        myCastle[x]--, myCastle[y]++;
        int curScore = 0;
        for(int i = 0; i < n; ++i){
            pair <int, int> result = play(i);
            curScore += result.first;
            castle[i].f += result.second;
        }
        if(curScore < lastScore){
            myCastle[x]++, myCastle[y]--;
        }else{
            lastScore = curScore;
        }
    }
    cout << lastScore << endl;
    for(int i = 0; i < myCastle.size(); ++i){
        cout << myCastle[i] << " ";
    }
    cout << endl;
    // dp[i][x][y] = dp[i - 1][x + a][y + b] + (i + 1) / a / b
}
