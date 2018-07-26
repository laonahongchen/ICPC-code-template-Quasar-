#include<cstdio>  
#include<string>  
#include<cstring>  
#include<algorithm>  
using namespace std;  
int mu[100001],prime[100001];  
bool check[100001];   
int tot;  
inline void findmu()  
{  
     memset(check,false,sizeof(check));  
     mu[1]=1;  
     int i,j;  
     for(i=2;i<=100000;i++)  
     {  
          if(!check[i])  
          {  
               tot++;  
               prime[tot]=i;  
               mu[i]=-1;  
          }  
          for(j=1;j<=tot;j++)  
          {  
               if(i*prime[j]>100000)  
                    break;  
               check[i*prime[j]]=true;  
               if(i%prime[j]==0)  
               {  
                    mu[i*prime[j]]=0;  
                    break;  
               }  
               else  
                    mu[i*prime[j]]=-mu[i];  
          }  
     }  
}  
int sum[100001];  
//找[1,n],[1,m]内互质的数的对数  
inline long long solve(int n,int m)  
{  
     long long ans=0;  
     if(n>m)  
          swap(n,m);  
     int i,la=0;  
     for(i=1;i<=n;i=la+1)  
     {  
          la=min(n/(n/i),m/(m/i));  
          ans+=(long long)(sum[la]-sum[i-1])*(n/i)*(m/i);  
     }  
     return ans;  
}  
int main()  
{  
     //freopen("b.in","r",stdin);  
    // freopen("b.out","w",stdout);  
     findmu();  
     sum[0]=0;  
     int i;  
     for(i=1;i<=100000;i++)  
          sum[i]=sum[i-1]+mu[i];  
     int a,b,c,d,k;  
     int T;  
     scanf("%d",&T);  
     while(T--)  
     {  
          scanf("%d%d%d%d%d",&a,&b,&c,&d,&k);  
          long long ans=0;  
          ans=solve(b/k,d/k)-solve((a-1)/k,d/k)-solve(b/k,(c-1)/k)+solve((a-1)/k,(c-1)/k);  
          printf("%lld\n",ans);  
     }  
     return 0;  
} 

