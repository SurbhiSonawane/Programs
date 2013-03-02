#include<iostream>
#include<string>
#include"header_rbt.h"
#include <fstream>  //for file operations
#include <locale>
#include<cctype>
using namespace std;
int main()
{
  int option,num;
  int *pntr,*pn;
  RBT<int> obj;
  do
  {
    cout<<"Menu:\n";
    cout<<"1.Insert an element\n";
    cout<<"2.Delete an element\n3.Search for an element\n";
    cout<<"4.Inorder Succ\n5.InOrderPred\n6.Max\n7.Min\n";
    cout<<"8.Print Inorder\n9.Print Post Order\n10.Print Preorder\n";
    cout<<"11.Height\n12.BlackHeight\n13.Exit\nEnter your choice(1-7)\n";
    cin>>option;
    switch(option)
    {
      case 1:cout<<"Enter\n";
             cin>>num;
             pntr=new int;
             *pntr=num;
             pn=obj.insert(pntr);
             if(pn==NULL)
               cout<<"Insertion Unsuccessfull\n";
             break;
      case 2:cout<<"enter\n";
             cin>>num;
             pntr=new int;
             *pntr=num;
             obj.Delete(pntr);
             break;
      case 3:cout<<"enter\n";
             cin>>num;
             pntr=new int;
             *pntr=num;
             pn=obj.search(pntr);
             if(pn==NULL)
               cout<<"Element not found\n";
             else
               cout<<"Element present in the bst\n";
             break;
      case 4:cout<<"Inorder Succ\n";
             cout<<"Enter\n";
             cin>>num;
             pntr=new int;
             *pntr=num;
             pn=obj.InOrderSucc(pntr);
             if(pn!=NULL)
              cout<<*pn<<"\n";
             break;
      case 5:cout<<"Inorder Pred\n";
             cout<<"Enter\n";
             cin>>num;
             pntr=new int;
             *pntr=num;
             pn=obj.InOrderPred(pntr);
             if(pn!=NULL)
              cout<<*pn<<"\n";
             break;
      case 6:pntr=obj.Max();
             cout<<*pntr<<"\n";
             break;
      case 7:pntr=obj.Min();
             cout<<*pntr<<"\n";
             break;
      case 8:cout<<"Inorder\n";
             num=obj.PrintInOrder();
             break;
      case 9:cout<<"PostOrder\n";
             num=obj.PrintPostOrder();
             break;
      case 10:cout<<"Preorder\n";
             num=obj.PrintPreOrder();
             break;
      case 11:num=obj.Height();
              if(num!=-1)
                cout<<num<<"\n";
              break;
      case 12:cout<<"Enter\n";
              cin>>num;
              pntr=new int;
              *pntr=num;
              num=obj.BlackHeight(pntr);
              if(num!=-10)
                cout<<num<<"\n";
              break;
     default:cout<<"Exiting\n";
             
    }
  }while(option!=13);
 
  return 0;
}
 
