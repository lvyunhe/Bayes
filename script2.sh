#!/bin/bash
awk '{
	cid=$3;
	count_all+=1;
	c_count[cid]+=1;
#统计每个类目的数量（c(cid)）
	for(i=4;i<=NF;i++){
	if(cid in c_count){
		word=$(i);
		arr[cid,word]+=1;
#arr下标为cid"\t"word出现在一个记录里的组合，arr数组值为包含此组合的数量（c(word,cid)）
		w_count[word]=1;
	}
	}
}END{
	v=length(w_count);
#v表示word词典总数
	for(k in arr){
		p_wc=log(arr[k]+1)-log(count_all+v);
#计算条件概率p(word/cid)
		split(k,arr1,SUBSEP);
		print arr1[1]"\t"arr1[2]"\t"p_wc;
		}
	}'

