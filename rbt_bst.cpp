/*******************************************************************************

Compilation:g++ rbt_bst.cpp -Wall -o rbt_bst.out
*******************************************************************************/
#include<iostream>
#include<string>
#include"header_rbt.h"
#include <fstream>  //for file operations
#include <locale>
#include<cctype>
struct node_ll
{
  int key;
  node_ll* next;

};
class IndexEntry
{
  public:
  string word;
  node_ll *list;
  IndexEntry()
  {
    word='\0';
    list=NULL;
  }
  IndexEntry(string str)
  {
    word=str;
    list=NULL;
  }
  void insert_line_number(int num)
  {
    node_ll *pntr=new node_ll;
    pntr->key=num;
    pntr->next=NULL;  
    if(list==NULL)
      list=pntr;
    else
    {
      node_ll*temp;
      temp=list;
      list=pntr;
      pntr->next=temp;
    }
  }
  bool operator ==(IndexEntry &obj)
  {
    if(this->word.compare(obj.word)==0)
      return true;
    return false;
  }
  bool operator <(IndexEntry &obj)
  {
    if(this->word.compare(obj.word)<0)
      return true;
    return false;
  }
  bool operator >(IndexEntry &obj)
  {
    if(this->word.compare(obj.word)>0)
      return true;
    return false;
  }
  friend ostream &operator <<(ostream &out,IndexEntry &entry);
  
  
};
ostream &operator <<(ostream &out,IndexEntry &entry)
{
  out<<entry.word;
  return out;
}
int main()
{
RBT<IndexEntry> tree;
BST<IndexEntry> bstree;
string sentence,word;
char * filename=new char [50];
cout<<"enter the filename\n";
cin>>filename;
ifstream input_file (filename);
int line_num=1;int j;
if (input_file.is_open()) 
  {
    while (!input_file.eof())
    {
      getline(input_file,sentence);
      if(input_file.eof())
        break;
      int len=sentence.length();
      for(j=0;j<len;j++)
      {
        word="";
        char c;
        while(isalnum(sentence[j]))
        {
          c=tolower(sentence[j]);
          word=word+c;
          j++;
        }
        if(word!="")
        {
          IndexEntry*new_pntr=new IndexEntry;
          IndexEntry obj(word);
          IndexEntry*datap=&obj;
          *new_pntr=*datap;
          IndexEntry*obj_pntr=tree.insert(new_pntr);
          IndexEntry*bst_obj_pntr=bstree.insert(new_pntr);
          (*obj_pntr).insert_line_number(line_num);
          (*bst_obj_pntr).insert_line_number(line_num);
        }
       
      }
      line_num++;
    }
    input_file.close();
  }
  else
  {
    cout<<"Enable to open the given file\n";
  }
  cout<<"File Search\n";
  char choice='y';
  string searcht;
  while(choice=='y'||choice=='Y')
  {
    cout<<"enter the search term\n";
    cin>>searcht;
    IndexEntry searcht_obj(searcht);
    IndexEntry *p_obj=&searcht_obj;
    IndexEntry*f_pntr=tree.search(p_obj);
    if(f_pntr==NULL)
      cout<<"Term not found\n";
    else
    { 
      cout<<"The term has been found in the given line(s)\n";
      node_ll*node_p=f_pntr->list;
      int l;
      int k=0;
      while(node_p!=NULL)
      {
        if(node_p->key!=l || k==0)
          cout<<node_p->key<<"\n";
        l=node_p->key;
        node_p=node_p->next;
        k++;
      }
    }  
    cout<<"Do you want to continue(if yes-y/Y)\n";
    cin>>choice;
  }
  int option,num;
  IndexEntry*pn,*new_pntr,*datap;
  IndexEntry obj;
  do
  {
    cout<<"Menu:\n";
    cout<<"1.Delete an element\n2.Search for an element\n";
    cout<<"3.Inorder Succ\n4.InOrderPred\n5.Max\n6.Min\n";
    cout<<"7.Print Inorder\n8.Print Post Order\n9.Print Preorder\n";
    cout<<"10.Height of BST\n11.Height of RBT\n12.Black Height of RBT\n";
    cout<<"13.Exit\nEnter your choice(1-7)\n";
    cin>>option;
    if(option==1||option==2||option==3||option==4||option==12)
    {
      cout<<"enter\n";
      cin>>word;
      new_pntr=new IndexEntry;
      obj=IndexEntry(word);
      datap=&obj;
      *new_pntr=*datap; 
    }
    switch(option)
    {
      case 1:tree.Delete(new_pntr);
             break;
      case 2:pn=tree.search(new_pntr);
             if(pn==NULL)
               cout<<"Element not found\n";
             else
               cout<<"Element present in the bst\n";
             break;
      case 3:cout<<"Inorder Succ\n";
             pn=tree.InOrderSucc(new_pntr);
             if(pn!=NULL)
              cout<<*pn<<"\n";
             break;
      case 4:cout<<"Inorder Pred\n";
             pn=tree.InOrderPred(new_pntr);
             if(pn!=NULL)
              cout<<*pn<<"\n";
             break;
      case 5:pn=tree.Max();
             if (pn!=NULL)
               cout<<*pn<<"\n";
             break;
      case 6:pn=tree.Min();
             if(pn!=NULL)
               cout<<*pn<<"\n";
             break;
      case 7:cout<<"Inorder\n";
             num=tree.PrintInOrder();
             break;
      case 8:cout<<"PostOrder\n";
             num=tree.PrintPostOrder();
             break;
      case 9:cout<<"Preorder\n";
             num=tree.PrintPreOrder();
             break;
      case 10:num=bstree.Height();
              cout<<num<<"\n";
              break;
      case 11:num=tree.Height();
              cout<<num<<"\n";
              break;
      case 12:num=tree.BlackHeight(new_pntr);
              if(num!=-10)
                cout<<num<<"\n";
              break;
       
     default:cout<<"Exiting\n";
             
    }
  }while(option!=13);
  return 0;
}

  
 
