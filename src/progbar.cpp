/*
  Before loop: create a progbar object and tell it how many events are in the loop.
  During loop: call progbar::print(i) where i is the current event number
  After  loop: call progbar::terminate()
  Example:

    int n = 1000;
    progbar bar(n);
    for(int i = 0; i < n; i++)
    {
      if(i%10==0) bar.print(i);
    }
    bar.terminate();
*/
#include "progbar.h"
#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;
progbar::progbar(int n_events)
{
  nevents=n_events;
  barwidth=80;
  t0=time(0);
}
progbar::progbar(int n_events, int bar_width)
{
  nevents=n_events;
  barwidth=bar_width;
  t0=time(0);
}
void progbar::print(int ievent)
{
  int perc = (int)(100*ievent/nevents)+1;
  // \e[?25l hides the cursor
  cout << "\r\e[?25l ┃";
  for(int ibar = 0; ibar < (perc*barwidth)/100; ibar++)
    cout << "█";
  for(int ibar = (perc*barwidth)/100; ibar < barwidth; ibar++)
    cout << "░";
  cout << "┃ " << perc << "% " << flush;
  long t1 = time(0);
  cout << (t1-t0)/60 << ":" << setw(2) << setfill('0') << (t1-t0)%60 << "\e[?25h" << flush;
  return;
}
void progbar::terminate()
{
  this->print(nevents-1);
  cout << "\t " << nevents << " events processed " << setfill(' ') << endl;
  return;
}
void progbar::reset()
{
  t0=time(0);
  return;
}
