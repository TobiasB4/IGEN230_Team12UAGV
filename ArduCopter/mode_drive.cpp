#include "Copter.h"

float ModeDrive::SteeringOut = 0.0f;
float ModeDrive::ThrottleOut = 0.0f;

bool ModeDrive::init(bool ignore_checks)
{
    if (copter.ap.land_complete) //check if landed
    {
        motors->disable_enable(false); //turn off propellor motors, turn on drive motors
        return true;
    }
    else
    {
        gcs().send_text(MAV_SEVERITY_CRITICAL, "Must be landed to switch to Rover");
        return false; //refuse to switch to rover if not landed
    }
    motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::THROTTLE_UNLIMITED);
}

void ModeDrive::run()
{
    if (!motors->armed())
    {
        //if it is NOT armed
        // Motors should be Stopped
        SteeringOut = 0;
        ThrottleOut = 0;
    }
    else
    {
        //if it IS armed
        ModeDrive::get_pilot_input();
        convert_input();
        //motors->testoutputfunction();
    }
}

//add this prototype to class def
void ModeDrive::get_pilot_input()
{
    //Honestly have no idea what this value is supposed to be so I am using a squashing function
    //900 and 2100
    if (channel_roll->get_control_in() > 30000.f)
    {
        SteeringOut = ~channel_roll->get_control_in();
    }
    SteeringOut = channel_roll->get_control_in();

    // some value between 0 and 1
    //pwm_from_range found in SRV_CHANNEL
    //becomes throttle actuator value
    //function(actuator, value)
    ThrottleOut = get_pilot_desired_throttle();
}

void ModeDrive::exit()
{
    motors->disable_enable(true);
    motors->set_desired_spool_state(AP_Motors::DesiredSpoolState::SHUT_DOWN);
}

void ModeDrive::convert_input()
{
    //force between -1 and 1
    SteeringOut /= 4500.f;

    SteeringOut = 1500.f + 500.f * SteeringOut;
    ThrottleOut = 0.f + 2000.f * ThrottleOut;
}
