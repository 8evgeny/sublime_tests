#include <cassert>
#include <cstdio>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

// вспомогательный класс для демонстрации полиморфизма времени выполнения ниже
struct B {
    virtual void bar() { std::cout << "B::bar\n"; }
    virtual ~B() = default;
};
struct D : B {
    D() { std::cout << "D::D\n"; }
    ~D() { std::cout << "D::~D\n"; }
    void bar() override { std::cout << "D::bar\n"; }
};

// функция, принимающая unique_ptr, может принимать его по значению или по правосторонней
// ссылке
std::unique_ptr<D> pass_through(std::unique_ptr<D> p)
{
    p->bar();
    return p;
}

// вспомогательная функция для демонстрации пользовательского удаления ниже
void close_file(std::FILE* fp) { std::fclose(fp); }

// Демонстрация связанного списка на основе unique_ptr
struct List {
    struct Node {
        int data;
        std::unique_ptr<Node> next;
        Node(int data)
            : data { data }
            , next { nullptr }
        {
        }
    };
    List()
        : head { nullptr } {};
    // N.B. итеративный деструктор, чтобы избежать переполнения стека в длинных списках
    ~List()
    {
        while (head)
            head = std::move(head->next);
    }
    // copy/move и другие API пропущены для простоты
    void push(int data)
    {
        auto temp = std::make_unique<Node>(data);
        if (head)
            temp->next = std::move(head);
        head = std::move(temp);
    }

private:
    std::unique_ptr<Node> head;
};

int main()
{
    std::cout << "1) Демонстрация уникальной семантики владения\n";
    {
        auto p = std::make_unique<D>(); // p это unique_ptr, которому принадлежит D
        auto q = pass_through(std::move(p));
        assert(!p); // теперь p ничем не владеет и имеет нулевой указатель
        q->bar(); // а q владеет объектом D
    } // ~D вызывается здесь

    std::cout << "2) Демонстрация полиморфизма во время выполнения\n";
    {
        std::unique_ptr<B> p = std::make_unique<D>(); // p это unique_ptr, которому
            // принадлежит D как указатель
            // на базовый класс
        p->bar(); // виртуальный вызов

        std::vector<std::unique_ptr<B>> v; // unique_ptr может храниться в контейнере
        v.push_back(std::make_unique<D>());
        v.push_back(std::move(p));
        v.emplace_back(new D);
        for (auto& p : v)
            p->bar(); // виртуальная диспетчеризация
    } // ~D вызывается 3 раза

    std::cout << "3) Демонстрация пользовательского удаления\n";
    std::ofstream("demo.txt") << 'x'; // подготовка файла для чтения
    {
        std::unique_ptr<std::FILE, decltype(&close_file)> fp(std::fopen("demo.txt", "r"),
            &close_file);
        if (fp) // fopen могла потерпеть неудачу; в этом случае fp содержит нулевой указатель
            std::cout << (char)std::fgetc(fp.get()) << '\n';
    } // здесь вызывается fclose(), но только если FILE* не является нулевым указателем
    // (то есть, если fopen успешна)

    std::cout << "4) Демонстрация пользовательского удаления лямбда-выражением\n";
    {
        std::unique_ptr<D, std::function<void(D*)>> p(new D, [](D* ptr) {
            std::cout << "уничтожение с помощью пользовательского средства удаления...\n";
            delete ptr;
        }); // p владеет D
        p->bar();
    } // вызывается лямбда, указанная выше, и D уничтожается

    std::cout << "5) Демонстрация формы массива unique_ptr\n";
    {
        std::unique_ptr<D[]> p(new D[3]);
    } // вызывает ~D 3 раза

    std::cout << "6) Демонстрация связанного списка\n";
    {
        List l;
        for (long n = 0; n != 1'000'000; ++n)
            l.push(n);
        std::cout << "уничтожает 1'000'000 узлов... ";
    } // уничтожает все 1 миллион узлов
    std::cout << "Готово.\n";
}
