#include "common.h"
#include "config.h"
/**
 * @brief converts decimal number to mask value.
 *
 * @param dec mask bit
 * @return uint value where "dec" bit is set to "1"
 **/
uint decimalToMask ( uint dec )
{
    return ( ( uint ) 1 << ( dec - 1 ) );
}
float round ( float f )
{
    return floor ( f + 0.5f );
}
double round ( double d )
{
    return floor ( d + 0.5 );
}
long double round ( long double ld )
{
    return floor ( ld + 0.5 );
}
/**
 * @brief atomic increment
 *
 * @param value value to increment
 * @return volatile long int
 **/
volatile long atomicIncrement ( volatile long* value )
{
    return __sync_add_and_fetch ( value, 1 );
}
/**
 * @brief atomic decrement
 *
 * @param value value to decrement
 * @return volatile long int
 **/
volatile long atomicDecrement ( volatile long* value )
{
    return __sync_sub_and_fetch ( value, 1 );
}
/**
 * @brief converts int to string. NOT SAFE!
 *
 * @param buf buffer where converted string will store
 * @param num number value to convert
 * @return void
 **/
void intToString ( char * buf, int num )
{
    sprintf ( buf,"%u",num );
}
string intToString ( int num )
{
    char buf[128];
    snprintf ( buf, 128, "%u",num );
    return buf;
}
/**
 * @brief convert string to timestamp
 *
 * @param str source string containing time
 * @return int timestamp
 **/
int getTimeFromString ( const char * str )
{
    uint time_res = 0;
    char * p = ( char* ) str;
    uint multiplier;
    string number_temp;
    uint multipliee;
    number_temp.reserve ( 10 );
    while ( *p != 0 )
    {
        // always starts with a number.
        if ( !isdigit ( *p ) )
            break;
        number_temp.clear();
        while ( isdigit ( *p ) && *p != 0 )
        {
            number_temp += *p;
            ++p;
        }
        // try to find a letter
        if ( *p != 0 )
        {
            // check the type
            switch ( tolower ( *p ) )
            {
            case 'y':
                multiplier = TIME_YEAR;
                break;
            case 'm':
                multiplier = TIME_MONTH;
                break;
            case 'd':
                multiplier = TIME_DAY;
                break;
            case 'h':
                multiplier = TIME_HOUR;
                break;
            default:
                return -1;
                break;
            }
            ++p;
        }
        else
            multiplier = TIME_MINUTE; // Defaults to MINUTES, if no letter is given
        multipliee = atoi ( number_temp.c_str() );
        time_res += ( multiplier * multipliee );
    }
    return time_res;
}
/**
 * @brief convert timestamp to string
 *
 * @param timestamp timestamp value
 * @return :string resulting string
 **/
string getStringFromTimeStamp ( uint timestamp )
{
    int seconds = ( int ) timestamp;
    int mins= 0;
    int hours= 0;
    int days= 0;
    int months= 0;
    int years= 0;
    if ( seconds >= 60 )
    {
        mins = seconds / 60;
        if ( mins )
        {
            seconds -= mins*60;
            if ( mins >= 60 )
            {
                hours = mins / 60;
                if ( hours )
                {
                    mins -= hours*60;
                    if ( hours >= 24 )
                    {
                        days = hours/24;
                        if ( days )
                        {
                            hours -= days*24;
                            if ( days >= 30 )
                            {
                                months = days / 30;
                                if ( months )
                                {
                                    days -= months*30;
                                    if ( months >= 12 )
                                    {
                                        years = months / 12;
                                        if ( years )
                                        {
                                            months -= years*12;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    char szTempBuf[100];
    string szResult;

    if ( years )
    {
        intToString ( szTempBuf, years );
        szResult += szTempBuf;
        szResult += " years, ";
    }

    if ( months )
    {
        intToString ( szTempBuf, months );
        szResult += szTempBuf;
        szResult += " months, ";
    }

    if ( days )
    {
        intToString ( szTempBuf, days );
        szResult += szTempBuf;
        szResult += " days, ";
    }

    if ( hours )
    {
        intToString ( szTempBuf, hours );
        szResult += szTempBuf;
        szResult += " hours, ";
    }

    if ( mins )
    {
        intToString ( szTempBuf, mins );
        szResult += szTempBuf;
        szResult += " minutes, ";
    }

    if ( seconds )
    {
        intToString ( szTempBuf, seconds );
        szResult += szTempBuf;
        szResult += " seconds";
    }

    return szResult;
}

const char * szDayNames[7] =
{
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
};

const char * szMonthNames[12] =
{
    "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
};
/**
 * @brief convert timestamp to DataTime string
 *
 * @param timestamp timestamp value
 * @return :string resulting string
 **/
string getDataTimeFromTimeStamp ( uint timestamp )
{
    char szTempBuf[100];
    time_t t = ( time_t ) timestamp;
    tm * pTM = localtime ( &t );

    string szResult;
    szResult += szDayNames[pTM->tm_wday];
    szResult += ", ";

    intToString ( szTempBuf, pTM->tm_mday );
    szResult += szTempBuf;
    szResult += " ";

    szResult += szMonthNames[pTM->tm_mon];
    szResult += " ";

    intToString ( szTempBuf, pTM->tm_year+1900 );
    szResult += szTempBuf;
    szResult += ", ";
    intToString ( szTempBuf, pTM->tm_hour );
    szResult += szTempBuf;
    szResult += ":";
    intToString ( szTempBuf, pTM->tm_min );
    szResult += szTempBuf;
    szResult += ":";
    intToString ( szTempBuf, pTM->tm_sec );
    szResult += szTempBuf;

    return szResult;
}
/**
 * @brief test string for containing utf8 characters
 *
 * @param str const char pointer to string to test
 * @return bool true - contain UTF8 chars, false - not
 **/
bool isStringUTF8 ( const char *str )
{
    int   i;
    unsigned char cOctets;  // octets to go in this UTF-8 encoded character
    unsigned char chr;
    bool  bAllAscii= true;
    long iLen = ( long ) strlen ( str );

    cOctets= 0;
    for ( i= 0; i <iLen; i++ )
    {

        chr = ( unsigned char ) str[i];

        if ( ( chr & 0x80 ) != 0 ) bAllAscii= false;

        if ( cOctets == 0 )
        {
            if ( chr>= 0x80 )
            {
                do
                {
                    chr <<= 1;
                    cOctets++;
                }
                while ( ( chr & 0x80 ) != 0 );

                cOctets--;
                if ( cOctets == 0 ) return false;
            }
        }
        else
        {
            if ( ( chr & 0xC0 ) != 0x80 )
                return false;

            cOctets--;
        }
    }
    if ( cOctets> 0 )
        return false;
    if ( bAllAscii )
        return false;
    return true;
}
/**
 * @brief split string into tokens
 *
 * @param src source string to split
 * @param sep seporator - string containing the delimiter
 * @return vector< string > vector of tokens
 **/
vector<string> strSplit ( const string &src, const string &sep )
{
    vector<string> res;
    string s;
    for ( string::const_iterator i = src.begin(); i != src.end(); i++ )
    {
        if ( sep.find ( *i ) != string::npos )
        {
            if ( s.length() ) res.push_back ( s );
            s = "";
        }
        else
        {
            s += *i;
        }
    }
    if ( s.length() ) res.push_back ( s );
    return res;
}
time_t convTimePeriod ( uint dLength, char dType )
{
    time_t rawtime = 0;
    if ( dLength == 0 )
        return rawtime;
    struct tm * ti = localtime ( &rawtime );
    switch ( dType )
    {
    case 'h':		// hours
        ti->tm_hour += dLength;
        break;
    case 'd':		// days
        ti->tm_mday += dLength;
        break;
    case 'w':		// weeks
        ti->tm_mday += 7 * dLength;
        break;
    case 'm':		// months
        ti->tm_mon += dLength;
        break;
    case 'y':		// years
        // are leap years considered ? do we care ?
        ti->tm_year += dLength;
        break;
    default:		// minutes
        ti->tm_min += dLength;
        break;
    }
    return mktime ( ti );
}
void logError ( const char *str )
{
    FILE *logfile;
    if ( ( logfile = fopen ( Config::getSingletonPtr()->getParam(Config::LS_ERROR_LOG_PATH).c_str(), "a+" ) ) )
    {
        time_t		now;
        struct tm	ptm;

        time ( &now );
        localtime_r ( &now, &ptm );

        fprintf ( logfile, "%04d-%02d-%02d %02d:%02d:%02d %s\n",
                  ptm.tm_year+1900, ptm.tm_mon+1, ptm.tm_mday,
                  ptm.tm_hour, ptm.tm_min, ptm.tm_sec, str );
        fclose ( logfile );
    }
}

void logTrace ( const char *str )
{
    FILE *logfile;
    if ( ( logfile = fopen ( Config::getSingletonPtr()->getParam(Config::LS_ERROR_LOG_PATH).c_str(), "a+" ) ) )
    {
        time_t		now;
        struct tm	ptm;

        time ( &now );
        localtime_r ( &now, &ptm );

        fprintf ( logfile, "%04d-%02d-%02d %02d:%02d:%02d %s\n",
                  ptm.tm_year+1900, ptm.tm_mon+1, ptm.tm_mday,
                  ptm.tm_hour, ptm.tm_min, ptm.tm_sec, str );
        fclose ( logfile );
    }
}
