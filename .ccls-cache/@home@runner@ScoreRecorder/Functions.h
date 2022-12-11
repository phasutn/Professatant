#include <cstdlib>
#include <iomanip>

int random_num(int prevrand = 0, int n = 1);

int random_num(int prevrandom, int n){
  srand(prevrandom);
  return rand() % n;
}

int timed_random(int range, int prevnum){
  srand(time(0));
  int i = 0,randnum;
  //This loop will not break until new number from rand()
  //is generated, which is seeded from srand(time(0)).
  //It takes 1 second for rand() to be re-seeded, which
  //creates a dramatic effect when generating values in     
  //the terminal.
  while(i<1){
    srand(time(0));
    randnum = rand();
    if(randnum != prevnum) i++; 
  }
  return (randnum % range)+1;  //range = 5 -> output = 1,2,3,4,5
}

void print_header(int target){
  switch(target){
     
    case 0: 
      cout<<"Sleep (Hr)"<<endl;
      break;
    case 1:
      cout<<"Eat (Hr)"<<endl;
      break;
    case 2:
      cout<<"Study (Hr)"<<endl;
      break;
    case 3:
      cout<<"Meditate (Hr)"<<endl;
      break;
    case 4:
      cout<<"Movie (Hr)"<<endl;
      break;
    case 5:
      cout<<"Game (Hr)"<<endl;
      break;
    case 6:
      cout<<"Coffee (Time Used)"<<endl;
      break;
    case 7:
      cout<<"Energy Drink (Time Used)"<<endl;
      break;
    case 8:
      cout<<"Pill (Time Used)"<<endl;
      break;
    case 9:
      cout<<"End Program"<<endl;
      break;

    default: break;
  }
}

void sort_record(int records[20][11], int target){
  int i,j,value,value2;
  int temp_records[20][2];
  for(i = 0;i<20;i++){
      temp_records[i][0] = records[i][target]; //Index 0 = target
      temp_records[i][1] = records[i][10];     //Index 1 = Day(Index 10)
  }
  /* 
  This function uses an inserting algorithm to sort in descending order.
  The input that we use for this function is a 2D array in order to output both
  the "target" information as well as the day it was done.
  Firstly I make another temp. 2D array that contains the target information
  in its [day][0] index and the day in [day][1] index.
  Then it get sorted normally with the addition of another temp value that 
  insertion sorting uses to move the [day][1] index value along with its [day][0]
  */
  
  
  for(i=1;i<20;i++){
    value = temp_records[i][0]; 
    value2 = temp_records[i][1];
    for(j=i-1;j>=0 && temp_records[j][0] < value;j--){
      temp_records[j+1][0] = temp_records[j][0];
      temp_records[j+1][1] = temp_records[j][1];
    }
    temp_records[j+1][0] = value;
    temp_records[j+1][1] = value2;
  }
  print_header(target);
  for (i = 0; i < 20; i++) {
    cout<<"Day - "<<temp_records[i][1];
    if(temp_records[i][1] >= 10) cout<<""<<setw(7); 
    else cout<<""<<setw(8);
    cout<<temp_records[i][0]<<endl;
  }
    cout << endl;
}

