#include "CourseRun.h"

CourseRun::CourseRun(Course course){
    this->course = course;

    if(this->course == L) {
        createCourseL();
    }else if(this->course == R){
        createCourseR();
    }

    setNextState();
}

CourseRun::~CourseRun(){
    for_each(lots.begin(), lots.end(), DeleteObject());
    lots.clear();
    ev3_speaker_play_tone(480, 100);
}

void CourseRun::init(){
}

void CourseRun::setNextState(){
    if(this->course == L) {
        nextState = PARKING;
    }else if(this->course == R){
        nextState = STOP;
    }
}

// coruseの距離は1000 1050くらいで調整
void CourseRun::createCourseL(){
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 20, 0.4, 0.0, 0.03, 40));
    patterns.push_back(new RunPattern(LINE_TRACE, 60, DISTANCE, 50, 0.25, 0.03, 0.03, 60));

    patterns.push_back(new RunPattern(LINE_TRACE, 60, DISTANCE, 70, 0.35, 0.01, 0.03, 60));
    patterns.push_back(new RunPattern(LINE_TRACE, 60, DISTANCE, 70, 0.25, 0.03, 0.03, 60));
    patterns.push_back(new RunPattern(LINE_TRACE, 60, DISTANCE, 70, 0.35, 0.01, 0.03, 60));

    // s字
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 70, 0.45, 0.01, 0.035, 60));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 30, 0.45, 0.01, 0.035, 60));

    // GATE1からの円
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 120, 0.45, 0.01, 0.035, 60)); // 適切な値 ふらつく
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 20, 0.25, 0.03, 0.03, 60)); // 500

    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 90, 0.35, 0.01, 0.03, 60));

    patterns.push_back(new RunPattern(LINE_TRACE, 60, DISTANCE, 90, 0.25, 0.03, 0.03, 60));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 70, 0.4, 0.01, 0.03, 60)); // GATE2

    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 10, 0.25, 0.03, 0.03, 60));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 30, 0.45, 0.01, 0.035, 60));

    patterns.push_back(new RunPattern(LINE_TRACE, 60, DISTANCE, 150, 0.4, 0.01, 0.04, 60)); // 最後の円
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 30, 0.25, 0.03, 0.03, 60));

    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 80, 0.5, 0.0, 0.03, 60));
    patterns.push_back(new RunPattern(LINE_TRACE, 25, COLOR, 2, 0.5, 0.1, 0.03, 30));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, DISTANCE, 30, 0.5, 0.1, 0.03, 40));
    patterns.push_back(new RunPattern(LINE_TRACE, 15, COLOR, 8, 0.5, 0.1, 0.03, 40));

    patterns.push_back(new RunPattern(TURNING, 20, BLACKLINE, 1, DIRECTION_LEFT));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.4, 0.01, 0.03, 80));
    patterns.push_back(new RunPattern(TURNING, 20, BLACKLINE, 1, DIRECTION_RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.4, 0.01, 0.03, 80, RIGHT));
    patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 20));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.4, 0.01, 0.03, 80, RIGHT));
    patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 20));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.4, 0.01, 0.03, 80, RIGHT));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1)); 
}

void CourseRun::createCourseR(){
    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 20, 0.7, 0.0, 0.03, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 50, 0.25, 0.0, 0.03, 60, RIGHT));

    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 70, 0.35, 0.0, 0.03, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 70, 0.25, 0.0, 0.03, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 70, 0.35, 0.0, 0.03, 60, RIGHT));

    // s字
    patterns.push_back(new RunPattern(LINE_TRACE, 40, DISTANCE, 70, 0.5, 0.01, 0.03, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 30, 0.6, 0.01, 0.03, 60, RIGHT));

    // GATE1からの円
    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 100, 0.65, 0.01, 0.05, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 45, DISTANCE, 20, 0.25, 0.01, 0.03, 60, RIGHT)); // 500

    patterns.push_back(new RunPattern(LINE_TRACE, 40, DISTANCE, 90, 0.45, 0.01, 0.03, 60, RIGHT));

    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 90, 0.25, 0.01, 0.03, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 35, DISTANCE, 70, 0.5, 0.01, 0.03, 60, RIGHT));

    patterns.push_back(new RunPattern(LINE_TRACE, 40, DISTANCE, 10, 0.25, 0.01, 0.03, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 30, 0.55, 0.01, 0.03, 60, RIGHT));

    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 150, 0.65, 0.01, 0.05, 60, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 50, DISTANCE, 60, 0.25, 0.01, 0.03, 80, RIGHT));
}