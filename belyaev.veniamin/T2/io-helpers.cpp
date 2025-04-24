#include "io-helpers.hpp"
#include "stream-guard.hpp"

belyaev::DelimeterIO::DelimeterIO(char expected_, bool caseSensitive_):
  expected(expected_),
  caseSensitive(caseSensitive_)
{}

std::istream& belyaev::operator>>(std::istream& in, const DelimeterIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  char c = '0';
  in >> c;
  if (!dest.caseSensitive)
  {
    if (in && (tolower(c) != dest.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  else
  {
    if (in && (c != dest.expected))
    {
      in.setstate(std::ios::failbit);
    }
  }
  return in;
}

std::ostream& belyaev::operator<<(std::ostream& out, const DoubleEIO&& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  belyaev::StreamGuard streamGuard(out);

  int exp = 0;
  double mantissa = dest.value;

  if (mantissa == 0.0)
  {
    out << "0.0e+0";
    return out;
  }

  while (std::abs(mantissa) >= 10.0)
  {
    exp++;
    mantissa /= 10.0;
  }

  while (std::abs(mantissa) < 1.0)
  {
    exp--;
    mantissa *= 10.0;
  }

  out << mantissa;

  out << "e";
  if (exp >= 0)
  {
    out << "+";
  }
  else
  {
    out << "-";
  }
  out << exp;

  return out;
}

std::ostream& belyaev::operator<<(std::ostream& out, const PairLLIO& dest)
{
  std::ostream::sentry sentry(out);
  if (!sentry)
  {
    return out;
  }
  belyaev::StreamGuard streamGuard(out);

  out << "(:N ";
  out << dest.value.first;
  out << ":D ";
  out << dest.value.second;
  out << ":)";
  return out;
}

std::istream& belyaev::operator>>(std::istream& in, const DoubleEIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  std::string doubleHold;
  if (!std::getline(in, doubleHold, ':'))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (doubleHold.find('e') == doubleHold.find('E'))
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  try
  {
    size_t index = 0;
    double number = std::stod(doubleHold, &index);

    if (index != doubleHold.length())
    {
      in.setstate(std::ios::failbit);
      return in;
    }
    in.unget();
    dest.value = number;
  }
  catch (const std::exception& e)
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::istream& belyaev::operator>>(std::istream& in, const PairLLIO&& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }

  using sep = DelimeterIO;
  in >> sep{'('};
  in >> sep{':'};
  in >> sep{'N'};
  in >> dest.value.first;
  in >> sep{':'};
  in >> sep{'D'};
  in >> dest.value.second;
  in >> sep{':'};
  in >> sep{')'};
  return in;
}

std::istream& belyaev::operator>>(std::istream& in, const StringIO& dest)
{
  std::istream::sentry sentry(in);
  if (!sentry)
  {
    return in;
  }
  return std::getline(in >> DelimeterIO{'"'}, dest.value, '"');
}
