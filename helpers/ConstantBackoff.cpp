//
// Created by andrew on 5.5.15.
//

#include "ConstantBackoff.h"

void ConstantBackoff::backoff() {
    //std::this_thread::yield();
    //usleep(rand() % duration + 1);
    usleep(250);
    //duration = std::min(256, duration * 2);
}