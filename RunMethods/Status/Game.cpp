#include "Game.h"

Game::Game(Course course){
    this->course = course;

    if(this->course == L) {
        createCourseL();
        edge_line = Line_L;
    } else if(this->course == R){
        createCourseR();
        edge_line = Line_R;
    }
    setNextState();
}

Game::~Game(){
}

void Game::init(){
}

void Game::setNextState(){
    nextState = PARKING;
}

void Game::straight(){ // 色を検知するまで直進
    Edge edge;
    if (edge_line == Line_L) {
        edge = LEFT;
    } else {
        edge = RIGHT;
    }
    patterns.push_back(new RunPattern(LINE_TRACE, 20, DISTANCE, 5, 0.5, 0.0, 0.1, 25, edge));
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.3, 0.0, 0.1, 25, edge));
}

void Game::jumpCircle(){ // サークルを直進で乗り超える
    patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 12));

    if (edge_line == Line_R) {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 20, DIRECTION_RIGHT));
    } else {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 20, DIRECTION_LEFT));
    }
    straight();
}

void Game::turnR(){ // 右90度旋回
    if (edge_line == Line_R) {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 107, DIRECTION_RIGHT));
        edge_line = Line_R;
    } else {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 95, DIRECTION_RIGHT));
        edge_line = Line_R;
    }
    straight();
}

void Game::turnL(){ // 左90度旋回
    if (edge_line == Line_R) {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 95, DIRECTION_LEFT));
        edge_line = Line_L;
    } else {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 107, DIRECTION_LEFT));
        edge_line = Line_L;
    }
    straight();
}

void Game::turnBack(){ // 180度旋回
    if (edge_line == Line_R) {
        patterns.push_back(new RunPattern(SPIN, 10, DIRECTION, 150, DIRECTION_LEFT));
        
    } else {
        patterns.push_back(new RunPattern(SPIN, 10, DIRECTION, 150, DIRECTION_RIGHT));

    }
    straight();
}

void Game::release(int direction){ // ブロックのリリース
    if (direction < 180) {
        patterns.push_back(new RunPattern(STRAIGHT, 15, DISTANCE, 10));
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, direction, DIRECTION_RIGHT));
        patterns.push_back(new RunPattern(ARM, 180, 100));
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, direction + 10, DIRECTION_LEFT));
        patterns.push_back(new RunPattern(STRAIGHT, -15, DISTANCE, 8));
    } else {
        patterns.push_back(new RunPattern(STRAIGHT, 15, DISTANCE, 10));
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, 360 - direction, DIRECTION_LEFT));
        patterns.push_back(new RunPattern(ARM, 180, 100));
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, 360 - direction + 8, DIRECTION_RIGHT));
        patterns.push_back(new RunPattern(STRAIGHT, -15, DISTANCE, 8));
    }
}

void Game::parking(int direction){ // 駐車に向けた動き 
    if (direction == 0) {
    } else if (direction < 180) {
        patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 5));
        patterns.push_back(new RunPattern(SPIN, 10, DIRECTION, direction, DIRECTION_RIGHT));
    } else {
        patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 5));
        patterns.push_back(new RunPattern(SPIN, 10, DIRECTION, 360 - direction, DIRECTION_LEFT));
    }
    patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1)); 
}

void Game::createCourseL(){
    Block &block = Block::singleton();
    int blocks[8]={block.cross1, block.cross2, block.cross3, block.cross4, block.cross5, block.cross6, block.cross7, block.cross8};
    int bonus[2]={block.bonus_pos, block.bonus_color};
    int number = block.number;

    turnR();

    for (int i = 0; i < 10; i++){
        turnL();
        turnL();
        release(35);
        turnR();
        turnL();
        release(325);
        jumpCircle();
        release(35);
        turnL();
        turnL();
        turnR();
        release(325);
        turnL();
        jumpCircle();
    }
}

void Game::createCourseR(){
    Block &block = Block::singleton();
    int blocks[8]={block.cross1, block.cross2, block.cross3, block.cross4, block.cross5, block.cross6, block.cross7, block.cross8};
    int bonus[2]={block.bonus_pos, block.bonus_color};
    int number = block.number;

    // patterns.push_back(new RunPattern(BRAKE, 0, DISTANCE, 30));
}