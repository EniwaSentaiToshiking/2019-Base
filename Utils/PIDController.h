#ifndef PIDController_H
#define PIDController_H

// #define DELTA_T 0.004

#include "PID.h"

class PIDController
{
  private:
	int previous_error = 0;
	int current_error = 0;
	double integral = 0;
	double differential = 0;
	const float absMax = 100;
	const float dt = 0.004; /* TRACER_TASKのハンドラ周期<sec>と同じ */

  public:
	PIDController();
	int getTurn(PID *pid, unsigned int sensor_val, unsigned int target_val, int absMax);
	int math_limit(int pid_value, int absMax);

	virtual ~PIDController();
};
#endif