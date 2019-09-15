#include "Game.h"

Game::Game(Course course){
    this->course = course;

    if(this->course == L) {
        createCourseL();
    }else if(this->course == R){
        createCourseR();
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

void Game::createCourseL(){
    Block &block = Block::singleton();
    int blocks[8]={block.cross1, block.cross2, block.cross3, block.cross4, block.cross5, block.cross6, block.cross7, block.cross8};
    int bonus[2]={block.bonus_pos, block.bonus_color};
    int number = block.number;

    patterns.push_back(new RunPattern(BRAKE, 0, DISTANCE, 30));
}

void Game::createCourseR(){
    Block &block = Block::singleton();
    int blocks[8]={block.cross1, block.cross2, block.cross3, block.cross4, block.cross5, block.cross6, block.cross7, block.cross8};
    int bonus[2]={block.bonus_pos, block.bonus_color};
    int number = block.number;

    patterns.push_back(new RunPattern(BRAKE, 0, DISTANCE, 30));
}