#include <iomanip>
#include <iostream>
using namespace std;
#include "Functions.h"
#include <string.h>

class Student{
  private:
    string name;
    int anxiety, hunger; //Affects dexterity, and minor effects on Grade
    unsigned int dexterity; //Heavily affects the Grade
    float grade;
    unsigned int hour; //hour per day
    int records[20][11]; //[day][sleep,eat,study,meditate.movie,game,coffee,energy_drink,pill,day]
    unsigned int day = 1;
  public:
    Student(string n = "JIMMY", int anx = 0, int hunger = 25, int dex = 0, float grade = 0.0);
    ~Student();
    void init_records(); //Assign Index [1-20][10] to each corresponding day.
    int return_records(int,int);

    //Basic Actions
    void sleep();
    void eat();
    void study();
    int study_choice();
    void test(int day = 0);
    void action();

    //Anxiety Decreaser
    void meditate(); 
    void movie();
    void game();

    //Day Cycle
    bool check_hour(int hr=0);
    int get_hour() {return hour;}

    //Misc
    bool notsick();  //Check if student is not sick 
    void printstat(); //Print currrent stats (anxiety, hunger, dext, grade)
    void day_cycle(); //Increase Day and reset hour
    int getday();    //return current day
    void print_sort(int = 0); //print sorted targetted stat
};

               
Student::Student(string n ,int anx, int hung, int dex, float grd){
    name = n;
  
    anxiety = anx;
    hunger = hung;
    dexterity = dex;
  
    grade = grd;
    hour = 24;
}

Student::~Student(){
  cout<<name<<" Has Graduated"<<endl;
}

void Student::init_records(){
    for(int i = 0;i<20;i++){
    records[i][10] = i+1;
  }
}

void Student::sleep(){  //Action sleep, sleep until the end of day, various effect from sleep duration
  hunger -= 15;
  if(hunger <=  0){
    cout<<"[SLEEP] - You starved yourself and damaged your health"<<endl;
    dexterity -= (3 + hunger);
    anxiety += (3 + hunger);
  }
  // 13++
  if(hour>=13){
    cout<<"[SLEEP] - You overslept and missed class."<<endl;
    anxiety += (hour-8);
  }
  //10-12
  else if(10 <= hour && hour <= 12){
    cout<<"[SLEEP] - You slept a bit too much and strained your back"<<endl;
    anxiety += (hour - 9);
  }
  // 7-9
  else if(7 <= hour && hour <= 9){
    cout<<"[SLEEP] - You slept a good amount last night"<<endl;
    dexterity += (9 - hour);
  }
  // 6--
  else if(hour<=6){
    cout<<"[SLEEP] - You did not get enough sleep last night."<<endl;
    dexterity -= (8 - hour);
  }
  records[day][0] += hour;  //Record sleep hour
  hour -= hour;
}

void Student::eat(){  //Action eat
  if(check_hour(2)){
    cout<<"[FOOD] - You ate some food."<<endl;
    hunger += 10;
    records[day][1] += 2;  //Record eat hour
    hour -= 2;
  }
}

void Student::study(){  //Action study
  int hr;
  hr = study_choice();
  anxiety += 4 + ((hr-4)/2);
  if(hr > 4) records[day][5+((hr-4)/2)] += 1;  //record boost usage
  records[day][2] += hr;
  dexterity += hr;
  hour -= hr;
}

int Student::study_choice(){  //Ask if player want to use boost
  int choice,hr;
  do{
    cout<<"Do you want to consume anything to help study longer?"<<endl;
    cout<<"0 - Nothing (4 hours)"<<endl;
    cout<<"1 - Coffee (6 hours)"<<endl;
    cout<<"2 - Energy Drink (8 hours)"<<endl;
    cout<<"3 - Pill (the safe kind) (10 hours)"<<endl;
    cout<<"-> ";
    cin>>choice;
  }while(choice > 3 || choice < 0);
  switch(choice){
    case 0: hr = 4;
      break;
    case 1: hr =  6;
      break;
    case 2: hr =  8;
      break;
    case 3: hr =  10;
      break;
    default: cout<<"ERROR"<<endl;
      hr =  0;
      break;
  }
  if(check_hour(hr)) return hr;
    else return 0;
}

void Student::test(int day){ //Do a test even on certain days, generate random scores within a range based on dexterity, give GPA as average score
  if(day == 3) cout<<"[TEST] - You Took the quizzes that lasted 2 Days"<<endl;
  else if(day == 13) cout<<"[TEST] - You Took the Mid-Term Exam that lasted 4 Days"<<endl;
  else if(day == 8) cout<<"[TEST] - You Took the quizzes that lasted 2 Days"<<endl;
  else if(day == 18) cout<<"[TEST] - You Took the Final-Term Exam that lasted 4 Days"<<endl;
  else return;
  
  int i,temp_grade,rnum,subject = 5;
  
  temp_grade=0;
  for(i=1;i<=subject;i++){
    rnum = (timed_random(100-dexterity, rnum-dexterity-1))+dexterity; 
    cout<<"Subject "<<i<<": "<<rnum<<endl;
    temp_grade += rnum; //s1 + s2 + s3 + s4 + ... + sN = sTotal
  }
  //Mean score across all subjects (sTotal / N)
  temp_grade /= subject;
  //1st Test (If grade is 0 and the date is the first test)
  if(grade == 0 && (day >= 12 && day <= 14)) grade += temp_grade;  
  //2nd 3rd... Test
  else grade = (grade + temp_grade)/2; 
  cout<<"GPA: "<<grade<<endl;
  hour = 0;
}

void Student::action(){  //Ask for action to do
  int act;
  if((day >= 3 && day <= 4) ||   //Test for 2 days
    (day >= 8 && day <= 10) ||   //Test for 3 days
    (day >= 13 && day <= 14) ||   //Test for 2 days
    (day >= 18 && day <= 20)){  //Test for 3 days
    test(day);
    return;
  }
  cout<<" -Choose your Action-"<<endl;
  cout<<"Hour Left - "<<hour<<endl;
  cout<<"1 - Sleep"<<endl;
  cout<<"2 - Eat"<<endl;
  cout<<"3 - Study"<<endl;
  cout<<"4 - Meditate"<<endl;
  cout<<"5 - Watch a Movie"<<endl;
  cout<<"6 - Play Videogames"<<endl;
  cout<<"7 - QUIT"<<endl;
  cout<<"-> ";
  cin>>act;
  switch(act){
    case 1: 
      sleep();
      break;
    case 2: eat();
      break;
    case 3: study();
      break;
    case 4: meditate();
      break;
    case 5: movie();
      break;
    case 6: game();
      break;
    case 7: day = 61;
      break;
    default: 
      cout<<"[ERROR] - Invalid Action!"<<endl;
      break;
  }
  return;
}

void Student::meditate(){  //Action meditate, anxiety is reduced proportionally
  if(check_hour(3)){
    int recover = anxiety / 3;
    cout<<"[MEDITATE] - You meditated for an hour and replenished"<<endl;
    anxiety -= recover;
    records[day][3] += 3;  //Record meditate hour
    hour -= 3;
  }
}

void Student::movie(){  //Action movie, anxiety is reduced but dexterity is also reduced
  if(check_hour(5)){
    cout<<"[MOVIE] - You watched movie for three hours"<<endl;
    dexterity -= 3;
    if(anxiety<80) anxiety += 3;
    else anxiety += 1;
    records[day][4] += 5;  //Record movie hour
    hour -= 5;
  }
}

void Student::game(){  //Action game, play game for indicated hour, the result is randomized to either reduce or give anxiety
  srand(time(0));
  int hr;
  int prevnum = rand();
  cout<<"[HOUR] - How many hours do you play?"<<endl;
  cout<<"-> ";
  cin>>hr;
  if(check_hour(hr)){
    cout<<"[GAME] - You played game for "<<hr<<" hours"<<endl;
    int rnum = timed_random(hr*2, prevnum); //(range, prevnum(to avoid same random));
    if (rnum >= rnum/2) anxiety -= rnum;  //reduce anxiety
    else anxiety += rnum;  //increase anxiety
    hunger -= hr;
    dexterity -= (hr/3);
    records[day][5] += hr;  //Record game hour
    hour -= hr;
  }
}

bool Student::check_hour(int hr_need){  //Check if there is enough hour for an action
  if(hour>=hr_need)
    return hour >= hr_need;
  else{
    cout<<"[TIME] - You do not have enough time."<<endl;
    return 0;
  }
}

void Student::printstat(){  //Print all stat
  cout<<" _______________________________"<<endl;
  if(anxiety>=10) cout<<"| Anxiety - "<<anxiety<<setw(19)<<"|"<<endl; 
   else cout<<"| Anxiety - "<<anxiety<<setw(20)<<"|"<<endl;
  if(hunger>=10)cout<<"| Hunger - "<<hunger<<setw(20)<<"|"<<endl;
   else cout<<"| Hunger - "<<hunger<<setw(21)<<"|"<<endl;
  if(dexterity>=10)cout<<"| Dexterity - "<<dexterity<<setw(17)<<"|"<<endl;
   else cout<<"| Dexterity - "<<dexterity<<setw(18)<<"|"<<endl;
  if(grade !=0)cout<<"| Grade - "<<grade<<setw(19)<<"|"<<endl;
   else cout<<"| Grade - "<<grade<<setw(22)<<"|"<<endl;
  cout<<"|_______________________________"<<"|"<<endl<<endl;
}


bool Student::notsick(){  //Check if sick
  return anxiety<=100;
}

void Student::day_cycle(){  //Change day and reset hour
  //Skip 3 Days If You are sick (Separated 'if' because sick can still test) + Reduce Anxiety
  if(!notsick()){
    day += 3; 
    anxiety /= 4;
  }
  //Quiz 1 day 3-4
  if(day >= 3 && day <= 4) day = 5;
  //Quiz 2 day 13-14
  else if(day >= 13 && day <= 14) day = 15;
  //Midterm day 8-10
  else if(day >= 8 && day <= 10) day = 11;
  //Final day 18-20
  else if(day >= 18 && day <= 20) day = 21;
  //Normal Day
  else if(notsick()) day++;
  hour = 24;
}

int Student::getday(){
  return day;
}

int Student::return_records(int i, int j){
  return records[i][j];
}

void Student::print_sort(int target){
  //[day][sleep,eat,study,meditate.movie,game,coffee,energy_drink,pill]
  while(target != 9){
    cout<<"What Stat Would You Like To See?"<<endl;
    cout<<"0 - Sleep"<<endl;
    cout<<"1 - Eat"<<endl;
    cout<<"2 - Study"<<endl;
    cout<<"3 - Meditate"<<endl;
    cout<<"4 - Movie"<<endl;
    cout<<"5 - Game"<<endl;
    cout<<"6 - Coffee"<<endl;
    cout<<"7 - Energy Drink"<<endl;
    cout<<"8 - Pill"<<endl;
    cout<<"9- End Program"<<endl;
    cin>>target;
    sort_record(records, target - 1);
  }
}