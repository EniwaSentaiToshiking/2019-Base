#include "Parking.h"

Parking::Parking(Course course){
    this->course = course;

    if(this->course == L) {
        createCourseL();
    }else if(this->course == R){
        createCourseR();
    }

    setNextState();
}

Parking::~Parking(){
}

void Parking::init(){
}

void Parking::setNextState(){
    nextState = STOP;
}

void Parking::createCourseL(){
    //直線
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 2, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 1, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 2, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 1, 1.3, 0.0, 0.02, 40));

    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 60, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 4, 1.3, 0.0, 0.02, 40));

    patterns.push_back(new RunPattern(TURNING, 30, DIRECTION, 65, DIRECTION_LEFT));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, DISTANCE, 12, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(SPIN, 30, DIRECTION, 70, DIRECTION_RIGHT));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));
    patterns.push_back(new RunPattern(SPIN, 20, DIRECTION, 10, DIRECTION_LEFT));


    // patterns.push_back(new RunPattern(LINE_TRACE, 15, COLOR, 2, 1.3, 0.0, 0.02, 40)); 
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1)); // ここまでの2行はゲーム攻略の方に含めるほうが良きかな

    patterns.push_back(new RunPattern(SPIN, 30, DIRECTION, 75, DIRECTION_RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 15, COLOR, 2, 1.3, 0.0, 0.02, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 15, DISTANCE, 10, 1.3, 0.0, 0.02, 40, RIGHT));

    patterns.push_back(new RunPattern(SPIN, 40, DIRECTION, 65, DIRECTION_LEFT));
    patterns.push_back(new RunPattern(STRAIGHT, 30, DISTANCE, 25));
    patterns.push_back(new RunPattern(SPIN, 40, DIRECTION, 65, DIRECTION_LEFT));
}

void Parking::createCourseR(){
    //直線
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 2, 1.3, 0.0, 0.02, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 1, 1.3, 0.0, 0.02, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 2, 1.3, 0.0, 0.02, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 30, COLOR, 1, 1.3, 0.0, 0.02, 40, RIGHT));
    //曲がる
    patterns.push_back(new RunPattern(LINE_TRACE, 30, DISTANCE, 60, 1.3, 0.0, 0.02, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 4, 1.3, 0.0, 0.02, 40, RIGHT));

    patterns.push_back(new RunPattern(TURNING, 30, DIRECTION, 65, DIRECTION_RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 5, 12, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(TURNING, 30, DIRECTION, 65, DIRECTION_LEFT));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 5, 12, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 2, 12, 1.3, 0.0, 0.02, 40));
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1));



    patterns.push_back(new RunPattern(LINE_TRACE, 15, COLOR, 2, 1.3, 0.0, 0.02, 40, LEFT)); 
    patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 25));
    patterns.push_back(new RunPattern(SPIN, 30, DIRECTION, 65, DIRECTION_LEFT));
    patterns.push_back(new RunPattern(STRAIGHT, 10, BLACKLINE, 1)); // ここまでの3行はゲーム攻略の方に含めるほうが良きかな
    
    patterns.push_back(new RunPattern(SPIN, 30, DIRECTION, 65, DIRECTION_RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 15, COLOR, 2, 1.3, 0.0, 0.02, 40, RIGHT));
    patterns.push_back(new RunPattern(LINE_TRACE, 15, DISTANCE, 10, 1.3, 0.0, 0.02, 40, RIGHT));

    patterns.push_back(new RunPattern(SPIN, 40, DIRECTION, 60, DIRECTION_LEFT));
    patterns.push_back(new RunPattern(STRAIGHT, 30, DISTANCE, 40));
}