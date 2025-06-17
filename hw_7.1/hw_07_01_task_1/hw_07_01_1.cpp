// Задание 1

#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

size_t clientCounter{0};

void clientScore(const size_t &clients, size_t &count)
{
    while (count < clients)
    {
        cout << "Пришел клиент... \n";
        count++;
        cout << "Клиентов в очереди: " << count << endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void operatorScore(size_t &count)
{
    while (count > 0)
    {
        cout << "Обслужен клиент... \n";
        count--;
        cout << "Осталось клиентов: " << count << endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main()
{
    size_t clients{0};

    cout << "Введите количество обслуживаемых клиентов: ";
    cin >> clients;

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