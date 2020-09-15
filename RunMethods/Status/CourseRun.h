#include "RunStatus.h"
#include "Course.h"

class CourseRun : public RunStatus
{
  private:
    Course course;
    // vector<Lot *> lots;

    void createCourseL();
    void createCourseR();

  public:
    CourseRun(Course course);
    void init();
    void setNextState();
    virtual ~CourseRun();
};