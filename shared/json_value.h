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

    bool isNull() const;
    bool isString() const;
    bool isBool() const;
    bool isNumber() const;
    bool isArray() const;
    bool isObject() const;

    const std::string &getString() const;
    bool asBool() const;
    double asNumber() const;
    const JSONArray &asArray() const;
    const JSONObject &asObject() const;

    std::string stringify() const;

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
