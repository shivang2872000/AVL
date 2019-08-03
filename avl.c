//reference taken from geeks for geek and datastructure through c book


#include<stdio.h>
#include<stdlib.h>


struct node
{
        int key;
        struct node *left;
        struct node *right;
        int balance;
};

struct node *root;



struct node* pred1(struct node *root, struct node* pred,int k)
{    if(root==NULL)
     return NULL;

 if(root->key==k)
 {

  if(root->left!=NULL)
  { struct node *tmp =root->left;
    while(tmp->right)
    tmp=tmp->right;

    pred=tmp;
  }
  return pred;
 }


 if(root->key<k)
 {pred=root;
  pred1(root->right,pred,k);
 }
 else
 {pred=root;
  pred1(root->left, pred, k);
 }

}

int balance(struct node *N)
{
        if (N == NULL)
                return 0;
        return N->balance;
}

struct node* succ1(struct node *root,struct node* succ, int k)
{    if(root==NULL)
 return NULL;

 if(root->key==k)
 {


 if(root->right !=NULL)
 { struct node *tmp =root->right;
    while(tmp->left)
    tmp=tmp->left;

     succ=tmp;
  }
 return succ;
 }

 if(root->key>k)
 {succ=root;
  succ1(root->left, succ, k);
 }
else
 {succ=root;
  succ1(root->right,succ,k);
 }
}
void search()
{ int k,z=0,j=0;
  printf("Enter the key\n");
  scanf("%d",&k);

  if(root==NULL)
   printf("Tree is Empty\n");

  else if(root!=NULL)
  { struct node *curr=root;

    while(curr!=NULL)
   { if(curr->key==k)
     {z=z+1;
      break;
     }
     else if(curr->key<k)
     {curr=curr->right;
      j=j+1;}
     else
     {curr=curr->left;
      j=j+1;}
   }

   if(z==1)
   printf("Node found\n");
   else
 printf("NO node found\n");
  }

}

void inorder(struct node* temp)
{
    if (temp == NULL)
        return;


    inorder(temp->left);

    printf("%d ",temp->key);
    inorder(temp->right);
}

void levelorder(struct node* root)
{
    int h = balance(root);
    int i;
    for (i=0; i<=h; i++)
        givenlevel(root, i);
}


void givenlevel(struct node* root, int level)
{
    if (root == NULL)
        return;
    if (level == 0)
        printf("%d ", root->key);
    else if (level > 0)
    {
        givenlevel(root->left, level-1);
        givenlevel(root->right, level-1);
    }
}
void preorder(struct node* temp)
{
    if (temp == NULL)
        return;


    printf("%d ",temp->key);

    preorder(temp->left);


  preorder(temp->right);
}
void postorder(struct node* temp)
{
    if (temp == NULL)
        return;
    postorder(temp->left);


    postorder(temp->right);

    printf("%d ",temp->key);
}






int max(int a, int b)
{
        return (a > b)? a : b;
}


struct node* newnode(int key)
{
        struct node* node = (struct node*)
                                                malloc(sizeof(struct node));
        node->key = key;
        node->left = NULL;
        node->right = NULL;
        node->balance = 1;
        return node;
}

struct node *rightRotate(struct node *y)
{
        struct node *x = y->left;
        struct node *T2 = x->right;


        x->right = y;
        y->left = T2;

        y->balance = max(balance(y->left), balance(y->right))+1;
        x->balance = max(balance(x->left), balance(x->right))+1;

        return x;
}

struct node *leftrotate(struct node *x)
{
        struct node *y = x->right;
 struct node *T2 = y->left;

        y->left = x;
        x->right = T2;


        x->balance = max(balance(x->left), balance(x->right))+1;
        y->balance = max(balance(y->left), balance(y->right))+1;

        return y;
}

int getbalance(struct node *N)
{
        if (N == NULL)
                return 0;
        return balance(N->left) - balance(N->right);
}


struct node* insert(struct node* node, int key)
{
                   if (node == NULL)
                return(newnode(key));

        if (key < node->key)
                node->left = insert(node->left, key);
        else if (key > node->key)
                node->right = insert(node->right, key);
        else
                return node;


        node->balance = 1 + max(balance(node->left),
                                                balance(node->right));
        int balance = getbalance(node);


        if (balance > 1 && key < node->left->key)
                return rightRotate(node);


        if (balance < -1 && key > node->right->key)
                return leftrotate(node);


        if (balance > 1 && key > node->left->key)
        {
                node->left = leftrotate(node->left);
                return rightRotate(node);
        }

 if (balance < -1 && key < node->right->key)
        {
                node->right = rightRotate(node->right);
                return leftrotate(node);
        }


        return node;
}



int balancetree( struct node *n1)
{ int lht,rht;
  if(n1==NULL)
  return 0;

  else
  { lht=balancetree(n1->left);
    rht=balancetree(n1->right);

    if(lht>=rht)
    return lht+1;
    else
    return rht+1;
  }
}


void balancenode()
{ int key,z=0,x;
  printf("Enter the key\n");
  scanf("%d",&key);

  if(root==NULL)
  printf("Tree is Empty\n");

 else{
  struct node *curr=root;

  while(curr!=NULL)
  { if(curr->key==key)
   {z=z+1;
    break;}

   else if(curr->key<=key)
   curr=curr->right;
   else
   curr=curr->left;

  }

 if(z==0)
   printf("node not found\n");
   else if(z==1)
   {x=balancetree(curr);
    printf("node is at balance %d\n",x-1);}
   }
}

void depth()
{ int key,j=0,z=0;
  printf("Enter the key\n");
  scanf("%d",&key);

  if(root==NULL)
  printf("Tree is Empty\n");

 else{
  struct node *curr=root;

  while(curr!=NULL)
  { if(curr->key==key)
   {z=z+1;
    break;}

   else if(curr->key<=key)
   { curr=curr->right;
    j=j+1;}

   else
   { curr=curr->left;
     j=j+1;
   }
  }

   if(z==0)
   printf("node not found\n");
   else if(z==1)
   printf("node is at depth %d\n",j);
 }

}
struct node * minimum(struct node* node)
{
    struct node* current = node;


    while (current->left != NULL)
        current = current->left;

    return current;
}

struct node* deletenode(struct node* root, int key)
{


    if (root == NULL)
        return root;


    if ( key < root->key )
        root->left = deletenode(root->left, key);

    else if( key > root->key )
        root->right = deletenode(root->right, key);

    else
    {

        if( (root->left == NULL) || (root->right == NULL) )
        {
                             struct node *temp = root->left ? root->left :
                                             root->right;


            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
             *root = *temp;
            free(temp);
        }
        else
        {

            struct node* temp = minimum(root->right);

            root->key = temp->key;

            root->right = deletenode(root->right, temp->key);
        }
    }

    if (root == NULL)
      return root;

    root->balance = 1 + max(balance(root->left),
                           balance(root->right));


    int balance = getbalance(root);

                                if (balance > 1 && getbalance(root->left) >= 0)
        return rightRotate(root);


    if (balance > 1 && getbalance(root->left) < 0)
    {
        root->left =  leftrotate(root->left);
        return rightRotate(root);
    }


    if (balance < -1 && getbalance(root->right) <= 0)
        return leftrotate(root);

    if (balance < -1 && getbalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftrotate(root);
    }

    return root;
}

struct node* lca(struct node *n1,int k1,int k2)
{   if(n1==NULL)
    return NULL;

    if(n1->key<k1 && n1->key<k2)
    return lca(n1->right,k1,k2);

    if(n1->key>k1 && n1->key>k2)
    return lca(n1->left,k1,k2);

    return n1;
}

int main()
{
 root = NULL;
 struct node *temp;
  int i,d,f,k1,k2,z;

                             for(i=1;;i++)
  { printf("1)Insert\n");
    printf("2)Search\n");
    printf("3)Delete\n");
    printf("4)Inorder\n");
    printf("5)Preoder\n");
    printf("6)Postorder\n");
    printf("7)Depth\n");
    printf("8)balance of Tree\n");
    printf("9)balance of Node\n");
                                   printf("10)LCA\n");
    printf("11)Level Order\n");
    printf("12)Predecessor\n");
    printf("13)Successor\n");
    printf("14)exit\n");
    scanf("%d",&d);
    if(d==1)
   {printf("Please enter key\n");
    scanf("%d",&f);
    root = insert(root, f);
   }
    else if(d==2)
    search();
    else if(d==3)
   {printf("Please enter key\n");
    scanf("%d",&f);
    root = deletenode(root, f);
   }

    else if(d==4)
    {inorder(root);
     printf("\n");}
   else if(d==5)
    {preorder(root);
     printf("\n");}
   else if(d==6)
    {postorder(root);
     printf("\n");}
   else if(d==7)
   depth();
   else if(d==8)
   {z=balancetree(root);
    printf("balance of Tree is:%d\n",z-1);
   }
   else if(d==9)
   balancenode();
   else if(d==10)
  { printf("Enter k1 and k2\n");
    scanf("%d%d",&k1,&k2);
    temp=lca(root,k1,k2);
    printf("LCA is %d\n",temp->key);
  }

   else if(d==11)
   {printf("Level Order traversal of binary tree is \n");
    levelorder(root);
    printf("\n");
   }
   else if(d==12)
   { struct node* pred=NULL;
     struct node *temp;
     printf("Please enter key\n");
 scanf("%d",&z);
     temp=pred1(root,pred,z);

     if(temp!=NULL)
     printf("Predecessor: %d\n",temp->key);
     else
     printf("No predecessor\n");
   }

   else if(d==13)
   { struct node* succ=NULL;
     struct node *temp;
     printf("Please enter key\n");
     scanf("%d",&z);
     temp=succ1(root,succ,z);
                                   if(temp!=NULL)
     printf("successor: %d\n",temp->key);
     else
     printf("No successor\n");
   }
   if(d=14)
   break;

   else
   break;
  }




return 0;
}
