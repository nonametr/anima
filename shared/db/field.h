#ifndef FIELD_H
#define FIELD_H

#include "../common.h"

class Field
{
public:

    inline void setValue(char* value) {
        mValue = value;
    }

    inline const char* getString() {
        return mValue;
    }
    inline float getFloat() {
        return mValue ? static_cast<float>(atof(mValue)) : 0;
    }
    inline bool getBool() {
        return mValue ? atoi(mValue) > 0 : false;
    }
    inline uint8 getUInt8() {
        return mValue ? static_cast<uint8>(atol(mValue)) : 0;
    }
    inline int8 getInt8() {
        return mValue ? static_cast<int8>(atol(mValue)) : 0;
    }
    inline uint16 getUInt16() {
        return mValue ? static_cast<uint16>(atol(mValue)) : 0;
    }
    inline int16 getInt16() {
        return mValue ? static_cast<int16>(atol(mValue)) : 0;
    }
    inline uint32 getUInt32() {
        return mValue ? static_cast<uint32>(atol(mValue)) : 0;
    }
    inline int32 getInt32() {
        return mValue ? static_cast<int32>(atol(mValue)) : 0;
    }
    uint64 getUInt64()
    {
        if (mValue)
        {
            uint64 value;
            sscanf(mValue, "%llu", (long long unsigned int*)&value);
            return value;
        }
        else
            return 0;
    }

private:
    char* mValue;
};

#endif // FIELD_H
