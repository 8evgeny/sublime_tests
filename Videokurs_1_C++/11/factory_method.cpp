// Фабричный метод (Factory method)

#include <iostream>

enum class Storage { mysql, postgres };

struct IStorage {
    virtual ~IStorage() = default;

    virtual void open() = 0;
    virtual void execute_query() = 0;
    virtual void close() = 0;
};

class MysqlStorage : public IStorage {
    void open() override
    {
        std::cout << "connect to mysql" << std::endl;
    }

    void execute_query() override
    {
        std::cout << "fetch mysql result" << std::endl;
    }

    void close() override
    {
        std::cout << "disconnect from mysql" << std::endl;
    }
};

class PostgresStorage : public IStorage {
    void open() override
    {
        std::cout << "connect to pg" << std::endl;
    }

    void execute_query() override
    {
        std::cout << "fetch pg result" << std::endl;
    }

    void close() override
    {
        std::cout << "disconnect from pg" << std::endl;
    }
};

int main(int argc, char* [])
{
    auto environment = argc ? Storage::postgres : Storage::mysql;

    IStorage* storage;
    switch (environment) {
    case Storage::mysql:storage = new MysqlStorage();
        break;

    case Storage::postgres:storage = new PostgresStorage();
        break;
    }

    //

    storage->open();
    storage->execute_query();
    storage->close();

    delete storage;

    return 0;
}
