/*******************************************************************************
Title:IMPLEMENTING A BST AND USING IT TO IMPLEMENT FILE SEARCH

Compilation:g++ bst_file_search.cpp -Wall -o bst_file_search.out
*******************************************************************************/
#include<iostream>
#include<string>
#include"binaryTree_header.h"
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
BST<IndexEntry> tree;
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
          (*obj_pntr).insert_line_number(line_num);
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
  tree.PrintInOrder();
  
  return 0;
}
