//
//  main.cpp
//  RoundRobinScheduling
//
//  Created by Akhil Verghese on 4/18/13.
//  Copyright (c) 2013 Akhil Verghese. All rights reserved.
//

#include<cstdio>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;

template<class T>
class BIT
{
    T *tree;
    int maxVal;
public:
    BIT(int N)
    {
        tree = new T[N+1];
        memset(tree,0,sizeof(T)*(N+1));
        maxVal = N;
    }
    void update(int idx, T val)
    {
        while (idx <= maxVal)
        {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }
    //Returns the cumulative frequency of index idx
    T read(int idx)
    {
        T sum=0;
        while (idx>0)
        {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }
};

typedef pair < long long , long long > ii;

bool cmp(const ii &a, const ii & b){
    
    if(a.first==b.first)
        return a.second < b.second;
    return a.first < b.first;
    
}


ii a[55555];
long long ans[55555];


int main(){
    int N;
    scanf("%d",&N);
    BIT<int> B(N+1);
    for(int i=1;i<=N;i++){
        int x;
        scanf("%d",&x);
        a[i].first=x;
        a[i].second=i;
        B.update(i,1);
    }
    sort(a,a+N+1);
    //for(int i=1;i<=N;i++) printf("%d %d\n",a[i].first,a[i].second);
    unsigned long long count=0;
    int last=1;
    for(int i=1;i<=N;i++){
        int idx= B.read(a[i].second);
        //printf("index %d\n",idx);
        
        ans[a[i].second]=count+ idx + (a[i].first-last)*(N-i+1);
        count+=1+(a[i].first-last)*(N-i+1);
        
        last=a[i].first;
        B.update(a[i].second,-1);
    }
    
    for(int i=1;i<=N;i++){
        printf("%lld\n",ans[i]);
    }
    
    
    return 0;
    
}

