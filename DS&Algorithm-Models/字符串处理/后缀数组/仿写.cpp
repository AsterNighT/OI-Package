#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <map>
#include <stack>
#include <set>
#include <vector>
#include <queue>
#define eps 10e-7
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define rep0(j,n) for(int j=0;j<n;j++)
#define rep1(j,n) for(int j=1;j<=n;j++)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define k(n) n->first
#define v(n) n->second
#define ll long long

using namespace std;
const int MAXINT = 100100;
string a;
int   tra_nk[MAXINT],      tsa[MAXINT],          ra_nk[MAXINT],  sa[MAXINT],   height[MAXINT],                 cnt[MAXINT],       tstr[MAXINT];
//    每一次倍增后的ra_nk，按第二关键字排序的sa，最终ra_nk，     最终sa，      sa[i-1]与sa[i]的最长公共前缀    基数排序计数数组， 按第二关键字排序后的第一关键字
int calcHeight(string s);
int calcSa(string s,int size);
int cmp(int *r,int p1,int p2,int l){
	return r[p1]==r[p2]&&r[p1+l]==r[p2+l];
}
int main() {
	cin>>a;
	a=a+"$"; //最后加一个最小的字符
	calcSa(a,128);//128的字符集大小对于纯字母和数字足够了
	calcHeight(a);
	rep1(i,a.length()-1){
		printf("%d ",sa[i]+1);
	}
	putchar('\n');
	rep0(i,a.length()-2){
		printf("%d ",height[i+2]);
	}
	putchar('\n');
    return 0;
}
int calcHeight(string s){
	int i,j,k,n=s.length();
	for(i=1;i<n;i++) ra_nk[sa[i]]=i;//最后那个$是第0名，好像没有第0名这种说法
	for(i=0,k=0;i<n;height[ra_nk[i++]]=k)
		for(k?k--:0,j=sa[ra_nk[i]-1];s[i+k]==s[j+k];k++); //height[0]没有意义，height[1]永远是0
	return 0;
}
int calcSa(string s,int size){
	int i,j,k=0,n=s.length();
	//求出只用一个字符的sa和tra_nk
	for(i=0;i<size;i++) cnt[i]=0;
	for(i=0;i<n;i++) cnt[tra_nk[i]=s[i]]++; //初始化tra_nk，并且统计有多少i这个字符
	for(i=1;i<size;i++) cnt[i]+=cnt[i-1];
	for(i=n-1;i>=0;i--) sa[--cnt[tra_nk[i]]]=i; //妙啊，这样就能排好sa，倒着循环保证排序稳定性
	//下面开始倍增
	for(j=1,k=1;k<n;j*=2,size=k){ //k==n说明所有后缀的排名都不相同，即已经排好了所有后缀
 		//按第二关键字求出tsa
		for(k=0,i=n-j;i<n;i++) tsa[k++]=i;//后面的那些根本没有第二关键字，排名最小，先放在前面
		for(i=0;i<n;i++) if(sa[i]>=j) tsa[k++]=sa[i]-j;//只有sa[i]>=j的才能成为一个字符串（sa[i]-j这个位置）的第二关键字，而且显然按照sa的顺序排本来就是有序的
		for(i=0;i<n;i++) tstr[i]=tra_nk[tsa[i]]; //ra_nk[sa[i]]=i，但这里是还没排完的，tstr是暂时按照第二关键字排序完以后的字符串的第一关键字
		//搞一遍基数排序
		for(i=0;i<size;i++) cnt[i]=0;
		for(i=0;i<n;i++) cnt[tstr[i]]++;
		for(i=1;i<size;i++) cnt[i]+=cnt[i-1];
		for(i=n-1;i>=0;i--) sa[--cnt[tstr[i]]]=tsa[i]; //妙啊，意思和只用一个字符的时候差不多
		//然后搞定新的tra_nk，现在tsa已经没用了，但是原来的tra_nk还要使，暂时把tra_nk存到tsa里面
		for(swap(tsa,tra_nk),k=1,tra_nk[sa[0]]=0,i=1;i<n;i++) //sa[0]是最后加的那个$，没用
			tra_nk[sa[i]]=cmp(tsa,sa[i-1],sa[i],j)?k-1:k++;
	}
	return 0;
}


