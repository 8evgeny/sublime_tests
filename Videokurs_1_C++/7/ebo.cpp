// empty base optimization
#include <iostream>

struct deleter {
//    double x;
    void operator()() {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
    }
};

struct ptr {
    int *x;
};

struct ptra {
    int *x;
    deleter y;

//    void deleter() {
//        y();
//    }

};

struct ptrd : deleter {
    int *x;

    void deleter() {
        (*this)();
    }
};

int main() {
//    std::cout << sizeof(deleter) << std::endl;

//    ptr p;
//    std::cout << sizeof(p) << std::endl;

//    ptra pa;
//    std::cout << sizeof(pa) << std::endl;
//    pa.deleter();

//    ptrd pd;
//    std::cout << sizeof(pd) << std::endl;
//    pd.deleter();
}
