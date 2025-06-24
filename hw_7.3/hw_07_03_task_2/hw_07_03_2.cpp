// Задание 2 For_each

#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <functional>
#include <numeric>

using namespace std;

// Функция, реализующая параллельное применение for_each
template <typename Iter, typename Function>
void parallel_for_each(Iter first, Iter last, Function func)
{
    // Базовое условие остановки рекурсии
    if (first >= last)
        return;

    // Максимальное количество элементов в одном потоке
    static const int MAX_BLOCK_SIZE = 100;

    // Рассчитываем длину диапазона
    long length = distance(first, last);

    // Если длина меньше предела, используем обычный for_each
    if (length <= MAX_BLOCK_SIZE)
    {
        for_each(first, last, func);
        return;
    }

    // Делиим область пополам
    Iter middle = first + length / 2;

    // Рекурсивно запускаем потоки для левой и правой частей
    future<void> left_future(async(
        launch::async,
        [&]()
        { parallel_for_each(first, middle, func); }));

    future<void> right_future(async(
        launch::async,
        [&]()
        { parallel_for_each(middle, last, func); }));

    // Ожидаем завершение обеих ветвей
    left_future.get();  // ждем завершения левого потока
    right_future.get(); // ждем завершения правого потока
}

// Тестовая функция, выводящая элементы вектора
// void print_element(const int &element)
// {
//     cout << element << " ";
// }

int main()
{
    vector<int> vec(1000);
    iota(vec.begin(), vec.end(), 1); // заполним вектор значениями от 1 до 1000

    // Применение параллельного for_each
    parallel_for_each(vec.begin(), vec.end(), [](const int &val)
                      { cout << val * 2 << "\n"; });

    return 0;
}
