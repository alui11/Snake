//Alison Lui
//Snake Main

#include <unistd.h>
#include <iostream>
using namespace std;
#include "snakeboard.h"
#include "gfxnew.h"

int main(){
  Snakeboard sboard; //create board
  int wd=600, ht=600; //window width and height
  char c = ' '; //to store user input
  int gameOver;
  gfx_open(wd,ht,"Snake");
  gfx_clear();
  gfx_flush();
  while(c != 'q'){
    //opening message
    gfx_clear();
    gfx_flush();
    gfx_color(108,36,240);
    gfx_changefont("rk24");
    gfx_text(275,150,"Snake");
    gfx_text(150,230,"Steer with the arrow keys");
    gfx_text(200,260,"Eat to grow longer");
    gfx_text(90, 290, "Don't bump into walls or yourself");
    gfx_text(125,320,"Press q at any time to quit");
    gfx_text(75,350,"Press a number key to choose a level");
    gfx_text(20,450,"(1) Beginner");
    gfx_text(195,450,"(2) Easy");
    gfx_text(320,450,"(3) Medium");
    gfx_text(465,450,"(4) Hard");
    gfx_flush();
    //wait for user to choose level or quit
    while(c!='1' && c!='2' && c!='3' && c!='4'){
      c = gfx_wait();
      sboard.setMap(c-'0');
      if(c=='q') return 0;
    }
    //play game
    while(c != 'm'){ //returns here when 'r' is pressed for replay
      while(c != 'q'){
        c = ' '; //clear c in case it is still 'r'
        gfx_clear();
        gfx_flush();
        sboard.display();
        gfx_flush();
        usleep(50000 - 500*sboard.getSnakeLength()); //get faster as snake gets longer
        if(gfx_event_waiting()){ //change direction if arrow key pressed
          c = gfx_wait();
          if(c=='Q' || c=='R' || c=='S' || c=='T')
            sboard.setDirection(c);
        }
        gameOver = sboard.advance(); //advance snake forward by one square
        if(gameOver==1){
          break;
        }
      }
      while(c != 'r' && c != 'm'){
        gfx_color(108,36,240);
        gfx_text(255,200,"Game Over");
        gfx_text(195,275,"Press 'r' to replay");
        gfx_text(90,350,"Press 'm' to return to the main menu");
        c = gfx_wait();
        if(c=='q') return 0;
      }
      sboard.initialize(); //initialize board for new game
    }
  }
}
