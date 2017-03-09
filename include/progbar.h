#ifndef __PROGBAR_H__
#define __PROGBAR_H__
class progbar
{
	private:
		long t0;
		unsigned nevents, barwidth;
	public:
		progbar(int);
		progbar(int, int);
		progbar(unsigned);
		progbar(unsigned, unsigned);
		void print(int);
		void print(unsigned);
		void terminate();
		void reset();
};
#endif
