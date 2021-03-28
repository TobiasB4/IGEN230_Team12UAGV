#include "Copter.h"

#define ThrottleOut 0
#define SteeringOut 1

bool ModeDrive::init(bool ignore_checks)
{
    //set_range() for SRV_CHANNEL to 1 for throttle calcs
    //disable all motors except for our servos steering and throttle
    return true;
}

void ModeDrive::run()
{
    //Ask Daniel to put in public
    //
    float driveModeOutputs[] = {0, 0};

    ModeDrive::get_pilot_input(driveMod)

        if (!motors->armed())
    {
        // Motors should be Stopped
        motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
    }
    // find the code under Rover/mode_steering.cpp
}

//add this prototype to class def
void ModeDrive::get_pilot_input(float driveModeOutputs[])
{

    if ("Something bad happens or no rc input")
    {
        //tell Daniel to add to the class and declare zero on mode drive init
        driveModeOutputs[ThrottleOut] = 0;
        driveModeOutputs[SteeringOut] = 0;
        return;
    }

    //Some PWM signal between 900 and 2100
    //set_output_norm() found in SRV_CHANNEL
    //force it to between 0 and 1
    driveModeOutputs[SteeringOut] = (900 - channel_roll->get_control_in()) / (2100 - 900);

    // some value between 0 and 1
    //pwm_from_range found in SRV_CHANNEL
    //becomes throttle actuator value
    //function(actuator, value)
    driveModeOutputs[ThrottleOut] = Mode::get_pilot_desired_throttle();
}