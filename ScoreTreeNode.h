class STN{
  private:
    STN* leftPtr;
    STN* rightPtr;
    float score;
    int year;
    int ID;
  public:
    STN(float, int, int); 
    ~STN();
    STN* get_left(){return leftPtr; }
    STN* get_right(){return rightPtr; }

    void set_left(STN* t){leftPtr = t; }
    void set_right(STN* t){rightPtr = t; }

    float get_score(){return score;}
    void set_score(float x){score = x;}

    int get_year(){return year;}
    void set_year(int x=0){year = x;}

    int get_ID(){return ID;}
    void set_ID(int x){ID = x;}
};
typedef STN* STNPtr;

STN::STN(float value, int yr, int id){
  score = value;
  leftPtr = NULL;
  rightPtr = NULL;
  year = yr;
  ID = id;
} 

STN::~STN(){
  cout<<"Score "<<score<<" is deleted."<<endl;
}
