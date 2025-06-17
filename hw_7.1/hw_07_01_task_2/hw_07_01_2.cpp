// Задание 2

#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <thread>
#include <chrono>
#include <execution>

using namespace std;

const int EL_1000 = 1000;
const int EL_10000 = 10000;
const int EL_100000 = 100000;
const int EL_1000000 = 1000000;

void makeData(vector<size_t> &vec, size_t size)
{
    size_t number{0};
    for (size_t i = 0; i < size; i++)
    {
        number = rand() * 0.01;
        vec[i] = number;
    }
}

void dataAdd(const vector<size_t> &v1, const vector<size_t> &v2, vector<size_t> &result)
{
    for (size_t i = 0; i < v1.size(); i++)
    {
        result.push_back(v1[i] + v2[i]);
    };
}

void dataPart(const vector<size_t> &data, vector<size_t> &part, const size_t start, const size_t fin)
{
    for (size_t i = start; i <= fin; i++)
    {
        part.push_back(data[i]);
    }
}

void thread1(const int vsize, vector<double> &time)
{
    // 1 thread
    vector<size_t> data1(vsize);
    vector<size_t> data2(vsize);
    vector<size_t> addResult;

    makeData(data1, vsize);
    makeData(data2, vsize);

    auto start = chrono::steady_clock::now();
    dataAdd(data1, data2, addResult);
    auto fin = chrono::steady_clock::now();
    chrono::duration<double> duration_seconds = (fin - start);
    time.push_back(duration_seconds.count());
}

void thread2(const int vsize, vector<double> &time)
{
    // 2 thread
    unsigned int n = 2; // кол-во потоков
    unsigned int step = vsize / n;
    vector<size_t> data1(vsize);
    vector<size_t> data2(vsize);
    vector<pair<size_t, size_t>> partBoard(n); // границы
    vector<size_t> data1_part1;
    vector<size_t> data1_part2;
    vector<size_t> data2_part1;
    vector<size_t> data2_part2;
    vector<size_t> result_part1;
    vector<size_t> result_part2;

    makeData(data1, vsize);
    makeData(data2, vsize);

    unsigned int st = 0;
    for (int i = 0; i < n; i++)
    {
        partBoard[i].first = st;
        st += step;
        partBoard[i].second = st - 1;
    }

    dataPart(data1, data1_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data1, data1_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data2, data2_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data2, data2_part2, partBoard[1].first, partBoard[1].second);

    auto start = chrono::steady_clock::now();
    thread t1(dataAdd, ref(data1_part1), ref(data2_part1), ref(result_part1));
    thread t2(dataAdd, ref(data1_part2), ref(data2_part2), ref(result_part2));
    t1.join();
    t2.join();
    for (const auto &el : result_part2)
    {
        result_part1.push_back(el);
    }
    auto fin = chrono::steady_clock::now();
    chrono::duration<double> duration_seconds = (fin - start);
    time.push_back(duration_seconds.count());
}

void thread4(const int vsize, vector<double> &time)
{
    // 4 thread
    unsigned int n = 4; // кол-во потоков
    unsigned int step = vsize / n;
    vector<size_t> data1(vsize);
    vector<size_t> data2(vsize);
    vector<pair<size_t, size_t>> partBoard(n); // границы

    vector<size_t> data1_part1;
    vector<size_t> data1_part2;
    vector<size_t> data1_part3;
    vector<size_t> data1_part4;

    vector<size_t> data2_part1;
    vector<size_t> data2_part2;
    vector<size_t> data2_part3;
    vector<size_t> data2_part4;

    vector<size_t> result_part1;
    vector<size_t> result_part2;
    vector<size_t> result_part3;
    vector<size_t> result_part4;

    makeData(data1, vsize);
    makeData(data2, vsize);

    unsigned int st = 0;
    for (int i = 0; i < n; i++)
    {
        partBoard[i].first = st;
        st += step;
        partBoard[i].second = st - 1;
    }

    dataPart(data1, data1_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data1, data1_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data1, data1_part3, partBoard[2].first, partBoard[2].second);
    dataPart(data1, data1_part4, partBoard[3].first, partBoard[3].second);

    dataPart(data2, data2_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data2, data2_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data2, data2_part3, partBoard[2].first, partBoard[2].second);
    dataPart(data2, data2_part4, partBoard[3].first, partBoard[3].second);

    auto start = chrono::steady_clock::now();
    thread t1(dataAdd, ref(data1_part1), ref(data2_part1), ref(result_part1));
    thread t2(dataAdd, ref(data1_part2), ref(data2_part2), ref(result_part2));
    thread t3(dataAdd, ref(data1_part3), ref(data2_part3), ref(result_part3));
    thread t4(dataAdd, ref(data1_part4), ref(data2_part4), ref(result_part4));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    for (const auto &el : result_part2)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part4)
    {
        result_part3.push_back(el);
    }
    for (const auto &el : result_part3)
    {
        result_part1.push_back(el);
    }
    auto fin = chrono::steady_clock::now();
    chrono::duration<double> duration_seconds = (fin - start);
    time.push_back(duration_seconds.count());
}

void thread8(const int vsize, vector<double> &time)
{
    // 8 thread
    unsigned int n = 8; // кол-во потоков
    unsigned int step = vsize / n;
    vector<size_t> data1(vsize);
    vector<size_t> data2(vsize);
    vector<pair<size_t, size_t>> partBoard(n); // границы

    vector<size_t> data1_part1;
    vector<size_t> data1_part2;
    vector<size_t> data1_part3;
    vector<size_t> data1_part4;
    vector<size_t> data1_part5;
    vector<size_t> data1_part6;
    vector<size_t> data1_part7;
    vector<size_t> data1_part8;

    vector<size_t> data2_part1;
    vector<size_t> data2_part2;
    vector<size_t> data2_part3;
    vector<size_t> data2_part4;
    vector<size_t> data2_part5;
    vector<size_t> data2_part6;
    vector<size_t> data2_part7;
    vector<size_t> data2_part8;

    vector<size_t> result_part1;
    vector<size_t> result_part2;
    vector<size_t> result_part3;
    vector<size_t> result_part4;
    vector<size_t> result_part5;
    vector<size_t> result_part6;
    vector<size_t> result_part7;
    vector<size_t> result_part8;

    makeData(data1, vsize);
    makeData(data2, vsize);

    unsigned int st = 0;
    for (int i = 0; i < n; i++)
    {
        partBoard[i].first = st;
        st += step;
        partBoard[i].second = st - 1;
    }

    dataPart(data1, data1_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data1, data1_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data1, data1_part3, partBoard[2].first, partBoard[2].second);
    dataPart(data1, data1_part4, partBoard[3].first, partBoard[3].second);
    dataPart(data1, data1_part5, partBoard[4].first, partBoard[4].second);
    dataPart(data1, data1_part6, partBoard[5].first, partBoard[5].second);
    dataPart(data1, data1_part7, partBoard[6].first, partBoard[6].second);
    dataPart(data1, data1_part8, partBoard[7].first, partBoard[7].second);

    dataPart(data2, data2_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data2, data2_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data2, data2_part3, partBoard[2].first, partBoard[2].second);
    dataPart(data2, data2_part4, partBoard[3].first, partBoard[3].second);
    dataPart(data2, data2_part5, partBoard[4].first, partBoard[4].second);
    dataPart(data2, data2_part6, partBoard[5].first, partBoard[5].second);
    dataPart(data2, data2_part7, partBoard[6].first, partBoard[6].second);
    dataPart(data2, data2_part8, partBoard[7].first, partBoard[7].second);

    auto start = chrono::steady_clock::now();
    thread t1(dataAdd, ref(data1_part1), ref(data2_part1), ref(result_part1));
    thread t2(dataAdd, ref(data1_part2), ref(data2_part2), ref(result_part2));
    thread t3(dataAdd, ref(data1_part3), ref(data2_part3), ref(result_part3));
    thread t4(dataAdd, ref(data1_part4), ref(data2_part4), ref(result_part4));
    thread t5(dataAdd, ref(data1_part5), ref(data2_part5), ref(result_part5));
    thread t6(dataAdd, ref(data1_part6), ref(data2_part6), ref(result_part6));
    thread t7(dataAdd, ref(data1_part7), ref(data2_part7), ref(result_part7));
    thread t8(dataAdd, ref(data1_part8), ref(data2_part8), ref(result_part8));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    for (const auto &el : result_part2)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part4)
    {
        result_part3.push_back(el);
    }
    for (const auto &el : result_part6)
    {
        result_part5.push_back(el);
    }
    for (const auto &el : result_part8)
    {
        result_part7.push_back(el);
    }
    for (const auto &el : result_part3)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part5)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part7)
    {
        result_part1.push_back(el);
    }
    auto fin = chrono::steady_clock::now();
    chrono::duration<double> duration_seconds = (fin - start);
    time.push_back(duration_seconds.count());
}

void thread16(const int vsize, vector<double> &time)
{
    // 16 thread
    unsigned int n = 16; // кол-во потоков
    unsigned int step = vsize / n;
    vector<size_t> data1(vsize);
    vector<size_t> data2(vsize);
    vector<pair<size_t, size_t>> partBoard(n); // границы

    vector<size_t> data1_part1;
    vector<size_t> data1_part2;
    vector<size_t> data1_part3;
    vector<size_t> data1_part4;
    vector<size_t> data1_part5;
    vector<size_t> data1_part6;
    vector<size_t> data1_part7;
    vector<size_t> data1_part8;
    vector<size_t> data1_part9;
    vector<size_t> data1_part10;
    vector<size_t> data1_part11;
    vector<size_t> data1_part12;
    vector<size_t> data1_part13;
    vector<size_t> data1_part14;
    vector<size_t> data1_part15;
    vector<size_t> data1_part16;

    vector<size_t> data2_part1;
    vector<size_t> data2_part2;
    vector<size_t> data2_part3;
    vector<size_t> data2_part4;
    vector<size_t> data2_part5;
    vector<size_t> data2_part6;
    vector<size_t> data2_part7;
    vector<size_t> data2_part8;
    vector<size_t> data2_part9;
    vector<size_t> data2_part10;
    vector<size_t> data2_part11;
    vector<size_t> data2_part12;
    vector<size_t> data2_part13;
    vector<size_t> data2_part14;
    vector<size_t> data2_part15;
    vector<size_t> data2_part16;

    vector<size_t> result_part1;
    vector<size_t> result_part2;
    vector<size_t> result_part3;
    vector<size_t> result_part4;
    vector<size_t> result_part5;
    vector<size_t> result_part6;
    vector<size_t> result_part7;
    vector<size_t> result_part8;
    vector<size_t> result_part9;
    vector<size_t> result_part10;
    vector<size_t> result_part11;
    vector<size_t> result_part12;
    vector<size_t> result_part13;
    vector<size_t> result_part14;
    vector<size_t> result_part15;
    vector<size_t> result_part16;

    makeData(data1, vsize);
    makeData(data2, vsize);

    unsigned int st = 0;
    for (int i = 0; i < n; i++)
    {
        partBoard[i].first = st;
        st += step;
        partBoard[i].second = st - 1;
    }

    dataPart(data1, data1_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data1, data1_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data1, data1_part3, partBoard[2].first, partBoard[2].second);
    dataPart(data1, data1_part4, partBoard[3].first, partBoard[3].second);
    dataPart(data1, data1_part5, partBoard[4].first, partBoard[4].second);
    dataPart(data1, data1_part6, partBoard[5].first, partBoard[5].second);
    dataPart(data1, data1_part7, partBoard[6].first, partBoard[6].second);
    dataPart(data1, data1_part8, partBoard[7].first, partBoard[7].second);

    dataPart(data1, data1_part9, partBoard[8].first, partBoard[8].second);
    dataPart(data1, data1_part10, partBoard[9].first, partBoard[9].second);
    dataPart(data1, data1_part11, partBoard[10].first, partBoard[10].second);
    dataPart(data1, data1_part12, partBoard[11].first, partBoard[11].second);
    dataPart(data1, data1_part13, partBoard[12].first, partBoard[12].second);
    dataPart(data1, data1_part14, partBoard[13].first, partBoard[13].second);
    dataPart(data1, data1_part15, partBoard[14].first, partBoard[14].second);
    dataPart(data1, data1_part16, partBoard[15].first, partBoard[15].second);

    dataPart(data2, data2_part1, partBoard[0].first, partBoard[0].second);
    dataPart(data2, data2_part2, partBoard[1].first, partBoard[1].second);
    dataPart(data2, data2_part3, partBoard[2].first, partBoard[2].second);
    dataPart(data2, data2_part4, partBoard[3].first, partBoard[3].second);
    dataPart(data2, data2_part5, partBoard[4].first, partBoard[4].second);
    dataPart(data2, data2_part6, partBoard[5].first, partBoard[5].second);
    dataPart(data2, data2_part7, partBoard[6].first, partBoard[6].second);
    dataPart(data2, data2_part8, partBoard[7].first, partBoard[7].second);

    dataPart(data2, data2_part9, partBoard[8].first, partBoard[8].second);
    dataPart(data2, data2_part10, partBoard[9].first, partBoard[9].second);
    dataPart(data2, data2_part11, partBoard[10].first, partBoard[10].second);
    dataPart(data2, data2_part12, partBoard[11].first, partBoard[11].second);
    dataPart(data2, data2_part13, partBoard[12].first, partBoard[12].second);
    dataPart(data2, data2_part14, partBoard[13].first, partBoard[13].second);
    dataPart(data2, data2_part15, partBoard[14].first, partBoard[14].second);
    dataPart(data2, data2_part16, partBoard[15].first, partBoard[15].second);

    auto start = chrono::steady_clock::now();
    thread t1(dataAdd, ref(data1_part1), ref(data2_part1), ref(result_part1));
    thread t2(dataAdd, ref(data1_part2), ref(data2_part2), ref(result_part2));
    thread t3(dataAdd, ref(data1_part3), ref(data2_part3), ref(result_part3));
    thread t4(dataAdd, ref(data1_part4), ref(data2_part4), ref(result_part4));
    thread t5(dataAdd, ref(data1_part5), ref(data2_part5), ref(result_part5));
    thread t6(dataAdd, ref(data1_part6), ref(data2_part6), ref(result_part6));
    thread t7(dataAdd, ref(data1_part7), ref(data2_part7), ref(result_part7));
    thread t8(dataAdd, ref(data1_part8), ref(data2_part8), ref(result_part8));
    thread t9(dataAdd, ref(data1_part9), ref(data2_part9), ref(result_part9));
    thread t10(dataAdd, ref(data1_part10), ref(data2_part10), ref(result_part10));
    thread t11(dataAdd, ref(data1_part11), ref(data2_part11), ref(result_part11));
    thread t12(dataAdd, ref(data1_part12), ref(data2_part12), ref(result_part12));
    thread t13(dataAdd, ref(data1_part13), ref(data2_part13), ref(result_part13));
    thread t14(dataAdd, ref(data1_part14), ref(data2_part14), ref(result_part14));
    thread t15(dataAdd, ref(data1_part15), ref(data2_part15), ref(result_part15));
    thread t16(dataAdd, ref(data1_part16), ref(data2_part16), ref(result_part16));
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    t6.join();
    t7.join();
    t8.join();
    t9.join();
    t10.join();
    t11.join();
    t12.join();
    t13.join();
    t14.join();
    t15.join();
    t16.join();
    for (const auto &el : result_part2)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part4)
    {
        result_part3.push_back(el);
    }
    for (const auto &el : result_part6)
    {
        result_part5.push_back(el);
    }
    for (const auto &el : result_part8)
    {
        result_part7.push_back(el);
    }
    for (const auto &el : result_part10)
    {
        result_part9.push_back(el);
    }
    for (const auto &el : result_part12)
    {
        result_part11.push_back(el);
    }
    for (const auto &el : result_part14)
    {
        result_part13.push_back(el);
    }
    for (const auto &el : result_part16)
    {
        result_part15.push_back(el);
    }

    for (const auto &el : result_part3)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part5)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part7)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part9)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part11)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part13)
    {
        result_part1.push_back(el);
    }
    for (const auto &el : result_part15)
    {
        result_part1.push_back(el);
    }

    auto fin = chrono::steady_clock::now();
    chrono::duration<double> duration_seconds = (fin - start);
    time.push_back(duration_seconds.count());
}

void printInfo(const vector<vector<double>> &arr)
{
    cout << "Количество аппаратных ядер: " << thread::hardware_concurrency() << endl;
    cout << endl;
    cout << "\t\t1000\t\t" << "10000\t\t" << "100000\t\t" << "1000000\t\t" << endl;
    int ppn{0};
    for (int i = 0; i < arr.size(); i++)
    {
        if (!i)
        {
            ppn = 1;
        }
        else
        {
            ppn *= 2;
        };
        cout << to_string(ppn) << " потоков\t";
        for (auto t : arr[i])
        {
            cout << fixed << setprecision(7) << t << "s\t";
        }
        cout << endl;
    }
}

int main()
{

    vector<vector<double>> resTimeThread(5);

    try
    {
        thread1(EL_1000, resTimeThread[0]);
        thread1(EL_10000, resTimeThread[0]);
        thread1(EL_100000, resTimeThread[0]);
        thread1(EL_1000000, resTimeThread[0]);

        thread2(EL_1000, resTimeThread[1]);
        thread2(EL_10000, resTimeThread[1]);
        thread2(EL_100000, resTimeThread[1]);
        thread2(EL_1000000, resTimeThread[1]);

        thread4(EL_1000, resTimeThread[2]);
        thread4(EL_10000, resTimeThread[2]);
        thread4(EL_100000, resTimeThread[2]);
        thread4(EL_1000000, resTimeThread[2]);

        thread8(EL_1000, resTimeThread[3]);
        thread8(EL_10000, resTimeThread[3]);
        thread8(EL_100000, resTimeThread[3]);
        thread8(EL_1000000, resTimeThread[3]);

        thread16(EL_1000, resTimeThread[4]);
        thread16(EL_10000, resTimeThread[4]);
        thread16(EL_100000, resTimeThread[4]);
        thread16(EL_1000000, resTimeThread[4]);

        printInfo(resTimeThread);
    }
    catch (const exception &err)
    {
        cout << err.what() << endl;
    }

    return 0;
}