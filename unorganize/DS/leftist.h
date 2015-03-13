struct node{
	int k;// data
	node *left,*right;
	int dist;
};
typedef node* tree;

int distance(tree pq)	
{ return pq==NULL ? 0 : pq->dist ; };
void fixdist(tree pq)
{
	if ( distance(pq->left) < distance(pq->right) )
		swap(pq->left,pq->right);
	pq->dist = distance(pq->right) + 1;
};
tree merge(tree a,tree b)	
{
	if ( a == NULL ) return b;
	else if ( b == NULL ) return a ;
	else if ( a->k > b->k ) {
		a->right = merge( a->right, b );
		fixdist( a );
		return a;
	}else{
		b->right = merge( a, b->right );
		fixdist( b );
		return b;
	}
};

tree remove(tree pq)	
{ return merge( pq->left, pq->right ); };

tree insert(tree x,tree pq)
{
	if ( pq==NULL )	return x ;
	else if ( pq->k > x->k ) {
			pq->right = insert( x, pq->right );
			fixdist( pq );
			return pq ;
	}else{
		x->left = pq;
		return x ;
	}
}