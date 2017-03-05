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
#define rep(j) for(int i=0;i<j;i++)

using namespace std;

const int MAXINT = 1000;
string str,a;
int p[MAXINT]={};
int init(){
	str="$";
	str+="#";
	rep(a.length()){
		str+=a[i];
		str+="#"; 
	}
}

int kp(){
	int mx=0,id=0;
	for(int i=1;i<str.length();i++){
		if(mx>i){
			p[i]=min(p[2*id-i],mx-i);
		}else{
			p[i]=1;
		}
		for(;str[i+p[i]]==str[i-p[i]];p[i]++);
		if(i+p[i]>mx){
			mx=i+p[i];
			id=i;
		}
	} 
} 

int main() {
	cin>>a;
	init();
	kp();
	cout<<str<<endl;
	rep(str.length()){
 		cout<<p[i]-1<<' ';
	} 
    return 0;
}

