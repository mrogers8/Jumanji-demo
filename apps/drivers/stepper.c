/*
 * stepper.c
 * Signal recving program in the user space
 * Used in part from http://people.ee.ethz.ch/~arkeller/linux/code/signal_user.c
 * Modified by rogmelan
 *
 */
#include "../include/stepper.h"

volatile bool complete_X = true;
volatile bool complete_Y = true;
struct sigaction stepper_sig;

//*****************************************************************************
//  stepper_init
//  Initialize interrupt handler
//*****************************************************************************
void stepper_hw_init (void)
{
  stepper_sig.sa_sigaction = receiveData;
  stepper_sig.sa_flags = SA_SIGINFO;
  sigaction(SIG_TEST, &stepper_sig, NULL);

  set_pid();
}

//*****************************************************************************
//*****************************************************************************
int set_pid(void)
{

        char buf[10];
        int fd = open(PID_REG, O_WRONLY);
        if(fd < 0) {
                perror("open");
                return -1;
        }
        sprintf(buf, "%i", getpid());
        if (write(fd, buf, strlen(buf) + 1) < 0) {
                perror("fwrite");
                return -1;
        }
  close(fd);
  return 0;
}

//*****************************************************************************
//*****************************************************************************
int clear_pid(void)
{

        char buf[10];
        int fd = open(PID_REG, O_WRONLY);
        if(fd < 0) {
                perror("open");
                return -1;
        }

 memset(buf,0,10);
 if (write(fd, buf, strlen(buf) + 1) < 0) {
                perror("fwrite");
                return -1;
        }
  close(fd);
  return 0;
}

//*****************************************************************************
//  receiveData
//  Interrupt Handler for Stepper Motor X
//*****************************************************************************
void receiveData (int n, siginfo_t *info, void *unused)
{
   int status;

   status = ece453_reg_read(STATUS_REG);
   //printf("DEBUG: receiveData begin [status_reg: %d]\n", status);
   if (status & STATUS_X_MASK) {
   	ece453_reg_write(CONTROL_X_REG, 0x05);
	complete_X = true;
	ece453_reg_write(STATUS_REG, (status & ~STATUS_X_MASK));
	//printf("DEBUG: Stepping X Complete\n");
   }
   if (status & STATUS_Y_MASK) {
        ece453_reg_write(CONTROL_Y_REG, 0x05);
	complete_Y = true;
	ece453_reg_write(STATUS_REG, (status & ~STATUS_Y_MASK));
	//printf("DEBUG: Stepping Y Complete\n");
   }

   //printf("DEBUG: interrupt handler completed [status_reg: %d]\n", ece453_reg_read(STATUS_REG));
}

//*****************************************************************************
//  forceStop_X
//  Forced Stop for Stepper Motor X
//*****************************************************************************
void forceStop_X (void)
{
   ece453_reg_write(CONTROL_X_REG, 0x05);
   complete_X = true;
   //printf("DEBUG: Stepping X Force Stopped\n");
}

//*****************************************************************************
//  forceStop_Y
//  Forced Stop for Stepper Motor Y
//*****************************************************************************
void forceStop_Y (void)
{
   ece453_reg_write(CONTROL_Y_REG, 0x05);
   complete_Y = true;
   //printf("DEBUG: Stepping Y Force Stopped\n");
}

//*****************************************************************************
//  step_x
//  Control for X-Axis Stepper Motor Unit
//
//  steps      stepper value (not spaces) for movement
//  direction  constant values from .h file for forward/backward movement
//  Return: 0 for success, 1 for failure
//*****************************************************************************
int step_x (int steps, int direction)
{
  char response[80];

  // Disable the Stepper Motor
  ece453_reg_write(CONTROL_X_REG, 0x05);

  // If there are any outstanding interrupts, clear them.
  ece453_reg_write(IM_REG, 0x01);
  ece453_reg_write(IRQ_REG, 0x01);

  // Set up the speed at which the motor spins
  ece453_reg_write(STEP_PERIOD_X_REG, 0x3D090);

  // Set the step count reg to the value in steps
  ece453_reg_write(STEP_COUNT_X_REG, steps);
  //printf("DEBUG: X = %d\n", steps);

  complete_X = false;

  // Configure the control register so that the stepper motor stops once the step count reaches 0
  if (direction == STEPPER_EAST) {
  	ece453_reg_write(CONTROL_X_REG, 0x1B);
  } else if (direction == STEPPER_WEST) {
	ece453_reg_write(CONTROL_X_REG, 0x19);
  } else {
//	printf("ERROR: Invalid Stepper X Direction Value\n");
	return 1;
  }

  return 0;
}

//*****************************************************************************
//  step_y
//  Control for Y-Axis Stepper Motor Unit
//
//  steps      stepper value (not spaces) for movement
//  direction  constant values from .h file for forward/backward movement
//  Return: 0 for success, 1 for failure
//*****************************************************************************
int step_y (int steps, int direction)
{
  char response[80];

  // Disable the Stepper Motor
  ece453_reg_write(CONTROL_Y_REG, 0x05);

  // If there are any outstanding interrupts, clear them.
  ece453_reg_write(IM_REG, 0x01);
  ece453_reg_write(IRQ_REG, 0x01);

  // Set up the speed at which the motor spins
  ece453_reg_write(STEP_PERIOD_Y_REG, 0x3D090);

  // Set the step count reg to the value in steps
  ece453_reg_write(STEP_COUNT_Y_REG, steps);
  //printf("DEBUG: Y = %d\n", steps);

  complete_Y = false;

  // Configure the control register so that the stepper motor stops once the step count reaches
  // 0

  if (direction == STEPPER_NORTH) {
  	ece453_reg_write(CONTROL_Y_REG, 0x19);
  } else if (direction == STEPPER_SOUTH) {
	ece453_reg_write(CONTROL_Y_REG, 0x1B);
  } else {
	//printf("ERROR: Invalid Stepper Y Direction Value\n");
	return 1;
  }

  return 0;
}
