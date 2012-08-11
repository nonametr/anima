#ifndef _COMMON_H
#define _COMMON_H

#include "exeption.h"
#include <stdio.h>
#include <iostream>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <vector>
#include <assert.h>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <openssl/md5.h>

#define DBG_LVL_TRACE 8

#define DEBUG
// #define RELEASE

#ifdef RELEASE
#define USE_STL_CPP0X
#endif

#ifdef USE_STL_CPP0X
#define USE_STL_UNORDERED_MAP
#define USE_STL_SHARED_PTR
#endif

#ifdef USE_STL_UNORDERED_MAP
#define associative_container unordered_map
#define associative_multi_container unordered_multimap
#else
#define associative_container map
#define associative_multi_container multimap
#endif

#ifdef USE_STL_SHARED_PTR
#include <memory>
#else
#include <boost/shared_ptr.hpp>
#define shared_ptr boost::shared_ptr
#endif

#define MAX_PERCENT 10000
#define emitExeption(code) ErrorExeption( code, string(__FILE__) + string(":") + intToString ( __LINE__ ) +string ( "[" )\
+ string ( __FUNCTION__ ) + string("]") )

typedef unsigned long long uint64;
typedef long long int64;
typedef unsigned int uint32;
typedef int int32;
typedef unsigned short int uint16;
typedef short int int16;
typedef unsigned char uint8;
typedef char int8;

enum OBJECT_TYPES {ITEM = 0, LOCATION, BOSS, BOSS_STRIKE, ITEM_PACK, BULLETS, EXP, GOLD, MONEY, LVL, ENERGY, COLLECTION, COLLECTION_PART, GLOBAL,
OBJECT_TYPES_SIZE};
static std::string object_types_str[OBJECT_TYPES_SIZE] = {"items", "locations", "bosses", "boss_strikes", "item_packs", "globals", "globals", "globals",
"globals", "globals", "globals", "collections", "collections", "globals"};
class Server;

extern Server* iServer;
extern uint32 dbg_lvl;
extern std::string err_log_path;
extern std::string srv_log_path;

using namespace std;

        enum DBG_LVL { DISABLED = 0, VERY_LOW = 1, LOW = 2, MEDIUM = 3, OPTIMAL = 4, GOOD = 5, TOP = 6, EXTREAM = 7, CRAZY = 8, INSANE = 9, GODLIKE = 10  };

                                        void logError ( string err_log_path, const char *str );
                                        void logTrace ( string err_log_path, const char *str );

#ifndef RELEASE
#define traceerr( S, ... ) \
    {			\
        char __BUF__[32736];											\
        snprintf( __BUF__, sizeof(__BUF__)-1,							\
                                             "%s:%d %u [%s] " S,		__FILE__,				\
                                                                                            __LINE__, (unsigned int)time(NULL),				\
                                                                                            __FUNCTION__,			\
                                                                                            ## __VA_ARGS__ );		\
        perror(__BUF__);\
        errno = 0;\
    }
#define tracelog( LVL, S, ... )\
    {																	\
            if( dbg_lvl >= LVL )							\
            {																\
                    char __BUF__[32736];										\
                    snprintf( __BUF__, sizeof(__BUF__)-1,						\
                                                     "%s:%d [%s] " S,		__FILE__,			\
                                                                                                    __LINE__,			\
                                                                                                    __FUNCTION__,		\
                                                                                                    ## __VA_ARGS__ );	\
                    perror(__BUF__);\
                    errno = 0;\
            }																\
    }
#else
#define traceerr( S, ... ) \
    {			\
            char __BUF__[32736];										\
            snprintf( __BUF__, sizeof(__BUF__)-1,							\
                                             "%s:%d %u [%s] " S,		__FILE__,				\
                                                                                            __LINE__, (unsigned int)time(NULL),				\
                                                                                            __FUNCTION__,			\
                                                                                            ## __VA_ARGS__ );		\
            logError( err_log_path, __BUF__ );											\
    }
#define tracelog( LVL, S, ... )
\
    {																	\
            if( dbg_lvl >= LVL )											\
            {																\
                    char __BUF__[32736];										\
                    snprintf( __BUF__, sizeof(__BUF__)-1,						\
                                                     "%s:%d [%s] " S,		__FILE__,			\
                                                                                                    __LINE__,			\
                                                                                                    __FUNCTION__,		\
                                                                                                    ## __VA_ARGS__ );	\
                    logTrace( srv_log_path, __BUF__ );\
            }																\
    }
#endif

#define ASSERT_FAIL( EXPR ) if (!(EXPR)) { traceerr("ASSERT fail! EXPR = \"%s\"",#EXPR); assert(EXPR); ((void(*)())0)(); }
#define ASSERT_CONTINUE( EXPR ) if (!(EXPR)) { traceerr("ASSERT_CONTINUE fail! EXPR = \"%s\"",#EXPR); }
#define ASSERT_RETURN_FALSE( EXPR ) if (!(EXPR)) { traceerr("ASSERT_CONTINUE fail! EXPR = \"%s\"",#EXPR); return false; }
#define ASSERT_RETURN( EXPR ) if (!(EXPR)) { traceerr("ASSERT_CONTINUE fail! EXPR = \"%s\"",#EXPR); return; }
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
string shrinkSpaces(string &str);

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
 * @brief creating md5 from 'text'
 *
 * @param value value to generate md5 from
 * @param hash md5'ed value
 **/
void getMD5 ( char* text, char *hash );
/**
 * @brief fast int abs and recast to unsigned
 *
 * @param value value to abs
 * @return uint32 absed uint32 value
 **/
static inline uint32 absui ( const int value )
{
    return ( uint32 ) ( value ^ ( value >> 31 ) ) - ( value >> 31 );
}
/**
 * @brief fastest Method of float2int32
 *
 * @param value value to convert
 * @return int
 **/
static inline int float2int ( const float value )
{
    union
    {
        int getInt[2];
        double asDouble;
    } n;
    n.asDouble = value + 6755399441055744.0;

                 return n.getInt [0];
}
             /**
              * @brief Fastest Method of long2int32
              *
              * @param value value to convert
              * @return int
              **/
             static inline int long2int ( const double value )
{
    union
    {
        int getInt[2];
        double asDouble;
    } n;
    n.asDouble = value + 6755399441055744.0;

                 return n.getInt [0];
}
             /**
              * @brief return current precise time
              *
              * @return uint32
              **/
             inline uint32 getTickCount()
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
inline void reverseArray ( uint32* pointer, size_t count )
{
    size_t x;
    int * temp = ( int* ) malloc ( count );
    memcpy ( temp, pointer, count );
    for ( x = 0; x < count; ++x )
        pointer[x] = temp[count-x-1];
    free ( temp );
}
int getTimeFromString ( const char * str );
string getStringFromTimeStamp ( uint32 timestamp );
string getDataTimeFromTimeStamp ( uint32 timestamp );
uint32 decimalToMask ( uint32 dec );
bool isStringUTF8 ( const char *str );
volatile long atomicIncrement ( volatile long* value );
volatile long atomicDecrement ( volatile long* value );
vector<string> strSplit ( const string &src, const string &sep );
/**
 * @brief NEED DESC
 *
 * @param secs time_t value
 * @return uint32
 **/
inline uint32 secsToTimeBitFields ( time_t secs )
{
    tm* lt = localtime ( &secs );
    return ( lt->tm_year - 100 ) << 24 | lt->tm_mon  << 20 | ( lt->tm_mday - 1 ) << 14 | lt->tm_wday << 11 | lt->tm_hour << 6 | lt->tm_min;
}
time_t convTimePeriod ( uint32 dLength, char dType );
void intToString ( char * buf, int num );
string intToString ( int num );
string int64ToString ( long long int num );
string floatToString ( float num );
uint strToInt ( const char *str );
string doubleToString ( double num );
string getJsonParamStr ( string &data, string param );
string getJsonParamInt ( string &data, string param );
string getParam ( string &data, string param );

#endif
