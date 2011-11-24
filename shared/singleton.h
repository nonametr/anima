#ifndef SINGLETON_H
#define SINGLETON_H

#include "common.h"

template < class type > class Singleton
{
public:
    /// Destructor
    virtual ~Singleton( )
    {
        this->singleton_ptr = 0;
    }

    inline static type & getSingleton( )
    {
        ASSERT ( singleton_ptr );
        return *singleton_ptr;
    }
    inline static type * getSingletonPtr( )
    {
        ASSERT ( singleton_ptr );
        return singleton_ptr;
    }

protected:
    /// Constructor
    Singleton( )
    {
        /// If you hit this assert, this singleton already exists -- you can't create another one!
        ASSERT ( this->singleton_ptr == 0 );
        this->singleton_ptr = static_cast<type *> ( this );
    }

    /// Singleton pointer, must be set to 0 prior to creating the object
    static type * singleton_ptr;
};

/// Should be placed in the appropriate .cpp file somewhere
#define initialiseSingleton( type ) \
  template <> type * Singleton < type > :: singleton_ptr = 0

#define initialiseTemplateSingleton( temp, type ) \
  template <> temp< type > * Singleton < temp< type > > :: singleton_ptr = 0

#endif // SINGLETON_H
