// Алгоритмы шифрования
// Фейстель (Feistel cipher)
// Тритемиуса (Trithemius cipher)
// Побитовые сдвиги (Bit-shift cipher)

#include <iostream>
#include <string>
#include <random>
#include <time.h>
#include <queue>
#include <vector>
#include <memory>

#include <thread>
#include <mutex>

#include "timer_.h"
#include "ciphers.h"

using namespace std;
mutex mtx;

string random_str(int len)
{
    string s;
    for (int i = 0; i < len; i++)
        s += rand() % 256;
    return s;
}

void test_time(fCipher f, int n)
{
    string s = random_str(n);

    start_counter();
    f(s);
    double t = get_counter() / 1000;

    cout << "Время: " << t  << endl;
}

using conv_t = struct {
    double t_start[3];
    double t_end[3];
    string data;
};
using conv_shared = shared_ptr<conv_t>;
using conv_queue = queue<conv_shared>;
conv_t* generate_obj(int str_len)
{
    conv_t res;
    for (int i = 0; i < 3; i++) 
    {
        res.t_start[i] = 0;
        res.t_end[i] = 0;
    }   
    res.data = random_str(str_len);
    conv_t* ptr = new conv_t(res);
    return ptr;
}
conv_queue generate_queue(int queue_len, int str_len)
{
    conv_queue q;
    for (int i = 0; i < queue_len; i++)
        q.push(conv_shared(generate_obj(str_len)));
    return q;
}

void conv_thread(conv_queue& pre_queue, conv_queue& post_queue, fCipher f, int queue_len, int conv_n)
{
    conv_shared task;
    for (int i = 0; i < queue_len; i++)
    {
        while (pre_queue.empty()) {}
        task = pre_queue.front();
        task->t_start[conv_n] = get_counter();
        if (conv_n == 0)
        {
            pre_queue.pop();
        }
        else 
        {
            mtx.lock();
            pre_queue.pop();
            mtx.unlock();
        }

        f(task->data);

        task->t_end[conv_n] = get_counter();
        if (conv_n == 2)
        {
            post_queue.push(task);
        }
        else
        {
            mtx.lock();
            post_queue.push(task);
            mtx.unlock();
        }
    }
}

void process_data(conv_queue& task_queue)
{
    int queue_len = task_queue.size();
    conv_shared task;

    for (int i = 0; i < queue_len; i++)
    {
        task = task_queue.front();
        task_queue.pop();
        printf("%4d|\t %7.2lf:%7.2lf\t %7.2lf:%7.2lf\t %7.2lf:%7.2lf\n", i,
            task->t_start[0], task->t_end[0],
            task->t_start[1], task->t_end[1],
            task->t_start[2], task->t_end[2]);
        task_queue.push(task);
    }

    double t_wait, t_proc;
    double min_wait, max_wait, sum_wait;
    double min_proc, max_proc, sum_proc;
    min_wait = 1e10;    min_proc = 1e10;
    max_wait = -1;      max_proc = -1;
    sum_wait = 0;       sum_proc = 0;
    for (int i = 0; i < queue_len; i++)
    {
        task = task_queue.front();
        task_queue.pop();
        t_wait = (task->t_start[1] - task->t_end[0]) + 
            (task->t_start[2] - task->t_end[1]);
        min_wait = min(min_wait, t_wait);
        max_wait = max(max_wait, t_wait);
        sum_wait += t_wait;

        t_proc = task->t_end[2] - task->t_start[0];
        min_proc = min(min_proc, t_proc);
        max_proc = max(max_proc, t_proc);
        sum_proc += t_proc;
    }

    cout << endl << endl;
    printf("WAITING TIME:\t Min:%6.2lf\t Max:%6.2lf\t Avg:%6.2lf\n",
        min_wait, max_wait, sum_wait / queue_len);
    printf("PROCESS TIME:\t Min:%6.2lf\t Max:%6.2lf\t Avg:%6.2lf\n",
        min_proc, max_proc, sum_proc / queue_len);
}

void main_thread(int queue_len)
{
    fCipher f_arr[] = { FeistelCipher, TrithemiusCipher, BitShiftCipher };
    vector<thread> thread_arr;
    conv_queue q_arr[4];
    q_arr[0] = generate_queue(queue_len, 2*1000*1000);

    start_counter();
    for (int i = 0; i < 3; i++)
        thread_arr.push_back(thread(conv_thread,
            ref(q_arr[i]), ref(q_arr[i+1]), f_arr[i], queue_len, i));

    for (int i = 0; i < 3; i++)
        thread_arr[i].join();
    
    process_data(q_arr[3]);
}

int main(void)
{
    srand(static_cast<unsigned int>(time(0)));
    setlocale(LC_ALL, "Russian");

    /*string s = "J8pyter";

    BitShiftCipher(s);
    BitShiftReCipher(s);

    cout << "Before:\t" << s << endl;
    FeistelCipher(s);
    cout << "After:\t" << s << endl;
    FeistelReCipher(s);
    cout << "After:\t" << s << endl;*/

    /*for (int i = 0; i < 10; i++)
    {
        test_time(FeistelCipher, 1000 * 1000);
        test_time(TrithemiusCipher, 1000 * 1000);
        test_time(BitShiftCipher, 1000 * 1000);
        cout << endl << endl;
    }
    */

    int task_n;
    cout << "Введите количество задач: ";
    cin >> task_n;
    main_thread(task_n);

    return 0;
}