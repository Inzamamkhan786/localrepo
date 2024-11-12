#include<stdio.h>
#include<stdlib.h>

struct node{
    int key;
    struct node*left;
    struct node*right;
    int height;
};

struct node*insert(struct node*root,int key);
struct node*createNode(int key);
int max(int a,int b);
int getHeight(struct node*root);
int balanceFactor(struct node*root);
struct node*rightRotate(struct node*y);
struct node*leftRotate(struct node*x);
void inorder(struct node*root);



int max(int a,int b){
    if(a>b){
        return a ;
    }else{
        return b;
    }
}

int getHeight(struct node*root){
    if(root==NULL){
        return 0;
    }else{
        return root->height;
    }
    
}

int balanceFactor(struct node*root){
    if(root==NULL){
        return 0;
    }else{
        return (getHeight(root->left) - getHeight(root->right));
    }
}


struct node*rightRotate(struct node*y){
    struct node*x = y->left;
    struct node*T2 = x->right;

    x->right = y;
    y->left = T2;
    x->height = max(getHeight(x->left),getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left),getHeight(y->right)) + 1;
    return x;
}

struct node*leftRotate(struct node*x){
    struct node*y = x->right;
    struct node*T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left),getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left),getHeight(y->right)) + 1;
    return y;
}




int main(){
struct node*root=NULL;
root = insert(root,100);
root = insert(root,150);
root = insert(root,50);
root = insert(root,25);
root = insert(root,75);
root = insert(root,65);
root = insert(root,125);
root = insert(root,85);
root = insert(root,175);

inorder(root);

    return 0;
}

struct node*insert(struct node*root,int key){
    if(root==NULL){
        return createNode(key);
    }
    if(key<root->key){
        root->left = insert(root->left,key);
    }else if(key>root->key){
        root->right = insert(root->right,key);
    }
    return root;

    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    int bf = balanceFactor(root);

    //Left Left case;
    if(bf>1 && key<root->left->key){
        return rightRotate(root);
    }

    //Right Right case;
    if(bf<-1 && key>root->right->key){
        return leftRotate(root);
    }

    //Left Right case;
    if(bf>1 && key>root->left->key){
        root->left = leftRotate(root);
        return rightRotate(root);
    }
    //Right Left case;
    if(bf<-1 && key<root->right->key){
        root->right = rightRotate(root);
        return leftRotate(root);
    }
return root;

}


struct node*createNode(int key){
    struct node*newNode = (struct node*)malloc(sizeof(struct node));
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    newNode->key = key;
    return newNode;
}


void inorder(struct node*root){
    if(root==NULL){
        return;
    }else{
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}