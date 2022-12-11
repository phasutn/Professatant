#include "ScoreTreeNode.h"
using namespace std;

//Forward Declaration to declare "class_score(classroom*)"
//that will be defined in STD_LL.h later in main.cpp
class classroom;

class ST{
  private:
  	int size;
  	STN* rootPtr;
    classroom* class_x;
  public:
    ST();
    ~ST();
    void insert_tree(float, int, int);
    void class_score(classroom*, int);
    void deleteTree(STN*);
    STN* get_root(){ return rootPtr;}
    void new_avgscore_tree(float);
  
    //See how many people are under and above the class's mean GPA
    int get_leftside(STN*, int, int);
    int get_rightside(STN*, int, int);
  
    void print_tree(STN*, int, int, float);
};

ST::ST(){
  rootPtr = NULL;
  size = 0;
}

ST::~ST(){
  deleteTree(rootPtr);
  cout<<"Deforest-ed"<<endl;
}

void ST::deleteTree(STN* rootPtr){
  if(rootPtr){
    STN* currentPtr = rootPtr;
    deleteTree(currentPtr->get_left());
    deleteTree(currentPtr->get_right());
    delete currentPtr;
    size--;
  }
}
void ST::new_avgscore_tree(float value){
  if(rootPtr == NULL){
    STN* newFirstNode = new STN(value, 0, 0);
    if(newFirstNode){
      rootPtr = newFirstNode;
      size++;
    }
  }
  else{
    rootPtr->set_score(value);
  }
}

void ST::insert_tree(float value, int year, int id){
  bool inserted = false;
  STN* newNode = new STN(value, year, id);
  STN* t; //current
  if(newNode){
    if(size==0){
      rootPtr = newNode;
      }
    else{
      t = rootPtr;
      
      while(!inserted){
        if(t->get_score() > value){ //Insert Left
          if(t->get_left() == NULL){ 
            t->set_left(newNode);
            inserted = true;
          }
          else t = t->get_left();
        }
        else{ //Insert Right
          if(t->get_right() == NULL){ 
            t->set_right(newNode);
            inserted = true;
            }
          else t = t->get_right();
        }
      }
    }
    size++;
  }
  else{
    cout<<"Error"<<endl;
  }
  return;
}

int ST::get_leftside(STN* treePtr, int left, int year){
  if(treePtr){
    if(treePtr->get_year() == 0)
      left = get_leftside(treePtr->get_left(), left, year);
    else{
      if(treePtr->get_year() == year){
         left++;
         //cout<<"left - "<<left<<endl;
        }
      left = get_leftside(treePtr->get_left(), left, year);
      left = get_leftside(treePtr->get_right(), left, year);
    }
  }
  return left;
}

int ST::get_rightside(STN* treePtr, int right, int year){
  if(treePtr){
    if (treePtr->get_year() == 0)
      right = get_rightside(treePtr->get_right(), right, year);
    else{
       if(treePtr->get_year() == year){
         right++;
         //cout<<"right - "<<right<<endl;
        }
      right = get_rightside(treePtr->get_right(), right, year);
      right = get_rightside(treePtr->get_left(), right, year);
    }
  }
  return right;
}

//Print student score tree
void ST::print_tree(STN* treePtr, int x, int year, float AvgScore){
  if(treePtr){
    //cout<<"The year is "<<treePtr->get_year()<<endl;
    if (treePtr->get_year() == year){
        x++;
        print_tree(treePtr->get_right(),x,year,AvgScore);
        cout<<setw(x*5-5)<<treePtr->get_score()<<setw((x*5)+20)<<treePtr->get_ID()-6480000<<endl;
        print_tree(treePtr->get_left(),x,year,AvgScore);
      }
    else{
      if(treePtr->get_year() == 0) x++;
      print_tree(treePtr->get_right(),x,year,AvgScore);
      if(treePtr->get_year() == 0){
        cout<<"Average score: "<<AvgScore<<" ----------------------------"<<endl;
      }
      print_tree(treePtr->get_left(),x,year,AvgScore);
    }
  }
}
