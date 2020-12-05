// Хранитель (Memento)

#include <iostream>

class Memento {
    friend class Ops;

    int value;
public:
    Memento(int value_)
            :value(value_) { };
};

class Ops {
    int count = 0;

public:
    void do_it()
    {
        ++count;
    };

    void dump()
    {
        std::cout << count << std::endl;
    };

    Memento createSnapshot()
    {
        return Memento{count};
    }

    void restoreSnapshot(const Memento& memento)
    {
        count = memento.value;
    }
};

int main(int, char* [])
{
    Ops n;
    n.do_it();
    n.dump();

    auto snap = n.createSnapshot();

    n.do_it();
    n.dump();

    n.restoreSnapshot(snap);
    n.dump();

    return 0;
}
