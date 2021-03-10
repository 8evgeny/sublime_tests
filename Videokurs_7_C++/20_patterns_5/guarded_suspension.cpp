// Guarded suspension
// Monitor Object
// Thread pool
// Reactor
// Active Object

#include <chrono>
#include <condition_variable>
#include <iostream>
#include <queue>
#include <thread>
#include <future>

std::mutex console_m;

using args = std::tuple<
//        std::function<void(const std::string &, const std::string &)>,
        std::string,
        std::string
//        std::future<void>
        >;

std::condition_variable cv;
std::mutex cv_m;
std::queue<args> msgs;
std::atomic_bool quit;

void foo(const std::string &a, const std::string &b)
{
    console_m.lock();
    std::cerr << std::this_thread::get_id() << " foo(" << a << ", " << b << ")" << std::endl;
    console_m.unlock();
};

void bar(const std::string &a, const std::string &b)
{
    console_m.lock();
    std::cerr << std::this_thread::get_id() << " bar(" << a << ", " << b << ")" << std::endl;
    console_m.unlock();
};

void worker(std::queue<args>& q)
{
    while (!quit) {
        std::unique_lock<std::mutex> lk(cv_m);
        console_m.lock();
        std::cerr << std::this_thread::get_id() << " waiting... " << std::endl;
        console_m.unlock();
        cv.wait(lk, [&q]() { return !q.empty() || quit; });

        if (!q.empty()) {
            auto[a, b] = std::move(q.front());
            q.pop();
            auto s = q.size();
            lk.unlock();

            foo(a, b);
//            f(a, b);
//            f.get();

            console_m.lock();
            std::cerr << std::this_thread::get_id() << " leave " << s << std::endl;
            console_m.unlock();
        }
    }
}

int main()
{
    using namespace std::chrono_literals;
    std::thread t1(worker, std::ref(msgs)), t2(worker, std::ref(msgs)), t3(worker, std::ref(msgs));
//    std::this_thread::sleep_for(2s);
    {
        std::lock_guard<std::mutex> lk(cv_m);
//        msgs.emplace(std::async(std::launch::deferred, foo, "aa", "bb"));
//        msgs.emplace(foo, "aa", "bb");
        msgs.emplace("hello", "ru");
        msgs.emplace("hello", "en");
    }
    cv.notify_one();

    {
        std::lock_guard<std::mutex> lk(cv_m);
        msgs.emplace("hello", "jp");
        msgs.emplace("hello", "ch");
    }
    cv.notify_one();

    quit = true;
    cv.notify_all();

    t1.join();
    t2.join();
    t3.join();
    std::cerr << "ok" << std::endl;
}
