#include <iostream>
using namespace std;
#include "gfxnew.h"

int main(){
  gfx_open(600,600,"Test");
  char c = ' ';
  while(c != 'q'){
    c = gfx_wait();
    cout << c << endl;
  }
}
