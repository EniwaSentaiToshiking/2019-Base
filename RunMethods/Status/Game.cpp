#include "Game.h"

Game::Game(){
    // dijkstra = new Dijkstra();
    startGame();
    setNextState();
    this->course = course;

    if(this->course == L) {
        edge_line = Line_L; 
    }else if(this->course == R){
        edge_line = Line_R;
    }
}

Game::~Game(){
    ev3_speaker_play_tone(480, 100);
    // delete dijkstra;
}

void Game::init(){
}

void Game::setNextState(){
    nextState = STOP;
}

void Game::straight(){
    Edge edge;
    if(edge_line==Line_L){
        edge = LEFT;
    }else if(edge_line==Line_R){
        edge = RIGHT;
    }
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.5, 0.0, 0.00, 20, egde)); 
    patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 10.5));
    }
}

void Game::turnR(){
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.5, 0.0, 0.00, 20, LEFT));
    if(edge_line==Line_R){
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, -110, DIRECTION_RIGHT));
        edge_line = Line_R;
    }else{
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, -100, DIRECTION_RIGHT));
        edge_line = Line_R;
    }
    
}

void Game::turnL(){
    Edge edge;
    if(edge_line==Line_L){
        edge = LEFT;
    }else if(edge_line==Line_R){
        edge = RIGHT;
    }
    patterns.push_back(new RunPattern(LINE_TRACE, 20, COLOR, 8, 0.5, 0.0, 0.00, 20, edge));
    if(edge_line==Line_R){
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 100, DIRECTION_LEFT));
        edge_line = Line_L;
    }else if(edge_line==LineL){
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 110, DIRECTION_LEFT));
        edge_line = Line_L;
    }
}

void Game::turnBack(){
    if(edge_line==Line_R){
        patterns.push_back(new RunPattern(SPIN, 10, DIRECTION, -90, DIRECTION_RIGHT));
        patterns.push_back(new RunPattern(STRAIGHT, 10, DISTANCE, 1));
        patterns.push_back(new RunPattern(BRAKE, 0, CLOCK, 300));
        patterns.push_back(new RunPattern(SPIN, 10, BLACKLINE, 0, DIRECTION_RIGHT));
    }else{
        patterns.push_back(new RunPattern(SPIN, -10, DIRECTION, 90, DIRECTION_LEFT));
        patterns.push_back(new RunPattern(STRAIGHT, 10, DISTANCE, 1));
        patterns.push_back(new RunPattern(BRAKE, 0, CLOCK, 300));
        patterns.push_back(new RunPattern(SPIN, -10, BLACKLINE, 0, DIRECTION_LEFT));
    }
}

void Game::startGame(){
}