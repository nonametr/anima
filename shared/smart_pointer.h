#ifndef SMART_POINTER_H
#define SMART_POINTER_H

class ReferenceCounter
{
public:
   ReferenceCounter() : ref_count(0)
   {}
   inline bool release()   { return __sync_add_and_fetch( &ref_count, -1 ); };
   inline void addRef()    { __sync_add_and_fetch( &ref_count, 1 ); };
private:
   volatile unsigned int ref_count;
};

template <typename T>
class SmartPtr
{
public:
   SmartPtr() : ptr(NULL), rc(NULL), index(0)
   {
       rc = new ReferenceCounter();
       rc->addRef();
   };
   SmartPtr(T* pValue, unsigned int v_index) : ptr(pValue), rc(NULL), index(v_index)
   {
       rc = new ReferenceCounter();
       rc->addRef();
   }
   ~SmartPtr()
   {
       if(!rc->release())
       {
           if(ptr)
               delete ptr;
           if(rc)
               delete rc;
       }
   };
   SmartPtr(const SmartPtr<T>& sp) : ptr(sp.ptr), rc(sp.rc), index(sp.index)
   {
       rc->addRef();
   }
   SmartPtr<T>& operator = (const SmartPtr<T>& sp)
   {
       if (this != &sp)
       {
           if(!rc->release())
           {
               if(ptr)
               delete ptr;
               delete rc;
           }
           ptr     = sp.ptr;
           rc      = sp.rc;
           index   = sp.index;
           rc->addRef();
       }
       return *this;
   }

   SmartPtr<T>& operator = (const T* pointer)
   {
       if (this->ptr != pointer)
       {
           if(!rc->release())
           {
               delete ptr;
               delete rc;
           }
           ptr = pointer;
           rc->addRef();
       }
       return *this;
   }

   T* operator-> () const  { return ptr; }
   T& operator*() const    { return *ptr; }
private:
   T *ptr;
   ReferenceCounter *rc;
   unsigned int index;
};

#endif // SMART_POINTER_H
