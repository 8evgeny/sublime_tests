#include <string>
#include <vector>

class Database
{
//public:
  Database()
  {
    // read from book.txt
  }
public:
  std::string find_record(const std::string& name)
  {
    // find it!
    return {};
  }

  std::vector<std::string> lines;

  static Database& get()
  {
    static Database db;
    return db;
  }
};

struct RecordFinder
{
  std::vector<std::string> find_all(std::vector<std::string> names)
  {
    auto db = Database::get();

    std::vector<std::string> result;
    for (auto& name : names)
        result.push_back(db.find_record(name));

    return result;
  }
};

void foo()
{
  Database::get().find_record("");
}

void bar()
{
  
}