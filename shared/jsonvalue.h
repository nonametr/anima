/*
* It's part of the SimpleJSON Library - http://mjpa.in/json
*
* Copyright (C) 2010 Mike Anchor and modified by I.Kuruch
*/

#ifndef JSONVALUE_H
#define JSONVALUE_H

#include <vector>
#include <string>

#include "json.h"

class JSON;

enum JSONType { JSONType_Null, JSONType_String, JSONType_Bool, JSONType_Number, JSONType_Array, JSONType_Object };

class JSONValue
{
    friend class JSON;

public:
    JSONValue(/*NULL*/);
    JSONValue(const char *m_char_value);
    JSONValue(const std::string &m_string_value);
    JSONValue(bool m_bool_value);
    JSONValue(double m_number_value);
    JSONValue(const JSONArray &m_array_value);
    JSONValue(const JSONObject &m_object_value);
    ~JSONValue();

    bool IsNull() const;
    bool IsString() const;
    bool IsBool() const;
    bool IsNumber() const;
    bool IsArray() const;
    bool IsObject() const;

    const std::string &AsString() const;
    bool AsBool() const;
    double AsNumber() const;
    const JSONArray &AsArray() const;
    const JSONObject &AsObject() const;

    std::string Stringify() const;

protected:
    static JSONValue *Parse(const char **data);

private:
    static std::string StringifyString(const std::string &str);

    JSONType type;
    std::string string_value;
    bool bool_value;
    double number_value;
    JSONArray array_value;
    JSONObject object_value;
};

#endif // JSONVALUE_H
