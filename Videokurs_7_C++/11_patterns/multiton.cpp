// Пул одиночек (Multiton)

#include <iostream>
#include <map>

enum class Tag { main, db };

class Logger {
    Tag t;

public:
    Logger& operator=(const Logger&) = delete;
    static Logger& Instance(Tag t)
    {
        static std::map<Tag, Logger> instance;
        auto i = instance.find(t);
        if (i==instance.end()) {
            bool b;
            std::tie(i, b) = instance.emplace(std::make_pair(t, Logger(t)));
        }
        return i->second;
    }
    void info(const std::string& message)
    {
        std::cerr << "   info: [" << int(t) << "] " << message << std::endl;
    }
    void warn(const std::string& message)
    {
        std::cerr << "warning: [" << int(t) << "] " << message << std::endl;
    }

private:
    explicit Logger(Tag t_)
            :t(t_)
    {
    }
};

int main(int, char const**)
{
    Logger::Instance(Tag::main).info("started");
    Logger::Instance(Tag::db).warn("no db");
    Logger::Instance(Tag::main).info("finished");

    return 0;
}
