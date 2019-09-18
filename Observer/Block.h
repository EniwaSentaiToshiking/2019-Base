#include "Singleton.h"

#ifndef BLOCK_H
#define BLOCK_H

class Block : public Singleton<Block>
{
private:
  friend class Singleton<Block>;
  Block();

public:
  int cross1 = 3;
  int cross2 = 1;
  int cross3 = 2;
  int cross4 = 0;
  int cross5 = 2;
  int cross6 = 4;
  int cross7 = 1;
  int cross8 = 0;

  int bonus_pos = 4;
  int bonus_color = 4;

  int number = 2;

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