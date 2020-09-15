#include "PIDController.h"

PIDController::PIDController()
{
  // logger = new Logger("hoge.csv");
}

PIDController::~PIDController()
{
}

int PIDController::getTurn(PID *pid, unsigned int sensor_val, unsigned int target_val, int absMax)
{
  int p, i, d;
  float KP, KI, KD;

  KP = pid->p;
  KI = pid->i;
  KD = pid->d;

  previous_error = current_error;
  current_error = sensor_val - target_val;
  integral += current_error * dt;
  differential = (current_error - previous_error) / dt;

  p = KP * current_error;
  i = KI * integral;
  d = KD * differential;

  return math_limit(p + i + d, absMax);
}

int PIDController::math_limit(int pid_value, int absMax)
{
  if (pid_value > absMax)
    pid_value = absMax;
  else if (pid_value < absMax * -1)
    pid_value = absMax * - 1;
  return pid_value;
}