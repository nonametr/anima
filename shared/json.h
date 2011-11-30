/*
* It's part of the SimpleJSON Library - http://mjpa.in/json
*
* Copyright (C) 2010 Mike Anchor and modified by I.Kuruch
*/

#ifndef JSON_H
#define JSON_H

#include <vector>
#include <string>
#include <map>

/// Simple function to check a string 's' has at least 'n' characters
static inline bool simplejson_wcsnlen(const char *s, size_t n) 
{
    if (s == 0)
        return false;

    const char *save = s;
    while (n-- > 0)
    {
        if (*(save++) == 0) return false;
    }

    return true;
}

/// Custom types
class JSONValue;
typedef std::vector<JSONValue*> JSONArray;
typedef std::map<std::string, JSONValue*> JSONObject;

#include "jsonvalue.h"

class JSON
{
    friend class JSONValue;

public:
    static JSONValue* Parse(const char *data);
    static std::string Stringify(const JSONValue *value);
protected:
    static bool SkipWhitespace(const char **data);
    static bool ExtractString(const char **data, std::string &str);
    static double ParseInt(const char **data);
    static double ParseDecimal(const char **data);
private:
    JSON();
};

#endif // JSON_H
