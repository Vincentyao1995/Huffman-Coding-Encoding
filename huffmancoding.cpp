#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max_num_tree 256   //HUFFMAN树节点极限(出现不同类型字符的个数极限)
#define N 8    //HUFFMAN码长极限


struct huffmantree
{
	int w;
	char data;
	char code[N];
	char *str_code;
	unsigned int parent,lchild,rchild;
	int visited;
}HTNode,tree[max_num_tree];

char str[999];
int str_len,tree_len;

int load ()   
{
	FILE *fp=fopen("input.txt","r");
	if(fp==NULL){exit(0);printf("error!");}
	int i=0;
	
	while(!feof(fp))
	{
		if(feof(fp)==1)break;
		fscanf(fp,"%c",&str[i]);
		
		for(int u=0;u<max_num_tree;u++)
		{
			if(tree[u].data==NULL)
			{
				tree[u].data=str[i];
				++tree[u].w;
				break;
			}
			if(str[i]==tree[u].data)
			{
				++tree[u].w;
				break;
			}	
		}//for
		i++;
	}//while
	str_len=i;
	
	
	for(int u=0;tree[u].data!=NULL;u++)
		continue;
	tree_len=u;
	tree[u].data=0;
	tree[u].w=0;
	return u;
		
}
void huffmancoding(int n)
{
	int length=n;

	if(n<=1)return;
	int m=2*tree_len-1;
	for(int i=0;i<=m;++i)
	{
		tree[i].lchild=0;
		tree[i].parent=0;
		tree[i].rchild=0;
		if(i>=n)tree[i].w=0;
	}
	void Select(int*,int*);
	int s1,s2;
	for(i=n;i<=m-1;i++)
	{
	Select(&s1,&s2);
//	printf("%d %d\n",s1,s2);
	tree[s1].parent=i;	tree[s2].parent=i;
	tree[i].lchild=s1;	tree[i].rchild=s2;
	tree[i].w=tree[s1].w+tree[s2].w;
	}

	char *cd[256];
	cd[n-1]="\0";
	int start;
	for(i=0;i<=n;++i)//n==tree_len(number of leaf_node)
	{
		for(int c=i,int j=N-1,int f=tree[i].parent;f!=0;c=f,f=tree[f].parent)
		{
			if(tree[f].lchild==c)	
			{
				tree[i].code[j]='0';
				--j;
			}
			else 
			{
				tree[i].code[j]='1';
				--j;
			}
		}
		
	}

	for(i=0;i<tree_len;++i)
	for(int j=0;j<N;++j)
		if(tree[i].code[j]==NULL)
			tree[i].code[j]='*';

	FILE *fp;
	fp=fopen("output_huffman.txt","a");
	if(fp==NULL)exit(0);
	printf("码表为:\n");
	fprintf(fp,"码表为:\n");

	for(i=0;i<n;++i)
	{
//		tree[i].str_code[N]='\0';
		printf("%c :",tree[i].data);
		fprintf(fp,"%c :",tree[i].data);
		for(int j=0;j<N;j++)
		{
			if(tree[i].code[j]==NULL)tree[i].code[j]='*';

	
			//tree[i].str_code[j]=tree[i].code[j];	
			
			
			printf("%c",tree[i].code[j]);
			fprintf(fp,"%c",tree[i].code[j]);
		}
			printf("\n");
			fprintf(fp,"\n");
	}



	fcloseall();
}
void Select(int* s1,int* s2)
{
	huffmantree tree2[max_num_tree];
	
	int temp=0,judge=0;
		for(int i=0;i<max_num_tree;i++)
	{
		if(temp==1)
			break;
		if(tree[i].w==0)
			continue;
		if(tree[i].visited==1)
			continue;
		for(int j=0;j<max_num_tree;++j)
		{
			if(temp==1&&judge==-1)break;
			if(tree[j].w==0)continue;
			
			if(tree[j].visited==1)continue;
			if(tree[i].w>tree[j].w)
				{
					judge=-1;
					continue;
				}
			else 
				{
					if(tree[j+1].data==NULL&&tree[i].w<=tree[j].w)
					{
						*s1=i;
						tree[i].visited=1;
						temp=1;
						continue;
					}
					continue;
				}//else
			
		}//for j
	}//for i
	temp=0;
		for( i=0;i<max_num_tree;i++)
	{
		if(temp==1)
			break;
		if(tree[i].w==0)
			continue;
		if(tree[i].visited==1)
			continue;
		for(int j=0;j<max_num_tree;++j)
		{
			if(temp==1&&judge==-1)break;
			if(tree[j].w==0)continue;
			
			if(tree[j].visited==1)continue;
			if(tree[i].w>tree[j].w)
				{
					judge=-1;
					continue;
				}
			else 
				{
					if(tree[j+1].data==NULL&&tree[i].w<=tree[j].w)
					{
						*s2=i;
						tree[i].visited=1;
						temp=1;
						continue;
					}
					continue;
				}//else
			
		}//for j
	}//for i
}
void information(int length)
{
	FILE *fp;
	fp=fopen("output_huffman.txt","w");
	if(fp==NULL)exit(0);
	for(int n=0;n<str_len;n++)
	{	
		if(n==0)
		{
			fprintf(fp,"原字符串是:\n");
			printf("原字符串是:\n");
		}
			printf("%c",str[n]);
			fprintf(fp,"%c",str[n]);
	}
	printf("\n");
	fprintf(fp,"\n");
	
	for(n=0;n<length;n++)
		printf("%c出现次数是:%d\n",tree[n].data,tree[n].w);
	printf("\n");
	fcloseall();
}

void readcode()
{
	FILE *fp;
	fp=fopen("output_huffman.txt","a");
	if(fp==NULL)exit(0);

	FILE *fp2;
	fp2=fopen("output_code.txt","wb");
	if(fp2==NULL)exit(0);

	printf("编码为:\n");
	fprintf(fp,"编码为:\n");
	for(int i=0;i<str_len;i++)
		for(int j=0;j<tree_len;j++)
		{
			if(str[i]==tree[j].data)
			{
				for(int n=0;n<N;n++)
				{
					printf("%c",tree[j].code[n]);
					fprintf(fp,"%c",tree[j].code[n]);
					fprintf(fp2,"%c",tree[j].code[n]);
				}	
				printf(" ");
				fprintf(fp," ");
				break;
			}
				
		}
	printf("\n");
	fprintf(fp,"\n");
	fcloseall();

}

void uncompressed()
{
	FILE *fp;
	fp=fopen("output_huffman.txt","a");
	if(fp==NULL)exit(0);
	
	FILE *fp2;
	fp2=fopen("output_code.txt","r");
	if(fp2==NULL)exit(0);
	
	
	printf("解码为:\n");
	fprintf(fp,"\n解码为:\n");

	char judge[N+1]="0",string[256]="0";
	int s=0;
	
	while(!feof(fp2))
	{
	for(int i=0;i<N;i++)
		fscanf(fp2,"%c",&judge[i]);
	int temp=0;
	for(int w=0;w<tree_len;w++)
	{
		if(temp==1)break;
		for(i=0;i<N;i++)
		{
			if(i==N-1&&judge[i]==tree[w].code[i])
			{
			string[s]=tree[w].data;
			++s;
			temp=1;
			}
			if(judge[i]==tree[w].code[i])
				continue;
			else 
				break;
		}//for i<N
	}//for w<tree_len
	}//while
	for(int i=0;i<str_len-1;i++)
		{
			printf("%c",string[i]);
			fprintf(fp,"%c",string[i]);
		}
			printf("\n");
			fprintf(fp,"\n");	
			fcloseall();
}

void main()
{
	for(int ii=0;ii<max_num_tree;ii++)
	{
		tree[ii].w=0;
		tree[ii].visited=0;
	}

	int length;
	int load (); ///将字符串保存至str,并且计算出各字符权重,计入树结点中
	length=load();

	void information(int );//输出相关的一些信息(码表 原字符串等)
	information(length);

	void huffmancoding(int n);//huffmancoding
	huffmancoding(length);

	void readcode();       //编码
	readcode();

	void uncompressed();   //解码
	uncompressed();

}