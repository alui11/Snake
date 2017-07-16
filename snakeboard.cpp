//Alison Lui
//Class implementation for Snakeboard

#include <vector>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;
#include "snakeboard.h"
#include "gfxnew.h"

Snakeboard::Snakeboard(){
  size = 60;
  for(int i=0;i<size;i++){ //make board
    board.push_back(vector<int>(size, 0));
  }
  map = 1;
  initialize();
}

Snakeboard::~Snakeboard(){}

void Snakeboard::print(){ //print board as integers (for debugging)
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      cout << board[i][j];
    }
    cout << endl;
  }
}

void Snakeboard::setDirection(char c){ //set direction of snake motion
  direction = c;
}

int Snakeboard::getSnakeLength(){ //get length of snake
  return snakeLength;
}

void Snakeboard::setMap(int m){ //set level (map of walls)
  map = m;
  initialize();
}

void Snakeboard::display(){ //display in graphics window using gfx
  int blockSize = 10; //number of pixels to use as one square of the board
  int r = blockSize/2; //radius of circles to draw
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(board[i][j]==-1){ //make purple circles for food
        gfx_color(255,0,255);
        gfx_fill_circle(j*blockSize+r,i*blockSize+r,r);
      }else if(board[i][j]>0){ //make blue circles for snake
        gfx_color(0,255,255);
        gfx_fill_circle(j*blockSize+r,i*blockSize+r,r);
      }else if(board[i][j]==-2){ //make rectangles for bricks of wall
        gfx_color(0,255,0);
        gfx_rectangle(j*blockSize,i*blockSize,blockSize,blockSize);
      }
    }
  }
}

void Snakeboard::addFood(){ //randomly add food to the board
  bool added = false;
  int x, y;
  while(!added){
    srand(time(NULL));
    x = rand()%size;
    y = rand()%size;
    if(board[x][y]==0){
      board[x][y] = -1;
      added = true;
    }
  }
}

int Snakeboard::advance(){ //move snake forward and adjust food/snake length as necessary
  int headx,heady,tailx,taily,newHeadx,newHeady;
  //find and save current location of head and tail of snake
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      if(board[i][j]==1){
        headx = j;
        heady = i;
      }else if(board[i][j]==snakeLength){
        tailx = j;
        taily = i;
      }
      if(board[i][j]>0){
        board[i][j]++; //advance snake body
      }
    }
  }
  //find new location for head according to direction
  switch(direction){
    case 'Q':
      newHeadx = headx - 1;
      newHeady = heady;
      break;
    case 'R':
      newHeadx = headx;
      newHeady = heady - 1;
      break;
    case 'S':
      newHeadx = headx + 1;
      newHeady = heady;
      break;
    case 'T':
      newHeadx = headx;
      newHeady = heady + 1;
      break;
  }
  //warp around edges of screen
  if(newHeadx<0)
    newHeadx = size-1;
  else if(newHeadx>=size)
    newHeadx = 0;
  else if(newHeady<0)
    newHeady = size-1;
  else if(newHeady>=size)
    newHeady = 0;
  //if running into obstable or into itself, return 1 for game over
  if(board[newHeady][newHeadx]!=-1 && board[newHeady][newHeadx]!=0){
    return 1;
  }
  //if eating grow and add new food; else don't
  if(board[newHeady][newHeadx]!=-1){
    board[taily][tailx] = 0; //remove old tail to keep from growing
  }else{
    snakeLength++;
    addFood();
  }
  board[newHeady][newHeadx] = 1; //set new head
  return 0;
}

void Snakeboard::initialize(){ //initialize board for new game
  //clear board (0's)
  for(int i=0;i<size;i++){
    for(int j=0;j<size;j++){
      board[i][j] = 0;
    }
  }
  //Set up map
  int whydoineedthisvariable, n;
  switch(map){
    case 1:
      for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
          board[0][j] = -2;
          board[1][j] = -2;
          board[i][0] = -2;
          board[i][1] = -2;
          board[size-1][j] = -2;
          board[size-2][j] = -2;
          board[i][size-1] = -2;
          board[i][size-2] = -2;
        }
      }
      break;
    case 2:
      for(int n:{0,2*size/3}){
        for(int i=n;i<size/3.0+n;i++){
          for(int j=n;j<size/3.0+n;j++){
            board[0][j] = -2;
            board[1][j] = -2;
            board[i][0] = -2;
            board[i][1] = -2;
            board[size-1][j] = -2;
            board[size-2][j] = -2;
            board[i][size-1] = -2;
            board[i][size-2] = -2;
            board[size/2][j] = -2;
            board[size/2+1][j] = -2;
            board[size/2-1][j] = -2;
          }
        }
      }
      break;
    case 3:
      for(int i=0;i<size;i++){
        board[i][0] = -2;
        board[i][1] = -2;
        board[i][size-1] = -2;
        board[i][size-2] = -2;
      }
      whydoineedthisvariable = 0.6*size;
      for(int n:{0,whydoineedthisvariable}){
        for(int i=n;i<n+0.4*size;i++){
          for(int j=n;j<n+0.4*size;j++){
            board[size/2][j] = -2;
            board[i][size*0.4] = -2;
            board[i][size*0.6] = -2;
          }
        }
      }
      break;
    case 4:
      for(int i=6;i<size;i+=6){
        for(int j=6;j<size;j+=6){
          board[i][j] = -2;
        }
      }
      break;
  }
  //Make snake
  snakeLength = 6;
  for(int i=6;i<snakeLength+6;i++){
    board[size/3][i] = snakeLength-i+6; //snake body = ordered ints
  }
  //Add initial food
  addFood();
  //set initial direction of motion
  direction = 'S';
}
