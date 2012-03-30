/* 
 * File:   urlencode.h
 * Author: nonametr
 *
 * Created on May 5, 2011, 4:35 AM
 */

#ifndef URLENCODE_H
#define	URLENCODE_H

#include <string>
#include <string.h>
#include <malloc.h>

using namespace std;

int UrlDecode(const char *source, char *dest);
int UrlEncode(const char *source, char *dest, unsigned max);
string UrlDecodeString(const std::string & encoded);
string UrlEncodeString(const std::string & decoded);

#endif	/* URLENCODE_H */

