#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BLOCKSIZE 256

typedef int textKey;
typedef int textHeight;
typedef char textObject;

typedef struct textNode
{
        textKey key;
        textHeight height;
        struct textNode *leftNode;
        struct textNode *rightNode;
        struct textNode *parentNode;
} text_t;


int size;
int taken = 0;
int returned = 0;

/*
Functions Prototypes Starts
*/
int length_text(text_t *txt);
char* get_line(text_t *txt, int index);
void append_line(text_t *txt, char* new_line);
char* set_line(text_t *txt, int index, char* new_line);
void insert_line(text_t *txt, int index, char* new_line);
char* delete_line( text_t *txt, int index);
text_t *getNode();
void returnNode(text_t *node);
text_t *createNode();
int maxHeight(text_t *txt) ;
text_t *create_text();
void inorder(text_t *txt);
void rightRotation(text_t *txt);
void display(text_t *txt);
/*
Functions Prototypes Ends
*/


text_t *current = NULL, *textList = NULL;
/* Create the memory for a node from the Text List */
text_t *getNode()
{ 
	text_t *temp;
  	taken += 1;
  	if (textList != NULL)
  	{  
		temp = textList;
     		textList = textList -> rightNode;
  	}
  	else
  	{  
		if (current == NULL || size == 0)
     		{	  
			current = (text_t *) malloc(BLOCKSIZE * sizeof(text_t));
        		size = BLOCKSIZE;
     		}
     		temp = current++;
     		size -= 1;
  	}
  	return (temp);
}

/* Returns the deleted node to the Text List */
void returnNode(text_t *node)
{  
	node->rightNode = textList;
   	textList = node;
   	returned +=1;
}

/* Assigns the default values for each node */
text_t *createNode()
{  
	text_t *tempNode;
   	tempNode = getNode();
   	tempNode->leftNode = NULL;
	tempNode->rightNode = NULL;
	tempNode->parentNode = NULL;
   	tempNode->key = -1;
	tempNode->height = -1;
	return (tempNode);
}

/* Assigns the given line to a leaf node */
textObject *create_object(char *new_line)
{
	textObject *tmpObject = (textObject *) malloc(strlen(new_line)+1);
	if (tmpObject == NULL)
	{
		perror("Malloc failed in create object");
		return NULL;
	}
	strcpy(tmpObject, new_line);
	return (tmpObject);
}


/* Finds height of a tree or subtree */
int maxHeight(text_t *txt) 
{
	int ldepth, rdepth;
	if (txt->rightNode == NULL) 
	{
		return 0;
	}
   	else
   	{
   		ldepth = maxHeight(txt->leftNode);
       		rdepth = maxHeight(txt->rightNode);
       		if (ldepth < rdepth) 
		{
           		return (rdepth+1);
       		}
		else
		{ 
			return (ldepth+1);
   		}
	}
} 

/* Initialises the balanced tree data structure 
creates an empty text, whose length is 0*/
text_t *create_text()
{	
	text_t *tempNode;
	tempNode = createNode();
	return (tempNode);
}

/* Returns the number of lines of the current text */
int length_text(text_t *txt)
{
	if (txt->leftNode == NULL || txt == NULL)
	{
		return 0; 
	}
	else
	{
		return (txt->key);
	}
} 

/* Performs the leftNode rotation of a tree */
void leftRotation(text_t *txt)
{ 
	text_t *tempNode;
	tempNode = txt->leftNode;
	txt->leftNode = txt->rightNode;
	txt->rightNode = txt->leftNode->rightNode;
	txt->rightNode->parentNode = txt; 
	txt->leftNode->rightNode = txt->leftNode->leftNode;
	txt->leftNode->leftNode = tempNode;
        tempNode->parentNode = txt->leftNode; 
}

/* Performs the rightNode rotation of a tree */
void rightRotation(text_t *txt)
{ 
	text_t *tempNode;
	tempNode = txt->rightNode;
	txt->rightNode = txt->leftNode;
	txt->leftNode = txt->rightNode->leftNode;
	txt->leftNode->parentNode = txt; 
	txt->rightNode->leftNode = txt->rightNode->rightNode;
	txt->rightNode->rightNode = tempNode;
        tempNode->parentNode = txt->rightNode; 
}

/* inserts the line
before the line of number index, if such a line exists, to new line, renumbering all
lines after that line. If no such line exists, it appends new line as new last line.*/
void insert_line(text_t *txt, int index, char * new_line) 
{
	text_t *tempNode = txt;
	int finished;
	int count = index;
	if (txt->leftNode == NULL)
	{
		txt->leftNode = (text_t *) create_object(new_line); 
      		txt->key  = 1;
      		txt->rightNode  = NULL;
		txt->parentNode = NULL;
		txt->height = 0;
	}
	else if (index > (tempNode->key))
	{
		append_line(txt, new_line);
	}	
	else
	{
		while(tempNode->rightNode != NULL)
        	{
        		(tempNode->key)++;
			if (count <= tempNode->leftNode->key)
			{
				tempNode = tempNode->leftNode;
			}
			else
			{
				count -= tempNode->leftNode->key;
				tempNode = tempNode->rightNode;
			}
		}

	        text_t *old_leaf, *new_leaf;
        	old_leaf = getNode();
        	new_leaf = getNode();
        	old_leaf->leftNode = tempNode->leftNode;
        	old_leaf->key = 1;
        	old_leaf->rightNode  = NULL;
        	old_leaf->parentNode = tempNode;
        	old_leaf->height = 0;

        	new_leaf->leftNode = (text_t *) create_object(new_line);
        	new_leaf->key = 1;
        	new_leaf->rightNode  = NULL;
        	new_leaf->parentNode = tempNode;
        	new_leaf->height = 0;
        	tempNode->rightNode = old_leaf;
        	tempNode->leftNode = new_leaf;
		(tempNode->key)++; 
		tempNode->height = 0;

		finished = 0;
		while(!finished && tempNode!=NULL)
		{
			int temp_height, old_height;
			old_height = tempNode->height;
			if (tempNode->leftNode->height - tempNode->rightNode->height == 2)
			{ 
				if (tempNode->leftNode->leftNode->height - tempNode->rightNode->height == 1)
				{ 
					rightRotation(tempNode);
					tempNode->rightNode->height = tempNode->rightNode->leftNode->height + 1;
					tempNode->height = tempNode->rightNode->height + 1;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
					tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
				else
				{ 
					leftRotation(tempNode->leftNode);
					rightRotation(tempNode);
					temp_height = tempNode->leftNode->leftNode->height;
					tempNode->leftNode->height = temp_height + 1;
					tempNode->rightNode->height = temp_height + 1;
					tempNode->height = temp_height + 2;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
			}
			else if (tempNode->leftNode->height - tempNode->rightNode->height == -2)
			{ 
				if( tempNode->rightNode->rightNode->height - tempNode->leftNode->height == 1)
				{ 
					leftRotation(tempNode);
					tempNode->leftNode->height = tempNode->leftNode->rightNode->height + 1;
					tempNode->height = tempNode->leftNode->height + 1;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
				else
				{ 
					rightRotation(tempNode->rightNode);
					leftRotation(tempNode);
					temp_height = tempNode->rightNode->rightNode->height;
					tempNode->leftNode->height = temp_height + 1;
					tempNode->rightNode->height = temp_height + 1;
					tempNode->height = temp_height + 2;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
			}
      			else 
			{ 
				if(tempNode->leftNode->height > tempNode->rightNode->height)
				{
					tempNode->height = tempNode->leftNode->height + 1;
				}
				else
				{
					tempNode->height = tempNode->rightNode->height + 1;
				}
			}
			if (tempNode->height == old_height)
			{
				finished = 1;
			}
			tempNode = tempNode->parentNode;
		}
	}

}

/* Appends new line as new last line */
void append_line(text_t *txt, char *new_line) 
{
	text_t *tempNode = txt;
	int finished;
	if (txt->leftNode == NULL)
	{
		txt->leftNode = (text_t *) create_object(new_line);
		txt->rightNode = NULL;
		txt->parentNode = NULL;
		txt->key = 1;
		txt->height = 0;
	}
	else
	{
		while(tempNode->rightNode != NULL)
		{
			(tempNode->key)++;
			tempNode = tempNode->rightNode;
		}

		text_t *old_leaf, *new_leaf;
		old_leaf = getNode();
		new_leaf = getNode();
		old_leaf->leftNode = tempNode->leftNode;
         	old_leaf->key = tempNode->key;
         	old_leaf->rightNode  = NULL;
		old_leaf->parentNode = tempNode;	
		old_leaf->height = 0;

		new_leaf->leftNode = (text_t *) create_object(new_line);
         	new_leaf->key = tempNode->key;
         	new_leaf->rightNode  = NULL;
		new_leaf->parentNode = tempNode;
		new_leaf->height = 0;
		tempNode->leftNode = old_leaf;
		tempNode->rightNode = new_leaf;	
		(tempNode->key)++;		
		tempNode->height = 0;

		finished = 0;
		while(!finished && tempNode!=NULL)
		{
			int temp_height, old_height;
			old_height = tempNode->height;
			if (tempNode->leftNode->height - tempNode->rightNode->height == 2)
			{ 
				if (tempNode->leftNode->leftNode->height - tempNode->rightNode->height == 1)
				{ 
					rightRotation(tempNode);
					tempNode->rightNode->height = tempNode->rightNode->leftNode->height + 1;
					tempNode->height = tempNode->rightNode->height + 1;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
					tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
				else
				{ 
					leftRotation(tempNode->leftNode);
					rightRotation(tempNode);
					temp_height = tempNode->leftNode->leftNode->height;
					tempNode->leftNode->height = temp_height + 1;
					tempNode->rightNode->height = temp_height + 1;
					tempNode->height = temp_height + 2;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
			}
			else if (tempNode->leftNode->height - tempNode->rightNode->height == -2)
			{ 
				if( tempNode->rightNode->rightNode->height - tempNode->leftNode->height == 1)
				{ 
					leftRotation(tempNode);
					tempNode->leftNode->height = tempNode->leftNode->rightNode->height + 1;
					tempNode->height = tempNode->leftNode->height + 1;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
				else
				{ 
					rightRotation(tempNode->rightNode);
					leftRotation(tempNode);
					temp_height = tempNode->rightNode->rightNode->height;
					tempNode->leftNode->height = temp_height + 1;
					tempNode->rightNode->height = temp_height + 1;
					tempNode->height = temp_height + 2;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
			}
      			else 
			{ 
				if(tempNode->leftNode->height > tempNode->rightNode->height)
				{
					tempNode->height = tempNode->leftNode->height + 1;
				}
				else
				{
					tempNode->height = tempNode->rightNode->height + 1;
				}
			}
			if (tempNode->height == old_height)
			{
				finished = 1;
			}
			tempNode = tempNode->parentNode;
		}
	}
}

/* Gets the line of number index, if such a line exists, and returns NULL else */
char *get_line(text_t *txt, int index) 
{
	int count = index;
	text_t *tempNode = txt;
	if (txt->key < index || index == 0 || txt->key == -1)
	{
		return NULL;
	}
	else
	{
		while(tempNode->rightNode != NULL)
                {
                        if (count <= tempNode->leftNode->key)
                        {
                                tempNode = tempNode->leftNode;
                        }
                        else
                        {
                                count -= tempNode->leftNode->key;
                                tempNode = tempNode->rightNode;
                        }
                }
		return (textObject *)(tempNode->leftNode);
	}
} 

/* Sets the line of
number index, if such a line exists, to new line, and returns a pointer to the previous
line of that number. If no line of that number exists, it does not change the structure
and returns NULL.*/
char *set_line( text_t *txt, int index, char * new_line)
{
	int count = index;
	char *old_line;
        text_t *tempNode = txt;
        if (txt->key < index || index == 0 || txt->key == -1)
        {
                return NULL;
        }
        else
        {
                while(tempNode->rightNode != NULL)
                {
                        if (count <= tempNode->leftNode->key)
                        {
                                tempNode = tempNode->leftNode;
                        }
                        else
                        {
                                count -= tempNode->leftNode->key;
                                tempNode = tempNode->rightNode;
                        }
                }

		old_line = (textObject *) create_object(((textObject *)(tempNode->leftNode)));
		tempNode->leftNode = (text_t *) create_object(new_line);
                return old_line;
        }
} 

/* deletes the line of number index,
renumbering all lines after that line, and returns a pointer to the deleted line. */
char * delete_line(text_t *txt, int index) 
{
	text_t *tempNode, *upper_node, *other_node;
   	textObject *deleted_object;
	int count = index;
	int finished;
   	tempNode = txt;
	if (txt->leftNode == NULL || length_text(txt) < index)
	{
		return NULL;
	}
	else if (txt->rightNode == NULL)
	{
		deleted_object = (textObject *)txt->leftNode;
		txt->leftNode = NULL;
		txt->parentNode = NULL;
		txt->key = -1;
		txt->height = -1;
		return (deleted_object);
	}
	else
	{
		while(tempNode->rightNode != NULL)
      		{   
			upper_node = tempNode;
			(tempNode->key)--;
                        if (count <= tempNode->leftNode->key)
                        {
                                tempNode = tempNode->leftNode;
				tempNode = upper_node->leftNode;
                        	other_node = upper_node->rightNode;
                        }
                        else
                        {
                                count -= tempNode->leftNode->key;
                                tempNode = tempNode->rightNode;
				tempNode = upper_node->rightNode;
				other_node = upper_node->leftNode;
                        }
      		}
		upper_node->key   = other_node->key;
         	upper_node->leftNode  = other_node->leftNode;
         	upper_node->rightNode = other_node->rightNode;
                upper_node->height = other_node->height;
		if (upper_node->rightNode != NULL)
		{
			upper_node->leftNode->parentNode = upper_node;
			upper_node->rightNode->parentNode = upper_node;
         	}
		deleted_object = (textObject *) tempNode->leftNode;
         	returnNode(tempNode);
         	returnNode(other_node);
		upper_node = upper_node->parentNode;
		tempNode = upper_node;
 
		finished = 0;
		while(!finished && tempNode!=NULL)
		{
			int temp_height, old_height;
			old_height = tempNode->height;
			if (tempNode->leftNode->height - tempNode->rightNode->height == 2)
			{ 
				if (tempNode->leftNode->leftNode->height - tempNode->rightNode->height == 1)
				{ 
					rightRotation(tempNode);
					tempNode->rightNode->height = tempNode->rightNode->leftNode->height + 1;
					tempNode->height = tempNode->rightNode->height + 1;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
					tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
				else
				{ 
					leftRotation(tempNode->leftNode);
					rightRotation(tempNode);
					temp_height = tempNode->leftNode->leftNode->height;
					tempNode->leftNode->height = temp_height + 1;
					tempNode->rightNode->height = temp_height + 1;
					tempNode->height = temp_height + 2;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
			}
			else if (tempNode->leftNode->height - tempNode->rightNode->height == -2)
			{ 
				if( tempNode->rightNode->rightNode->height - tempNode->leftNode->height == 1)
				{ 
					leftRotation(tempNode);
					tempNode->leftNode->height = tempNode->leftNode->rightNode->height + 1;
					tempNode->height = tempNode->leftNode->height + 1;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
				else
				{ 
					rightRotation(tempNode->rightNode);
					leftRotation(tempNode);
					temp_height = tempNode->rightNode->rightNode->height;
					tempNode->leftNode->height = temp_height + 1;
					tempNode->rightNode->height = temp_height + 1;
					tempNode->height = temp_height + 2;
					tempNode->rightNode->key = tempNode->rightNode->leftNode->key + tempNode->rightNode->rightNode->key;
					tempNode->leftNode->key = tempNode->leftNode->leftNode->key + tempNode->leftNode->rightNode->key;
                                        tempNode->key = tempNode->leftNode->key + tempNode->rightNode->key;
				}
			}
      			else 
			{ 
				if(tempNode->leftNode->height > tempNode->rightNode->height)
				{
					tempNode->height = tempNode->leftNode->height + 1;
				}
				else
				{
					tempNode->height = tempNode->rightNode->height + 1;
				}
			}
			if (tempNode->height == old_height)
			{
				finished = 1;
			}
			tempNode = tempNode->parentNode;
		}

	       	return (deleted_object);
	}
}

/* Performs the inorder traversal of a given tree */
void inorder(text_t *txt)
{
	if (txt->rightNode == NULL)
	{
		printf("************************\n");
                int k=txt->key;
		int h=txt->height;
		int p=txt->parentNode;
                printf("The key is %d\n",k);
                printf("The height is %d\n",h);
                printf("The text is %s\n", (textObject *)txt->leftNode);
                printf("The parentNode address is %d\n", p);
                
		printf("************************\n");
		return;
	}
	else if (txt != NULL)
	{
		inorder(txt->leftNode);
		printf("************************\n");
		int k=txt->key;
		int h=txt->height;
		int p=txt->parentNode;
                printf("The key is %d\n",k);
                printf("The height is %d\n",h);
		printf("The text is %s\n", (textObject *)txt->leftNode);
		printf("The parentNode address is %d\n", p);
		printf("************************\n");	
		inorder(txt->rightNode);
	}
}

/* Prints the all the elements of the given node */
void display(text_t *txt)
{
        if (txt != NULL)
        {
                printf("\n\n ************************\n");
                printf("The key is %d\n",txt->key);
                printf("The height is %d\n",txt->height);
                printf("The text is %s", (textObject *)txt->leftNode);
                printf("************************ \n\n");
        }
	else
	{
		printf("Node is NULL\n");
	}
}


/* main Function Test cases for the texteditor */
int main()
{  
	text_t* create_text();
	int i, temp; text_t *txt1, *txt2,*txt3; char *c;
   	printf("starting \n");
   	txt1 = create_text();
   	txt2 = create_text();
	txt3 = create_text();
   	append_line(txt1, "line one" );
   	if( (temp = length_text(txt1)) != 1)
   	{  
		printf("Test 1: length should be 1, is %d\n", temp); exit(-1);
   	}
   	append_line(txt1, "line hundred" );
   	insert_line(txt1, 2, "line ninetynine" );
   	insert_line(txt1, 2, "line ninetyeight" );
   	insert_line(txt1, 2, "line ninetyseven" );
   	insert_line(txt1, 2, "line ninetysix" );
   	insert_line(txt1, 2, "line ninetyfive" );
   	for( i = 2; i <95; i++ )
     		insert_line(txt1, 2, "some filler line between 1 and 95" );
   	if( (temp = length_text(txt1)) != 100)
   	{  
		printf("Test 2: length should be 100, is %d\n", temp); exit(-1);
   	}
   	printf("found at line 1:   %s\n",get_line(txt1,  1));
   	printf("found at line 2:   %s\n",get_line(txt1,  2));
   	printf("found at line 99:  %s\n",get_line(txt1, 99));
   	printf("found at line 100: %s\n",get_line(txt1,100));
   	for(i=1; i<=10000; i++)
   	{  
		if( i%2==1 )
        		append_line(txt2, "A");
      		else 
        		append_line(txt2, "B");
   	}
   	if( (temp = length_text(txt2)) != 10000)
   	{  
		printf("Test 3: length should be 10000, is %d\n", temp); exit(-1);
   	}
   	c = get_line(txt2, 9876 );
   	if( *c != 'B')
     	{  
		printf("Test 4: line 9876 of txt2 should be B, found %s\n", c); exit(-1);
   	}
   	for( i= 10000; i > 1; i-=2 )
   	{  
		c = delete_line(txt2, i);
      		if( *c != 'B')
      		{  
			printf("Test 5: line %d of txt2 should be B, found %s\n", i, c); exit(-1);
      		}
      		append_line( txt2, c );
   	}
   	for( i=1; i<= 5000; i++ )
   	{  
		c = get_line(txt2, i);
      		if( *c != 'A')
      		{  
			printf("Test 6: line %d of txt2 should be A, found %s\n", i, c); exit(-1);
      		}
   	}
   	for( i=1; i<= 5000; i++ )
     		delete_line(txt2, 1 );
   	for( i=1; i<= 5000; i++ )
   	{  
		c = get_line(txt2, i);
      		if( *c != 'B')
      		{  
			printf("Test 7: line %d of txt2 should be B, found %s\n", i, c); exit(-1);
      		}
   	}
   	set_line(txt1, 100, "the last line");
   	for( i=99; i>=1; i-- )
     		delete_line(txt1, i );
   	printf("found at the last line:   %s\n",get_line(txt1,  1));
	for(i=0; i<1000000; i++)
	     append_line(txt3, "line" );   
	   if( (temp = length_text(txt3)) != 1000000)
	   {  printf("Test 8: length should be 1000000, is %d\n", temp); exit(-1);
	   }
	   for(i=0; i<500000; i++)
	     delete_line(txt3, 400000 );   
	   if( (temp = length_text(txt3)) != 500000)
	   {  printf("Test 9: length should be 500000, is %d\n", temp); exit(-1);
	   }
	   printf("End of tests\n");
}
