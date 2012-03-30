#ifndef THREAD_H
#define THREAD_H

#define _MULTI_THREADED
#include <pthread.h>
#include <string>
#include "common.h"

using namespace std;

class Thread
{
public:
    Thread() {};
    virtual ~Thread() {};
    virtual void run() = 0;
    virtual void onShutdown() = 0;///it should be almost atomic. no general mutex locks 
    uint32 getTid() { return _tid; }
    void setTid(uint32 tid) { _tid = tid; }
private:
    uint32 _tid;
};

class AtomicUInt
{
public:
    AtomicUInt() {
        Value = 0;
    }

    AtomicUInt( unsigned int InitialValue ) {
        Value = InitialValue;
    }

    inline unsigned int addVal( unsigned int AddValue )
    {
        unsigned int val = 0;

        val = __sync_add_and_fetch( &Value, AddValue );

        return val;
    }
    inline unsigned int subVal( unsigned int SubValue )
    {
        unsigned int val = 0;

        val = __sync_sub_and_fetch( &Value, SubValue );

        return val;
    }
    inline unsigned int setVal( unsigned int NewValue )
    {
        unsigned int ret = 0;

        ret = __sync_val_compare_and_swap( &Value, Value, NewValue );

        return ret;
    }
    unsigned int getVal() {
        return Value;
    }


private:
    // Disabled copy constructor
    AtomicUInt( const AtomicUInt &other ) {}

    // Disabled assignment operator
    AtomicUInt operator=( AtomicUInt &other ) {
        return *this;
    }
protected:
    volatile unsigned int Value;
};

class AtomicULong
{
public:
    AtomicULong() {
        Value = 0;
    }

    AtomicULong( unsigned long InitialValue ) {
        Value = InitialValue;
    }

    unsigned int setVal( unsigned long NewValue );
    unsigned int addVal( unsigned long AddValue );
    unsigned int getVal() {
        return Value;
    }


private:
    // Disabled copy constructor
    AtomicULong( const AtomicULong &other ) {}

    // Disabled assignment operator
    AtomicULong operator=( AtomicULong &other ) {
        return *this;
    }
protected:
    volatile unsigned long Value;
};

class AtomicCounter : public AtomicUInt
{
public:
    AtomicCounter() {
        Value = 0;
    }
    AtomicCounter( unsigned int InitialValue ) {
        Value = InitialValue;
    }

    unsigned int operator++();

    unsigned int operator--();

private:
    // Disabled copy constructor
    AtomicCounter( const AtomicCounter &other ) {}

    // Disabled assignment operator
    AtomicCounter operator=( const AtomicCounter &other ) {
        return *this;
    }
};

class AtomicFloat {
public:
    AtomicFloat() : Value( 0 ) {}

    AtomicFloat( float InitialValue ) {
        unsigned long iv = *( reinterpret_cast< unsigned long* >( &InitialValue ) );
        Value.setVal( iv );
    }

    float setVal( float NewValue );

    float getVal();

private:
    // Disabled copy constructor
    AtomicFloat( const AtomicFloat& other ) {}

    // Disabled assignment operator
    AtomicFloat operator=( const AtomicFloat& other ) {
        return *this;
    }

    AtomicULong Value;
};

class AtomicBoolean
{
public:
    AtomicBoolean() : Value( 0 ) {}

    AtomicBoolean( bool val ) {
        if ( val )
            Value.setVal( 1 );
        else
            Value.setVal( 0 );
    }

    bool setVal( bool val );

    bool getVal() {
        unsigned int val = 0;

        val = Value.getVal();

        return ( val & 1 );
    }

private:
    // Disabled copy constructor
    AtomicBoolean( const AtomicBoolean &other ) {}

    // Disabled assignment operator
    AtomicBoolean operator=( const AtomicBoolean &other ) {
        return *this;
    }

    AtomicUInt Value;
};

class Mutex
{
public:
    /** Initializes a mutex class, with pthread_mutex_init
     */
    Mutex();
    /** Deletes the associated mutex
     */
    virtual ~Mutex();
    inline void lock()
    {
        pthread_mutex_lock(&mutex);
    }
    inline void unlock()
    {
        pthread_mutex_unlock(&mutex);
    }
    /** @return false if cannot be lock, true if it was locked.
     */
    inline bool try_1k_lock()
    {
	unsigned int cnt = 0;
	while(pthread_mutex_trylock(&mutex))
	{
	  cnt++;
	  if(cnt > 1000)
	    return false;
	}
        return true;
    }
    inline bool try_lock()
    {
        return (pthread_mutex_trylock(&mutex) == 0);
    }
protected:
    static bool attr_initalized;
    static pthread_mutexattr_t attr;
    /** pthread struct used in system calls
     */
    pthread_mutex_t mutex;
};

///Mutex for short locks
class FastMutex {
public:
    FastMutex(): m_lock(UNLOCKED)
    {}
    bool try_lock()
    {
        if (__sync_lock_test_and_set(&m_lock, LOCKED) == LOCKED)
        {
            return false;
        }
        return true;
    }
    void lock()
    {
        while (__sync_lock_test_and_set(&m_lock, LOCKED) == LOCKED)
        {
            sleep(1);
        }
    }
    void unlock()
    {
        __sync_lock_release(&m_lock);
    }
private:
    enum lock_state { UNLOCKED, LOCKED };
    volatile lock_state m_lock;
};
///Mutex for RW short locks
class FastRWMutex {
public:
    FastRWMutex(): m_lock(UNLOCKED), lock_counter(0)
    {}
    bool lock_use()
    {
        __sync_add_and_fetch( &lock_counter, 1 );

        if ( __sync_bool_compare_and_swap(&m_lock, UNLOCKED, LOCKED_IN_USE) )
        {
            return true;
        }
        if ( __sync_bool_compare_and_swap(&m_lock, LOCKED_IN_USE, LOCKED_IN_USE) )
        {
            return true;
        }
        __sync_add_and_fetch( &lock_counter, -1 );
        return false;
    }
    void unlock_use()
    {
        __sync_bool_compare_and_swap(&m_lock, lock_counter, UNLOCKED);// lock_counter.GetVal() = LOCKED_IN_USE = 1 => UNLOCKED

        __sync_add_and_fetch( &lock_counter, -1 );
        return;
    }
    void lock_write()
    {
        while ( !__sync_bool_compare_and_swap(&m_lock, lock_counter, LOCKED) )
        {
            sleep(1);
        }
    }
    void unlock_write()
    {
        if (__sync_bool_compare_and_swap(&m_lock, LOCKED, UNLOCKED))
            return;
    }
private:
    enum lock_state { UNLOCKED, LOCKED_IN_USE, LOCKED };
    volatile lock_state m_lock;
    volatile unsigned int lock_counter;
};

template<class T>
class FQueue
{
public:
    FQueue() {
        first = last = NULL;
        size = 0;
    }
    volatile unsigned int size;

    unsigned int get_size()
    {
        lock.lock();
        unsigned int retval = size;
        lock.unlock();
        return retval;
    }

    void push(T &item)
    {
        h* p = new h;
        p->value = item;
        p->pNext = NULL;

        lock.lock();
        if (last != NULL)//have some items
        {
            last->pNext = (h*)p;
            last = p;
            ++size;
        }
        else //first item
        {
            last = first = p;
            size = 1;
        }
        lock.unlock();
    }

    T pop_nowait() {
        return pop();
    }

    T pop()
    {
        lock.lock();
        if (size == 0)
        {
            lock.unlock();
            return NULL;
        }

        h* tmp = first;
        if (tmp == NULL)
        {
            lock.unlock();
            return NULL;
        }

        if (--size) //more than 1 item
            first = (h*)first->pNext;
        else //last item
        {
            first = last = NULL;
        }

        lock.unlock();

        T returnVal = tmp->value;
        delete tmp;
        return returnVal;
    }

private:
    struct h
    {
        T value;
        void* pNext;
    };

    h * first;
    h * last;

    Mutex lock;
};

#endif // THREAD_H
