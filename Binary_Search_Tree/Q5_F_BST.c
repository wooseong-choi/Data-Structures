//////////////////////////////////////////////////////////////////////////////////

/* CE1007/CZ1007 Data Structures
Lab Test: Section F - Binary Search Trees Questions
Purpose: Implementing the required functions for Question 5
		 Implementing 'remove node' operation for BST*/
//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _bstnode{
	int item;
	struct _bstnode *left;
	struct _bstnode *right;
} BSTNode;   // You should not change the definition of BSTNode

typedef struct _stackNode{
	BSTNode *data;
	struct _stackNode *next;
}StackNode; // You should not change the definition of StackNode

typedef struct _stack
{
	StackNode *top;
}Stack; // You should not change the definition of Stack

///////////////////////// function prototypes ////////////////////////////////////

// You should not change the prototypes of these functions
void postOrderIterativeS2(BSTNode *root);

void insertBSTNode(BSTNode **node, int value);

void push(Stack *stack, BSTNode *node);
BSTNode *pop(Stack *s);
BSTNode *peek(Stack *s);
int isEmpty(Stack *s);
void removeAll(BSTNode **node);
BSTNode* removeNodeFromTree(BSTNode *root, int value);
void printTree(BSTNode *node);
///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	c = 1;

	//Initialize the Binary Search Tree as an empty Binary Search Tree
	BSTNode * root;
	root = NULL;

	printf("1: Insert an integer into the binary search tree;\n");
	printf("2: Print the post-order traversal of the binary search tree;\n");
	printf("3: remove haha;\n");
	printf("0: Quit;\n");


	while (c != 0)
	{
		printf("Please input your choice(1/2/3/0): ");
		scanf("%d", &c);

		switch (c)
		{
		case 1:
			printf("Input an integer that you want to insert into the Binary Search Tree: ");
			scanf("%d", &i);
			insertBSTNode(&root, i);
			break;
		case 2:
			printf("The resulting post-order traversal of the binary search tree is: ");
			postOrderIterativeS2(root); // You need to code this function
			printf("\n");
			break;
		case 3:
			printf("remove haha: ");
			scanf("%d", &i);
			removeNodeFromTree(root, i);
			printTree(root);
			break;
		case 0:
			removeAll(&root);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void postOrderIterativeS2(BSTNode *root)
{
	Stack stk;
	stk.top = NULL;
	Stack outputStk;
	outputStk.top = NULL;

	push(&stk, root);

	while(! isEmpty(&stk)){
		root = pop(&stk);
		push(&outputStk, root);
		if(root->left != NULL)
			push(&stk, root->left);
		if (root->right != NULL)
			push(&stk, root->right);
	}
	while (!isEmpty(&outputStk))
	{
		root = pop(&outputStk);
		printf("%d\n", root->item);
	}
	
}

/* Given a binary search tree and a key, this function
   deletes the key and returns the new root. Make recursive function. */
BSTNode* removeNodeFromTree(BSTNode *root, int value)
{	
	if(root == NULL){
		printf("root is null");
		return root;
	}
	// BSTNode *temp;
	// 안해!
	if(root->item == value){
		// printf("%s","뀨");
		if(root->left == NULL && root->right == NULL){
		// 경우 1 : 자식이 없는 노드 삭제의 경우
			free(root);
			return NULL;
		}
		else if (root->left != NULL && root->right != NULL){
		// 경우 2 : 자식 부자인 노드 삭제의 경우
			BSTNode *tempTwoC;
			tempTwoC = NULL;

			tempTwoC = root->right;
			
			while (tempTwoC->left != NULL)
			{
				tempTwoC = tempTwoC->left;
			}
			tempTwoC->left = root->left;	
			free(root);	// 동적할당 해제	
			root = tempTwoC;
			return root;
		}
		else{
		// 경우 3 : 자식 하나인 노드 삭제의 경우
			BSTNode *tempOneC = root;
			if(tempOneC->left != NULL){
				tempOneC = tempOneC->left;
				while(1){
					if( tempOneC->right != NULL){
						tempOneC = tempOneC->right;
					}else{
						free(root);
						root = tempOneC;
						break;
					}
				}
			}
			if(tempOneC->right != NULL){
				tempOneC = tempOneC->right;
				while(1){
					if( tempOneC->left != NULL){
						tempOneC = tempOneC->left;
					}else{
						free(root);
						root = tempOneC;
						break;
					}
				}
			}
		}
	}else{
		printf("트리 구조 확인 %d\n", root->item);
		if(root->item > value){
			root->left = removeNodeFromTree(root->left, value);
		}else{
			root->right = removeNodeFromTree(root->right, value);
		}
	}

	return root;

}

void printTree(BSTNode *node)
{
    if(node == NULL) return;

    printTree(node->left);
    printf("%d ",node->item);
    printTree(node->right);
}


///////////////////////////////////////////////////////////////////////////////

void insertBSTNode(BSTNode **node, int value){
	if (*node == NULL)
	{
		*node = malloc(sizeof(BSTNode));

		if (*node != NULL) {
			(*node)->item = value;
			(*node)->left = NULL;
			(*node)->right = NULL;
		}
	}
	else
	{
		if (value < (*node)->item)
		{
			insertBSTNode(&((*node)->left), value);
		}
		else if (value >(*node)->item)
		{
			insertBSTNode(&((*node)->right), value);
		}
		else
			return;
	}
}

//////////////////////////////////////////////////////////////////////////////////

void push(Stack *stack, BSTNode * node)
{
	StackNode *temp;

	temp = malloc(sizeof(StackNode));

	if (temp == NULL)
		return;
	temp->data = node;

	if (stack->top == NULL)
	{
		stack->top = temp;
		temp->next = NULL;
	}
	else
	{
		temp->next = stack->top;
		stack->top = temp;
	}
}


BSTNode * pop(Stack * s)
{
	StackNode *temp, *t;
	BSTNode * ptr;
	ptr = NULL;

	t = s->top;
	if (t != NULL)
	{
		temp = t->next;
		ptr = t->data;

		s->top = temp;
		free(t);
		t = NULL;
	}

	return ptr;
}

BSTNode * peek(Stack * s)
{
	StackNode *temp;
	temp = s->top;
	if (temp != NULL)
		return temp->data;
	else
		return NULL;
}

int isEmpty(Stack *s)
{
	if (s->top == NULL)
		return 1;
	else
		return 0;
}


void removeAll(BSTNode **node)
{
	if (*node != NULL)
	{
		removeAll(&((*node)->left));
		removeAll(&((*node)->right));
		free(*node);
		*node = NULL;
	}
}
