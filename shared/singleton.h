#ifndef SINGLETON_H
#define SINGLETON_H

#include "common.h"

template < class type > class Singleton
{
public:
    /// Destructor
    virtual ~Singleton( )
    {
        this->_singleton_ptr = 0;
    }

    inline static type & getSingleton( )
    {
        ASSERT ( _singleton_ptr );
        return *_singleton_ptr;
    }
    inline static type * getSingletonPtr( )
    {
        ASSERT ( _singleton_ptr );
        return _singleton_ptr;
    }

protected:
    /// Constructor
    Singleton( )
    {
        /// If you hit this assert, this singleton already exists -- you can't create another one!
        ASSERT ( this->_singleton_ptr == 0 );
        this->_singleton_ptr = static_cast<type *> ( this );
    }
private:
    /// Singleton pointer, must be set to 0 prior to creating the object
    static type * _singleton_ptr;
};

/// Should be placed in the appropriate .cpp file somewhere
#define initialiseSingleton( type ) \
  template <> type * Singleton < type > :: _singleton_ptr = 0
/// Should be placed in the appropriate .cpp file somewhere for tamplate singleton class
#define initialiseTemplateSingleton( temp, type ) \
  template <> temp< type > * Singleton < temp< type > > :: _singleton_ptr = 0

#endif // SINGLETON_H
