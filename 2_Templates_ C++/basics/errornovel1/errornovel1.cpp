#include <string>
#include <map>
#include <algorithm>

int main()
{
  std::map<std::string,double> coll;
  std::pair<std::string,double> pp;
  pp.first = "hellow";
  pp.second = 3.55;
  coll.insert(pp);
  coll.insert(std::pair<std::string,double>("qqq",4.66));
  //...
  // find the first nonempty string in coll:
  auto pos = std::find_if (coll.begin(), coll.end(),
                           [] (std::string const& s) { 
                             return s != "";
                           });
}
