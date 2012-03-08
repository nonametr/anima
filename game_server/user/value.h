#ifndef VALUE_H
#define VALUE_H

class Value
{
public:
    enum TYPE {UNKNOWN, STRING, INT, INT64, FLOAT, DOUBLE} type;
    Value(TYPE v_type):type(v_type), d64(0.0)
    {}
    Value(){}
    
    string toStr(){ return str_val; }
    int toInt(){ return i32; }
    long long int toInt64(){ return i64; }
    float toFloat(){ return f32; }
    double toDouble(){ return d64; }
    
    static Value create(int val)		{ Value v(INT); v.i32 = val; v.need_update = true; return v; };
    static Value create(long long int val) 	{ Value v(INT64); v.i64 = val; v.need_update = true; return v; };
    static Value create(float val)		{ Value v(FLOAT); v.f32 = val; v.need_update = true; return v; };
    static Value create(double val)		{ Value v(DOUBLE); v.d64 = val; v.need_update = true; return v; };
    static Value create(string val)		{ Value v(STRING); v.str_val = val; v.need_update = true; return v; };
    
    string str_val;
    union
    {
        int i32;
        long long int i64;
        float f32;
        double d64;
    };
    bool need_update;
};

#endif // VALUE_H
