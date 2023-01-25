#include <iostream>
#include <string>
#include <algorithm>
#include <random>

#include "CArray.h"

class Test
{
public:

  void run()
  {
    test_int();
    test_string();
  }

private:

  void test_int()
  {
    using size_type = CArray<int>::size_type;
    CArray<int> arr;

    // 1.1.добавление в цикле 20 случайных чисел в диапазоне от 0 до 100.
    std::cout << "1.1 Adding random numbers\n";

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    const size_type count = 20;
    for (size_type i = 0; i < count; i++)
      arr.push_back(dist(mt));

    print_array(arr);

    // 1.2.упорядочивание получившегося набора чисел по возрастанию.
    std::cout << "1.2 Sorting\n";

    std::sort(arr.begin(), arr.end());

    print_array(arr);

    // 1.3.удаление каждого 2 элемента.
    std::cout << "1.3 Erasing every 2th element\n";

    for (size_type i = 0; i < arr.size() / 2; i++)
      arr[i] = arr[2 * i];
    arr.resize(arr.size() / 2);

    print_array(arr);

    // 1.4.вставка 10 случайных чисел в диапазоне от 0 до 100 на случайные позиции.
    std::cout << "1.4 Inserting random numbers\n";

    const size_type insert_count = 10;
    for (size_type i = 0; i < insert_count; i++)
    {
      const size_type index = dist(mt) % arr.size();
      const int value = dist(mt);
      arr.insert(index, value);
    }

    print_array(arr);

    // 1.5.очистка контейнера
    std::cout << "1.5 Clearing\n";

    arr.clear();

    print_array(arr);
  }

  void test_string()
  {
    using size_type = CArray<std::string>::size_type;
    CArray<std::string> arr;

    // 2.1.добавление в цикле 15 случайно выбранных слов, состоящих из латинских букв в нижнем регистре.
    std::cout << "2.1 Adding words\n";

    const size_type count = 15;
    for (size_type i = 0; i < count; i++)
      arr.push_back(random_string());

    print_array(arr);

    // 2.2.упорядочивание получившегося набора слов по возрастанию.
    std::cout << "2.2 Sorting\n";

    std::sort(arr.begin(), arr.end());

    print_array(arr);

    // 2.3.удаление каждого слова, включающего в себя любую из букв a, b, c, d, e.
    std::cout << "2.3 Erasing every appropriate word\n";

    auto is_appropriate = [] (
        const std::string & s
      )
    {
      const std::string pattern = "abcde";
      for (auto c : s)
      {
        if (pattern.find(c) != std::string::npos)
          return true;
      }

      return false;
    };

    for (size_type i = arr.size(); i != 0; i--)
    {
      const auto & str = arr[i - 1];

      if (is_appropriate(str))
        arr.erase(i - 1);
    }

    print_array(arr);

    // 2.4.вставка 3 новых случайно выбранных слов на случайные позиции
    std::cout << "2.4 Inserting words\n";

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    const size_type insert_count = 3;
    for (size_type i = 0; i < insert_count; i++)
    {
      const size_type index = dist(mt) % arr.size();
      const std::string value = random_string();
      arr.insert(index, value);
    }

   print_array(arr);
  }

  template<typename TData>
  void print_array(
      CArray<TData> & _array
    )
  {
    for (auto val : _array)
      std::cout << val << " ";
    std::cout << "\n";
  }

  std::string random_string() 
  {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, 100);

    const std::string::size_type len = 2;
    const char alphanum[] = "abcdefghijklmnopqrstuvwxyz";
    std::string tmp_s;
    tmp_s.reserve(len);

    for (std::string::size_type i = 0; i < len; i++) {
      tmp_s += alphanum[dist(mt) % (sizeof(alphanum) - 1)];
    }

    return tmp_s;
  }
};

int main()
{
  Test().run();
  return 0;
}