#include <iostream>
#include <vector>

int main() {
    std::vector<int> v{1, 2, 3};

    // итератор на первое совпадение по значению или end()
    auto one_it = std::find(v.begin(), v.end(), 1);
    std::cout << *one_it << std::endl;

    auto op = [](auto a) {
        return a == 2;
    };
    // общий паттерн *_if - предикат
    // итератор на первое соответствие предикату или end()
    auto two_it = std::find_if(v.begin(), v.end(), op);
    std::cout << *two_it << std::endl;

    // итератор на первое НЕсоответствие предикату или end()
    auto it = std::find_if_not(v.begin(), v.end(), op);
    std::cout << *it << std::endl;

    // сколько элементов совпадают по значению
    auto c = std::count(v.begin(), v.end(), 1);
    std::cout << "count = " << c << std::endl;

    // сколько элементов соответствуют предикату
    c = std::count_if(v.begin(), v.end(), op);
    std::cout << "count_if = " << c << std::endl;

    // все ли элементы соответствуют предикату
    auto all = std::all_of(v.begin(), v.end(), op);
    std::cout << std::boolalpha << all << std::endl;

    // хотя бы один элемент соответствуют предикату
    auto any = std::any_of(v.begin(), v.end(), op);
    std::cout << any << std::endl;

    // ни один из элементов не соответствуют предикату
    auto none = std::none_of(v.begin(), v.end(), op);
    std::cout << none << std::endl;
}
