// Задание 1 Сортировка выбором

#include <iostream>
#include <vector>
#include <algorithm>
#include <future> // Для async, promise, future

using namespace std;

// Функция, выполняющая поиск минимального индекса асинхронно
size_t find_min_async(const vector<int> &arr, size_t start_idx)
{
    auto min_idx = start_idx;
    for (size_t i = start_idx + 1; i < arr.size(); ++i)
        if (arr[i] < arr[min_idx])
            min_idx = i;
    return min_idx;
}

void selection_sort(vector<int> &arr)
{
    int n = static_cast<int>(arr.size());

    for (int i = 0; i < n - 1; ++i)
    {
        // Запускаем асинхронное задание на поиск минимального значения
        future<size_t> fut = async(find_min_async, cref(arr), i);

        // Получаем индекс найденного минимального элемента
        size_t min_idx = fut.get();

        // Меняем местами найденный минимум с текущим элементом
        swap(arr[i], arr[min_idx]);
    }
}

int main()
{
    vector<int> vec = {78, 12, 45, 63, 9};

    cout << "Исходный вектор:\n";
    for (auto num : vec)
        cout << num << ' ';
    cout << '\n';

    selection_sort(vec); // Сортируем массив

    cout << "Отсортированный вектор:\n";
    for (auto num : vec)
        cout << num << ' ';
    cout << '\n';

    return 0;
}