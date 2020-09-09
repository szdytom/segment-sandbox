// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_SEMAPHORE_H
#define SSANDBOX_SEMAPHORE_H

#include <future>
#include <memory>

namespace ssandbox {

class semaphore {
public:
    void init();

    void post(int val);
    void wait();
    bool wait_for(unsigned int time_limit);
    int get();

private:
    std::shared_ptr<std::promise<int>> _target;
    std::future<int> _future;
};

}; // namespace ssandbox

#endif // SSANDBOX_SEMAPHORE_H