#include "RunStatus.h"
#include "Block.h"
#include "Course.h"

enum TraceLine{
  Line_R = 0,
  Line_L = 1,
};


class Game : public RunStatus
{
  private:
    Course course;

    void straight();
    void jumpCircle();
    void turnR();
    void turnL();
    void turnBack();
    void release(int direction);
    void parking(int direction);

    void createCourseL();
    void createCourseR();

    int edge_line;

  public:
    Game(Course course);
    void init();
    void setNextState();
    virtual ~Game();
};