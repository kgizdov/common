/*
	Before loop: create a progbar object and tell it how many events are in the loop.
	During loop: call progbar::print(i) where i is the current event number
	After	 loop: call progbar::terminate()
	Example:

		unsigned n = 1000;
		progbar bar(n);
		for(unsigned i = 0; i < n; i++)
		{
			if(i%10==0) bar.print(i);
		}
		bar.terminate();
*/
#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
#include "progbar.h"
using std::cout;
using std::endl;
using std::flush;
using std::setfill;
using std::setw;
using std::string;
progbar::progbar(int n_events)
{
	if (n_events < 0) n_events = -n_events;
	progbar(static_cast<unsigned>(n_events));
}
progbar::progbar(unsigned n_events)
{
	nevents  = n_events == 0 ? 1 : n_events;
	barwidth = 80;
	t0       = time(0);
}
progbar::progbar(int n_events, int bar_width)
{
	if (n_events < 0) n_events = -n_events;
	if (bar_width < 0) bar_width = -bar_width;
	progbar(static_cast<unsigned>(n_events),static_cast<unsigned>(bar_width));
}
progbar::progbar(unsigned n_events, unsigned bar_width)
{
	nevents  = n_events == 0 ? 1 : n_events;
	barwidth = bar_width == 0 ? 1 : bar_width;
	t0       = time(0);
}
void progbar::print(int ievent)
{
	if (ievent < 0) ievent = -ievent;
	print(static_cast<unsigned>(ievent));
}
void progbar::print(unsigned ievent)
{
	unsigned perc = static_cast<unsigned>((100 * ievent/nevents) + 1);
	// \e[?25l hides the cursor
	cout << "\r\e[?25l ┃";
	for (unsigned ibar = 0; ibar < (perc*barwidth)/100; ibar++)
		cout << "█";
	for (unsigned ibar = (perc*barwidth)/100; ibar < barwidth; ibar++)
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
	t0 = time(0);
	return;
}
