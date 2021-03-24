#ifndef ALOGGING_TASK_STACK_H_INCLUDED
#define ALOGGING_TASK_STACK_H_INCLUDED

#include <cinttypes>
#include <cstdlib>
#include <cstring>

class task_stack {
private:
    static constexpr size_t MaximumCombinedLength = 256;
    size_t *stack_{ nullptr };
    int32_t size_{ 0 };
    int32_t position_{ 0 };
    char value_[MaximumCombinedLength];

public:
    task_stack(size_t size);

public:
    void push(const char *name);
    void pop();

public:
    const char *get() {
        return value_;
    }
};

task_stack *get_task_stack();

class logged_task {
private:
    uint8_t pops_{ 0 };

public:
    logged_task(const char *name, const char *thing) {
        auto tasks = get_task_stack();
        if (tasks != nullptr) {
            tasks->push(name);
            tasks->push(thing);
            pops_ = 2;
        }
    }

    logged_task(const char *name) {
        auto tasks = get_task_stack();
        if (tasks != nullptr) {
            tasks->push(name);
            pops_ = 1;
        }
    }

    virtual ~logged_task() {
        while (pops_-- > 0) {
            get_task_stack()->pop();
        }
    }
};

#endif
