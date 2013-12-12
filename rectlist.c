

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int items[100000];
    int n; /* number of items */
} setint;

void setint_insert(setint* si, int item)
{
    int i;
    for (i =0; i< si->n ; i++)
    {
        if ( si->items[i] == item )
        {
            /* the item exist in the set*/
            return;
        }
    }
    /* push item to set */
    si->items[si->n] = item;
    si->n++;
}



typedef struct rectlist rectlist;
void rectlist_print(rectlist* list);
struct rectlist
{

    rectlist* next;
    int left, right, lower, upper;      
};

void rectlist_print(rectlist* list)
{
    printf("[%d , %d[ [%d , %d[, ",
                list->left, list->right, list->lower, list->upper);        
        if(list->next)
            rectlist_print(list->next);
}

/*-----------------------------------------------------------------------------*/

typedef struct ListNode ListNode;
void ListNode_print(ListNode* node);
void ListNode_printRecursive(ListNode* node);

struct ListNode
{
    int a, b , c , d;
    ListNode* next;   
};
void ListNode_print(ListNode* node)
{
    printf("[%d , %d[ [%d , %d[ , ", node->a, node->b, node->c ,node->d);
}
void ListNode_printRecursive(ListNode* node)
{
    ListNode_print(node);
    if(node->next)
        ListNode_printRecursive(node->next);
}
/*------------------------------------------------------------------*/

typedef struct StreeNode StreeNode;
void StreeNode_constructor(StreeNode* node, int key);
/*
 Deletes this node and all child nodes recursively
*/
void StreeNode_destructor(StreeNode* node);

void StreeNode_print(StreeNode* node, int tabs);
void StreeNode_printDetailed(StreeNode* node);
struct StreeNode
{
    int key;
    StreeNode* left;
    StreeNode* right;
    ListNode* list;    
};

void StreeNode_constructor(StreeNode* node, int key)
{
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->list = NULL;        
}

/*
 Deletes this node and all child nodes recursively
*/
void StreeNode_destructor(StreeNode* node)
{
    if(node->left)
    {
        StreeNode_destructor(node->left);
        free(node->left);
    }
    if(node->right)
    {
        StreeNode_destructor(node->right);
        free(node->right);
    }
}

void StreeNode_print(StreeNode* node, int tabs)
{
    int i;
    printf("%d",node->key);
    if(node->left)
    {
        printf("-------");
        StreeNode_print(node->left, tabs+1);
    }
    if(node->right)
    {
        for( i = 0 ; i < tabs ; i++)
            printf("\t");
        printf("--------");
        StreeNode_print(node->right, tabs+1);        
    }
    if(!node->left && !node->right)
        printf("\n");
}

void StreeNode_printDetailed(StreeNode* node)
{
    if(node->left)
        StreeNode_printDetailed(node->left);
    printf("(%d, ", node->key);
    if(node->list)
        ListNode_printRecursive(node->list);
    printf(")\n");
    if(node->right)
        StreeNode_printDetailed(node->right);
}

/*----------------------------------------------------------------------*/

typedef struct Stree Stree;
int* Stree_get_keys(Stree* tree, rectlist* data);
void Stree_create_balanced_tree(Stree* tree, int* keys);
void Stree_add_segment(Stree* tree, int a, int b, int c , int d);
void Stree_attachListNode(StreeNode* node, int a, int b , int c , int d);
void Stree_printTree(Stree* tree);
void Stree_printNodes(Stree* tree);
struct Stree
{
    StreeNode* root;
};

void Stree_printTree(Stree* tree)
{
    if(tree->root)
        StreeNode_print(tree->root,0);
}

void Stree_printNodes(Stree* tree)
{
    if(tree->root)
        StreeNode_printDetailed(tree->root);
}

void Stree_attachListNode(StreeNode* node, int a, int b , int c , int d)
{
    ListNode* lnode = (ListNode*) malloc( sizeof(ListNode) );
    lnode->a = a;
    lnode->b = b;
    lnode->c = c;
    lnode->d = d;
    lnode->next = node->list;
    node->list = lnode;
}

void Stree_constructor(Stree* tree, rectlist* data)
{
    int* keys = Stree_get_keys(tree, data);
    Stree_create_balanced_tree(tree, keys);
    rectlist* cur = data;
    while(cur)
    {
        Stree_add_segment(tree, cur->left, cur->right , cur->lower , cur->upper);
        cur = cur->next;
    }
    free(keys);
}

rectlist* Stree_query(Stree* tree, int x, int y)
{
    if(!tree->root->left)
        return(NULL);
    StreeNode* cur = tree->root;
    rectlist* result = NULL;
    while(cur->right)
    {
        if(x < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
        ListNode* curList = cur->list;
        while(curList)
        {
            if(y >= curList->c && y < curList->d) // point inside
            {
                rectlist* newList = (rectlist*) malloc( sizeof(rectlist) );                  
                newList->left = curList->a;
                newList->right = curList->b;
                newList->lower = curList->c;
                newList->upper = curList->d;
                newList->next = result;
                result = newList;
            }
            curList = curList->next;
        }
    }
    return(result);
}


int* Stree_get_keys(Stree* tree, rectlist* data)
{
   int k;
   setint keys;
   keys.n = 0;
   rectlist* cur = data;
   while(cur)
   {
       setint_insert(&keys, cur->left);
       setint_insert(&keys, cur->right);            
       cur = cur->next;
   }
   int* ret = (int*) malloc( (keys.n + 2) * sizeof(int) ); 
   ret[0] = -88;
   int i = 1;
   for(k=0; k< keys.n; k++)
   {
       ret[i] = keys.items[k];
       i++;
   }
   ret[i] = -1;        
   return(ret);
}

void Stree_create_balanced_tree(Stree* tree, int* keys)
{
    
    int* cur = keys;
    StreeNode* root = (StreeNode*) malloc( sizeof(StreeNode) );
    StreeNode_constructor (root, *cur);

    root->right = NULL;
    root->left = (StreeNode*) malloc( sizeof(StreeNode) ); 
    StreeNode_constructor (root->left, *cur);

    StreeNode* curNode = root;
    cur++;
    while(*cur != -1)   // -1 denotes end of list
    {
        StreeNode* newNode = (StreeNode*) malloc( sizeof(StreeNode) ); 
        StreeNode_constructor (newNode, *cur);

        newNode->right = NULL;
        newNode->left = (StreeNode*) malloc( sizeof(StreeNode) ); 
        StreeNode_constructor (newNode->left, *cur);

        curNode->right = newNode;
        curNode = newNode;
        cur++;
    }
    // join the trees
    while(root->right != NULL)
    {
        StreeNode *n1, *n2;
        curNode = root;
        while(curNode && curNode->right != NULL)
        {
            n1 = curNode->right;
            n2 = n1->right;
            n1->right = n1->left;
            n1->left = curNode->left;
            curNode->left = n1;
            curNode->right = n2;
            curNode = n2;
        }
    }
    tree->root = root->left;
}

void Stree_add_segment(Stree* tree, int a, int b, int c , int d)
{
   StreeNode *cur, *right, *left;
   if(!tree->root->left)
       exit(-1); // tree incorrect
   cur = tree->root;
   right = left = NULL;
   while(cur->right)   // not leaf
   {
       if(b < cur->key)
       {
           cur = cur->left;
       }
       else if(a > cur->key)
       {
           cur = cur->right;
       }
       else if(a < cur->key && b > cur->key)
       {
           right = cur->right;
           left = cur->left;
           break;
       }
       else if(a == cur->key)
       {
           right = cur->right;
           break;
       }
       else// b == cur->key
       {
           left = cur->left;
           break;
       }
   }

   if(left)
   {
       while(left->right)
       {
           if(a < left->key)
           {
               Stree_attachListNode(left->right , a , b , c , d);
               left = left->left;
           }
           else if(a == left->key)
           {
               Stree_attachListNode(left->right , a , b , c , d);
               break;
           }
           else
           {
               left = left->right;
           }
       }
       if(left->right == NULL && left->key == a)
       {
           Stree_attachListNode(left , a , b , c , d);
       }
   } // end left path

   if(right)
   {
       while(right->right)
       {
           if(right->key < b)
           {
               Stree_attachListNode(right->left , a , b , c , d);
               right = right->right;
           }
           else if(right->key == b)
           {
               Stree_attachListNode(right->left , a , b , c , d);
               break;
           }
           else
           {
               right = right->left;
           }
       }
   }
}
   

typedef struct strees
{
    Stree* tree;
}stree_t;

stree_t* create_2dstree(struct rectlist* data)
{
    Stree* tree = (Stree*) malloc( sizeof(Stree) ); 
    Stree_constructor( tree, data);
    stree_t* ret = (stree_t*) malloc( sizeof(stree_t) );
    ret->tree = tree;
    return(ret);
}

struct rectlist *query_2dstree(stree_t * tree, int x , int y)
{
    rectlist* rl = Stree_query(tree->tree,x,y);
    return(rl);
}



int main()
{  int i, j, sum;
   struct rectlist rect[1000100];
   struct rectlist *start, *tmp;
   stree_t * s;
   printf("starting \n");
   for(i = 0; i < 1000; i++)
   { for ( j= 0; j< 1000; j++)
     {   (rect[1000*i+j]).left = 10*i;
         (rect[1000*i+j]).right = 10*i + 40;
         (rect[1000*i+j]).lower = 10*j;
         (rect[1000*i+j]).upper = 10*j+5;
     }
   }
   for(i = 0; i<1000099; i++)
   {  (rect[i]).next = rect+(i+1);
   }
   (rect[1000099]).next = NULL;
   for(i=1000000; i<1000050; i++)
   {   (rect[i]).left =  100 + 10*(i-1000000);
       (rect[i]).right = 200000;
       (rect[i]).lower = 100;
       (rect[i]).upper = 110 + 10*(i-1000000);
   }
   for(i=1000050; i<1000090; i++)
   {   (rect[i]).left =  100;
       (rect[i]).right = 120;
       (rect[i]).lower = 100 + 100*(i-1000050);
       (rect[i]).upper = 200 + 100*(i-1000050);
   }
   for(i=1000090; i<1000100; i++)
   {   (rect[i]).left = 5000 + (i-1000090);
       (rect[i]).right = 10000 - (i-1000090);
       (rect[i]).lower = 5000 + (i-1000090);
       (rect[i]).upper = 10000 - (i-1000090);
   }
   start = tmp = &(rect[0]);
   i=0;
   while(tmp != NULL)
   {  i++;  tmp = tmp->next; }
   printf("Made %d rectangles\n", i);
   s = create_2dstree(start);
   printf("Built tree, now run tests\n");
   for(i = 0; i < 5; i++)
   { for ( j= 0; j< 1000; j++)
     {  if((start=query_2dstree(s,10*i+3, 10*j+7)) != NULL )
        {  printf("Error at position %d, %d\n", 10*i+3, 10*j+7);
	   printf("First rectangle in answer left %d, right %d, lower %d, upper %d\n",
           start->left, start->right, start->lower, start->upper);
           exit(-1);
        }
     }
   }
   for(i = 5; i < 8; i++)
   { for ( j= 0; j< 700; j++)
     {  int leftsum = 0;
        start= tmp= query_2dstree(s,10*i+3, 10*j+2);
        if( start == NULL )
	  {  printf("Error at position %d, %d: no rectangle found\n", 10*i+3, 10*j+2);
           exit(-1);
        }

        while( tmp != NULL )
	{  if( (tmp->lower != 10*j) || (tmp->upper != 10*j+5) )
           {  printf("Error at position %d, %d\n", 10*i+3, 10*j+2);
	      printf("Answer left %d, right %d, lower %d, upper %d\n",
                          tmp->left, tmp->right, tmp->lower, tmp->upper);
              exit(-1);
           }
	   leftsum += tmp->left;
           tmp = tmp->next;
        }
        if( leftsum != (140 + 40*(i-5)) )
        {  printf("Error at position %d, %d\n", 10*i+3, 10*j+2);
	   printf("leftsum is %d, should be %d\n", leftsum, 140+40*(i-5) );
           printf("answer rectangles left boundaries are\n");
           while(start != NULL )
	   {  printf("%d, ", start->left);
              start=start->next;
           }
           printf("\n");
           exit(-1);
        }
     }
   }

   printf("End of tests\n");
}
