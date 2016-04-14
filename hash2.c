#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX_SIZE 4000000


//定义链表结点
typedef struct Listnode{
	float Value;
	int Cid;
	struct Listnode* next;
}Listnode;

//链表初始化
Listnode* list_init(){
	Listnode* L;
	L=(Listnode*)malloc(sizeof(Listnode));
	if(L==NULL)
		printf("申请内存空间失败\n");
	L->next=NULL;
	return L;
}
//链表插入
Listnode* list_insert(int cid,float value,Listnode* L){
	Listnode* p;
	p=(Listnode*)malloc(sizeof(Listnode));
	p->Cid=cid;
	p->Value=value;
	p->next=L->next;
	L->next=p;
	return L;
}



//定义哈希结点
typedef struct node{
	char* Key;
	Listnode* list;
	struct node* next;
}node;
node* hashTable1[MAX_SIZE];
int hash_table1_size;

//哈希函数
unsigned int BKDRHash(char *str){
	unsigned int seed=131;
	unsigned int hash=0;
	while(*str){
		hash=hash*seed+(*str++);
	}
	return (hash & 0x7FFFFFFF);
}


//哈希表初始化
void hash_table1_init(){
	hash_table1_size=0;
	memset(hashTable1,0,sizeof(node*)*MAX_SIZE);
}

//插入key-value-cid值
void hash_table_insert1(char* key,char* value,char* cid){
	if(hash_table1_size>=MAX_SIZE){
		printf("out of hash table memory!\n");
		return;
	}
	unsigned int pos=BKDRHash(key)%MAX_SIZE;
	node* phead=hashTable1[pos];
	int flag=0;
	while(phead!=NULL){
		if(strcmp(phead->Key,key)==0){
			phead->list=list_insert(atoi(cid),atof(value),phead->list);
			flag=1;
			break;
		}
		else
			phead=phead->next;
	}
	node* pnew=(node*)malloc(sizeof(node));
	memset(pnew,0,sizeof(node));
	pnew->Key=(char*)malloc(sizeof(char)*(strlen(key)+1));
	pnew->list=(Listnode*)malloc(sizeof(Listnode*)*1000);
	if(flag==0){
	strcpy(pnew->Key,key);
	Listnode *head=list_init();
	pnew->list=list_insert(atoi(cid),atof(value),head);
    

	pnew->next=hashTable1[pos];
	hashTable1[pos]=pnew;

	hash_table1_size++;
	}
}

//查找键值为key的结点，并返回相应指针node
Listnode* hash_table1_lookup(char* key){
	unsigned int pos=BKDRHash(key)%MAX_SIZE;
	if(hashTable1[pos]){
		node* phead=hashTable1[pos];
		Listnode* head;
		while(phead){
			if(strcmp(key,phead->Key)==0){
				head=phead->list;
				return head;
			}
			else
				phead=phead->next;
		}
	}
	return NULL;
}

//释放哈希表内存空间
void hash_table1_release(){
	int i;
	for(i=0;i<MAX_SIZE;i++){
		if(hashTable1[i]){
		node* phead=hashTable1[i];
		while(phead){
			node* pTemp=phead;
			phead=phead->next;
			if(pTemp){
				free(pTemp->Key);
				free(pTemp);
			}
		}
	}
}
}

//将第一个词典存入链表
Listnode*  keep_data1(char* file){
	FILE* fp;
	char string[10000];
	if((fp=fopen(file,"r"))==NULL){
		printf("can not open the file!\n");
		exit(0);
	}
	char *k;
	char *v;
	Listnode *phead;
	Listnode *head=list_init();
	while(!feof(fp)){
		fgets(string,sizeof(string),fp);
		if(!feof(fp)){
		 k=strtok(string,"\t");
		 v=strtok(NULL,"\t");
	     phead=list_insert(atoi(k),atof(v),head);
		 head=phead;
	}
	}
	return head;
}
/*
//将第一个词典存入数组
void  get_data1(char* file){
	FILE* fp;
	char string[10000];
	if((fp=fopen(file,"r"))==NULL){
		printf("can not open the file!\n");
		exit(0);
	}
	char *k;
	char *v;
	int cid[20000];
	float pcid[20000];
	int c_count=0;
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
*/
//将第二个词典存入哈希表
void keep_data2(char* file){
	FILE* fp;
	char string[10000];
	if((fp=fopen(file,"r"))==NULL){
		printf("can not open the file!\n");
		exit(0);
	}
	char *k;
	char *v;
	char *c;
	while(!feof(fp)){
		fgets(string,sizeof(string),fp);
		if(!feof(fp)){
		 c=strtok(string,"\t");
		 k=strtok(NULL,"\t");
		 v=strtok(NULL,"\t");
		 hash_table_insert1(k,v,c);
	}
	}
}

/*
void main(){
	hash_table1_init();
	keep_data2("script2");
	Listnode *p=hash_table1_lookup("修身");
	while(p){
	printf("%d %f \n",p->Cid,p->Value);
	p=p->next;
	}
	hash_table1_release();
}
*/
