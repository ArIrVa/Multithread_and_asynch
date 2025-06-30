// Задача 2  Прогресс-бар с дополнением(*)

#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>
#include <algorithm>
#include <string>
#include <vector>
#include <numeric>
#include <sstream>
#include <iomanip>
#include <random>

using namespace std;

mutex work_mutex;

class MultProgressBarThread
{
public:
    MultProgressBarThread(int num_bars, int width) : num_bars_(num_bars), width_(width)
    {
        progress_.resize(num_bars_, 0);
        times_.resize(num_bars_, 0);
        bar_chars_.assign(num_bars_, std::string(width_, ' '));
        idx_err_.resize(num_bars_, 0);
        fill_ = '#';
    }

    void update(int &bar_index, int &progress, int &err, double &time)
    {
        if (bar_index < 0 || bar_index >= num_bars_)
        {
            return;
        }
        progress_[bar_index] = std::min(progress, 100);
        if (progress_[bar_index] == 100 && times_[bar_index] == 0)
        {
            times_[bar_index] = time;
        }
        idx_err_[bar_index] = err;
        int filled_width = (progress_[bar_index] * width_) / 100;
        int filled_err = (idx_err_[bar_index] * width_) / 100;
        if (filled_err > 0 && filled_err <= filled_width)
        {
            string red_beg = "\033[31m";
            string red_end = "\033[0m";
            string err_char = red_beg + fill_ + red_end;
            bar_chars_[bar_index] = std::string(filled_width, '#') + std::string(width_ - filled_width, ' ');
            bar_chars_[bar_index].replace(filled_err, 1, err_char);
        }
        else
        {
            bar_chars_[bar_index] = std::string(filled_width, '#') + std::string(width_ - filled_width, ' ');
        }
    }

    void display()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        cout << "id\t" << "Progress Bar";
        for (int i{0}; i < width_ - 10; ++i)
        {
            cout << " ";
        }
        cout << "Time" << endl;
        for (int i = 0; i < num_bars_; ++i)
        {
            string total_time = "";
            ostringstream time;
            if (progress_[i] == 100)
            {
                time << fixed << setprecision(6) << times_[i] << "s";
            }
            cout << i + 1 << " " << "[" << bar_chars_[i] << "] " << std::setw(3) << " " << string(time.str()) << std::endl;
        }
    }

private:
    int num_bars_;
    int width_;
    char fill_;
    vector<int> progress_;
    vector<double> times_;
    vector<string> bar_chars_;
    vector<int> idx_err_;
};

void calc(int &size, int &delay, int &progress, int &err, double &time)
{
    unique_lock<mutex> lk(work_mutex);
    auto start = chrono::steady_clock::now();
    bool is_err;
    err = rand() % 100;
    for (int i{0}; i < size; ++i)
    {
        lk.unlock();
        progress = static_cast<int>(static_cast<float>(i + 1) / size * 100);
        is_err = rand() / RAND_MAX;
        this_thread::sleep_for(chrono::milliseconds(delay));
        lk.lock();
    }
    auto fin = chrono::steady_clock::now();
    chrono::duration<double> duration_seconds = (fin - start);
    time = duration_seconds.count();
}

int main()
{

    int num_threads = 8; // количество потоков
    int calc_width = 50; // длина расчета
    int bar_width = 20;  // ширина прогресс-бара
    int delay;           // задержка

    MultProgressBarThread mbar(num_threads, bar_width);

    vector<thread> threads(num_threads);
    vector<int> progress(num_threads, 0);
    vector<int> progress_err(num_threads, 0);
    vector<double> times(num_threads, 0);
    vector<int> delays(num_threads, 0);

    srand(time(0));

    for (int i{0}; i < num_threads; ++i)
    {
        delays[i] = (rand() / 100000000);
    }

    std::vector<int>::iterator max_it = std::max_element(delays.begin(), delays.end());
    int max_delay = *max_it;

    try
    {
        for (int i{0}; i < num_threads; ++i)
        {
            delay = rand() % 100;
            threads[i] = thread(calc, ref(calc_width), ref(delays[i]), ref(progress[i]), ref(progress_err[i]), ref(times[i]));
        }
        for (int i{0}; i < calc_width; ++i)
        {
            for (int j{0}; j < num_threads; ++j)
            {
                mbar.update(j, progress[j], progress_err[j], times[j]);
            }
            mbar.display();
            std::this_thread::sleep_for(chrono::milliseconds(max_delay));
        }
        for (auto &t : threads)
        {
            t.join();
        }
    }
    catch (exception &err)
    {
        cout << err.what() << endl;
        for (auto &t : threads)
        {
            t.join();
        }
    }
    cout << max_delay;
    return 0;
}