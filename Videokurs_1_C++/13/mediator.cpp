// Посредник (Mediator)

// role & danger
// tags private public

#include <iostream>
#include <map>
#include <set>
#include <string>

enum class Role {
    user, admin
};

struct User {
    std::string name;
    Role role;
};

class Perm {
    std::map<std::string, Role> ops = {{"drop",   Role::admin},
                                       {"create", Role::admin},
                                       {"select", Role::user}};

public:
    bool enable_for(const std::string& op, Role role)
    {
        auto i = ops.find(op);
        if (i!=std::end(ops)) {
            return i->second==role;
        }
        return false;
    }
};

int main(int, char* [])
{
    Perm perm;

    auto v = User{"вася", Role::user};
    auto p = User{"петя", Role::admin};

    std::cout << perm.enable_for("drop", v.role) << std::endl;
    std::cout << perm.enable_for("drop", p.role) << std::endl;

    return 0;
}
