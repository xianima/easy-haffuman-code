#include"iostream"
using namespace std;
#include"stdio.h"
#define MAX 1000000
int haffuman[129][128];
FILE *openfile(char fname[30])
{
	FILE *fp;
	if((fp=fopen(fname,"r"))==NULL)
	{cout<<"can't open"<<endl;fp=NULL;}
	return fp;
}
void haffu(int a[],int lchild[],int rchild[],int i,int k)//建立哈夫曼编码数组
{
	i++;
	if(lchild[k]==0&&rchild[k]==0)
	{
		int j;
		for(j=0;j<i;j++)
			haffuman[k][j]=a[j];
		haffuman[k][j]=-1;
	}
	if(lchild[k]!=0)
	{
		a[i]=0;
		haffu(a,lchild,rchild,i,lchild[k]);
	}
	if(rchild[k]!=0)
	{
		a[i]=1;
		haffu(a,lchild,rchild,i,rchild[k]);
	}
}
void *movenumber(int a[],int length)//移动数组
{
	int i=0;
	for(;i<length;i++)
	{
		if(i<length-8)
			a[i]=a[i+8];
		else
			a[i]=-1;
	}
	return a;
}
	

int main()
{
	int a[129]={0};//统计出现的次数
	char fname[100];char c;int c1;//c 暂存字符
	int i,k,j;;//循环控制

	cin>>fname;
	FILE *fp;
	fp=openfile(fname);//打开文件

	while(!feof(fp))//统计字符出现的次数
	{
		c=fgetc(fp);
		c1=c-'0'+1;
		a[c1]++;
	}

	fclose(fp);//关闭文件

	//////////////////////////////////////////////////////////////
	int data[256],lchild[256]={0},rchild[256]={0},father[256]={0};//哈夫曼所用的数组
	int x1=0,x2=0;
	for(i=1;i<=128;i++)
		data[i]=a[i];
	data[0]=MAX;
	for(k=129;k<256;k++)
	{
		for(i=0;i<=k-1;i++)
		{
			if(data[i]<data[x1]&&father[i]==0)
				x1=i;
		}
		for(i=0;i<=k-1;i++)
		{
			if(data[i]<data[x2]&&father[i]==0&&data[i]>=data[x1]&&x1!=i)
				x2=i;
		}
		data[k]=data[x1]+data[x2];
		lchild[k]=x1;rchild[k]=x2;
		father[x1]=k;father[x2]=k;
		x2=0;x1=0;
	}
	///////////////////////////////////////////////////////建立哈夫曼树
	
	i=-1;k=254;
	int pausea[128];
	haffu(pausea,lchild,rchild,i,k);

	///////////////////////////////////////////////////////////////确定哈夫曼编码

	//////////////////////////////////////////////////////////////////

	int bianma[128],length=0;
	char ready;
	int readyt;
	char fname2[100];
	FILE *fp;
	cin>>fname2;
	fp=openfile(fname2);//打开文件

	while(!feof(fp))
	{
		ready=fgetc(fp);
		readyt=ready-'0'+1;
		for(i=0;i++;haffuman[readyt][i]==-1)
			bianma[length+i]=haffuman[readyt][i];
		length=length+i;
		if(length>8)
		{//输出八个二进制
			movenumber(bianma,length);
			length=length-8;
		}

	}

	fclose(fp);//关闭文件

	///////////////////////////////////////////////////////////////////将文件每个字符转换成哈夫曼编码，并输出二进制文件

	system("pause");
	return 0;
}