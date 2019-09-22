#include "Singleton.h"

#ifndef BLOCK_H
#define BLOCK_H

class Block : public Singleton<Block>
{
private:
  friend class Singleton<Block>;
  Block();

public:
  int cross1 = 0;
  int cross2 = 1;
  int cross3 = 1;
  int cross4 = 2;
  int cross5 = 2;
  int cross6 = 3;
  int cross7 = 3;
  int cross8 = 4;

  int bonus_pos = 1;
  int bonus_color = 1;

  int number = 1;

  // デフォルトコンストラクタ以外でインスタンスを構築したい場合、createInstance()を上書きする
  /*
  Hoge(int) { std::cout << "Hoge(int)" << std::endl; }
  static Hoge *createInstance()
  {
    return new Hoge(0);
  }
  */
};

#endif