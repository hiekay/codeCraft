#include<stdio.h>
#include"lib_io.h"

int main(int argc,char *argv[])
{
	
   
    char *topo[MAX_EDGE_NUM];
    int line_num;

    char *topo_file = argv[1];

    line_num = read_file(topo, MAX_EDGE_NUM, topo_file);

    printf("line num is :%d \n", line_num);
    if (line_num == 0)
    {
        printf("Please input valid topo file.\n");
        return -1;
    }

   
	return 0;
}


