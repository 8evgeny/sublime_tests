// Объектный пул (Object pool)

#include <array>
#include <iostream>
#include <vector>

class PgConnection { };

class PgConnectionPool {
public:
    ~PgConnectionPool()
    {
        for (const auto& i : pool) {
            std::cout << i.connection << std::endl;
            delete i.connection;
        }
    }

    PgConnection* get()
    {
        for (auto& object : pool) {
            if (!object.busy) {
                object.busy = true;
                return object.connection;
            }
        }

        auto block = PgConnectionBlock{new PgConnection, true};
        pool.push_back(block);

        return block.connection;
    }

    void put(PgConnection* connection)
    {
        for (auto& object : pool) {
            if (object.connection==connection) {
                object.busy = false;
                break;
            }
        }
    }

private:
    struct PgConnectionBlock {
        PgConnection* connection;
        bool busy;
    };

    std::vector<PgConnectionBlock> pool;
};

int main(int, char* [])
{
    PgConnectionPool pool;

    auto report_conn = pool.get();
    pool.put(report_conn); // swap 58 & 60

    auto admin_conn = pool.get();
    pool.put(admin_conn);

    return 0;
}
