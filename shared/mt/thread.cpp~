#include "thread.h"
#include "common.h"

using namespace std;

bool AtomicBoolean::setVal( bool val )
{
    unsigned int oldval = 0;

    if ( val )
        oldval = Value.setVal( 1 );
    else
        oldval = Value.setVal( 0 );

    return ( oldval & 1 );
}

unsigned int AtomicCounter::operator++()
{
    unsigned int val = 0;

    val = __sync_add_and_fetch( &Value, 1 );

    return val;
}

unsigned int AtomicCounter::operator--()
{
    unsigned int val = 0;

    val = __sync_add_and_fetch( &Value, -1 );

    return val;
}
unsigned int AtomicULong::addVal( unsigned long AddValue )
{
    unsigned long val = 0;

    val = __sync_add_and_fetch( &Value, AddValue );

    return val;
}
unsigned int AtomicULong::setVal( unsigned long NewValue )
{
    unsigned long ret = 0;

    ret = __sync_val_compare_and_swap( &Value, Value, NewValue );

    return ret;
}

float AtomicFloat::setVal( float NewValue )
{
    unsigned long iv = 0;
    float ret = 0.0f;

    iv = *( reinterpret_cast< unsigned long* >( &NewValue ) );
    ret = *( reinterpret_cast< float* >( Value.setVal( iv ) ));

    return ret;
}
float AtomicFloat::getVal()
{
    float val = 0.0f;

    val = *( reinterpret_cast< float* >( Value.getVal() ) );

    return val;
}

#define recursive_mutex_flag PTHREAD_MUTEX_RECURSIVE_NP

bool Mutex::attr_initalized = false;
pthread_mutexattr_t Mutex::attr;

Mutex::Mutex()
{
    if (!attr_initalized)
    {
        pthread_mutexattr_init(&attr);
        pthread_mutexattr_settype(&attr, recursive_mutex_flag);
        attr_initalized = true;
    }

    pthread_mutex_init(&mutex, &attr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutex);
}
