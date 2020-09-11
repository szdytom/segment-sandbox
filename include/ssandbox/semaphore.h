// -*- C++ -*- Part of the Segment Sandbox Project

#ifndef SSANDBOX_SEMAPHORE_H
#define SSANDBOX_SEMAPHORE_H

namespace ssandbox {

class semaphore {
public:
    semaphore();
    ~semaphore();

    void post(int val);
    void wait();
    bool wait_for(unsigned int time_limit);
    int get();

private:
    int _value;
    bool _mark;

public:
    static const unsigned int _time;
};

}; // namespace ssandbox

#endif // SSANDBOX_SEMAPHORE_H