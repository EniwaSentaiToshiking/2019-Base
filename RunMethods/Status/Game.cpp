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
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 104, DIRECTION_RIGHT));
        edge_line = Line_R;
    } else {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 92, DIRECTION_RIGHT));
        edge_line = Line_R;
    }
    straight();
}

void Game::turnL(){ // 左90度旋回
    if (edge_line == Line_R) {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 92, DIRECTION_LEFT));
        edge_line = Line_L;
    } else {
        patterns.push_back(new RunPattern(TURNING, 20, DIRECTION, 104, DIRECTION_LEFT));
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
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, direction + 5, DIRECTION_LEFT));
        patterns.push_back(new RunPattern(STRAIGHT, -15, DISTANCE, 9));
    } else {
        patterns.push_back(new RunPattern(STRAIGHT, 15, DISTANCE, 10));
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, 360 - direction, DIRECTION_LEFT));
        patterns.push_back(new RunPattern(ARM, 180, 100));
        patterns.push_back(new RunPattern(SPIN, 15, DIRECTION, 360 - direction + 5, DIRECTION_RIGHT));
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
    if (this->course == L) {
        patterns.push_back(new RunPattern(STRAIGHT, 20, BLACKLINE, 1)); 
    } else {
        patterns.push_back(new RunPattern(STRAIGHT, 20, DISTANCE, 25));
        patterns.push_back(new RunPattern(SPIN, 30, DIRECTION, 65, DIRECTION_LEFT));
        patterns.push_back(new RunPattern(STRAIGHT, 10, BLACKLINE, 1));
    } 
}

// 色　0:red 1:blue 2:yellow 3:green 4:black
void Game::createCourseL(){
    Block &block = Block::singleton();
    int blocks[8]={block.cross1, block.cross2, block.cross3, block.cross4, block.cross5, block.cross6, block.cross7, block.cross8};
    int bonus[2]={block.bonus_pos, block.bonus_color};
    int number = block.number;
    
    if(blocks[4] == 4 && (number == 1 || number == 4 || number == 6 || number == 7)) {
        if(number == 1) {
            turnL();
            release(35);
            turnR();
            if(blocks[2] == 3) {
                release(325);
                jumpCircle();
            } else if(blocks[2] == 0) {
                jumpCircle();
                release(325);
            } else {
                jumpCircle();
                release(35);
            }
            jumpCircle();
            release(325);
            parking(0);
        } else {
            if(number == 4) {
                release(325);
                jumpCircle();
            } else if(number == 6) {
                release(35);
                jumpCircle();
            } else {
                jumpCircle();
                release(35);
            }
            jumpCircle();
            if(blocks[5] == 0) {
                turnL();
                release(35);
            } else if(blocks[5] == 2) {
                release(325);
                turnL();
            } else {
                release(35);
                turnL();
            }
            turnR();
            release(325);
            parking(0);
        }
    } else if(blocks[2] == 4 && (number == 1 || number == 2 || number == 3 || number == 5)) {
        if(blocks[4] == 1) {
            release(325);
            jumpCircle();
        } else if(blocks[4] == 3) {
            release(35);
            jumpCircle();
        } else {
            jumpCircle();
            release(35);
        }
        turnL();
        if(number == 1) {
            release(325);
            turnR();
        } else if(number ==2) {
            release(35);
            turnR();
        } else if(number == 3) {
            turnR();
            release(325);
        } else {
            turnR();
            release(35);
        }
        jumpCircle();
        release(325);
        parking(0);
    } else if(blocks[5] == 4 && (number == 2 || number == 3 || number == 5 || number == 8)) {
        if(blocks[4] == 1) {
            release(325);
            jumpCircle();
        } else if(blocks[4] == 3) {
            release(35);
            jumpCircle();
        } else {
            jumpCircle();
            release(35);
        }
        jumpCircle();
        if(number == 5) {
            release(325);
            turnL();
        } else if(number == 3) {
            turnL();
            release(35);
        } else {
            release(35);
            turnL();
        }
        turnR();
        release(325);
        parking(0);
    } else if(blocks[4] != 2) {
        if(blocks[4] == 1) {
            release(325);
            jumpCircle();
        } else if(blocks[4] == 3) {
            release(35);
            jumpCircle();
        } else {
            jumpCircle();
            release(35);
        }
        if(blocks[5] == 0 || blocks[5] == 2 || blocks[5] == 1 || blocks[5] == 3) {
            jumpCircle();
            if(blocks[5] == 0) {
                turnL();
                release(35);
                turnR();
            } else if(blocks[5] == 3) {
                turnL();
                release(325);
                turnR();
            } else if(blocks[5] == 2) {
                release(325);
                turnL();
                turnR();
            } else {
                release(35);
                turnL();
                turnR();
            }
            release(325);
            parking(0);
        } else {
            turnL();
            if(blocks[2] == 2) {
                release(325);
                turnR();
            } else if(blocks[2] == 0) {
                turnR();
                release(325);
            } else {
                release(35);
                turnR();
            }
            jumpCircle();
            release(325);
            parking(0);
        }
    } else if(blocks[4] == 2) {
        turnL();
        release(35);
        turnR();
        if(blocks[2] ==3) {
            release(325);
            jumpCircle();
        } else if(blocks[2] == 0) {
            jumpCircle();
            release(325);
        } else {
            jumpCircle();
            release(35);
        }
        jumpCircle();
        release(325);
        parking(0);
    } else {
        turnL();
        turnR();
        jumpCircle();
        jumpCircle();
        parking(0);
    }
}

void Game::createCourseR(){
    Block &block = Block::singleton();
    int blocks[8]={block.cross1, block.cross2, block.cross3, block.cross4, block.cross5, block.cross6, block.cross7, block.cross8};
    int bonus[2]={block.bonus_pos, block.bonus_color};
    int number = block.number;

    char tmp[256];
	for (int i = 0; i < 8; i ++){
		snprintf(tmp, 255, "%s%d", tmp, blocks[i]);
	}
	
	ev3_lcd_draw_string(tmp, 0, 40);

    if (blocks[0] == 4) {
        turnR();
        if(blocks[3] == 2) {
            release(325);
            turnL();
            jumpCircle();
        } else {
            turnL();
            release(35);
            jumpCircle();
        }
        // 2の色正面捕獲
        if (blocks[2] == 0 && bonus[0] != 1) {
            release(35);
            turnL();
        } else if(blocks[2] == 2) {
            release(325);
            turnL();
        } else if(blocks[2] == 1) {
            turnL();
            release(35);
        } else {
            turnL();
            release(325);
        }
        turnL(); // 5の色後ろ捕獲
        if(blocks[5] == 1) {
            release(325);
        } else {
         release(35);
        }
        turnR();
        turnR();
        release(35);
        jumpCircle();
        turnR();
        if(blocks[4] == 0) {
            jumpCircle();
            release(35);
        } else {
            release(35);
            jumpCircle();
        }
        jumpCircle(); // 0位置黒左捕獲          
        // ボーナスナンバーによる場合分け
        switch (number) {
            case 1:
                turnR();
                turnR();
                jumpCircle();
                turnL();
                turnL();
                turnL();
                release(35);
                jumpCircle();
                parking(0);
                break;
            case 2:
                turnR();
                release(35);
                turnR();
                release(35);
                turnR();
                parking(0);
                break;
            case 3:
                turnR();
                jumpCircle();
                release(35);
                turnR();
                turnR();
                jumpCircle();
                parking(0);
                break;
            case 4:
                turnR();
                turnR();
                release(35);
                turnR();
                parking(0);
                break;
            case 5:
                turnR();
                turnR();
                turnL();
                release(35);
                turnR();
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
            case 6:
                turnR();
                turnR();
                jumpCircle();
                release(35);
                turnR();
                turnR();
                parking(260);
                break;
            case 7:
                turnR();
                turnR();
                jumpCircle();
                release(325);
                turnR();
                turnR();
                parking(260);
                break;
            case 8:
                turnR();
                turnR();
                jumpCircle();
                turnL();
                release(35);
                turnR();
                turnR();
                jumpCircle();
                turnR();
                jumpCircle();
                parking(260);
                break;
        }
    } else if(blocks[1] == 4) {
        turnR();
        if(blocks[3] == 2) {
            release(325);
            turnL();
            jumpCircle();
        } else {
            turnL();
            release(35);
            jumpCircle();
        }
        // 2の色正面捕獲
        if (blocks[2] == 0 && bonus[0] != 1) {
            release(35);
            turnL();
        } else if(blocks[2] == 2) {
            release(325);
            turnL();
        } else if(blocks[2] == 1) {
            turnL();
            release(35);
        } else {
            turnL();
            release(325);
        }
        turnL(); // 5の色後ろ捕獲
        if(blocks[5] == 1) {
            release(325);
        } else {
         release(35);
        }
        turnR();
        turnR();
        release(35);
        jumpCircle();
        turnR();
        if(blocks[4] == 0) {
            jumpCircle();
            release(35);
        } else {
            release(35);
            jumpCircle();
        }
        jumpCircle(); // 0位置色左捕獲
        turnR();
        release(35);
        jumpCircle(); // 1位置黒後捕獲
        // ボーナスナンバーによる場合分け
        switch (number) {
            case 1:
                turnR();
                turnR();
                release(35);
                jumpCircle();
                parking(0);
                break;
            case 2:
                turnR();
                jumpCircle();
                turnR();
                turnR();
                release(35);
                turnL();
                parking(0);
                break;
            case 3:
                release(35);
                turnR();
                turnR();
                jumpCircle();
                parking(0);
                break;
            case 4:
                turnR();
                turnR();
                release(325);
                jumpCircle();
                parking(0);
                break;
            case 5:
                turnR();
                release(325);
                turnR();
                jumpCircle();
                parking(0);
                break;
            case 6:
                turnR();
                jumpCircle();
                turnR();
                release(325);
                turnR();
                turnL();
                parking(0);
                break;
            case 7:
                turnR();
                jumpCircle();
                release(35);
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
            case 8:
                turnR();
                jumpCircle();
                release(325);
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
        }
    } else if(blocks[2] == 4) {
        if(blocks[6] == 1 || blocks[7] == 0) {
            turnL();
            turnR();
            release(35);
            jumpCircle();
            release(35);
            if(blocks[4] == 2) {
                jumpCircle();
                turnR();
                release(35);
                turnR();
                turnL(); // 2位置の黒捕獲(右から)
            } else {
                turnR();
                jumpCircle(); // 2位置の黒捕獲(右から)
            }
        } else if(blocks[5] == 0 || blocks[5] == 1 || blocks[5] == 2) {
            jumpCircle();
            if(blocks[5] == 0) {
                release(325);
                jumpCircle();
            } else if(blocks[5] == 1) {
                jumpCircle();
                release(325);
            } else {
                jumpCircle();
                release(35);
            }
            turnR(); // 2位置の黒捕獲(右から)
        } else {
            turnR();
            if(blocks[3] == 2) {
                release(325);
                turnL();
            } else {
                turnL();
                release(35);
            }
            turnL();
            release(325);
            turnR();
            turnR(); // 2位置の黒捕獲(右から)
        }
        switch(number) {
            case 1:
                release(325);
                turnL();
                parking(0);
                break;
            case 2:
                release(35);
                turnL();
                parking(0);
                break;
            case 3:
                turnR();
                release(325);
                jumpCircle();
                turnR();
                if(blocks[3] == 3) {
                    release(35);
                    turnR();
                    jumpCircle();
                    turnR();
                    turnL();
                    parking(0);
                } else if(blocks[3] == 0) {
                    turnR();
                    jumpCircle();
                    turnR();
                    release(325);
                    turnL();
                    parking(0);
                } else if(blocks[3] == 1) {
                    turnR();
                    jumpCircle();
                    release(325);
                    turnR();
                    turnL();
                    parking(0);
                } else {
                    turnR();
                    jumpCircle();
                    release(35);
                    turnR();
                    turnL();
                    parking(0);
                }
                break;
            case 4:
                turnR();
                turnR();
                turnR();
                release(35);
                jumpCircle();
                turnR();
                release(35);
                parking(260);
                break;
            case 5:
                turnR();
                release(35);
                turnR();
                if(blocks[5] == 3) {
                    release(325);
                    turnR();
                    turnR();
                    turnL();
                    parking(0);
                } else if(blocks[5] == 0) {
                    release(35);
                    turnR();
                    turnR();
                    turnL();
                    parking(0);
                } else if(blocks[5] == 1) {
                    turnR();
                    release(325);
                    turnR();
                    turnL();
                    parking(0);
                } else {
                    turnR();
                    release(35);
                    turnR();
                    turnL();
                    parking(0);
                }
                break;
            case 6:
                turnR();
                turnR();
                turnR();
                release(325);
                jumpCircle();
                turnR();
                release(35);
                parking(260);
                break;
            case 7:
                turnR();
                turnR();
                release(35);
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
            case 8:
                turnR();
                turnR();
                release(325);
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
        }
    } else if(blocks[3] == 4) {
        turnR(); // 3位置の黒捕獲(右から)
        switch(number) {
            case 1:
                turnL();
                jumpCircle();
                release(35);
                jumpCircle();
                parking(0);
                break;
            case 2:
                turnL();
                release(35);
                turnL(); // 5位置の色捕獲(左から)
                if(blocks[5] == 3) {
                    release(325);
                    turnR();
                    turnR(); // 2位置の色捕獲(左から)
                } else if(blocks[5] == 0) {
                    release(35);
                    turnR();
                    turnR(); // 2位置の色捕獲(左から)
                } else if(blocks[5] == 1) {
                    turnR();
                    release(325);
                    turnR(); // 2位置の色捕獲(左から)
                } else {
                    turnR();
                    release(35);
                    turnR(); // 2位置の色捕獲(左から)
                }
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
                break;
            case 3:
                release(325);
                turnL();
                turnL(); // 5位置の色捕獲(左から)
                if(blocks[5] == 3) {
                    release(325);
                    turnR();
                    turnR(); // 2位置の色捕獲(左から)
                } else if(blocks[5] == 0) {
                    release(35);
                    turnR();
                    turnR(); // 2位置の色捕獲(左から)
                } else if(blocks[5] == 1) {
                    turnR();
                    release(325);
                    turnR(); // 2位置の色捕獲(左から)
                } else {
                    turnR();
                    release(35);
                    turnR(); // 2位置の色捕獲(左から)
                }
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
                break;
            case 4:
                turnL();
                jumpCircle();
                release(325);
                jumpCircle();
                parking(0);
                break;
            case 5:
                jumpCircle();
                turnL();
                turnL(); 
                release(325); 
                jumpCircle(); // 5位置の色捕獲(左から)
                if(blocks[5] == 3) {
                    release(325);
                    turnR();
                    turnR(); // 2位置の色捕獲(左から)
                } else if(blocks[5] == 0) {
                    release(35);
                    turnR();
                    turnR(); // 2位置の色捕獲(左から)
                } else if(blocks[5] == 1) {
                    turnR();
                    release(325);
                    turnR(); // 2位置の色捕獲(左から)
                } else {
                    turnR();
                    release(35);
                    turnR(); // 2位置の色捕獲(左から)
                }
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
                break;
            case 6:
                turnL();
                turnL();
                turnR();
                release(325);
                jumpCircle();
                turnR();
                release(35);
                parking(260);
                break;
            case 7:
                turnL();
                turnL();
                release(35);
                turnR();
                turnR();
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
                break;
            case 8:
                turnL();
                turnL();
                release(325);
                turnR();
                turnR();
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
                break;
        }
    } else if(blocks[4] == 4) {
        if(blocks[5] != 3) {
            jumpCircle(); // 5位置の色捕獲(正面から)
            if(blocks[5] == 0) {
                release(325);
                jumpCircle();
                jumpCircle(); // 4位置の黒捕獲(正面から)
            } else if(blocks[5] == 1) {
                jumpCircle();
                release(325);
                jumpCircle(); // 4位置の黒捕獲(正面から)
            } else {
                jumpCircle();
                release(35);
                jumpCircle(); // 4位置の黒捕獲(正面から)
            }
        } else {
            turnL();
            turnR();
            release(35);
            jumpCircle();
            release(35);
            turnR();
            turnL(); // 4位置の黒捕獲(正面から)
        }
        switch(number) {
            case 1:
                turnR();
                release(35);
                jumpCircle();
                turnR();
                release(35);
                jumpCircle();
                release(35);
                jumpCircle();
                turnR();
                release(35);
                turnR();
                jumpCircle();
                if(blocks[2] == 2) {
                    release(325);
                } else {
                    release(35);
                }
                jumpCircle();
                parking(0);
                break;
            case 2:
                turnR();
                jumpCircle();
                turnR();
                release(35);
                jumpCircle();
                release(35);
                jumpCircle();
                turnR();
                release(35);
                turnR();
                jumpCircle();
                if(blocks[2] == 2) {
                    release(325);
                } else {
                    release(35);
                }
                jumpCircle();
                parking(0);
                break;
            case 3:
                turnR();
                jumpCircle();
                turnR();
                jumpCircle();
                release(35);
                jumpCircle();
                turnR();
                release(35);
                turnR();
                jumpCircle();
                if(blocks[2] == 2) {
                    release(325);
                } else {
                    release(35);
                }
                jumpCircle();
                parking(0);
                break;
            case 4:
                turnL();
                turnL();
                turnL();
                release(325);
                jumpCircle();
                if(blocks[2] == 2) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
                break;
            case 5:
                turnR();
                turnR();
                jumpCircle();
                release(35);
                turnL();
                turnL();
                release(325);
                jumpCircle();
                if(blocks[0] == 2) {
                    jumpCircle();
                    turnL();
                    release(325);
                    parking(80);
                } else {
                    turnL();
                    release(35);
                    turnR();
                    parking(0);
                }
                break;
            case 6:
                turnR();
                turnR();
                turnR();
                release(35);
                turnR();
                turnR();
                parking(260);
                break;
            case 7:
                turnL();
                turnL();
                release(325);
                jumpCircle();
                turnL();
                jumpCircle();
                if(blocks[5] == 3) release(325);
                turnL();
                if(blocks[2] == 2) {
                    release(325);
                } else {
                    release(35);
                }
                jumpCircle();
                parking(0);
                break;
            case 8:
                turnL();
                turnL();
                jumpCircle();
                release(325);
                turnL();
                jumpCircle();
                if(blocks[5] == 3) release(325);
                turnL();
                if(blocks[2] == 2) {
                    release(325);
                } else {
                    release(35);
                }
                jumpCircle();
                parking(0);
                break;
        }
    } else if(blocks[5] == 4) {
        jumpCircle(); // 5位置の黒捕獲(正面から)
        switch(number) {
        case 1:
            turnR();
            jumpCircle();
            turnL();
            release(325);
            if(blocks[0] == 2) {
                jumpCircle();
                turnL();
                release(325);
                parking(80);
            } else {
                turnL();
                release(35);
                turnR();
                parking(0);
            }
            break;
        case 2:
            turnR();
            release(325);
            if(blocks[2] == 0 || blocks[2]) {
                turnL();
                if(blocks[2] == 0) {
                    release(35);
                } else {
                    release(325);
                }   
                jumpCircle();
                parking(0);
            } else {
                jumpCircle();
                turnL();
                release(325);
                jumpCircle();
                turnL();
                release(325);
                parking(80);
            }
            break;
        case 3:
            turnR();
            release(35);
            if(blocks[2] == 0 || blocks[2]) {
                turnL();
                if(blocks[2] == 0) {
                    release(35);
                } else {
                    release(325);
                }
                jumpCircle();
                parking(0);
            } else {
                jumpCircle();
                turnL();
                release(325);
                jumpCircle();
                turnL();
                release(325);
                parking(80);
            }
            break;
        case 4:
            jumpCircle();
            release(35);
            if(blocks[2] == 0 || blocks[2] == 3) {
                turnR();
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
            } else {
                turnL();
                turnL();
                release(325);
                jumpCircle();
                turnL();
                release(325);
                jumpCircle();
                if(blocks[3] == 2){
                    release(325);
                    turnL();
                } else {
                    turnL();
                    release(35);
                }
                jumpCircle();
                release(325);
                jumpCircle();
                parking(0);
            }
            break;
        case 5:
            jumpCircle();
            turnR();
            turnR();
            release(35);
            if(blocks[1] == 0 || blocks[2] == 2) {
                turnL();
                turnL();
                release(325);
                turnL();
                release(35);
                turnR();
                parking(0);
            }
            break;
        case 6:
            jumpCircle();
            release(325);
            if(blocks[2] == 0 || blocks[2] == 3) {
                turnR();
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
            } else {
                turnL();
                turnL();
                release(325);
                jumpCircle();
                turnL();
                release(325);
                jumpCircle();
                if(blocks[3] == 2){
                    release(325);
                    turnL();
                } else {
                    turnL();
                    release(35);
                }
                jumpCircle();
                release(325);
                jumpCircle();
                parking(0);
            }
            break;
        case 7:
            release(325);
            jumpCircle();
            if(blocks[2] == 0 || blocks[2] == 3) {
                turnR();
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
            } else {
                turnL();
                turnL();
                release(325);
                jumpCircle();
                turnL();
                release(325);
                jumpCircle();
                if(blocks[3] == 2){
                    release(325);
                    turnL();
                } else {
                    turnL();
                    release(35);
                }
                jumpCircle();
                release(325);
                jumpCircle();
                parking(0);
            }
            break;
        case 8:
            turnR();
            turnR();
            turnR();
            release(35);
            jumpCircle();
            turnR();
            release(35);
            jumpCircle();
            release(35);
            if(blocks[4] == 3 || blocks[4] == 0) {
                jumpCircle();
                turnR();
                if(blocks[4] == 3) {
                    release(35);
                    jumpCircle();
                    parking(260);
                } else {
                    jumpCircle();
                    release(35);
                    parking(260);
                }
            } else {
                turnR();
                jumpCircle();
                if(blocks[2] == 0) {
                    release(325);
                } else {
                    release(35);
                }
                turnL();
                parking(0);
            }
            break;
        }
    } else if(blocks[6] == 4) {
        turnR();
        if(blocks[3] == 2) {
            release(325);
            turnL();
        } else {
            turnL();
            release(35);
        } 
        jumpCircle();
        if(blocks[2] == 2) {
            release(325);
        } else {
            release(35);
        }
        turnL();
        turnL();
        if(blocks[5] == 1) {
            release(325);
        } else {
            release(35);
        }
        jumpCircle();
        turnR();
        turnR();
        release(35);
        jumpCircle(); // 6位置の黒部録捕獲(正面から)
        switch(number) {
            case 1:
                turnR();
                jumpCircle();
                release(325);
                turnL();
                parking(0);
                break;
            case 2:
                turnR();
                jumpCircle();
                release(35);
                turnL();
                parking(0);
                break;
            case 3:
                turnR();
                jumpCircle();
                turnR();
                release(325);
                turnR();
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
            case 4:
                turnR();
                release(325);
                if(blocks[4] == 3) {
                    turnL();
                    turnR();
                    release(35);
                    parking(260);
                } else {
                    jumpCircle();
                    turnL();
                    parking(0);
                }
                break;
            case 5:
                turnR();
                turnR();
                release(325);
                turnL();
                turnL();
                jumpCircle();
                parking(0);
                break;
            case 6:
                release(35);
                if(blocks[4] == 2 || blocks[4] == 0) {
                    jumpCircle();
                    turnR();
                    if(blocks[4] == 2) {
                        release(35);
                        jumpCircle();
                    } else {
                        jumpCircle();
                        release(35);
                    } 
                    parking(260);
                } else {
                    turnR();
                    jumpCircle();
                    turnL();
                    parking(0);
                }
                break;
            case 7:
                turnR();
                jumpCircle();
                turnR();
                turnR();
                release(35);
                turnR();
                turnR();
                turnL();
                parking(0);
                break;
            case 8:
                turnR();
                turnR();
                release(35);
                jumpCircle();
                turnL();
                turnL();
                jumpCircle();
                jumpCircle();
                parking(0);
                break;
        }
    } else if(blocks[7] == 4) {
        turnR();
        if(blocks[3] == 2) {
            release(325);
            turnL();
        } else {
            turnL();
            release(35);
        } 
        jumpCircle();
        if(blocks[2] == 2) {
            release(325);
        } else {
            release(35);
        }
        turnL();
        turnL();
        if(blocks[5] == 1) {
            release(325);
        } else {
            release(35);
        }
        jumpCircle();
        turnR(); // 7位置の黒部録捕獲(右から)
        switch(number) {
            case 1:
                turnR();
                turnR();
                jumpCircle();
                turnL();
                release(35);
                jumpCircle();
                parking(0);
                break;
            case 2:
                turnR();
                turnR();
                jumpCircle();
                release(325);
                turnL();
                jumpCircle();
                parking(0);
                break;
            case 3:
                turnR();
                turnR();
                jumpCircle();
                release(35);
                turnL();
                jumpCircle();
                parking(0);
                break;
            case 4:
                turnR();
                turnR();
                turnL();
                release(35);
                if(blocks[4] == 0) {
                    jumpCircle();
                    turnR();
                    release(325);
                    parking(260);
                } else {
                    turnR();
                    turnL();
                    parking(0);
                }
                break;
            case 5:
                turnR();
                turnR();
                release(35);
                if(blocks[4] == 0) {
                    turnL();
                    jumpCircle();
                    turnR();
                    release(325);
                    parking(260);
                } else if(blocks[1] == 0 || blocks[0] == 2) {
                    jumpCircle();
                    jumpCircle();
                    turnL();
                    release(325);
                    jumpCircle();
                    turnL();
                    release(325);
                    parking(80);
                } else {
                    jumpCircle();
                    turnL();
                    jumpCircle();
                    parking(0);
                }
                break;
            case 6:
                turnR();
                turnR();
                turnL();
                release(325);
                if(blocks[4] == 0) {
                    jumpCircle();
                    turnR();
                    release(325);
                    parking(260);
                } else {
                    turnR();
                    turnL();
                    parking(0);
                }
                break;
            case 7:
                turnR();
                release(35);
                jumpCircle();
                if(blocks[6] == 1) {
                    release(35);
                    turnR();
                    jumpCircle();
                } else if(blocks[6] == 2) {
                    turnR();
                    release(325);
                    jumpCircle();
                } else {
                    turnR();
                    jumpCircle();
                    if(blocks[6] == 3) {
                        release(325);
                    } else {
                        release(35);
                    }
                }
                turnL();
                parking(0);
                break;
            case 8:
                turnR();
                turnR();
                jumpCircle();
                turnR();
                turnR();
                release(35);
                turnR();
                if(blocks[4] == 0) {
                    jumpCircle();
                    jumpCircle();
                    turnR();
                    release(325);
                    parking(260);
                } else if(blocks[1] == 0 || blocks[0] == 2) {
                    turnR();
                    jumpCircle();
                    turnL();
                    release(325);
                    jumpCircle();
                    turnL();
                    release(325);
                    parking(80);
                } else {
                    turnR();
                    turnL();
                    jumpCircle();
                    parking(0);
                }
                break;
        }
    } else {
        turnR();
        turnL();
        jumpCircle();
        jumpCircle();
        parking(0);
    }
}