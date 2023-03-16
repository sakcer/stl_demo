#include <algorithm>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <ostream>
#include <queue>
#include <thread>

template <typename T>
class Queue {
  private:
    std::queue<T>           w_que, r_que;
    std::mutex              mtx;
    std::condition_variable cond;

    void swapQue() {
        if (r_que.empty()) {
            swap(r_que, w_que);
            cond.notify_one();
        }
    }

  public:
    bool push(T& a) {
        std::unique_lock<std::mutex> lock(mtx);

        w_que.push(std::move(a));
        if (w_que.size() >= 100) {
            swapQue();
        }
        return true;
    }

    bool pop(T& a) {
        if (r_que.empty() && w_que.empty()) {
            return false;
        }
        if (r_que.empty()) {
            swapQue();
        }
        std::unique_lock<std::mutex> lock(mtx);
        a = r_que.front();
        r_que.pop();
        return true;
    }

    bool pop_wait(T& a) {
        std::unique_lock<std::mutex> lock(mtx);
        if (r_que.empty() && w_que.empty()) {
            cond.wait(lock);
        }

        if (r_que.empty()) {
            swapQue();
        }

        a = r_que.front();
        r_que.pop();
        return true;
    }
};

Queue<int> que;

void a() {
    int q;
    que.pop_wait(q);

    std::cout << q << std::endl;
}

void b() {
    int a = 10;
    for (int i = 0; i < 100; i++) {
        que.push(a);
    }
}

int main() {

}