// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./fmaw_timer.h"
#include "./fmaw_debug.h"

#include <nds.h>

#include <map>
#include <vector>

namespace FMAW {

namespace Timer {

// The speed of the timer when using ClockDivider_1024
#define TIMER_SPEED (BUS_CLOCK/1024)

typedef struct t_callback {
    /**
     * ID of this callback.
     */
    int ID;
    /**
     * Time when callback was added, used as offset.
     */
    unsigned int  init;
    /**
     * Amount of time to wait.
     */
    unsigned int  delta;
    /**
     * Whether action is repetive (true) or not.
     */
    bool repetitive;
    /**
     * Whether this action has to be removed from queue or not.
     */
    bool toBeRemoved;
    /**
     * Function to be called.
     */
    void (*function)(int);
} Callback;

// Here we will store registered functions.
std::map<int, Callback> registered_functions {};

// Next ID that can be used.
int next_registered_function_id = 0;

// Amount of ticks ellapsed.
unsigned int ticks = 0;

void init() {
    if (ticks == 0) {
        ticks++;
        timerStart(0, ClockDivider_1024, 0, NULL);
    }
}

int enqueue_function(void (*callback)(int), unsigned int delta,
                     bool repetitive) {
    Callback _callback;
    _callback.ID = next_registered_function_id;
    _callback.init = ticks + delta;
    _callback.delta = delta;
    _callback.repetitive = repetitive;
    _callback.toBeRemoved = false;
    _callback.function = callback;

    registered_functions[next_registered_function_id] = _callback;
    return next_registered_function_id++;
}

bool dequeue_function(int id) {
    if (registered_functions.find(id) != registered_functions.end()) {
        registered_functions[id].toBeRemoved = true;
        return true;
    }
    return false;
}

void check() {
    std::vector<int> toBeRemoved;

    ticks += timerElapsed(0);

    unsigned int ticks_ms = ticks / TIMER_SPEED * 1000 +
                            ((ticks % TIMER_SPEED) * 1000) / TIMER_SPEED;

    FMAW::printf("Ticks: %d", ticks);
    FMAW::printf("Ticks in ms: %u", ticks_ms);

    for (
        auto it = registered_functions.begin();
        it != registered_functions.end();
        it++
    ) {
        Callback entry = it->second;

        FMAW::printf("Init time: %u", entry.init);

        if (!entry.toBeRemoved && ticks_ms > entry.init) {
            entry.function(entry.ID);
            if (entry.repetitive)
                entry.init = ticks + entry.delta;
            else
                dequeue_function(entry.ID);
            FMAW::printf("Next time: %u", entry.init);
        }

        if (entry.toBeRemoved)
            toBeRemoved.push_back(entry.ID);
    }

    for (auto it = toBeRemoved.begin(); it != toBeRemoved.end(); it++)
        if (registered_functions.find(*it) != registered_functions.end())
            registered_functions.erase(*it);
}

}  // namespace Timer

}  // namespace FMAW
