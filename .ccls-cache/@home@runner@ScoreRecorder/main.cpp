#include <iostream>
#include "Student.h"

int main() {
  int target = 1,i,j;
  int records[20][9];
  srand(time(0));  //Initialize Unique Random Seed
  Student *s = new Student; 
  s->init_records(); //Assign Date to each array.
  while(s->getday()<=20){
    cout<<"===================[DAY - "<<s->getday()<<"]==================="<<endl;
    while(s->get_hour() > 0 && s->getday()<=20){
      s->action();
      s->printstat();
    }
    s->day_cycle();
  }
  while(target != 0){
    s->print_sort(target);
    }
  delete s;
}



/*

This Game is Called "Depressed Student Overload" (Might change later cuz too not-family-friendly)

The purpose of this game/simulation is to help students who are preparing for exams to balance their work-health balance.

The goal is simply to keep our main character, the student, happy and healthy but at the same time prepped up for the upcoming examination.

There are many tools that can be used to temporarily boost certain stats up, such as energy drinks to boost your stamina in short period of time. However, there are side effects to these substances. The stronger the effect the more heavily the student's health is damaged. For example, energy drinks although may momentarily increaese their stamina, it may decreases their sleep time and happiness which may have long term consequences.

For the gameplay part, each day you are given 24 hours just like in real life. You can choose yourself what to do with those time aka managing your own time. Each actions may take different amount of time, and some are even customizable. You can choose to end the day by sleeping, which mark that there are no other actions you would like to perform and thus skip to tomorrow.

There are two part of the game, first is the Midterm exam, and another is the Final Exam. You will given a day tracker to help you keep track of the day you have left to prepare for the exam.

Please note that if you treat your student character harshly and not maintain their happiness and sadness as well as their health, it will result in a gradual negative effect. And to a certain point can result in a sickness that require the student to be hospitalized, consequently wasting your time for exam preparation.

//README

-Maybe remove hap/sad and merge them into anxiety to match the theme of EDUCATION/ANXIETY. The stat effects the outcome of the grade.

-20 days -> phase 1/2 -> 10/10 -> 3 1 4 2 // 3 1 4 2 
 
*/