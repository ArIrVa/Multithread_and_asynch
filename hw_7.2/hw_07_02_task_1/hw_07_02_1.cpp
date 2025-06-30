// Задание 1 Атомарная очередь клиентов

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

using namespace std;

atomic<int> clientCounter{0}; // счетчик клиентов

void clientScore(const size_t &clients, atomic<int> &count)
{
    while (count < clients)
    {
        cout << "Пришел клиент...\n";
        count++;
        cout << "Клиентов в очереди: " << count.load(memory_order_relaxed) << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void operatorScore(atomic<int> &count)
{
    while (count > 0)
    {
        cout << "Обслужен клиент...\n";
        count--;
        cout << "Осталось клиентов: " << count.load(memory_order_relaxed) << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    size_t clients{0};

    cout << "Введите количество обслуживаемых клиентов: ";
    cin >> clients;
    cout << endl;

    while (true)
    {
        thread t1(clientScore, ref(clients), ref(clientCounter));
        thread t2(operatorScore, ref(clientCounter));
        t1.join();
        t2.join();

        if (!clientCounter)
            break;
    }

    return 0;
}