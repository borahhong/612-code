#include "launch_counter.h"
#include <Counter.h>

launch_counter::launch_counter(Counter& c) {
    counter_obj = &c;
}

double launch_counter::PIDGet() {
    //return rate
    return get_frequency();
}

double launch_counter::get_frequency() {
    return 1/(counter_obj->GetPeriod());
}
