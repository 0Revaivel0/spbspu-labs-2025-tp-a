#ifndef TYPES_HPP
#define TYPES_HPP
#include <iostream>
#include <string>

namespace shapkov
{
  struct doubleScientificIO
  {
    double& key;
  };
  struct ratio
  {
    std::pair< long long, unsigned long long > value;
    ratio(const std::pair<long long, unsigned long long>& p);
  };
  struct ratioIO
  {
    ratio& key;
  };
  struct stringIO
  {
    std::string& key;
  };
  struct labelIO
  {
    const std::string& exp;
  };
  std::istream& operator>>(std::istream& in, doubleScientificIO&& rhs);
  std::istream& operator>>(std::istream& in, ratioIO&& rhs);
  std::istream& operator>>(std::istream& in, stringIO&& rhs);
  std::istream& operator>>(std::istream& in, labelIO&& rhs);
  std::ostream& operator<<(std::ostream& out, const doubleScientificIO& rhs);
}
#endif
