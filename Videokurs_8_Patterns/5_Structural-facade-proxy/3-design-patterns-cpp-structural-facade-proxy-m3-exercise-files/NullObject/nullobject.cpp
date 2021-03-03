#include <cstdio>
#include <iostream>
#include <memory>
using namespace std;

#include <boost/lexical_cast.hpp>
using namespace boost;

struct Logger
{
  virtual ~Logger() = default;
  virtual void info(const string& s) = 0;
  virtual int warn(const string& s) = 0;
};

struct BankAccount
{
  std::shared_ptr<Logger> log;
  string name;
  int balance = 0;


  BankAccount(const std::shared_ptr<Logger>& logger, const string& name, const int balance)
    : log{logger},
      name{name},
      balance{balance}
  {
  }

  void deposit(int amount)
  {
    balance += amount;
    log->info("Deposited $" + lexical_cast<string>(amount)
      + " to " + name + ", balance is now $" + lexical_cast<string>(balance));
  }

  void withdraw(int amount)
  {
    if (balance >= amount)
    {
      balance -= amount;
      log->info("Withdrew $" + lexical_cast<string>(amount)
        + " from " + name + ", $" + lexical_cast<string>(balance) + " left");
    } 
    else
    {
      int count = log->warn("Tried to withdraw $" + lexical_cast<string>(amount) +
        " from " + name + " but couldn't due to low balance");
      if (count > 100)
      {
        exit(0);
      }
    }
  }
};

struct ConsoleLogger : Logger
{
  int count = 0;

  void info(const string& s) override
  {
    cout << "INFO: " << s << endl;
  }

  int warn(const string& s) override {
    cout << "WARNING!!! " << s << endl;
    return count++;
  }
};

struct NullLogger : Logger
{
  int warning_count;


  explicit NullLogger(const int warning_count)
    : warning_count{warning_count}
  {
  }

  void info(const string& s) override
  {
  }

  int warn(const string& s) override
  {
    return warning_count;
  }
};

int main(int ac, char* av)
{
  auto logger = make_shared<NullLogger>(10);
  BankAccount account{ logger, "primary account", 1000 };

  account.deposit(2000);
  account.withdraw(2500);
  account.withdraw(1000);

  getchar();
  return 0;
}
