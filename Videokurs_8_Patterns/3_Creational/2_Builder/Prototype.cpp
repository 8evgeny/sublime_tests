#include <string>


enum class Currency
{
  USD,
  GBP,
  EUR
};

struct Expense
{
  std::string type;
  float amount;
  Currency currency;
};

