#pragma once

#include "CArrayIterator.h"

template<typename TData>
class CArray
{
public:
  using value_type = TData;
  using size_type = unsigned int;
  using iterator = CArrayIterator<CArray<TData>>;

  CArray()
  {
    const size_type default_capacity = 2;
    realloc(default_capacity);
  }

  CArray(
      const CArray & _array
    )
  {
    realloc(_array.capacity);
    array_size = _array.array_size;
    for (size_type i = 0; i < _array.size(); i++)
      new(&data[i]) TData(_array.data[i]);
  }

  ~CArray()
  {
    clear();
    ::operator delete(data, capacity * sizeof(TData));
  }

  void push_back(
      const TData & _value
    )
  {
    if (array_size >= capacity)
      realloc(capacity * 2);

    new(&data[array_size]) TData(_value);
    array_size++;
  }

  void insert(
     size_type _index,
     const TData & _value
    )
  {
    if (array_size == 0)
    {
      push_back(_value);
      return;
    }
    if (_index > array_size)
      return;

    if (array_size >= capacity)
      realloc(capacity * 2);
    
    array_size++;
    for (size_type i = array_size - 1; i > _index; i--)
      new(&data[i]) TData(std::move(data[i - 1]));
    
    new(&data[_index]) TData(_value);
  }

  void erase(
     size_type _index
    )
  {
    if (array_size == 0)
      return;

    if (_index > array_size)
      return;

    for (size_type i = _index; i < array_size - 1; i++)
      new(&data[i]) TData(std::move(data[i + 1]));

    array_size--;
  }

  void clear()
  {
    std::destroy(begin(), end());

    array_size = 0;
  }

  size_type size() const
  {
    return array_size;
  }

  TData & operator[](
      size_type _index
    )
  {
    return data[_index];
  }

  const TData & operator[] (
      size_type _index
    ) const
  {
    return data[_index];
  }

  iterator begin()
  {
    return iterator(data);
  }

  iterator end()
  {
    return iterator(data + array_size);
  }

  void resize(
      size_type _new_size
    )
  {
    if (_new_size < array_size)
    {
      std::destroy(begin() + _new_size, end());

      array_size = _new_size;
      return;
    }
    
    if (_new_size > capacity)
    {
      realloc(_new_size);
      return;
    }
  }

protected:
  TData * data = nullptr;

  size_type array_size = 0;
  size_type capacity = 0;

  void realloc(
      size_type _new_capacity
    )
  {
    if (array_size > _new_capacity)
      array_size = _new_capacity;

    TData * new_data = static_cast<TData*>(::operator new (_new_capacity * sizeof(TData)));

    for (size_type i = 0; i < array_size; i++)
    {
      new(&new_data[i]) TData(std::move(data[i]));
      data[i].~TData();
    }

    ::operator delete(data, capacity * sizeof(TData));
    data = new_data;
    capacity = _new_capacity;
  }
};