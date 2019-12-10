//
//  main.cpp
//  Algorithmic_Problem_Solving_Strategies
//
//  Created by WoohyunSHIN_Air on 2019/10/23.
//  Copyright © 2019 WoohyunSHIN_Air. All rights reserved.
//

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// p.117,119 구간의 최대값


const int MIN = numeric_limits<int>::min();
const int MAX = numeric_limits<int>::max();

// 최대 연속 부분 구간 합 문제를 푸는 "동적 계획법" 알고리즘. 시간복잡도 O(N)
int fastesMaxSum(const vector<int>& A){
    size_t N = A.size();
    int ret = MIN, psum =0;
    for(int i=0;i<N;++i){
        psum = max(psum,0) + A[i];
        ret = max(psum,ret);
    }
    return ret;
}

// 최대 연속 부분 구간 합 문제를 푸는 "정복" 알고리즘. 시간복잡도 O(NlogN)
int fastMaxSum(const vector<int>& A, int lo, int hi){
    // 기저사례: 구간의 길이가 1일 경우
    if(lo == hi) return A[lo];
    int mid= (lo+hi)/2;
    
    // 두 부분에 모두 걸쳐 있는 최대 합 구간을 찾는다. 이 구간은 A[i,mid]와 A[mid+1,j] 형태를 갖는 구간의 합으로 이루어진다.
    // A[i,mid] 형태를 갖는 최대구간을 찾는다.
    int left = MIN, right= MAX, sum = 0;
    for(int i = mid;i>=lo;--i){
        sum += A[i];
        left = max(left,sum);
    }
    // A[mid+1,j] 형태를 갖는 최대구간을 찾는다.
    sum = 0;
    for(int j = mid+1; j<=hi;++j){
        sum += A[j];
        right = max(right,sum);
    }
    
    // 최대 구간이 두 조각 중 하나에만 속해 있는 경우의 답을 재귀 호출로 찾는다.
    int single = max(fastMaxSum(A, lo, mid),fastMaxSum(A, mid+1, hi));
    
    // 두 경우 중 최대치를 반환한다.
    return max(left+right,single);
}

// A[]의 연속된 부분 구간의 최대합을 구한다. 시간복잡도 O(N^2)
int betterMaxSum(const vector<int>& A){
    size_t N = A.size();
    int ret = MIN;
    for(int i=0;i<N;++i){
        int sum=0;
        for(int j=i;j<N;++j){
            // 구간 A[i,j]의 합을 구한다.
            sum += A[j];
            ret = max(ret,sum);
        }
    }
    return ret;
}

// A[]의 연속된 부분 구간의 최대합을 구한다. 시간복잡도 O(N^3)
int inefficientMaxSum(const vector<int>& A){
    size_t N = A.size();
    int ret = MIN;
    for(int i=0;i<N;++i){
        for(int j=i;j<N;++j){
            // 구간A[i,j]의 합을 구한다
            int sum=0;
            for(int k=i;k<=j;++k){
                sum += A[k];
            }
            ret = max(ret,sum);
        }
    }
    return ret;
}

// p.112 삽입정렬
void insertSort(vector<int>& A){
    for(int i=0;i<A.size();++i){
        int j=i;
        while(j>0 && A[j-1]>A[j]){
            swap(A[j-1], A[j]);
            --j;
        }
    }
}


// p.111 선택정렬
void selectionSort(vector<int>& A){
    for(int i=0;i<A.size();++i){
        int minIndex = i;
        for(int j=i+1;j<A.size();++j){
            if(A[minIndex]>A[j]){
                minIndex = j;
            }
        }
        swap(A[i],A[minIndex]);
    }
}

// p.108 선형 탐색 : 시간 알고리즘
int firstIndex(const vector<int>& array, int element){
    for(int i=0;i<array.size();++i){
        if(array[i]==element){
            return i;
        }
    }
    return -1;
}

// p.105 소인수 분해 알고리즘
vector<int> factor(int n){
    // n=1인 경우는 예외로한다
    if(n == 1) return vector<int>(1,1);
    vector<int> ret;
    for(int div=2;n>1;++div){
        while(n % div ==0){
            n /= div;
            ret.push_back(div);
        }
    }
    return ret;
}




// p.103 음식 메뉴 정하기
const int INF = 987654321;

// 이 메뉴로 모두가 식사할 수있는지 여부를 반환한다.
bool canEverybodyEat(const vector<int>& menu);
// 요리할 수있는 음식의 종류 수
int M;
// food 번째 음식을 만들지 여부를 결정한다.
int selectMenu(vector<int>& menu, int food){
    // 기저사례 : 모든 음식에 대해 만들지 여부를 결정했을 때
    if(food==M){
        if(canEverybodyEat(menu)){
            return menu.size();
        }
        // 아무것도 못 먹는 사람이 있으면 아주 큰 값을 반환한다.
        return INF;
    }
    
    // 이 음식을 만들지 않는 경우의 답을 계산한다.
    int ret = selectMenu(menu,food+1);
    // 이 음식을 만드는 경우의 답을 계산해서 더 작은 것을 취한다.
    menu.push_back(food);
    ret = std::min(ret, selectMenu(menu,food+1));
    menu.pop_back();
    return ret;
}



// p.96 선형 시간에 이동 평균
std::vector<double> movingAverage2(const std::vector<double>& A,int M){
    std::vector<double> ret;
    size_t N = A.size();
    double partialSum = 0;
    for(int i=0;i<M-1;++i)
        partialSum += A[i];
    for(int i=M-1;i<N;++i){
        partialSum += A[i];
        ret.push_back(partialSum / M);
        partialSum -= A[i-M+1];
    }
    return ret;
}


// p.95 이동평균선
std::vector<double> movingAVerage1(const std::vector<double>& A,int M){
    std::vector<double> ret;
    size_t N = A.size();
    for(int i=M-1; i<N;++i){
        double partialSum = 0;
        for(int j=0; j<M;++j){
            partialSum = partialSum + A[i-j];
        }
        ret.push_back(partialSum / M);
    }
    return ret;
}


// p.94
int majority2(const std::vector<int>& A){
    size_t N = A.size();
    
   std::vector<int> count(101, 0);
    
    for(int i=0;i<N;++i){
        count[A[i]]++;
    }
    
    int majority=0;
    for(int i=0;i<=100;++i){
        if(count[i] > count[majority]){
            majority=i;
        }
    }
    return majority;
}

// p.93
int majority1(const std::vector<int>& A){
    size_t N = A.size();
    int majority = 1, majorityCount = 0;
    for(int i=0;i<N;++i){
        int V = A[i], count=0;
        for(int j=0;j<N;j++){
            if(A[j]==V){
                ++count;
            }
        }
        
        if(count>majorityCount){
            majorityCount = count;
            majority = V;
        }
    }
    return majority;
}

int main(int argc, const char * argv[]) {
    int result = majority1({1,2,3,4,4,4,5});
    std::cout << result;
    return 0;
}

