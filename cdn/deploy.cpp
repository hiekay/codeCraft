#include "deploy.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

#define INF 10000
// translate the char to int
void  my_atoi( int *output,const char *str)
{
	//assert(NULL !=str);

	int lenth=strlen(str);
	*output=0;
	while(lenth>0)
	{		
		while(isdigit(*str))
		{
			*output=*output*10+*str-'0';
			str++;
			lenth--;
		}
		output++;
		str++;
		lenth--;
	}	
}

struct Edge
{
	int cap;
	int cost;
};

struct Consumer
{
	int start;
	int end;
	int cost;
};
//你要完成的功能总入口
void deploy_server(char * topo[MAX_EDGE_NUM], int line_num,char * filename)
{
	//char *data=topo[0];
	//int x=my_atoi(data);
	int firstline[3]={0,0,0};
	my_atoi(firstline,topo[0]);
	
	int nodeNum,netNum,cosNum;
	nodeNum=firstline[0];
	netNum=firstline[1];
	cosNum=firstline[2];
	
	my_atoi(firstline,topo[2]);
	int serverCost;
	serverCost=firstline[0];
	
	int max=nodeNum+2;
	Edge map[max][max];// common node and the virtual source and meeting point
	for (int i=0;i<max;i++)
	{	for(int j=0;j<max;j++)
		{
			map[i][j].cap=0;
			map[i][j].cost=INF;
		}
	}
			
	int from ,to;
	for(int i=4;i<netNum+4;i++)
	{
		int fourline[4]={0,0,0,0};
		my_atoi(fourline,topo[i]);
		from=fourline[0];
		to=fourline[1];
		map[from][to].cap=fourline[2];
		map[from][to].cost=fourline[3];
		map[to][from].cap=fourline[2];
		map[to][from].cost=fourline[3];
	}
	
	Consumer consumer[cosNum];
	int count=0;
	for(int i=netNum+5;i<netNum+5+cosNum;i++)
	{
		int threeline[3]={0,0,0};
		my_atoi(threeline,topo[i]);
		consumer[count].start=threeline[0];
		consumer[count].end=threeline[1];
		consumer[count].cost=threeline[2];
		count++;
	}
	// add the source point 	only out

	for(int i=0;i<nodeNum;i++)
	{	map[nodeNum][i].cost=serverCost;
		map[nodeNum][i].cap=INF;
	}
	//add the meetin point     only in	
	for(int i=0;i<count;i++)
	{	map[consumer[i].end][nodeNum+1].cap=consumer[i].cost;
		map[consumer[i].end][nodeNum+1].cost=0;
	}
	for ( from=0;from<nodeNum+2;from++)
	{
		for(to=0;to<nodeNum+2;to++)
		{
			printf("%d %d %d %d **\n",from,to,map[from][to].cap,map[from][to].cost);	
		}
		
		printf("next line\n");
	}	
	

	// 需要输出的内容
	char * topo_file = (char *)"17\n\n0 8 0 20\n21 8 0 20\n9 11 1 13\n21 22 2 20\n23 22 2 8\n1 3 3 11\n24 3 3 17\n27 3 3 26\n24 3 3 10\n18 17 4 11\n1 19 5 26\n1 16 6 15\n15 13 7 13\n4 5 8 18\n2 25 9 15\n0 7 10 10\n23 24 11 23";

	// 直接调用输出文件的方法输出到指定文件中(ps请注意格式的正确性，如果有解，第一行只有一个数据；第二行为空；第三行开始才是具体的数据，数据之间用一个空格分隔开)
	write_result(topo_file, filename);

}




