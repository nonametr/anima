#ifndef VALUE_H
#define VALUE_H

class Value
{
public:
    enum TYPE {UNKNOWN, STRING, INT, INT64, FLOAT, DOUBLE} type;
    
    string toStr(){ return str_val; }
    int toInt(){ return i32; }
    long long int toInt64(){ return i64; }
    float toFloat(){ return f32; }
    double toDouble(){ return d64; }
    
    Value(TYPE v_type):type(v_type), d64(0.0)
    {}
    Value(){}
    Value(int val, bool update = false):type(INT), d64(0.0)		{ i32 = val; need_sql_update = update; };
    Value(long long int val, bool update = false):type(INT64), d64(0.0)	{ i64 = val; need_sql_update = update; };
    Value(float val, bool update = false):type(FLOAT), d64(0.0)		{ f32 = val; need_sql_update = update; };
    Value(double val, bool update = false):type(DOUBLE), d64(0.0)	{ d64 = val; need_sql_update = update; };
    Value(string val, bool update = false):type(STRING), d64(0.0)	{ str_val = val; need_sql_update = update; };
    
    string str_val;
    union
    {
        int i32;
        long long int i64;
        float f32;
        double d64;
    };
    bool need_client_update;
    bool need_sql_update;
};

#endif // VALUE_H
