#include<iostream>
#include<string>
#include <fstream>  //for file operations
#include <locale>
#include<cctype>
using namespace std;
template<class T>
class BST;
template<class T>
class TreeNode
{  public:
  TreeNode<T>*left_child;
  TreeNode<T>*right_child;
  TreeNode<T>*parent;
  T*key_pntr;
  TreeNode()
  {
    left_child=NULL;
    right_child=NULL;
    parent=NULL;
    key_pntr=NULL;
  }
  friend class BST<T>;
  friend class IndexEntry;
  bool operator == (TreeNode<T> &node);
  bool operator < (TreeNode<T> &node);
  bool operator >(TreeNode<T> &node);
};

template<class T>
bool TreeNode<T>::operator ==(TreeNode<T> &node)
{
  if(*(this->key_pntr)==*(node.key_pntr))
    return true;
  return false;
}
template<class T>
bool TreeNode<T>:: operator <(TreeNode<T> &node)
{
  if(*(this->key_pntr)<*(node.key_pntr))
    return true;
  return false;
}
template<class T>
bool TreeNode<T>:: operator >(TreeNode<T> &node)
{
  if(*(this->key_pntr)>*(node.key_pntr))
    return true;
  return false;
}
template<class T>
class BST
{  public:
  TreeNode<T>*root;
  BST()
  {
    root=NULL;
  }
  virtual TreeNode<T>*search2(T*datap);
  virtual T*search(T*datap);
  virtual T*insert(T*datap);
  virtual T*Min();
  virtual T*Max();
  virtual T*InOrderSucc(T*datap);
  virtual T*InOrderPred(T*datap);
  virtual void Delete(T*datap);
  virtual int PrintPostOrder();
  virtual int PrintPreOrder();
  virtual int PrintInOrder();
  virtual int Height();
  virtual void inorder(TreeNode<T>*pntr);
  virtual void preorder(TreeNode<T>*pntr);
  virtual void postorder(TreeNode<T>*pntr);
  virtual int height_finding(TreeNode<T>*pntr);
  friend class TreeNode<T>;
  friend class IndexEntry;
};

template<class T>
TreeNode<T>* BST<T>::search2(T*datap)
{
  TreeNode<T>*newnode_pntr=new TreeNode<T>;
  newnode_pntr->key_pntr= new T;
  *(newnode_pntr->key_pntr)=*datap;
  TreeNode<T>*pntr=root;
  while(pntr!=NULL)
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
T* BST<T>::search(T*datap)
{
  TreeNode<T>*newnode_pntr=new TreeNode<T>;
  newnode_pntr->key_pntr= new T;
  *(newnode_pntr->key_pntr)=*datap;
  TreeNode<T>*pntr=root;
  while(pntr!=NULL)
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
T* BST<T>::insert(T*datap)
{
  TreeNode<T>*newnode_pntr=new TreeNode<T>;
  newnode_pntr->key_pntr= new T;
  *(newnode_pntr->key_pntr)=*datap;
  T*find_pntr=search(newnode_pntr->key_pntr);
  if(find_pntr!=NULL)
    return find_pntr;
  TreeNode<T>*pntr=root;
  TreeNode<T>*prev=pntr;
  while(pntr!=NULL)
  {
    prev=pntr;
    if(*newnode_pntr<*pntr)
      pntr=pntr->left_child;
    else
      pntr=pntr->right_child;
   }
  newnode_pntr->parent=prev;
  if(prev==NULL)
    root=newnode_pntr;
  else if(*newnode_pntr<(*prev))
    prev->left_child=newnode_pntr;
  else
    prev->right_child=newnode_pntr;
  return newnode_pntr->key_pntr;
}
template<class T>
T*BST<T>::Min()
{
  TreeNode<T>*pntr=root;
  TreeNode<T>*prev=pntr;
  while(pntr!=NULL)
  {
    prev=pntr;
    pntr=pntr->left_child;
  }
  return prev->key_pntr;
}
template<class T>
T*BST<T>::Max()
{
  TreeNode<T>*pntr=root;
  TreeNode<T>*prev=pntr;
  while(pntr!=NULL)
  {
    prev=pntr;
    pntr=pntr->right_child;
  }
  return prev->key_pntr;
}
template<class T>
T*BST<T>::InOrderSucc(T*datap)
{
  TreeNode<T>* node =search2(datap);
  TreeNode<T>*prev;
  if(node->right_child==NULL && node->parent== NULL)
  {
    cout<<"No successor\n";
    return NULL;
  }
  if(node->right_child!=NULL)
  {
    TreeNode<T>* pntr=node->right_child;
    prev=pntr;
    while(pntr!=NULL)
    {
      prev=pntr;
      pntr=pntr->left_child;
    }
    return prev->key_pntr;
  }
  TreeNode<T>* pa=node->parent;
  prev=NULL;
  while(pa!=NULL && node==pa->right_child)
  {
    prev=pa;
    node=pa;
    pa=node->parent;
  }
    if(prev!=NULL && node==prev->right_child)
      return prev->key_pntr;
  else 
  {
    cout<<"No Successor\n";
    return NULL;
  }
}
template<class T>
T*BST<T>::InOrderPred(T*datap)
{
  TreeNode<T>* node =search2(datap);
  TreeNode<T>*prev;
  if(node->left_child==NULL && node->parent== NULL)
  {
    cout<<"No Predecessor\n";
    return NULL;
  }
  if(node->left_child!=NULL)
  {
    TreeNode<T>* pntr=node->left_child;
    prev=pntr;
    while(pntr!=NULL)
    {
      prev=pntr;
      pntr=pntr->right_child;
    }
    return prev->key_pntr;
  }
  TreeNode<T>* pa=node->parent;
  prev=NULL;
  while(pa!=NULL && node==pa->left_child)
  {
    prev=pa;
    node=pa;
    pa=node->parent;
  }
  if(prev!=NULL && node==prev->left_child)
      return prev->key_pntr;
  else 
  {
    cout<<"No Predecessor\n";
    return NULL;
  }
}
template<class T>
void BST<T>::Delete(T* datap)
{
  TreeNode<T> *x,*y;
  int check=0;
  TreeNode<T>* node =search2(datap);
  if(node==NULL) 
  {
    cout<<"Element not present in the BST\n";
    check=1;
  }
  if(node==root && node->left_child==NULL && node->right_child==NULL)
  {
    cout<<"element successfully deleted\n";
    root=NULL;
    check=1;
  }
  if(check!=1) 
  {
    if(node->left_child==NULL || node->right_child==NULL)
      y=node;
    else
      y=search2(InOrderSucc(node->key_pntr));
      //finding the inorder successor of the node that has to be deleted(in case of node having 2 children).
    if(y->left_child!=NULL)
      x=y->left_child;
    else
      x=y->right_child;
    if(x!=NULL && x!=root && y!=root)
      x->parent=y->parent;
    if(y->parent==NULL)
    {
      root=x;
      x->parent=NULL;
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
}
template<class T>
int BST<T>::PrintInOrder()
{
  if(root==NULL)
  {
    cout<<"Tree is empty\n";
    return 0;  
  }
  inorder(root);
  return 0;
}
template<class T>
void BST<T>::inorder(TreeNode<T>*pntr)
{
  if(pntr!=NULL)
  {
    inorder(pntr->left_child);
    cout<<*(pntr->key_pntr)<<"\n";
    inorder(pntr->right_child);
  }
}
template<class T>
int BST<T>::PrintPostOrder()
{
  if(root==NULL)
  {
    cout<<"Tree is empty\n";
    return 0;  
  }
  postorder(root);
  return 0;
}
template<class T>
void BST<T>::postorder(TreeNode<T>*pntr)
{
  if(pntr!=NULL)
  {
    postorder(pntr->left_child);
    postorder(pntr->right_child);
    cout<<*(pntr->key_pntr)<<"\n";
  }
}
template<class T>
int BST<T>::PrintPreOrder()
{
  if(root==NULL)
  {
    cout<<"Tree is empty\n";
    return 0;  
  }
  preorder(root);
  return 0;
}
template<class T>
void BST<T>::preorder(TreeNode<T>*pntr)
{
  if(pntr!=NULL)
  {
    cout<<*(pntr->key_pntr)<<"\n";
    preorder(pntr->left_child);
    preorder(pntr->right_child);
  }
}
template<class T>
int BST<T>::Height()
{
  if(root==NULL)
  {
    cout<<"Tree is empty\n";
    return -1;
  }
  int h;
  h=height_finding(root);
  return h;
}
template<class T>
int BST<T>::height_finding(TreeNode<T>*pntr)
{
    if (pntr==NULL)
      return -1;
    if (height_finding(pntr->left_child)>height_finding(pntr->right_child))
      return 1+height_finding(pntr->left_child);
    else
      return 1+height_finding(pntr->right_child);
}

  
  
