#include <algorithm>
#include <chrono>
#include <exception>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

void accumulate( std::vector< int >::iterator first,
                 std::vector< int >::iterator last,
                 std::promise< int > accumulate_promise )
{
    int sum = std::accumulate( first, last, 0 );
    accumulate_promise.set_value( sum ); // Notify future
}

void do_work( std::promise< void > barrier )
{
    std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
    barrier.set_value();
}

int add( std::shared_future< int >& a )
{
    static int sum = 10;
    sum += a.get();
    return sum;
}

int main()
{
    // Demonstrate using promise<int> to transmit a result between threads.
    std::vector< int > numbers = { 1, 2, 3, 4, 5, 6 };
    std::promise< int > accumulate_promise;
    std::future< int > accumulate_future = accumulate_promise.get_future();
    std::thread work_thread(
        accumulate, numbers.begin(), numbers.end(), std::move( accumulate_promise ) );
    accumulate_future.wait(); // wait for result
    std::cout << "result=" << accumulate_future.get() << '\n';
    work_thread.join(); // wait for thread completion

    // Demonstrate using promise<void> to signal state between threads.
    std::promise< void > barrier;
    std::future< void > barrier_future = barrier.get_future();
    std::thread new_work_thread( do_work, std::move( barrier ) );
    barrier_future.wait();
    new_work_thread.join();

    // another example
    //    std::promise< int > pr;
    //    std::future< int > fut = pr.get_future();

    //    std::shared_future< int > sf = fut.share();

    //    auto future_result = std::async( add, std::ref( sf ) );

    //    pr.set_value( 7 );
    //    // pr.set_exception( std::make_exception_ptr( std::runtime_error( "Oops" ) ) );

    //    std::cout << future_result.get() << std::endl;

    //    pr.set_value( 7 );

    // std::cout << future_result.get() << std::endl;

    auto a = std::async( [] {
        std::this_thread::sleep_for( std::chrono::seconds( 10 ) );
        std::cout << "first" << std::endl;
    } );

    auto b = std::async( [] {
        std::this_thread::sleep_for( std::chrono::seconds( 5 ) );
        std::cout << "second" << std::endl;
    } );

    std::cout << "main" << std::endl;

    std::packaged_task< int() > t;
}
