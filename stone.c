#include <string.h>
#include <stdio.h>
#include <math.h>

const int INF = 1 << 30;
#define MIN(a, b)  ((a) > (b) ? (a) : (b))
#define N 205

int dp[N][N];
int sum[N];
int a[N];

int getMinval(int *a, int n)
{
    for(int i = 0; i < n; i++)
    {
        dp[i][i] = 0;
    }

    for(int v = 1; v < n; v++)
    {
        for(int i = 0;i < n-v; i++)
        {
            int j = i + v;
            dp[i][j] = INF;
            int tmp = sum[j] - (i > 0 ? sum[i-1]:0);
            for(int k = i; k < j; k++)
                dp[i][j] = MIN(dp[i][j], dp[i][k] + dp[k+1][j] + tmp);
        }
    }
    return dp[0][n-1];
}

int main()
{
    int n;
    while(scanf("%d", &n) != EOF)
    {
        for(int i = 0;i < n; i++)
        {
            scanf("%d", &a[i]);
        }

        sum[0] = a[0];

        for(int i = 1; i< n ; i++)
        {
            sum[i] = sum[i-1] + a[i];
        }
        printf("%d\n",getMinval(a,n));
    }
    return 0;
}





#include <string.h>
#include <stdio.h>

const int INF = 1 << 30;
#define N 1005

int dp[N][N];
int p[N][N];
int sum[N];
int n;

int getMinval()
{
    for(int i=1; i<=n; i++)
    {
        dp[i][i] = 0;
        p[i][i] = i;
    }
    for(int len=1; len<n; len++)
    {
        for(int i=1; i+len<=n; i++)
        {
            int end = i+len;
            int tmp = INF;
            int k = 0;
            for(int j=p[i][end-1]; j<=p[i+1][end]; j++)
            {
                if(dp[i][j] + dp[j+1][end] + sum[end] - sum[i-1] < tmp)
                {
                    tmp = dp[i][j] + dp[j+1][end] + sum[end] - sum[i-1];
                    k = j;
                }
            }
            dp[i][end] = tmp;
            p[i][end] = k;
        }
    }
    return dp[1][n];
}

int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        sum[0] = 0;
        for(int i=1; i<=n; i++)
        {
            int val;
            scanf("%d",&val);
            sum[i] = sum[i-1] + val;
        }
        printf("%d\n",getMinval());
    }
    return 0;
}




circle stone
#include<iostream>
using namespace std;
int N;//石子的堆数
int num[100]={0};//每堆石子个数

int sum(int begin,int n)
{
     int total=0;
     for (int i=begin;i<=begin+n-1;i++)
     {   if(i==N)
              total=total+num[N];//取代num[0]
         else
              total=total+num[i%N];
     }
     return total;
}
int stone_merge()
{
       int score[100][100];//score[i][j]:从第i堆石子开始的j堆石子合并后最小得分
       int n,i,k,temp;
       for (i=1;i<=N;i++)       
           score[i][1]=0;//一堆石子，合并得分为0

       //num[0]=num[N];//重要：sum()函数中i=N时,取num[0]
       for (n=2;n<=N;n++)//合并的石子的堆数
       {
           for (i=1;i<=N;i++)//合并起始位置
           {
               score[i][n]=score[i][1]+score[(i+1-1)%N+1][n-1];
               for (k=2;k<=n-1;k++)//截断位置
               {
                  temp=score[i][k]+score[(i+k-1)%N+1][n-k];
                  if(temp <score[i][n]) 
                        score[i][n] = temp;//从第i开始的k堆是：第i+0堆到第(i+k-1)%N堆
               }
               score[i][n]+=sum(i,n);
           }
       }  
       int min=2147483647;   
       for (i=1;i<=N;i++)
       {    if (min>score[i][N])           
                  min=score[i][N];//取从第i堆开始的N堆的最小者
       }
       return min;
}

int main()
{
       int min_count=0;
       cin>>N;//石子的堆数
       while(N!=0)
       {
           for (int i=1;i<=N;i++)
               cin>>num[i];//每堆石子的数量//从1开始,num[0]不用        
           min_count=stone_merge();
           cout<<min_count<<endl;

           for(i=0;i<N;i++)//准备下一轮
               num[i]=0;
           min_count=0;
           cin>>N;
       }
       return 0;
}

#include<stdio.h>
int N;//最多100堆石子:N=100
int num[200]={0};

int stone_merge()
{
    int score[200][101]={0};//l[i][j]:从第i堆石子起合并n堆石子的最小得分
    int n,i,k,temp;
    for(i=0;i<2*N;i++)
        score[i][1]=0;//一堆石子合并得分为0
    for(n=2;n<=N;n++)//合并n堆石子
    {
        for(i=0;i<=2*N-n;i++)//从第i对开始合并(有一次重复运算，但省去了循环取数，简化了程序)
        {
            score[i][n]=score[i][1]+score[i+1][n-1];
            for(k=2;k<n;k++)//划分
            {   temp=score[i][k]+score[k+i][n-k];
                if(temp<score[i][n])
                    score[i][n]=temp;//取(i,n)划分两部分的得分
            }
            for(k=i;k<i+n;k++)
                score[i][n]+=num[k];//加上此次合并得分
        }
    }
    int min=2147483647;//int(4位)最大值为2147483647
    for(i=0;i<N;i++)
    {
        if(score[i][N]<min)
            min=score[i][N];//从第i堆开始取N堆石子，的最小合并得分
    }
    return min;
}

int main()
{
    int min_count;
    scanf("%d",&N);//N堆石子
    while(N!=0)
    {
        for(int i=0;i<N;i++)
            scanf("%d",&num[i]);//每堆石子的数量
        for(i=N;i<2*N;i++)
            num[i]=num[i-N];//复制一倍，化简环形计算（N堆石子是围成一个环的）
        if(N==1)    min_count=0;
        else if(N==2)    min_count=num[0]+num[1];
        else    min_count=stone_merge();
        printf("%d\n",min_count);

        for(i=0;i<200;i++)    num[i]=0;//准备下一轮
        min_count=0;
        scanf("%d",&N);
    }
    return 0;
}
