// Multi Index

#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <string>
#include <iostream>


struct User
{
    int id;
    std::string name;
    int age;
};

int main()
{
    boost::multi_index::multi_index_container<
            User,
            boost::multi_index::indexed_by<
                    boost::multi_index::hashed_unique<
                            boost::multi_index::member<
                                    User, int, &User::id
                            >
                    >,
                    boost::multi_index::hashed_non_unique<
                            boost::multi_index::member<
                                    User, std::string, &User::name
                            >
                    >,
                    boost::multi_index::hashed_non_unique<
                            boost::multi_index::member<
                                User, int, &User::age
                            >
                    >
            >
    > staff;

    auto x = staff.insert({0, "root", 32});
    std::cout << x.first->name << ", " << x.second << std::endl;
    x = staff.insert({0, "sergey", 32});
    std::cout << x.first->name << ", " << x.second << std::endl;
    staff.insert({1, "oleg", 23});
    staff.insert({2, "andrew", 19});

    auto &index_by_id = staff.get<0>();
    std::cout << "count(id=0)=" << index_by_id.count(0) << std::endl;

    auto &index_by_name = staff.get<1>();
    auto oleg = index_by_name.find("oleg");
    std::cout << "id=" << oleg->id << ", name=" << oleg->name << ", age=" << oleg->age << std::endl;

    auto &index_by_age = staff.get<2>();
    std::cout << "count(age=32)=" << index_by_age.count(32) << std::endl;
}
