#pragma once

template<typename CArray>
class CArrayIterator
{
public:
  using iterator_category = std::random_access_iterator_tag;
  using value_type = typename CArray::value_type;
  using difference_type = std::ptrdiff_t;
  using pointer = typename value_type *;
  using reference = value_type &;

  CArrayIterator(
      pointer _ptr
    )
    : ptr(_ptr) 
  { 
  }

  CArrayIterator & operator++()
  {
    ptr++;
    return *this;
  }

  CArrayIterator operator++(int)
  {
    auto temp(*this);
    ++(*this);
    return temp;
  }

  CArrayIterator & operator--()
  {
    ptr--;
    return *this;
  }

  CArrayIterator operator--(int)
  {
    auto temp(*this);
    --(*this);
    return temp;
  }

  reference operator[](
      typename CArray::size_type _index
    )
  {
    return *(ptr + _index);
  }

  reference operator*()
  {
    return *ptr;
  }
  
  const reference operator*() const 
  {
    return *ptr;
  }

  pointer operator->()
  {
    return ptr;
  }

  bool operator==(
      const CArrayIterator & _rhs
    ) const
  {
    return ptr == _rhs.ptr;
  }

  bool operator!=(
      const CArrayIterator & _rhs
    ) const
  {
    return !(*this == _rhs);
  }

  difference_type operator-(
      const CArrayIterator & _rhs
    ) const
  {
    return ptr - _rhs.ptr;
  }

  CArrayIterator & operator+=(
      difference_type _off
    )
  {
    this->ptr += _off;
    return *this;
  }

  CArrayIterator & operator-=(
      difference_type _off
    )
  {
    this->ptr -= _off;
    return *this;
  }

  bool operator<(
      CArrayIterator _rhs
    )
  {
    return ptr < _rhs.ptr;
  }
private:
  pointer ptr;
};

template <class CArrayIterator>
CArrayIterator operator+(
    typename CArrayIterator::difference_type _off,
    CArrayIterator _rhs
  ) 
{
  _rhs += _off;
  return _rhs;
}

template <class CArrayIterator>
CArrayIterator operator+(
    CArrayIterator _rhs,
    typename CArrayIterator::difference_type _off
  )
{
  _rhs += _off;
  return _rhs;
}

template <class CArrayIterator>
CArrayIterator operator-(
    CArrayIterator _rhs,
    typename CArrayIterator::difference_type _off
  )
{
  _rhs -= _off;
  return _rhs;
}

template <class CArrayIterator>
CArrayIterator operator-(
    typename CArrayIterator::difference_type _off,
    CArrayIterator _rhs
  )
{
  _rhs -= _off;
  return _rhs;
}