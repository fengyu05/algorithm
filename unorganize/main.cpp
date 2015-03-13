#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

//////////////////////////////////////////////////////////////////////////
// 非递归链表翻转
struct node
{
	int dat;
	node* next;
	node(int p_dat,node* p_next=0):dat(p_dat),next(p_next){}
};
node* insert_fnt(int p_dat,node* head=0){
	return new node(p_dat,head);
}
void visit(node* head)
{
	for (head;head;head=head->next)
	{
		cout<<head->dat<<endl;
	}
}
node* reverse(node* head)
{
	node *ptr=head,*prev=0;
	while(ptr){
		node* tmp=ptr->next;
		ptr->next=prev;
		prev=ptr;
		ptr=tmp;
	}
	return prev;
}
//////////////////////////////////////////////////////////////////////////
// 交换链表相邻两项
//////////////////////////////////////////////////////////////////////////
node* swappair(node* head)
{
	node *ptr=head,*res=0;
	if(ptr==0||ptr->next==0) return head;
	else res=ptr->next;
	while (ptr&&ptr->next)
	{
		node* tmp=ptr->next,*tmp2=ptr->next->next;		
		if(tmp2==0||tmp2->next==0)
			ptr->next=tmp2;
		else
			ptr->next=tmp2->next;
		tmp->next=ptr;
		ptr=tmp2;
	}
	return res;
}
int main()
{	
	node* head=0;
	for(int i=1;i<9;i++){
		head=insert_fnt(i,head);
	}
	visit(head);
	head=swappair(head);
	visit(head);
	return 0;
}