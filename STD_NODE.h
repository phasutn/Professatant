#include <string.h>
#include <iostream>
// namespace std;

class stud{
  private:
    string name;
    int class_number, year, ID;
    float GPA;
    stud* nextstud;
    
  public:
    stud(string name = "N/A", int class_number = 0, 
         int year = 0, int ID = 6480000, float GPA = 0.0);
    ~stud();
    stud* get_next(){ return nextstud; }
    void set_next(stud* stu){ nextstud = stu; }

    int get_ID(){ return ID;}
    void set_ID(int x){ ID = x;}

    float get_score(){ return GPA;}
    void set_score(float x){GPA = x;}

    int get_year(){return year;}
    void set_year(int x){year = x;}
    void move_year(){year++;}
    void set_class_num(int x){class_number = x;}

};

typedef stud* studPtr;

stud::stud(string pname, int pclass_number, int pyear, int pID,float pGPA){
  name = pname;
  class_number = pclass_number;
  year = pyear;
  ID = pID;
  GPA = pGPA;

  nextstud = NULL;
}

stud::~stud(){
  cout<<ID<<" "<<name<<" Has Graduated"<<endl;
}
