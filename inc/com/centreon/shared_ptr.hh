/*
** Copyright 2011-2013 Merethis
**
** This file is part of Centreon Clib.
**
** Centreon Clib is free software: you can redistribute it and/or modify
** it under the terms of the GNU Affero General Public License as
** published by the Free Software Foundation, either version 3 of the
** License, or (at your option) any later version.
**
** Centreon Clib is distributed in the hope that it will be useful, but
** WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
** Affero General Public License for more details.
**
** You should have received a copy of the GNU Affero General Public
** License along with Centreon Clib. If not, see
** <http://www.gnu.org/licenses/>.
*/

#ifndef CC_SHARED_PTR_HH
#  define CC_SHARED_PTR_HH

#  include <cstddef>
#  include "com/centreon/namespace.hh"

CC_BEGIN()

/**
 *  @class shared_ptr shared_ptr.hh
 *  @brief Keep pointer reference.
 *
 *  This class will delete the pointer it is holding when it goes out
 *  of scope, provided no other QSharedPointer objects are
 *  referencing it.
 */
template <typename T>
class           shared_ptr {
  template          <typename U>
  friend class      shared_ptr;
public:
  typedef void (*pdeleter)(void*);

  /**
   *  Constructor.
   *
   *  @param[in] data Pointer.
   */
                shared_ptr(T* data = NULL, pdeleter deleter = &operator delete)
                  : _count(data ? new unsigned int(1) : NULL),
                    _data(data),
                    _deleter(deleter) {}

  /**
   *  Copy constructor.
   *
   *  @param[in] right Object to copy.
   */
                shared_ptr(shared_ptr const& right)
                  : _count(NULL),
                    _data(NULL),
                    _deleter(NULL) {
    operator=(right);
  }

  /**
   *  Copy constructor.
   *
   *  @param[in] right Object to copy.
   */
                template<typename U>
                shared_ptr(shared_ptr<U> const& right)
                  : _count(NULL),
                    _data(NULL),
                    _deleter(NULL) {
    operator=(right);
  }

  /**
   *  Destructor.
   */
                ~shared_ptr() throw () {
    clear();
  }

  /**
   *  Assignment operator.
   *
   *  @param[in] right Object to copy.
   *
   *  @return This object.
   */
  shared_ptr&   operator=(shared_ptr const& right) {
    if (this != &right) {
      clear();
      _data = right._data;
      _deleter = right._deleter;
      _count = right._count;
      if (_count)
        ++(*_count);
    }
    return (*this);
  }

  /**
   *  Assignment operator.
   *
   *  @param[in] right Object to copy.
   *
   *  @return This object.
   */
  template<typename U>
  shared_ptr&   operator=(shared_ptr<U> const& right) {
    if (_data != static_cast<T*>(right._data)) {
      clear();
      if (right._data) {
        _data = static_cast<T*>(right._data);
        _deleter = right._deleter;
        _count = right._count;
        if (_count)
          ++(*_count);
      }
    }
    return (*this);
  }

  /**
   *  Equal operator.
   *
   *  @param[in] right The object to compare.
   *
   *  @return True if is the same object, otherwize false.
   */
  bool          operator==(shared_ptr<T> const& right) const throw () {
    return (_data == right._data);
  }

  /**
   *  Equal operator.
   *
   *  @param[in] right The object to compare.
   *
   *  @return True if is the same object, otherwize false.
   */
  bool          operator!=(shared_ptr<T> const& right) const throw () {
    return (!operator==(right));
  }

  /**
   *  Dereferencing pointer.
   *
   *  @return Dereferenced pointer.
   */
  T&            operator*() const throw () {
    return (*_data);
  }

  /**
   *  Get the pointer associate with this object.
   *
   *  @return Pointer.
   */
  T*            operator->() const throw () {
    return (_data);
  }

  /**
   *  Clear pointer and reference counter.
   */
  void          clear() throw () {
    if (_count && !(--(*_count))) {
      _deleter(_data);
      delete _count;
    }
    _count = NULL;
    _data = NULL;
    return ;
  }

  /**
   *  Get the pointer associated with this object.
   *
   *  @return Pointer associated with this object.
   */
  T*            get() const throw () {
    return (_data);
  }

  /**
   *  Check if data is null.
   *
   *  @return True if data is null, otherwise false.
   */
  bool          is_null() const throw () {
    return (!_data);
  }

private:
  unsigned int* _count;
  T*            _data;
  pdeleter      _deleter;
};

CC_END()

#endif // !CC_SHARED_PTR_HH

