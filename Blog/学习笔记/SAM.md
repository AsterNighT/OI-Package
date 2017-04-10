# 后缀自动机 #
## 0x00 前言 ##
- 纠结了⑤天终于大概理解了后缀自动机
- 这个东西实在是太要命了，虽然代码很短，但是理解起来太困难
- 趁着理解还新鲜赶紧写一发笔记
- 我会尽量写得详细且便于理解，以供他人参考（我以后忘记了回头来看

-----
- 做一些符号规定
- S：我们建立后缀自动机的字符串
- S[i]：S的第i位
- prefix[i]：S长为i的前缀
- suffix[i]：你意会一下
- parent[p]：p这个状态在后缀链（parent tree）中的前驱（父亲）
- max[p]：p这个状态的最长子串长度
- min[p]：p这个状态的最短子串长度
- R[p]：p这个状态的右端点集合
- Sub[p]：p这个状态的子串集合
- root：后缀自动机的根，表示空串
- last：最后一个插入的节点
- 一般用i,j,k表示位置，p,q表示状态
## 0x01 后缀自动机是啥 ##
- 这显然有个基础的问题
- 什么叫自动机（AutoMaton）？
- 有限状态自动机（Finite-state machine, FSM）是一种表现状态和转移的结构
- 可以这么理解：一棵trie就是一个自动机，她能接受所有插入过的单词并转移到终止状态，且她不能接受任何没有插入过的单词（不能转移到终止状态）。如果我们只考虑转移合法，不一定要求终止，她还能接受所有插入过的单词的前缀。
- 一个字符串S的后缀自动机（SuffixAutoMaton，SAM）是一个自动机（废话），她能接受S的所有后缀（拓展为所有后缀的前缀，即所有子串）

## 0x02 怎么搞呢 ##
- 哇，看上去好高大上啊
- 大概和后缀数组是差不多的东西吧？
- 那要怎么构造它呢？
- 有一个粗暴而低效的办法：直接构造这个字符串的一棵全裸后缀树，显然这是一个合法的后缀自动机
- 但这太低效了，我们需要一个$ O(nlog_2{n}) $ 或更优的办法才能和后缀数组齐头并进不分高低，幸运的是，我们有一个线性的作法，比后缀数组不知道高到哪里去了
- 我们称这个办法为增量法，即假设我们已经得到了S的一个前缀prefix[i]，我们向已得到的SAM中插入S[i+1]并维护SAM的性质
- 如此从空串开始依次插入S中所有字符，我们就得到了S的SAM

## 0x03 注意事项 ##
- 下面大概正式开始
- 注意如果哪里不理解了，回忆一下SAM的目的是什么
- 是**识别所有S的后缀**，子串只是附带功能
- 这是一个重点

## 0x04 状态的表示 ##
- 既然我们需要线性的构造方式，那么显然状态数和转移数都要是线性的
- 转移显然是用字符转移
- 状态如何去表示呢？
- 假如你有一个文本编辑器，你要输入S的某一个后缀，这里假设S是"ABCBBABC"
- 你第一次输入了一个A
- 你有可能输入的是那些后缀？显然只有"ABCBBABC"和"ABC"
- 为什么？因为A是这些后缀的前缀
- 同样，如果你第一次输入"BC"，那么你可能的输入只有"BCBBABC"和"BC"
- 我们发现，每个子串能拓展到的后缀完全是由这个子串在S中的出现位置决定的
- 进一步说，是由每一次出现的右端点位置决定的
- 假设我们已经得到了一个子串所有的出现右端点位置集合R $  \{R_{1},R_{2}...R_{n} \} $
- 如果往这个子串前面加上一些字符或者从前面删掉一些字符，出现右端点位置集合没变，那显然加上或者删去这些字符对于状态没有影响
- 那么这些没有影响的操作能得到的所有子串就有着相同的情况
- 我们称这些子串是一个等价类（equivalent class），他们属于一个集合Sub
- 具体的来说，我们的状态表示是：一个状态是一个右端点的集合R $  \{  R_{1},R_{2}...R_{n} \} $
- 更进一步，我们发现一个状态所包含的子串的长度是一个连续的区间
- 记为[min[p],max[p]]
- 不同状态的Sub之间没有交集（正确性是显然的，有交集就可以合并两个状态）

-----
- 现在我们能表示状态了，我们要考虑一下状态之间的关系
- 假设两个状态p,q的R集合有交集（没有交集是可能的）
- 考虑交集中的某一个位置i，由于Sub不能相交，所以[min，max]也不能相交（不然i这个位置就能产生相同的子串）
- 不妨设max[p]<min[q]
- 那么Sub[p]中所有子串长度都比Sub[q]中的要短
- 两者出现的右端点还是一样的
- 那不是说明Sub[p]都是Sub[q]的后缀么
- 那么R[q]出现的位置，R[p]肯定也出现了
- 所以R[q]是R[p]的真子集（显然不能相等吧）
- 这样就说明，两个状态的R要么交集为空，要么一个是另一个的真子集
- 那我们考虑转移到终点的状态，显然R大小为1，这样的状态有|S|那么多个
- 每一个不是终点的状态起码能把R分为两个非空部分，很容易证明状态是O(|S|)的
- 这样我们就证明了状态的线性，以及明确了状态的表示
- 转移的线性证明详见陈立杰讲课PPT（提示：考虑后缀自动机的树形图）

-----
- 令一个状态p的parent[p]表示一个状态q，q满足R[p]是R[q]的真子集且R[q]尽可能小
- 显然有max[q]=min[p]-1，这很显然，把一个等价类中最短的子串头上在砍去一个字符，R集合就会不可避免的扩大，且这次扩大的范围是最小的
- 这样parent就形成了一个树的结构，称之为parent tree，并把一个状态到另一个状态的parent路径称为后缀链（suffix link）
- 充分理解后缀链这个名字的含义有助于我们理解这个概念（详见《组合数学》，以下仅简略介绍）
- **链**是一种 子集 的 集合，集合中任何两个子集都是包含关系
- 一条后缀链上的任意两个点的R集合都是包含关系

------
- 其实我们并不需要真的记录R，**R集合其实是使用parent tree结构表示的**
- **最终得到的SAM转移既不需要parent tree，也不需要R集合，这两个东西的用处是帮我们一步步构造SAM**
- 这是第二个重点

----
- 我们来粗略说明一下这样的状态表示也能识别所有子串
- 考虑以i位置结尾的子串，首先找到i这个位置的终止状态p
- 不断地通过parent[p]向上爬，从p到root的[min,max]区间的交集显然是[1,i]，这样它就表示出了所有以i结尾的子串

## 0x05 状态的转移 ##
- 转移相对好理解，就是往R中的每个位置i后面尝试拼一个字符，如果能拼上就在转移后的R中加入i+1
- 比如S还是"ABCBBABC"
- 状态{3,8}用字符'B'转移得到状态{8}（想想为啥？）

## 0x06 线性构造 ##
- 现在我们既会表示状态，又会表示转移了
- 该开始讨论如何构造了
- 痛苦从这里开始

---
- 我们现在已经得到了prefix[i]的SAM
- 如何插入S[i+1]？
- 牢记我们的目的，我们要让SAM识别prefix[i+1]的所有后缀
- 我们其实只要在prefix[i]的所有后缀（包括一个空串）后面插入一个S[i+1]就行了
- 我们如何找到prefix[i]的所有后缀？我们首先要找到终点i，这不就是我们上一次插入的那个么
- 用last表示S[i]的终止状态，不断地在parent tree中向上爬就能找到prefix[i]的所有后缀
- 我们新建一个点np，这个点的R只有{i+1}，显然max[np]=max[last]+1（后面多加了S[i+1]这个字符）
- 这时我们需要分类讨论
- 设当前爬到的这个状态为p
- 如果p没有S[i+1]这个字符的转移，显然加上S[i+1]后会转移到np，那么给他加上这个转移就行了
- 如果p有S[i+1]这个字符的转移呢？
- 回顾我们的目的：识别prefix[i+1]的所有后缀
- 如果一个状态p有S[i+1]这个字符的转移，那么它的parent,grandparent......肯定都有
- 其实现在这个SAM已经能识别prefix[i+1]的所有后缀，可是我们不知道np的parent是谁，这导致所有状态的R集合中都没有i+1，这会给我们之后的添加字符造成问题
- 我们现在需要往合适的R[sp]集合中加入i+1这个位置（即让parent[np]=sp）
- 假设q是p用S[i+1]转移后的状态
- 我们强行给R[q]加入{L+1}这个位置？（即让parent[np]=q）
- 不太行，虽然R[p]中有L这个位置，但是R[q]中不一定有。强行插入会导致max[q]变小
- 考虑"AA**AA**XB**AA**"
- R[p]={4,8}
- 用X转移，得到R[q]={5},max[q]=5（**AAAAX**BAA）
- 如果我们从后面插入一个X，并且强行把9这个位置塞进R[q]，会导致max[q]=3（AA**AAX**B**AAX**），从而引发一系列问题
- 当然如果max[q]==max[p]+1就不会有这样的问题，直接让parent[np]=q就行了
- 这个时候，我们发现有两种情况
- 第一种：**AAAAX**BAAX     这个就是q这个状态（这里讨论的是max[q]!=max[p]+1的情况）
- 第二种：AA**AAX**B**AAX** 我们给这种情况新建一个状态nq
- 显然max[nq]=max[p]+1（后面多了一个S[i+1]）
- 显然R[q]是R[nq]的真子集，而且有parent[q]=parent[nq]
- 而且有parent[np]=parent[nq]
- **或者说，nq就是由q和np组成的**
- 而parent[nq]=parent[q]（原来的）
- 这是因为min[q]现在在min[nq]里，这样保持了原来长度的连贯性
- 然后对于q所有的转移，显然nq也同样可以使用（R[nq]新加的S[i+1]在转移上不起作用），所以直接拷贝即可
- 新建状态的部分就做完了，对于所有会转移到q的p的祖先（包括p），把转移重新指向nq即可

-----
- 这里似乎有一个遗留问题，那些转移不到q的祖先怎么办？
- 要时刻记得SAM此时的目的，我们要让SAM识别prefix[i+1]的所有后缀
- 现在识别了吗？识别了
- 那还要考虑parent tree
- 转移不到q的p的祖先，**转移到的一定是q的祖先**，而我们已经处理完了q（在q或者nq的R集合里想办法加入了i+1这个位置），即**我们已经在转移到的q的祖先的R集合中加入了i+1这个位置**
- **R集合其实是使用parent tree结构表示的**

## 0x07 总结 ##
- 对于插入一个字符i+1
- 新建一个节点np
- 找到上一次插入的终止位置last
- 对于last及其祖先（统称为p）
- 没有S[i+1]转移：插入新的转移到np
- 有S[i+1]转移：设转移到的状态为q，若max[q]=max[p]+1，parent[np]=q，结束这一阶段，否则
- 新建节点nq
- 把q的转移拷贝给nq
- parent[nq]=parent[q]，parent[q]=nq，parent[np]=nq
- 把所有转移到q的p改成转移到nq
- 搞完啦！

## 0x08 感受 ##
- 彻底地理解R集合的表示方式和SAM的目的对于理解SAM太重要了

## 0x09 代码 ##

<pre lang=”cpp” line=”1″>
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
#define rep0(j,n) for(int j=0;j<n;++j)
#define rep1(j,n) for(int j=1;j<=n;++j)
#define pb push_back
#define set0(n) memset(n,0,sizeof(n))
#define ll long long

using namespace std;
const int MAXINT = 1000;

struct State {
State *parent, *son[26];
int val;
State ( int _val ) : val ( _val ), parent ( 0 ) {
memset ( son, 0, sizeof ( son ) );
}
State ( ) {}
};
struct SuffixAutoMaton {
State *root, *last, *present;
SuffixAutoMaton() {
root = new State ( 0 );
last = root;
present = root;
}
void extend ( char c ) {
int w = c - 'a';
State *p = last;
State *np = new State ( p->val + 1 );
for ( ; p && p->son[w] == 0; p = p->parent ) p->son[w] = np;
if ( p == 0 ) np->parent = root;
else {
State *q = p->son[w];
if ( p->val + 1 == q->val ) {
np->parent = q;
} else {
State *nq = new State ( p->val + 1 );
memcpy ( nq->son, q->son, sizeof ( q->son ) );
nq->parent = q->parent;
q->parent = nq;
np->parent = nq;
for ( ; p && p->son[w] == q; p = p->parent ) p->son[w] = nq;
}
}
last = np;
}
bool transit(char c){
int w = c - 'a';
if(present->son[w]==NULL) return false;
else present=present->son[w];
return true;
}
};
int main() {
return 0;
}
</pre>

很短嘛！SAM部分也就20+

括弧，代码在wordpress上显示不出来，我也不知道为什么



## 0x10 一个例题 ##
> 求两个字符串A,B的最长公共子串

- SA水题
- 考虑怎么用SAM做
- 对A建SAM，用B在SAM上面跑
- 如果当前状态为p，B中的一个字符在SAM上没有相应的转移，就让p=parent[p]直到有转移为止
- 用max[p]+1更新答案

## 0x11 一些额外问题 ##
- 维护一个点是不是终止节点（转移到了后缀）：只有最后一步的last到root的后缀链上的点才是终止节点
- 维护一个点的R集合中的最小值：每次新建的点显然不会使这个值变小，所有只要对新建的点初始化一下就行了
- 维护一个点的min：不就是parent的max+1么

## 0x12 一个遗留问题 ##
- 细心的读者可能发现了，我们证明了状态数和转移数是线性的，但是还有一步的复杂度线性我们未予证明
- 即构造SAM过程中修改last到root的后缀链这一部分
- 这是可证的，详见
- http://www.aiuxian.com/article/p-2504420.html
- 最终结论是后缀自动机的复杂度是线性的

## 0x13 后记 ##
- 这篇笔记参考了以下文章
- 《SAM后缀自动机》——陈立杰
- http://huntzhan.org/suffix-automaton-tutorial/
- http://www.aiuxian.com/article/p-2504420.html