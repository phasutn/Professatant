#include "STD_NODE.h"
#include "ScoreTree.h"

class classroom{
  private:
   stud* hol; //head of linked list
   int size;
   //int id = 6480000;
  public:
      classroom();
      ~classroom();
      void insert_node(string name = "N/A", int class_number = 0, 
                       int year = 0, int ID = 6480000,float GPA = 0.0);
	    void insert_node(stud*);
      void remove_student(int);
      void first_year(int);
      void change_year();
      void assignID(stud* newStudent);
      float get_meanscore();

      int get_size(){return size;}
      stud* get_hol(){return hol;}

};

classroom::classroom(){
  hol=NULL;
  size=0;
}
classroom::~classroom(){ 
  cout<<"Deleting Classroom"<<endl;
  studPtr t;
  t=hol;
  int i;
  for(i=0;i<size;i++){
   hol=hol->get_next();
   delete(t);
   t=hol;
  } 
}
void classroom::first_year(int numofstud){
  studPtr currentPtr,newPtr;

  string name;
  int class_num = 0;
  int year = 0;

  
  int i;
  for(i=0;i<numofstud;i++){
    cout<<"Student name: ";
    cin>>name;
    class_num++;
    //id++;
    
    newPtr = new stud(name, class_num, year/*, id*/);
    currentPtr = hol;
    
    if(newPtr != NULL){
      if(currentPtr != NULL){
        while (currentPtr->get_next() != NULL) {
           currentPtr = currentPtr->get_next();
        }
        currentPtr->set_next(newPtr);
        size++;
      }
      else{
        hol = newPtr;
        size++;
      }
      assignID(newPtr);
    }
  }
}

float classroom::get_meanscore(){
  studPtr tempPtr = hol;
  float totalscore = 0;
  int i;
  if(tempPtr){
    for(i = 0;i< size;i++){
      totalscore += tempPtr -> get_score();
      tempPtr = tempPtr -> get_next();
    }
  }
  return totalscore / size;  
}

void classroom::change_year(){
  studPtr currentPtr = hol;
  if(currentPtr != NULL){
    int i, class_num = 1, choice, leaving_stud_id;
    float gpa;
    string name;

    do{
      cout<<"Is there any change in the student number?\n"
      <<"1 - Add a student\n"
      <<"2 - Remove a student\n"
      <<"3 - No change"<<endl;
      cin>>choice;
      switch (choice){
        case 1:{
          cout<<"What is the new student's name?"<<endl<<"->";
          cin>>name;
          studPtr newStudent =  new stud(name);
          if(newStudent){
            insert_node(newStudent);
            assignID(newStudent);
            newStudent -> set_year(hol->get_year());
          }
          else cout<<"Error inserting new student";
          break;
        }
        case 2:{
          cout<<"What is the last 4 digti of the student's id? (648xxxx)"<<endl<<"->";
          cin>>leaving_stud_id;
          remove_student(6480000 + leaving_stud_id);
        }
          default: break;
      }
    }while(choice != 3);
    
    for(i=0;i<size;i++){
      cout<<currentPtr->get_ID()<<" GPA: ";
      cin>>gpa;
      currentPtr -> set_score(gpa);
      currentPtr -> move_year();
      currentPtr -> set_class_num(class_num);
      class_num++;
      currentPtr = currentPtr -> get_next();
    }
    /*currentPtr = hol;
    tree -> insert_tree(get_meanscore());
    for(i=0;i<size;i++){
      tree -> insert_tree(currentPtr->get_score());
      currentPtr = currentPtr -> get_next();
    }*/
    //tree -> class_score(class_x);
  }
}

void classroom::assignID(stud* newStudent){
  int i;
  studPtr tempPtr = hol;
  if(tempPtr != NULL){
    int highestID = tempPtr->get_ID();
    for(i = 0; i < size; i++){
      if(tempPtr -> get_next() != NULL) tempPtr = tempPtr -> get_next();
      if(tempPtr->get_ID() > highestID) highestID = tempPtr -> get_ID();
    }
    newStudent -> set_ID(highestID + 1);
  }
}

void classroom::insert_node(stud* newStudent){
 studPtr currentPtr, newPtr = newStudent;
  if(newPtr!=NULL){
    currentPtr=hol;
    while(currentPtr->get_next()!=NULL){ //?!?!?!?***
      currentPtr=currentPtr->get_next();
    }
    currentPtr->set_next(newPtr);
    ++size;
    }
   else {
      cout <<"New Student Not inserted."<<endl;
   }
}

void classroom::remove_student(int id){
  studPtr currentPtr = hol, previousPtr;
  bool deleted = false;
  if(hol){
    while(currentPtr)
      if(currentPtr->get_ID() == id){
        studPtr t = currentPtr;
        currentPtr = currentPtr->get_next();
        previousPtr->set_next(currentPtr);
        delete t;
        size--;
        deleted = true;
      }
    else{
      previousPtr = currentPtr;
      currentPtr = currentPtr->get_next();
    }
  }
  if(deleted) cout<<"Deleted student successfully."<<endl;
  else cout<<"Deleting student failed."<<endl;
}

void ST::class_score(classroom* class_x, int year){
  int i;
  int class_size = class_x->get_size();
  studPtr tempPtr = class_x->get_hol();
  if(tempPtr){
    cout<<"Average GPA: "<<class_x->get_meanscore()<<endl;
    new_avgscore_tree(class_x->get_meanscore());
    for(i = 0;i < class_size;i++){
      insert_tree(tempPtr->get_score(), year);
      if(tempPtr->get_next() != NULL) tempPtr = tempPtr -> get_next();
    }
  }
}


