// Приспособленец (Flyweight)

#include <iostream>
#include <map>

class Image
{
public:
    void resize(int, int) {};
};

class ImageResizer
{
    std::map<int, Image> images;
public:
    Image get_box(int w)
    {
        auto i = images.find(w);
        if (i == images.end()) {
            Image img;
            img.resize(w, w);

            bool b;
            std::tie(i, b) = images.emplace(w, img);
        }
        return i->second;
    }
};

int main(int, char *[])
{
    ImageResizer rs;

    rs.get_box(100);
    rs.get_box(1000);
    rs.get_box(1000);
}
