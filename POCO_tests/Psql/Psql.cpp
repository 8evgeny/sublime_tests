#include "Poco/Data/Session.h"
#include "Poco/Data/PostgreSQL/Connector.h"
#include <vector>
#include <iostream>

#include <Poco/ActiveRecord/Context.h>
#include <Poco/Data/PostgreSQL/PostgreSQLException.h>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;

struct Person
{
    std::string name;
    std::string address;
    int         age;
};

int main(int argc, char** argv)
{

    // register PostgreSQL connector
    Poco::Data::PostgreSQL::Connector::registerConnector();
    // create a session
    Poco::Data::Session session(Poco::Data::PostgreSQL::Connector::KEY, "host=127.0.0.1 user=postgres password=postgres dbname=niokrDB port=5432");
    try {
        session << "DROP TABLE IF EXISTS Person", now;
        // (re)create table
        session << "CREATE TABLE Person (Name VARCHAR(30), Address VARCHAR, Age INTEGER)", now;

        // insert some rows
        Person person =
        {
            "Bart Simpson",
            "Springfield",
            12
        };

        Statement insert(session);
        insert << "INSERT INTO Person VALUES($1, $2, $3)",
            use(person.name),
            use(person.address),
            use(person.age);
        insert.execute();

        person.name    = "Lisa Simpson";
        person.address = "Springfield";
        person.age     = 10;

        insert.execute();

    //     a simple query
        Statement select(session);
        select << "SELECT Name, Address, Age FROM Person",
            into(person.name),
            into(person.address),
            into(person.age),
            range(0, 1); //  iterate over result set one row at a time

        while (!select.done())
        {
            select.execute();
            std::cout << person.name << " " << person.address << " " << person.age << std::endl;
        }
    } catch (Poco::Data::PostgreSQL::StatementException &e) {
                std::cout << e.displayText()  << std::endl;
                return 1;
        }
    return 0;
}
