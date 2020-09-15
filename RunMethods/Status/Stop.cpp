#include "Stop.h"

Stop::Stop(){
    patterns.push_back(new RunPattern(LINE_TRACE, 0, DISTANCE, 10, 0.0, 0.0, 0.0, 18, RIGHT));
}