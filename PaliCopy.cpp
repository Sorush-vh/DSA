#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <string>
using namespace std;
const int maxn=5000010;
const int x=123;
typedef long long unsigned ULL;
typedef pair<int,int> pii;
queue<pii> q;
ULL H0[maxn],H1[maxn],xp[maxn];
void hash_init(string s)
{
	int n=s.size();
	H0[n]=H1[n]=0;
	for(int i=n-1;i>=0;i--) H0[i]=H0[i+1]*x+(s[i]-'a');
	for(int i=0;i<=n-1;i++) H1[n-i-1]=H1[n-i]*x+(s[i]-'a');
	xp[0]=1;
	for(int i=1;i<=n;i++) xp[i]=xp[i-1]*x;
}
int main()
{
	string s;
	cin>>s;
	hash_init(s);
	int n=s.size();
	int ans=1;
	q.push(make_pair(1,1));
	while(!q.empty())
	{
		pii t=q.front();q.pop();
		int u=t.first,c=t.second;
		int v1=2*u,v2=2*u+1;
		if(v1<=n)
		{
			if(H0[0]-H0[u]*xp[u]==H1[n-v1]-H1[n-v1+u]*xp[u])
			{
				q.push(make_pair(v1,c+1));
				ans+=c+1;
			}
			else q.push(make_pair(v1,0));
		}
		if(v2<=n)
		{
			if(H0[0]-H0[u]*xp[u]==H1[n-v2]-H1[n-v2+u]*xp[u])
			{
				q.push(make_pair(v2,c+1));
				ans+=c+1;
			}
			else q.push(make_pair(v2,0));
		}
	}
	printf("%d\n",ans);
	return 0;
}