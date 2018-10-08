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
