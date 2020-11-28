// Компоновщик (Composite)

#include <iostream>
#include <vector>

struct FileSystemObject
{
    virtual ~FileSystemObject() = default;

    virtual int size() = 0;
    virtual void add_object(FileSystemObject *) {};
};

class File : public FileSystemObject
{
    int size() override
    {
        return 1024;
    }
};

class Directory : public FileSystemObject
{
public:
    int size() override
    {
        int total = 0;
        for(auto fo : c) {
            total += fo->size();
        }
        return total;
    }

    void add_object(FileSystemObject *fso) override
    {
        c.push_back(fso);
    }
private:
    std::vector<FileSystemObject *> c;
};


Directory* subdir()
{
    Directory *d = new Directory;
    d->add_object(new File);
    d->add_object(new File);
    return d;
}

int main(int, char *[])
{
    Directory* root = new Directory;
    root->add_object(subdir());

    std::cout << root->size() << std::endl;
}
