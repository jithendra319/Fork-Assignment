#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
struct Node {
    int data,childCount;
    struct Node* children[20];
};
 
struct Node* CreateNode(int data)
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->childCount = 0;
    return newNode;
}

struct Node* searchNode(struct Node* root,int node,int oddChild,int evenChild){
	if( root == NULL ){
		return NULL;
	}
	if( root->data == node ){
		return root;
	}
	int child;
	struct Node* temp;
	if( root->data %2 == 0 ){
		child = evenChild;
	}else{
		child = oddChild;
	}
	for(int j=0;j<child;j++){
		temp = searchNode(root->children[j],node,oddChild,evenChild);
		if(temp != NULL){
			return temp;
		}
	}
	return NULL;
}

void* InsertNode(struct Node* root, int data)
{
    struct Node* temp = CreateNode(data);
    if (root == NULL) {
        root = temp;
        return root;
    }
    root->children[root->childCount] = temp;
    root->childCount += 1;

}


void insertIntoNary(struct Node* root,int parent,int data,int oddChild,int evenChild){
	struct Node* insertIntoNode = searchNode(root,parent,oddChild,evenChild);	
	if(insertIntoNode != NULL){
		InsertNode(insertIntoNode,data);
		return;
	}else{
		printf("\n Node Not Found %d <-- parent %d <-- child\n",parent,data);
	}
}

void inorder(struct Node* temp,int oddChild,int evenChild)
{
    if ( temp == NULL )
        return;
    int childs; 
    if( temp->data %2 ==0 ){
    	childs = evenChild;
    }else{
    	childs = oddChild;
    }
    if( temp -> childCount == 0 ) {
    	printf("PID: %d \n",temp->data);
    }
    
    for(int i=0;i<temp->childCount;i++){
    	if( i == 1 ) {
    		printf("PID: %d \n",temp->data);
    	}
    	inorder(temp->children[i],oddChild,evenChild);
    }
    if(temp->childCount==1 && temp->childCount){
    	printf("PID: %d \n",temp->data);
    }
}

int getChild(int data,int oddChild,int evenChild){
	int childs; 
	if( data %2 == 0 ){
	    	childs = evenChild;
	}else{
    		childs = oddChild;
	}
	return childs;
}

void createNaryTree(int* queue,int front,int rear,int oddChild,int evenChild){
	int currentPid = getpid();
	struct Node* root = CreateNode(currentPid);
	int count = 0, i = 0,childs = getChild(currentPid,oddChild,evenChild);
	printf("\nINORDER TRAVERSAL OF PIDS ARE \n");
	for(int j = 0;j<childs;j++){
		insertIntoNary(root,currentPid,queue[count],oddChild,evenChild);
		count++;
	}
	while(i<=rear && count<=rear){
		childs = getChild(queue[i],oddChild,evenChild);
		for( int j = 0 ; j < childs && count<=rear ; j++ ){
			if( queue[count] != 0 ){
				insertIntoNary(root,queue[i],queue[count],oddChild,evenChild);
				count++;
			}
		}
		i++;
	}
	inorder(root,oddChild,evenChild);
}
 
