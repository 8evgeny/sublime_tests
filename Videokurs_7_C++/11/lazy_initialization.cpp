// Ленивая инициализация (Lazy initialization)

#include <iostream>
#include <utility>

class File {
    std::string name;

public:
    explicit File(std::string name)
            :name(std::move(name))
    {
        std::cout << "create " << name << std::endl;
    }
    ~File()
    {
        std::cout << "close " << name << std::endl;
    }
    void write(const std::string& line_)
    {
        std::cout << "write " << line_ << " into " << name << std::endl;
    }
};

class FileOnDemand {
    std::string name;
    File* file;

public:
    explicit FileOnDemand(std::string name)
            :name(std::move(name)), file(nullptr) { }
    ~FileOnDemand()
    {
        delete file;
    }
    File* operator->()
    {
        if (!file) {
            file = new File(name);
        }
        return file;
    }
};

int main(int, char* [])
{
    File/*OnDemand*/ file("test.txt");

    size_t n = 0/*2*/;
    for (size_t i = 0; i<n; ++i) {
        file.write(std::to_string(i));
    }

    return 0;
}
