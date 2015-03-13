template<class T>
class BST
{
	struct node
	{
		T key;
		node *l,*r,*p;
		node(T key,node* p=0,node* l=0,node* r=0):key(key),l(l),r(r),p(p){}
	};
typedef node* link;
	link root;
	void __free(link t){
		if(t!=0){
			__free(t->l);
			__free(t->r);
			delete t;
		}
	}
	link search(link x,T k){
		if(x==0||k==x->key) return x;
		if(k< x->key)
			return search(x->l,k);
		else
			return search(x->r,k);
	}
	link bst_min(link x){
		while(x->l!=0)
			x=x->l;
		return x;
	}
	link bst_max(link x){
		while(x->r!=0)
			x=x->r;
		return x;
	}
	link bst_successor(link x){
		if(x->r!=0)
			return bst_min(x->r);
		link y=x->p;
		while(y!=0&&x==y->r){
			x=y;
			y=y->p;
		}
		return y;
	}
	link bst_predecessor(link x){
		if(x->l!=0)
			return bst_max(x->l);
		link y=x->p;
		while(y!=0&&x==y->l){
			x=y;
			y=y->p;
		}
		return y;
	}
	link buildbst(T *pre,T *in,int len,link p){
		T r=pre[0];
		link root=new node(r,p);
		if(len==1)
			return root;
		int i;
		for(i=0;i<len;i++)
			if(in[i]==r)
				break;
		if(i!=0) root->l=buildbst(pre+1,in,i,root);
		if(i<len-1) root->r=buildbst(pre+i+1,in+i+1,len-i-1,root);	
		return root;
	}
	void walk(link x){
		if(x!=0){
			// preorder
			walk(x->l);
			// inorder
			walk(x->r);
			// postorder
		}
	}
public:
	BST(link r=0):root(r){}
	~BST(){ __free(root);}
	void insert(T k){
		link y=0,x=root;
		while(x!=0){
			y=x;
			if(k < x->key)
				x=x->l;
			else
				x=x->r;
		}
		link z=new node(k,y);
		if(y==0)
			root=z;
		else if(k< y ->key)
			y->l=z;
		else
			y->r=z;
	}
	link operator[](T k){
		return search(root,k);
	}
	bool remove(T k){
		link z=search(root,k);
		if(z==0) return false;
		link x,y;
		if(z->l==0||z->r==0)
			y=z;
		else
			y=bst_successor(z);
		if(y->l!=0)
			x=y->l;
		else
			x=x->r;
		if(x!=0)
			x->p=y->p;
		if(y->p==0)
			root=x;
		else if(y==y->p->l)
			y->p->l=x;
		else
			y->p->r=x;
		if(y!=z)
			z->key=y->key;
		return true;
	}	
};


link buildbst(istream& in,link p){ // preorder parentheses code 
	int open=0,key;				//(5(4(11(7()())(2()()))()) (8(13()())(4()(1()()))))
	char c,next;
	link root;
	while(in>>c){
		if(c=='('){
			next=in.peek();
			if(next==')'){
				in>>c;
				return 0;
			}
			open++;
			in>>key;
			root=new node(key,p);
			root->l=build(in,root);
			root->r=build(in,root);
		}else if(c==')'){
			open--;
			if(open==0)
				break;			
		}
	}
	return root;
}
