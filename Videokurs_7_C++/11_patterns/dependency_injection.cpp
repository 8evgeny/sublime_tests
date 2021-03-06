// Внедрение зависимости (Dependency Injection)

#include <array>
#include <iostream>

struct IStorage {
    virtual ~IStorage() = default;

    virtual void execute_query() = 0;
};

class Report {
    IStorage* storage;

public:
    explicit Report(IStorage* storage_)
            :storage(storage_) { }

    void print()
    {
        storage->execute_query();
        std::cout << "done" << std::endl;
    }
};

class TestStorage : public IStorage {
    void execute_query() override
    {
        std::cout << "... fetching data" << std::endl;
    }
};

int main(int, char* [])
{
    IStorage* s = new TestStorage;

    Report report(s);
    report.print();

    delete s;

    return 0;
}
