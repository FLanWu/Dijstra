#include <iostream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

const int N = 1234;
const int INF = 0x3f3f3f; //定义无穷大的值
int G[N][N]; //存储图
int dist[N]; //记录第一个节点到N的最小距离
int vis[N]; //判断是否访问到
int n,m;

void print_G();

void InitMap(int nodNum, int nodPari){
	int i, j, k;
	for(i = 1; i <= nodNum; i++){
		for(j = 1; j <= nodNum; j++){
			if(i == j){
				G[i][j] = 0;
			}else{
				G[i][j] = INF;
			}
		}
	}
	srand((unsigned)time(NULL));
	for(k = 1; k <= nodPari; k++){
		//生成1到nodNum之间的随机数
		i = rand() % nodNum + 1;
		j = rand() % nodNum + 1;
		if(i != j && G[i][j] == INF){
			//生成1到1023之间的随机数
			G[i][j] = G[j][i] = rand() % (20 - 1) + 1;
		}else{
			k --;
		}

	}
	print_G();
	return ;
}

//打印地图
void print_G(){
	printf("随机生成有%d个节点,有%d条边的联通图\n",n,m);
	printf("生成邻接矩阵为：\n");
	int i,j;
	for(i = 1; i <= n; i++){
		for(j = 1; j <= n; j++){
			if(G[i][j] < INF)
				printf("%d\t", G[i][j]);
			else
				printf("[∞]\t");
		}
		printf("\n");
	}
}

//核心代码
void dij(int start, int destination)
{
	int num = 1; //记录更新轮次
    int pos = start;
    for(int i=1;i<=n;i++)
    {
    	//找到start的相邻节点，并将距离依次付给dist[i]
    	dist[i]=G[start][i];
    }
    //记录访问过的节点
    vis[pos]=1;
    //共进行n轮，将所有节点都便利一遍
    for(int i=1;i<n;i++)
    {
    	printf("第%d轮更新:\n", num);
        int mins=INF;

        for(int j=1;j<=n;j++)
        {
        	//找相邻节点距离最短的赋值给mins
            if(!vis[j] && dist[j] < mins)
            {
            	pos=j; mins=dist[j];

            }
        }
        printf("============开始节点%d到%d的距离：%d ================\n", start, pos, mins);
        //将最小距离节点加入访问过得集合中
        vis[pos]=1;

        for(int j=1;j<=n;j++)
        {
            if(!vis[j] && dist[j] > dist[pos]+G[pos][j])
            {
            	//如果最近节点比经过一个节点的距离大，则更新
            	dist[j]=dist[pos]+G[pos][j];
            	printf("更新====>开始节点%d经过%d到%d的距离：%d\n", start, pos, j, dist[j]);
            }
        }
        printf("\n");
        num ++; //更新轮次增加1
    }
    //输出到destination的最小距离
    if(dist[destination] < INF)
    	printf("++++++++++>%d到%d的距离为%d<++++++++++++++++\n", start, destination, dist[destination]);
    else
    	printf("++++++++++>%d到%d不可达<++++++++++++++++\n", start, destination);
}

int main()
{
    while(true)
    {
        //对vis数组分配空间
    	srand((unsigned)time(NULL));
    	n = rand() % 10 + 1;
    	if(n == 1){
    		m = 0;
    	}else{
    		//要使图成为无向联通图，则边的条数至少在在n-1和n*(n-1)/2-1之间
    		m = rand() % ((n * (n - 1))/2 - (n-1)) + (n-1);
    	}
    	InitMap(n,m);
        memset(vis,0,sizeof(vis));
        //以节点1为起点
        int start,destination;
		printf("请输入开始节点start: ");
		cin >> start;
		printf("请输入你想知道距离的目的地：");
		cin >> destination;
        while(  start < 1 || start > n || destination < 1 || destination > n ){
        	printf("输入的start和destination有误，请输入1到%d之间的数\n",n);
        	cin >> start >> destination;
        }

        dij(start, destination);
        int exit;
        scanf("%d", &exit);
        if(exit == 0){
        	break;
        }
    }
    return 0;
}
