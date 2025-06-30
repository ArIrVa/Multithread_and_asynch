// Задача 3  Защищенный обмен данными

#include <iostream>
#include <thread>
#include <mutex>
#include <string>

// using namespace std;

// #define SWAP_LOCK
// #define SWAP_UNIQUE_LOCK
#define SWAP_SCOPED_LOCK

#define INT
// #define FLOAT

template <typename T>
class Data
{
public:
    Data() : data_{0} {}
    Data(T &data) : data_{data} {}
    Data &operator=(const Data &other) = delete;

    Data &operator=(Data &&other) noexcept
    {
        data_ = other.data_;
        return *this;
    }

    T &getData()
    {
        return data_;
    }

    std::mutex mtx;

private:
    T data_;
};

#ifdef SWAP_LOCK
template <typename T>
void swap(Data<T> &d1, Data<T> &d2)
{
    d1.mtx.lock();
    d2.mtx.lock();
    Data<T> tmp_data;
    tmp_data = std::move(d1);
    d1 = std::move(d2);
    d2 = std::move(tmp_data);
    d1.mtx.unlock();
    d2.mtx.unlock();
}
#endif

#ifdef SWAP_UNIQUE_LOCK
template <typename T>
void swap(Data<T> &d1, Data<T> &d2)
{
    std::unique_lock<std::mutex> lk1{d1.mtx, std::adopt_lock};
    std::unique_lock<std::mutex> lk2{d2.mtx, std::adopt_lock};
    Data<T> tmp_data;
    tmp_data = std::move(d1);
    d1 = std::move(d2);
    d2 = std::move(tmp_data);
}
#endif

#ifdef SWAP_SCOPED_LOCK
template <typename T>
void swap(Data<T> &d1, Data<T> &d2)
{
    std::scoped_lock{d1.mtx, d2.mtx};
    Data<T> tmp_data;
    tmp_data = std::move(d1);
    d1 = std::move(d2);
    d2 = std::move(tmp_data);
}
#endif

template <typename T>
void input_value(T &v1, T &v2)
{
    std::cout << "Введите данные 1: ";
    std::cin >> v1;
    std::cout << "Введите данные 2: ";
    std::cin >> v2;
}

template <typename T>
void print_info(const std::string &state, Data<T> &d1, Data<T> &d2)
{
    std::cout << "Данные " + state + ":" << std::endl;
    std::cout << "данные 1: " << d1.getData() << std::endl;
    std::cout << "данные 2: " << d2.getData() << std::endl;
}

int main()
{

//---- int -------------
#ifdef INT
    int val1, val2;
    input_value(val1, val2);
    Data<int> d1(val1), d2(val2);
    print_info(std::string("до"), d1, d2);
    std::thread t(swap<int>, std::ref(d1), std::ref(d2));
    t.join();
    print_info(std::string("после"), d1, d2);
#endif

//----- float ------------
#ifdef FLOAT
    float val1, val2;
    input_value(val1, val2);
    Data<float> d1(val1), d2(val2);
    print_info(std::string("до"), d1, d2);
    std::thread t(swap<float>, std::ref(d1), std::ref(d2));
    t.join();
    print_info(std::string("после"), d1, d2);
#endif

    return 0;
}