#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <vector>
#include <queue>
#define eps 10e-7
#define INF 0x3f3f3f3f
#define rep(j) for(int i=0;i<j;i++)

using namespace std;
const int MAXINT = 1000;
int next[MAXINT]={};
int kmp(string a,string b);
int calc_next(string a); 
string a,b; 
int main() {
	cin>>a>>b;
	calc_next(b);
	kmp(a,b);
    return 0;
}

int calc_next(string a){
	memset(next,0,sizeof(next));
	int k=0,i;
	for(i=1;i<a.length();i++){   // 重要：从1开始循环！！！！！！！不然next[0]的基准意义（没有相同前后缀）会爆炸 
		while(k>0&&a[k]!=a[i]){
			k=next[k-1];
		}
		if(a[k]==a[i]){
			k++;
		}
		next[i]=k;
	}
}

int kmp(string a,string b){
	int k=0;
	rep(a.length()){
		while(k>0&&b[k]!=a[i]){
			k=next[k-1];
		}
		if(b[k]==a[i]){
			k++;
		}
		if(k==b.length()){
			cout<<i-k+1<<endl;
		}
	}
}
