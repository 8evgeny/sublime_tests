#include <cstring>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

void do_process(const char* data, std::size_t size);

void do_process_in_background(const char* data, std::size_t size) {
    // We need to copy data, because we do not know,
    // when it will be deallocated by the caller
    char* data_cpy = new char[size];
    std::memcpy(data_cpy, data, size);

    // Starting thread of execution to process data
    boost::thread(boost::bind(&do_process, data_cpy, size));

    // We can not delete[] data_cpy, because
    // do_process1 or do_process2 may still work with it
}

#include <boost/shared_array.hpp>
void do_process_shared_array(const boost::shared_array<char>& data, std::size_t size) {
    do_process(data.get(), size);
}

void do_process_in_background_v1(const char* data, std::size_t size) {
    // We need to copy data, because we do not know, when it will be
    // deallocated by the caller
    boost::shared_array<char> data_cpy(new char[size]);
    std::memcpy(data_cpy.get(), data, size);

    // Starting thread of execution to process data
    boost::thread(boost::bind(&do_process_shared_array, data_cpy, size))
            .detach();

    // no need to call delete[] for data_cpy, because
    // data_cpy destructor will deallocate data when
    // reference count will be zero
}


#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

void do_process_shared_ptr(
        const boost::shared_ptr<char[]>& data,
        std::size_t size)
{
    do_process(data.get(), size);
}

void do_process_in_background_v2(const char* data, std::size_t size) {
    // Faster than 'First solution'
    boost::shared_ptr<char[]> data_cpy = boost::make_shared<char[]>(size);
    std::memcpy(data_cpy.get(), data, size);

    // Starting thread of execution to process data
    boost::thread(boost::bind(&do_process_shared_ptr, data_cpy, size))
            .detach();

    // data_cpy destructor will deallocate data when
    // reference count will be zero
}

void do_process_shared_ptr2(
        const boost::shared_ptr<char>& data,
        std::size_t size)
{
    do_process(data.get(), size);
}

void do_process_in_background_v3(const char* data, std::size_t size) {
    // Same speed as in First solution
    boost::shared_ptr<char> data_cpy(
                new char[size],
                boost::checked_array_deleter<char>()
    );
    std::memcpy(data_cpy.get(), data, size);

    // Starting threads of execution to process data
    boost::thread(boost::bind(&do_process_shared_ptr2, data_cpy, size))
            .detach();

    // data_cpy destructor will deallocate data when
    // reference count will be zero
}

#include <boost/chrono/duration.hpp>
int main () {
    // do_process_in_background(); // Will cause a memory leak
    char ch[] = "Hello dear reader.";
    do_process_in_background_v1(ch, sizeof(ch));
    do_process_in_background_v2(ch, sizeof(ch));
    do_process_in_background_v3(ch, sizeof(ch));

    // Give all the threads a chance to finish
    // Note: It is an awfull design, but it is OK
    // for example
    boost::this_thread::sleep_for(boost::chrono::seconds(2));
    return 0;
}

void do_process(const char* data, std::size_t size) {
    assert(size);
    assert(data);
}
