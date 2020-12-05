// Одиночка (Singleton)

#include <iostream>

class Logger {
public:
    Logger(const Logger& root) = delete; // [2]
    Logger& operator=(const Logger&) = delete; // [3]

    static Logger& Instance()
    {
        static Logger instance;
        return instance;
    }

    void info(const std::string& message)
    {
        os << "   info: " << message << std::endl;
    }

    void warn(const std::string& message)
    {
        os << "warning: " << message << std::endl;
    }

private:
    Logger() // [1]
            :os{std::cerr} { }

    std::ostream& os; // [3]
};

int main(int, char* [])
{
//    Logger sly_newbie; // [1]
//    Logger sly_adv(Logger::Instance()); // [2]
//    Logger::Instance() = Logger::Instance(); // [3]
    Logger::Instance().info("started");
    Logger::Instance().warn("program is empty");

    return 0;
}
