#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include "data_struct.hpp"

int main()
{
  std::vector< zholobov::DataStruct > data;
  while (!std::cin.eof()) {
    std::copy(std::istream_iterator< zholobov::DataStruct >(std::cin), std::istream_iterator< zholobov::DataStruct >(),
              std::back_inserter(data));
    if (std::cin.fail()) {
      std::cin.clear();
      std::string temp;
      std::getline(std::cin, temp);
    }
  }

  //  std::sort(data.begin(), data.end());

  std::copy(data.begin(), data.end(), std::ostream_iterator< zholobov::DataStruct >(std::cout, "\n"));

  return 0;
}
