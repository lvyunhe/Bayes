#!/bin/bash
awk -F"\t" '{
	cid=$3;
	count_all+=1;
	count[cid]+=1;
#统计每种类目的数量存放在数组count[cid]中
#for(cid in count){
#		t+=count[cid];
#t表示列表里边所有类目的总和数（没有去重）
#	}
}END{
	for(cid in count){
		p_cid=log(count[cid])-log(count_all);
#每种类目占类目总和的概率p(cid)
	print cid"\t"p_cid;
	}
}'

		
