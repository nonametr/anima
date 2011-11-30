#ifndef _COMMON_H
#define _COMMON_H

#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <assert.h>

typedef unsigned int uint;

using namespace std;

enum DBG_LVL { DISABLED = 0, VERY_LOW = 1, LOW = 2, MEDIUM = 3, OPTIMAL = 4, GOOD = 5, TOP = 6, EXTREAM = 7, CRAZY = 8, INSANE = 9, GODLIKE = 10  };

void logError ( const char *str );
void logTrace ( const char *str );

#ifndef RELEASE
#define traceerr( S, ... ) \
    {			\
        char __BUF__[32736];											\
        snprintf( __BUF__, sizeof(__BUF__)-1,							\
                                             "%s:%d [%s] " S,		__FILE__,				\
                                                                                            __LINE__,				\
                                                                                            __FUNCTION__,			\
                                                                                            ## __VA_ARGS__ );		\
        perror(__BUF__);\
    }
#define tracelog( LVL, S, ... ) 																	\
    {																	\
            if( Config::getSingletonPtr()->getParam(Config::LS_DBG_LVL) >= LVL )							\
            {																\
                    char __BUF__[32736];										\
                    snprintf( __BUF__, sizeof(__BUF__)-1,						\
                                                     "%s:%d [%s] " S,		__FILE__,			\
                                                                                                    __LINE__,			\
                                                                                                    __FUNCTION__,		\
                                                                                                    ## __VA_ARGS__ );	\
                    perror(__BUF__);\
            }																\
    }
#else
#define traceerr( S, ... ) \
    {			\
            char __BUF__[32736];											\
            snprintf( __BUF__, sizeof(__BUF__)-1,							\
                                             "%s:%d [%s] " S,		__FILE__,				\
                                                                                            __LINE__,				\
                                                                                            __FUNCTION__,			\
                                                                                            ## __VA_ARGS__ );		\
            logError( __BUF__ );											\
    }
#define tracelog( LVL, S, ... ) 																	\
    {																	\
            if( Config::getSingletonPtr()->getParam(Config::LS_DBG_LVL) >= LVL )											\
            {																\
                    char __BUF__[32736];										\
                    snprintf( __BUF__, sizeof(__BUF__)-1,						\
                                                     "%s:%d [%s] " S,		__FILE__,			\
                                                                                                    __LINE__,			\
                                                                                                    __FUNCTION__,		\
                                                                                                    ## __VA_ARGS__ );	\
                    logTrace( __BUF__ );\
            }																\
    }
#endif

#define ASSERT_FAIL( EXPR ) if (!(EXPR)) { traceerr("ASSERT fail! EXPR = \"%s\"",#EXPR); assert(EXPR); ((void(*)())0)(); }
#define ASSERT_CONTINUE( EXPR ) if (!(EXPR)) { traceerr("ASSERT_CONTINUE fail! EXPR = \"%s\"",#EXPR); }
#define ASSERT_RETURN( EXPR ) if (!(EXPR)) { traceerr("ASSERT_CONTINUE fail! EXPR = \"%s\"",#EXPR); return false; }
#define ASSERT ASSERT_FAIL

/**
 * @brief describes count of seconds in time unit
 **/
enum TimeVariables
{
    TIME_SECOND = 1,
    TIME_MINUTE = TIME_SECOND * 60,
    TIME_HOUR   = TIME_MINUTE * 60,
    TIME_DAY	= TIME_HOUR * 24,
    TIME_MONTH	= TIME_DAY * 30,
    TIME_YEAR	= TIME_MONTH * 12
};
/**
 * @brief fast int abs
 *
 * @param value value to abs
 * @return absed int val
 **/
static inline int absi ( const int value )
{
    return ( value ^ ( value >> 31 ) ) - ( value >> 31 );
}
/**
 * @brief fast int abs and recast to unsigned
 *
 * @param value value to abs
 * @return uint absed uint value
 **/
static inline uint absui ( const int value )
{
    return ( uint ) ( value ^ ( value >> 31 ) ) - ( value >> 31 );
}
/**
 * @brief fastest Method of float2int32
 *
 * @param value value to convert
 * @return int
 **/
static inline int float2int ( const float value )
{
    union { int asInt[2];
        double asDouble;
    } n;
    n.asDouble = value + 6755399441055744.0;

    return n.asInt [0];
}
/**
 * @brief Fastest Method of long2int32
 *
 * @param value value to convert
 * @return int
 **/
static inline int long2int ( const double value )
{
    union { int asInt[2];
        double asDouble;
    } n;
    n.asDouble = value + 6755399441055744.0;

    return n.asInt [0];
}
/**
 * @brief return current precise time
 *
 * @return uint
 **/
inline uint getTickCount()
{
    struct timeval tv;
    gettimeofday ( &tv, NULL );
    return ( tv.tv_sec * 1000 ) + ( tv.tv_usec / 1000 );
}
/**
 * @brief reverse ellements of array
 *
 * @param pointer pointer to array to reverse
 * @param count size of array
 * @return void
 **/
inline void reverseArray ( uint* pointer, size_t count )
{
    size_t x;
    int * temp = ( int* ) malloc ( count );
    memcpy ( temp, pointer, count );
    for ( x = 0; x < count; ++x )
        pointer[x] = temp[count-x-1];
    free ( temp );
}
int getTimeFromString ( const char * str );
string getStringFromTimeStamp ( uint timestamp );
string getDataTimeFromTimeStamp ( uint timestamp );
uint decimalToMask ( uint dec );
bool isStringUTF8 ( const char *str );
float round ( float f );
double round ( double d );
long double round ( long double ld );
volatile long atomicIncrement ( volatile long* value );
volatile long atomicDecrement ( volatile long* value );
vector<string> strSplit ( const string &src, const string &sep );
/**
 * @brief NEED DESC
 *
 * @param secs time_t value
 * @return uint
 **/
inline uint secsToTimeBitFields ( time_t secs )
{
    tm* lt = localtime ( &secs );
    return ( lt->tm_year - 100 ) << 24 | lt->tm_mon  << 20 | ( lt->tm_mday - 1 ) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}
time_t convTimePeriod ( uint dLength, char dType );
void intToString ( char * buf, int num );

#endif
