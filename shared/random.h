#ifndef RANDOM_H
#define RANDOM_H

#include <time.h>
#include "singleton.h"

#define mix(a,b,c,d,e,f,g,h)	\
{								\
   a^=b<<11; d+=a; b+=c;		\
   b^=c>>2;  e+=b; c+=d;		\
   c^=d<<8;  f+=c; d+=e;		\
   d^=e>>16; g+=d; e+=f;		\
   e^=f<<10; h+=e; f+=g;		\
   f^=g>>4;  a+=f; g+=h;		\
   g^=h<<8;  b+=g; h+=a;		\
   h^=a>>9;  c+=h; a+=b;		\
}

#define RANDOM_BUFEER_SIZE	32*32

class Random : public Singleton<Random>
{
public:

	typedef  unsigned long int  ub4;

	Random();

	int Rand( int a, int b );

private:

	void Mix();

	int	array_offset;
	ub4 randrsl[RANDOM_BUFEER_SIZE];
	ub4 mm[RANDOM_BUFEER_SIZE];
	ub4 aa, bb, cc;
};

#define iRandom Random::getSingletonPtr()

#endif // RANDOM_H
