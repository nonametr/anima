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

void logerror ( const char *str );
void logtrace ( const char *str );

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
            if( Config::getGonfig()->dbg_lvl >= LVL )													\
            {																\
                    char __BUF__[32736];										\
                    snprintf( __BUF__, sizeof(__BUF__)-1,						\
                                                     "%s:%d [%s] " S,		__FILE__,			\
                                                                                                    __LINE__,			\
                                                                                                    __FUNCTION__,		\
                                                                                                    ## __VA_ARGS__ );	\
                    printf( "\e[1;32m---%s\e[0m\n", __BUF__ );\
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
            logerror( __BUF__ );											\
    }
#define tracelog( LVL, S, ... ) 																	\
    {																	\
            if( Config::getGonfig()->dbg_lvl >= LVL )													\
            {																\
                    char __BUF__[32736];										\
                    snprintf( __BUF__, sizeof(__BUF__)-1,						\
                                                     "%s:%d [%s] " S,		__FILE__,			\
                                                                                                    __LINE__,			\
                                                                                                    __FUNCTION__,		\
                                                                                                    ## __VA_ARGS__ );	\
                    logtrace( __BUF__ );\
            }																\
    }
#endif

#define ASSERT_FAIL( EXPR ) if (!(EXPR)) { traceerr("ASSERT fail! EXPR = \"%s\"",#EXPR); assert(EXPR); ((void(*)())0)(); }
#define ASSERT_CONTINUE( EXPR ) if (!(EXPR)) { traceerr("ASSERT_CONTINUE fail! EXPR = \"%s\"",#EXPR); }
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
/**
 * @brief convert string to timestamp
 *
 * @param str source string containing time
 * @return int timestamp
 **/
int getTimeFromString ( const char * str );
/**
 * @brief convert timestamp to string
 *
 * @param timestamp timestamp value
 * @return :string resulting string
 **/
string getStringFromTimeStamp ( uint timestamp );
/**
 * @brief convert timestamp to DataTime string
 *
 * @param timestamp timestamp value
 * @return :string resulting string
 **/
string getDataTimeFromTimeStamp ( uint timestamp );
/**
 * @brief converts decimal number to mask value.
 *
 * @param dec mask bit
 * @return uint value where "dec" bit is set to "1"
 **/
uint decimalToMask ( uint dec );
/**
 * @brief test string for containing utf8 characters
 *
 * @param str const char pointer to string to test
 * @return bool true - contain UTF8 chars, false - not
 **/
bool isStringUTF8 ( const char *str );
/**
 * @brief fast round float
 *
 * @param f value to round
 * @return float
 **/
float round ( float f );
/**
 * @brief fast round double
 *
 * @param d value to round
 * @return double
 **/
double round ( double d );
/**
 * @brief fast round long double
 *
 * @param ld value to round
 * @return long double
 **/
long double round ( long double ld );
/**
 * @brief atomic increment
 *
 * @param value value to increment
 * @return volatile long int
 **/
volatile long atomicIncrement ( volatile long* value );
/**
 * @brief atomic decrement
 *
 * @param value value to decrement
 * @return volatile long int
 **/
volatile long atomicDecrement ( volatile long* value );
/**
 * @brief split string into tokens
 *
 * @param src source string to split
 * @param sep seporator - string containing the delimiter
 * @return vector< string > vector of tokens
 **/
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
/**
 * @brief NEED DESC
 *
 * @param dLength ...
 * @param dType ...
 * @return time_t
 **/
time_t convTimePeriod ( uint dLength, char dType );
/**
 * @brief converts int to string. NOT SAFE!
 *
 * @param buf buffer where converted string will store
 * @param num number value to convert
 * @return void
 **/
void intToString ( char * buf, int num );

#endif
