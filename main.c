#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#include"hash2.c"
#include"time.h"

int cid[20000];
float pcid[20000];
int c_count=0;

void get_data1(char* file){
	FILE* fp;
	char string[10000];
	if((fp=fopen(file,"r"))==NULL){
		printf("can not open the file!\n");
		exit(0);
	}
	char *k;
	char *v;
	while(!feof(fp)){
		fgets(string,sizeof(string),fp);
		if(!feof(fp)){
			k=strtok(string,"\t");
			v=strtok(NULL,"\t");
			cid[c_count]=atoi(k);
			pcid[c_count]=atof(v);
			c_count+=1;
		}
	}
	fclose(fp);
}

//读入预测文件
void main(){
	double start,finish;
	start=clock();
			
	FILE *fp;
	char arr[1024];
	char file[20];
	printf("输入测试文件\n");
	scanf("%s",file);
	//读取预测word
	if((fp=fopen(file,"r"))==NULL){
		printf("error");
		exit(0);
	}


	hash_table1_init();
	keep_data2("script2");

	get_data1("script1");

	char *a[100];
	char *title;
	float count=0;
	float Rcount=0;
	while(!feof(fp)){
		fgets(arr,1024,fp);
		if(!feof(fp)){
			char *ch=strtok(arr,"\n");
			char *buf=strtok(arr,"\t");
			int matchcid;
			matchcid=atoi(buf);
			title=strtok(NULL,"\t");
			printf("%s	真正的类目：%d ",title,matchcid);
			count++;
	        int i=0;
	        char *buffer=strtok(title," ");
	        while(buffer!=NULL){
				a[i++]=buffer;
		        buffer=strtok(NULL," ");
			}
			int wordcount=i;
			int k,j;
			int R_cid;
	        float pmax=0,sum;
					for(k=0;k<c_count;k++){
						sum=pcid[k];
						for(j=0;j<wordcount;j++){
							Listnode *p2=hash_table1_lookup(a[j]);
							while(p2){
								if(p2->Cid==cid[k]){
									sum=sum+(p2->Value);
									break;
								}
								else
									p2=p2->next;
							}
						}
							if(sum<pmax){
								pmax=sum;
								R_cid=cid[k];
						}
					}
			//printf("预测的类目：%d\n",R_cid);
			if(R_cid==matchcid)
				Rcount++;
			else
				printf("正确的类目：%d,预测错误的类目：%d\n",matchcid,R_cid);
		}
	}
	float R=(Rcount/count)*100;
	printf("正确率：%f%\n",R);
	finish=clock();
	printf("运行时间：%f seconds\n",(finish-start)/CLOCKS_PER_SEC);
}
	


