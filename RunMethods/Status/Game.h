#include "RunStatus.h"
#include "Dijkstra.h"
#include "Block.h"

enum TraceLine{
  Line_R = 0,
  Line_L = 1,
};

class Game : public RunStatus
{
  private:
  	Dijkstra *dijkstra;
    void straight();
    void turnR();
    void turnL();
    void turnBack();
    void release(int direction, int before_point, int now_point);
    void blockcatch(int direction);

    int edge_line;

  public:
    Game(Course course);
    void init();
    void setNextState();
    void startGame();
    virtual ~Game();
};