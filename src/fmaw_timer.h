#ifndef FMAW_TIMER_H
#define FMAW_TIMER_H

#include <map>

namespace FMAW {

namespace Timer {

/**
 * Inits time subsystem if required.
 */
void init();

/**
 * Enqueues given function so it will be called
 * @param  callback   Function to be called. Method will be given its ID as
 *                    unique parameter.
 * @param  delta      Time in ms to wait before calling the function.
 *                    Note that precision is 5ms!
 * @param  repetitive Whether this callback should be enqueued again after
 *                    being called.
 * @return            An identificar to cancel enqueued action later.
 */
int enqueue_function(void (*callback)(int), unsigned int delta,
                     bool repetitive);

/**
 * Dequeues given function so it won't called again.
 * @param  id Function to be dequeued.
 * @return    Whether function was dequeued properly or not.
 */
bool dequeue_function(int id);

/**
 * Runs any function that needed to be called.
 */
void check();

}  // namespace Timer

}  // namespace FMAW

#endif