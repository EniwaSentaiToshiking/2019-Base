#include "RunStatus.h"
#include "Block.h"
#include "Course.h"

class Game : public RunStatus
{
  private:
    Course course;

    void createCourseL();
    void createCourseR();

  public:
    Game(Course course);
    void init();
    void setNextState();
    virtual ~Game();
};