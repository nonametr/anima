#include "random.h"

initialiseSingleton ( Random );

Random::Random(): array_offset(0), aa(0), bb(0), cc(0)
{
	int i;
	ub4 a,b,c,d,e,f,g,h;
	aa=bb=cc=0;
	a=b=c=d=e=f=g=h=0x9e3779b9;

	for( i = 0; i < 4; ++i ) {
		mix(a,b,c,d,e,f,g,h);
	}

	randrsl[3] = time(NULL);

	for( i = 0; i < RANDOM_BUFEER_SIZE; i += 8 ) {
		a+=randrsl[i  ]; b+=randrsl[i+1]; c+=randrsl[i+2]; d+=randrsl[i+3];
		e+=randrsl[i+4]; f+=randrsl[i+5]; g+=randrsl[i+6]; h+=randrsl[i+7];
		mix(a,b,c,d,e,f,g,h);
		mm[i  ]=a; mm[i+1]=b; mm[i+2]=c; mm[i+3]=d;
		mm[i+4]=e; mm[i+5]=f; mm[i+6]=g; mm[i+7]=h;
	}

	for( i = 0; i < RANDOM_BUFEER_SIZE; i += 8 ) {
		a+=mm[i  ]; b+=mm[i+1]; c+=mm[i+2]; d+=mm[i+3];
		e+=mm[i+4]; f+=mm[i+5]; g+=mm[i+6]; h+=mm[i+7];
		mix(a,b,c,d,e,f,g,h);
		mm[i  ]=a; mm[i+1]=b; mm[i+2]=c; mm[i+3]=d;
		mm[i+4]=e; mm[i+5]=f; mm[i+6]=g; mm[i+7]=h;
	}

	Mix();
}

int Random::Rand( int a, int b )
{
	if( a == b ) return a;
	if( b == 0 ) return 0;
	if( b < a ) {
		a = a^b;
		b = a^b;
		a = a^b;
	}

	if( array_offset >= RANDOM_BUFEER_SIZE ) {
		Mix();
	}

	return ( a + randrsl[ array_offset++ ]%(b-a+1) );
}

void Random::Mix()
{
	register ub4 i, x, y;

	cc = cc + 1;
	bb = bb + cc;

	for( i = 0; i < RANDOM_BUFEER_SIZE; ++i )
	{
		x = mm[i];
		switch( i%4 ) {
		case 0: aa = aa^(aa<<13);	break;
		case 1: aa = aa^(aa>>6);	break;
		case 2: aa = aa^(aa<<2);	break;
		case 3: aa = aa^(aa>>16);	break;
		};
		aa              = mm[(i+128)%RANDOM_BUFEER_SIZE] + aa;
		mm[i]      = y  = mm[(x>>2)%RANDOM_BUFEER_SIZE]  + aa + bb;
		randrsl[i] = bb = mm[(y>>10)%RANDOM_BUFEER_SIZE] + x;
	}

	array_offset = 0;
}

