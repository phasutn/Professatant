#include <iostream>
#include <iomanip>
using namespace std;
#include "STD_LL.h"


void instructions();

int main() {
  //classroom c
  classroom* c = new classroom();
  unsigned int choice, view_choice;
  int year = 1;
  int years_of_study;
  int student;
  //ST* scoretree = new ST();
  int right = 0;
  int left = 0;
  cout<<"How many students have admissioned?"<<endl;
  cout<<"->";
  cin>>student;
  c->first_year(student);
  cout<<"How many years of study?"<<endl;
  cout<<"->";
  cin>>years_of_study;
  int AvgScore[years_of_study];
  //ST** scoretreelist = new ST*[years_of_study];
  ST* scoretree = new ST();

  
  while(year<=years_of_study+1 && choice != 3){
    if(year == years_of_study+1) cout<<"ALL STUDENTS HAVE GRADUATED"<<endl;
    else cout<<"Year: "<<year<<endl;
    instructions();
    cout<<"->";
    cin>>choice;
    switch (choice){
      case 1:{
        if(year != years_of_study+1){
          c->change_year();
          AvgScore[year-1] = c->get_meanscore();
          scoretree->class_score(c,year);
          year++;
        }
        else cout<<"Students have graduated, cannot change year anymore.\n"
                 <<"Press 3 to exit."<<endl;
        break;
      }
      case 2:{
        do{
          cout<<"What year do you want to check?"<<endl;
          cout<<"->";
          cin>>view_choice;
          }while(view_choice>year-1 || view_choice <= 0);
        
        //cout<<"Mean - "<<c->get_meanscore()<<endl;
        scoretree->print_tree(scoretree->get_root(), 0, view_choice, AvgScore[view_choice-1]);
        right = scoretree->get_rightside(scoretree->get_root(), 0, view_choice);
        left = scoretree->get_leftside(scoretree->get_root(), 0, view_choice);
        cout<<"There are "<<right<<" people whose GPAs are above or equal to average"<<endl;
        cout<<"There are "<<left<<" people whose GPAs are below average"<<endl;
        
        break;
      }
      case 3:{
        cout<<"Exitting"<<endl;
        break;
      }
      default:
        cout<<"Invalid choice"<<endl;
        break;
    }
  }
  /*
  cout<<"Mean - "<<c->get_meanscore()<<endl;
  scoretree->class_score(c);
  scoretree->print_tree(scoretree->get_root(), 0);
  right = scoretree->get_rightside(scoretree->get_root(), right,(scoretree->get_root())->get_score());
  left = scoretree->get_leftside(scoretree->get_root(), left, (scoretree->get_root())->get_score());
  cout<<"There are "<<right<<" people whose GPAs are above average"<<endl;
  cout<<"There are "<<left<<" people whose GPAs are below average"<<endl;*/
  cout<<"All students have graduated"<<endl;
  delete(c);
  delete(scoretree);
  return 0;
}


void instructions()
{ 
   cout<< "Enter your choice:\n"
      "   1 - Move to next year\n"
      "   2 - View past record\n"
      "   3 - Exit"<<endl;
}


/*

year 1 > year 2 > year 3 > .... > year 6 (GRADUATED)

[LL] s1 > s2 > s3 > s4 > ....

[BST] MeanScore = rootPtr -> Check Class Score Status

*/