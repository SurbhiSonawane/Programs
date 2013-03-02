#include<iostream>
#include<string>
#include <fstream>  //for file operations
#include <locale>
#include<cctype>
#include "header_bst.h"
using namespace std;
static const int red   = 0;
static const int black = 1;
template<class T>
class RBT;
template<class T>
class RBTnode :public TreeNode<T>
{
  public:
  RBTnode<T>*left_child;
  RBTnode<T>*right_child;
  RBTnode<T>*parent;
  T*key_pntr;
  int colour;
  bool operator == (RBTnode<T> &node);
  bool operator < (RBTnode<T> &node);
  bool operator >(RBTnode<T> &node);
  friend class RBT<T>;
  friend class IndexEntry;
 
};
template<class T>
class RBT:public BST<T>
{  
  public:
  RBTnode<T>*root;
  RBTnode<T>*nil;
  RBT()
  {
    nil=new RBTnode<T>;
    nil->parent=NULL;
    nil->left_child=NULL;
    nil->right_child=NULL;
    nil->colour=black;
    nil->key_pntr=NULL;
    root=nil;
  }
  T*insert(T*datap);
  RBTnode<T>*search2(T*datap);
  T*search(T*datap);
  T*Min();
  T*Max();
  T*InOrderSucc(T*datap);
  T*InOrderPred(T*datap);
  void Delete(T*datap);
  int BlackHeight(T *x);
  void leftRotate(RBTnode<T> *x);
  void rightRotate(RBTnode<T> *x);
  int PrintInOrder();
  int PrintPostOrder();
  int PrintPreOrder();
  void inorder(RBTnode<T>*pntr);
  void preorder(RBTnode<T>*pntr);
  void postorder(RBTnode<T>*pntr);
  int Height();
  int height_finding(RBTnode<T>*pntr);
  friend class RBTnode<T>;
  friend class IndexEntry;
};
template<class T>
RBTnode<T>* RBT<T>::search2(T*datap)
{
  RBTnode<T>*newnode_pntr=new RBTnode<T>;
  newnode_pntr->key_pntr= new T;
  *(newnode_pntr->key_pntr)=*datap;
  RBTnode<T>*pntr=root;
  while(pntr!=nil)
  {
    if(*pntr==*newnode_pntr)
      return pntr;
    else if(*newnode_pntr<(*pntr))
      pntr=pntr->left_child;
    else
      pntr=pntr->right_child;
  }
  return NULL;
}
template<class T>
T* RBT<T>::search(T*datap)
{
  RBTnode<T>*newnode_pntr=new RBTnode<T>;
  newnode_pntr->key_pntr= new T;
  *(newnode_pntr->key_pntr)=*datap;
  RBTnode<T>*pntr=root;
  while(pntr!=nil)
  {
    if(*pntr==*newnode_pntr)
    { 
      return pntr->key_pntr;
    }
    else if(*newnode_pntr<(*pntr))
      pntr=pntr->left_child;
    else
      pntr=pntr->right_child;
  }
  return NULL;
}
template<class T>
T* RBT<T>:: insert(T *datap)
{
  RBTnode<T>*newnode_pntr=new RBTnode<T>;
  newnode_pntr->parent=nil;
  newnode_pntr->left_child=nil;
  newnode_pntr->right_child=nil;
  newnode_pntr->colour=red;
  newnode_pntr->key_pntr= new T;
  *(newnode_pntr->key_pntr)=*datap;
  T*find_pntr=search(newnode_pntr->key_pntr);
  if(find_pntr!=NULL)
    return find_pntr;
  RBTnode<T>*pntr=root;
  RBTnode<T>*prev=nil;
  while(pntr!=nil)
  {
    prev=pntr;
    if(*newnode_pntr<*pntr)
      pntr=pntr->left_child;
    else
      pntr=pntr->right_child;
   }
  newnode_pntr->parent=prev;
  if(prev==nil)
    root=newnode_pntr;
  else if(*newnode_pntr<(*prev))
    prev->left_child=newnode_pntr;
  else
    prev->right_child=newnode_pntr;
  RBTnode<T>*node_pntr=newnode_pntr;
  RBTnode<T>*y2=nil;
  while(newnode_pntr->parent->colour==red)
  {
    if(newnode_pntr->parent==newnode_pntr->parent->parent->left_child)
    {
      y2=newnode_pntr->parent->parent->right_child;
      if(y2->colour==red)
      {
        newnode_pntr->parent->colour=black;
        y2->colour=black;
        newnode_pntr->parent->parent->colour=red;
        newnode_pntr=newnode_pntr->parent->parent;
      }
      else 
      {
        if(newnode_pntr==newnode_pntr->parent->right_child)
        {
          newnode_pntr=newnode_pntr->parent;
          leftRotate(newnode_pntr);
        }
        newnode_pntr->parent->colour=black;
        newnode_pntr->parent->parent->colour=red;
        rightRotate(newnode_pntr->parent->parent);
      }
    }
    else
    {
      y2=newnode_pntr->parent->parent->left_child;
      if(y2->colour==red)
      {
        newnode_pntr->parent->colour=black;
        y2->colour=black;
        newnode_pntr->parent->parent->colour=red;
        newnode_pntr=newnode_pntr->parent->parent;
      }
      else 
      {
        if(newnode_pntr==newnode_pntr->parent->left_child)
        {
          newnode_pntr=newnode_pntr->parent;
          rightRotate(newnode_pntr);
        }
        newnode_pntr->parent->colour=black;
        newnode_pntr->parent->parent->colour=red;
        leftRotate(newnode_pntr->parent->parent);  
      }
    }
  }
  root->colour=black;
  
  return node_pntr->key_pntr;
}
template<class T>
void RBT<T>::leftRotate(RBTnode<T> *x)
{ 
  RBTnode<T>*y=x->right_child;
  x->right_child=y->left_child;
  if(y->left_child!=nil && y->left_child!=NULL)
    y->left_child->parent=x;
  y->parent=x->parent;
  if(x->parent==nil)
    root=y;
  else if(x==x->parent->left_child)
    x->parent->left_child=y;
  else
    x->parent->right_child=y;
  y->left_child=x;
  x->parent=y;
}
template<class T>
void RBT<T>::rightRotate(RBTnode<T> *x)
{ 
  RBTnode<T>*y=x->left_child;
  x->left_child=y->right_child;
  if(y->right_child!=nil)
    y->right_child->parent=x;
  y->parent=x->parent;
  if(x->parent==nil)
    root=y;
  else if(x==x->parent->right_child)
    x->parent->right_child=y;
  else
    x->parent->left_child=y;
  y->right_child=x;
  x->parent=y;
}
template<class T>
bool RBTnode<T>::operator ==(RBTnode<T> &node)
{
  if(*(this->key_pntr)==*(node.key_pntr))
    return true;
  return false;
}
template<class T>
bool RBTnode<T>:: operator <(RBTnode<T> &node)
{
  if(*(this->key_pntr)<*(node.key_pntr))
    return true;
  return false;
}
template<class T>
bool RBTnode<T>:: operator >(RBTnode<T> &node)
{
  if(*(this->key_pntr)>*(node.key_pntr))
    return true;
  return false;
}
template<class T>
int RBT<T>::PrintInOrder()
{
  if(root==nil)
  {
    cout<<"Tree is empty\n";
    return 0;  
  }
  inorder(root);
  return 0;
}
template<class T>
void RBT<T>::inorder(RBTnode<T>*pntr)
{
  if(pntr!=nil)
  {
    inorder(pntr->left_child);
    cout<<*(pntr->key_pntr)<<"\t"<<pntr->colour<<"\n";
    inorder(pntr->right_child);
  }
}
template<class T>
void RBT<T>::Delete(T*datap)
{
  RBTnode<T> *x,*y;
  int check=0;
  RBTnode<T>* node =search2(datap);
  if(node==NULL) 
  {
    cout<<"Element not present in the BST\n";
    check=1;
  }
  if(node==root && node->left_child==nil && node->right_child==nil)
  {
    cout<<"element successfully deleted\n";
    root=nil;
    check=1;
  }
  if(check!=1) 
  {
    if(node->left_child==nil || node->right_child==nil)
      y=node;
    else
      y=search2(InOrderSucc(node->key_pntr));
      //finding the inorder successor of the node that has to be deleted(in case of node having 2 children).
    if(y->left_child!=nil)
      x=y->left_child;
    else
      x=y->right_child;
    if(x!=nil && x!=root && y!=root)
      x->parent=y->parent;
    if(y->parent==nil)
    {
      root=x;
      x->parent=nil;
    }
    else if(y==(y->parent)->left_child )
      (y->parent)->left_child=x;
    else if(y==(y->parent)->right_child)
      (y->parent)->right_child=x;
    if(y!=node)
    {
      //swapping the contents of the node to be deleted and its successor
      *(node->key_pntr)=*(y->key_pntr); 
      if(node->right_child==y)
      node->right_child=y->right_child;
    }
    cout<<"Element successfully deleted\n";
  }
  RBTnode<T>*w;
  if(node!=NULL && node->colour==black && root!=nil)
  {
    while(x!=root && x->colour==black && x!=nil)
    {
      if(x==x->parent->left_child)
      {
        w=x->parent->right_child;
        if(w->colour==red)
        {
          w->colour=black;
          x->parent->colour=red;
          leftRotate(x->parent);
          w=x->parent->right_child;
        }
        if(w->left_child->colour==black && w->right_child->colour==black)
        {
          w->colour=red;
          x=x->parent;
        }
        else 
        {
          if (w->right_child->colour==black)
          {
            w->left_child->colour=black;
            w->colour=red;
            rightRotate(w);
            w=x->parent->right_child;
          }
          w->colour=x->parent->colour;
          x->parent->colour=black;
          w->right_child->colour=black;
          leftRotate(x->parent);
          x=root;
        }
      }
      else
      {
        w=x->parent->left_child;
        if(w->colour==red)
        {
          w->colour=black;
          x->parent->colour=red;
          rightRotate(x->parent);
          w=x->parent->left_child;
        }
        if(w->right_child->colour==black && w->left_child->colour==black)
        {
          w->colour=red;
          x=x->parent;
        }
        else 
        {
          if (w->left_child->colour==black)
          {
            w->right_child->colour=black;
            w->colour=red;
            leftRotate(w);
            w=x->parent->left_child;
          }
          w->colour=x->parent->colour;
          x->parent->colour=black;
          w->left_child->colour=black;
          rightRotate(x->parent);
          x=root;
        } 
      }
    }
    if(x!=NULL)
      x->colour=black; 
  }
}
template<class T>
T*RBT<T>::Min()
{
  if(root==nil)
  {
    cout<<"Tree is empty\n";
    return NULL;
  }
  RBTnode<T>*pntr=root;
  RBTnode<T>*prev=pntr;
  while(pntr!=nil)
  {
    prev=pntr;
    pntr=pntr->left_child;
  }
  return prev->key_pntr;
}
template<class T>
T*RBT<T>::Max()
{
  if(root==nil)
  {
    cout<<"Tree is empty\n";
    return NULL;
  }
  RBTnode<T>*pntr=root;
  RBTnode<T>*prev=pntr;
  while(pntr!=nil)
  {
    prev=pntr;
    pntr=pntr->right_child;
  }
  return prev->key_pntr;
}
template<class T>
T*RBT<T>::InOrderSucc(T*datap)
{
  RBTnode<T>* node =search2(datap);
  RBTnode<T>*prev;
  if(node==NULL||(node->right_child==nil && node->parent== nil))
  {
    cout<<"No successor\n";
    return NULL;
  }
  if(node->right_child!=nil)
  {
    RBTnode<T>* pntr=node->right_child;
    prev=pntr;
    while(pntr!=nil)
    {
      prev=pntr;
      pntr=pntr->left_child;
    }
    return prev->key_pntr;
  }
  RBTnode<T>* pa=node->parent;
  prev=pa;
  while(pa!=nil && node==pa->right_child)
  {
    prev=pa;
    node=pa;
    pa=node->parent;
  }
    if(prev!=nil && node==prev->left_child)
      return prev->key_pntr;
  else 
  {
    cout<<"No Successor\n";
    return NULL;
  }
}
template<class T>
T*RBT<T>::InOrderPred(T*datap)
{
  RBTnode<T>* node =search2(datap);
  RBTnode<T>*prev;
  if(node==NULL||(node->left_child==nil && node->parent== nil))
  {
    cout<<"No Predecessor\n";
    return NULL;
  }
  if(node->left_child!=nil)
  {
    RBTnode<T>* pntr=node->left_child;
    prev=pntr;
    while(pntr!=nil)
    {
      prev=pntr;
      pntr=pntr->right_child;
    }
    return prev->key_pntr;
  }
  RBTnode<T>* pa=node->parent;
  prev=pa;
  while(pa!=nil && node==pa->left_child)
  {
    prev=pa;
    node=pa;
    pa=node->parent;
  }
  if(prev!=nil && node==prev->right_child)
      return prev->key_pntr;
  else 
  {
    cout<<"No Predecessor\n";
    return NULL;
  }
}
template<class T>
int RBT<T>::PrintPostOrder()
{
  if(root==nil)
  {
    cout<<"Tree is empty\n";
    return 0;  
  }
  postorder(root);
  return 0;
}
template<class T>
void RBT<T>::postorder(RBTnode<T>*pntr)
{
  if(pntr!=nil)
  {
    postorder(pntr->left_child);
    postorder(pntr->right_child);
    cout<<*(pntr->key_pntr)<<"\t"<<pntr->colour<<"\n";
  }
}
template<class T>
int RBT<T>::PrintPreOrder()
{
  if(root==nil)
  {
    cout<<"Tree is empty\n";
    return 0;  
  }
  preorder(root);
  return 0;
}
template<class T>
void RBT<T>::preorder(RBTnode<T>*pntr)
{
  if(pntr!=nil)
  {
    cout<<*(pntr->key_pntr)<<"\t"<<pntr->colour<<"\n";
    preorder(pntr->left_child);
    preorder(pntr->right_child);
  }
}
template<class T>
int RBT<T>::Height()
{
  if(root==nil)
  {
    cout<<"Tree is empty\n";
    return -1;
  }
  int h;
  h=height_finding(root);
  return h;
}
template<class T>
int RBT<T>::height_finding(RBTnode<T>*pntr)
{
    if (pntr==NULL)
      return -1;
    if (height_finding(pntr->left_child)>height_finding(pntr->right_child))
      return 1+height_finding(pntr->left_child);
    else
      return 1+height_finding(pntr->right_child);
}
template<class T>
int RBT<T>::BlackHeight(T *x)
{
  if(root==nil)
  { 
    cout<<"Tree is empty\n";
    return 0;
  }
  RBTnode<T>*pntr=search2(x);
  if(pntr==NULL)
  { 
    cout<<"element not found\n";
    return -10;
  }
  int height=0;
  while(pntr!=nil)
  {
    if(pntr->colour==black)
      height++;
    pntr=pntr->left_child;
  }
  return height;
}
  


