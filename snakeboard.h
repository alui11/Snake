//Alison Lui
//Class for gameboard for Snake

#include <vector>
using namespace std;

class Snakeboard{
  public:
    Snakeboard();
    ~Snakeboard();
    void setDirection(char);
    int getSnakeLength();
    void setMap(int);
    void print(); //for debugging purposes
    void display();
    void addFood();
    int advance();
    void initialize();
  private:
    int size; //size of board
    vector< vector<int> > board; //board pieces represented by ints
    int snakeLength;
    char direction; //current direction of motion
    int map; //setting for map of walls (level)
};
