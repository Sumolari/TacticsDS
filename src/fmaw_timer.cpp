// Copyright 2015 Lluís Ulzurrun de Asanza Sàez

#include "./fmaw_timer.h"
#include "./fmaw_debug.h"

#include <nds.h>

#include <map>
#include <vector>

namespace FMAW {

namespace Timer {

/**
 * The speed of the timer when using ClockDivider_1024
 */
#define TIMER_SPEED (BUS_CLOCK/1024)

/**
 * Macro to convert given tick-time to milliseconds.
 * @param  x Time to convert to milliseconds, expressed as clock-ticks.
 * @return   Time in milliseconds.
 */
#define TICKS_TO_MS(x) x / TIMER_SPEED * 1000 + \
    ((x % TIMER_SPEED) * 1000) / TIMER_SPEED

/**
 * Macro to convert given milliseconds to clock-ticks.
 * @param  x Milliseconds to convert to clock-ticks.
 * @return   Time in clock-ticks.
 */
#define MS_TO_TICKS(x) x * TIMER_SPEED / 1000

/**
 * Maximum amount of ticks that will be counted before reseting counter to 1.
 */
#define MAX_TICKS 100000

/**
 * Macro that given an amount of ticks returns the corresponding, wrapped,
 * amount of ticks.
 * @param  x Initial amount of ticks
 * @return   Wrapped, valid, amount of ticks.
 */
#define TICKS_TO_VALID_RANGE(x) (x % MAX_TICKS)

typedef struct t_callback {
    /**
     * ID of this callback.
     */
    int ID;
    /**
     * Time when callback was added, used as offset, in ticks.
     */
    unsigned int  init;
    /**
     * Amount of time to wait, in ticks.
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
    registered_functions[next_registered_function_id] = {
        next_registered_function_id,
        TICKS_TO_VALID_RANGE(ticks + MS_TO_TICKS(delta)),
        TICKS_TO_VALID_RANGE(MS_TO_TICKS(delta)),
        repetitive,
        false,
        callback
    };
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

    ticks = TICKS_TO_VALID_RANGE(ticks + timerElapsed(0));

    for (
        auto it = registered_functions.begin();
        it != registered_functions.end();
        it++
    ) {
        Callback entry = registered_functions[it->first];

        if (!entry.toBeRemoved && ticks > entry.init) {
            entry.function(entry.ID);
            if (entry.repetitive)
                registered_functions[it->first].init = TICKS_TO_VALID_RANGE(
                        ticks + entry.delta);
            else
                dequeue_function(entry.ID);
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
