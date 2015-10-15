/* ========================================
 *created by Samuel Bury Jan. 31, 2015
 *last modified date: Jan. 31, 2015
*/
#include <project.h>

//Initializations of global variables
//TODO should this be global or should we declare it in main and pass a
//////pointer to each function?
uint8 data_array[14]; //stores the parsed instructions from the wiznet
uint16 feedback_count;
uint8 timerFlag;

//this ISR will be used to set our timeFlag according to our timer component
///set to the time of the longest path for our code
//TODO test how long it takes code to run before really implementing this
/*
CY_ISR(timer_isr)
{
    uint32 isr_var = Timer_1_GetInterruptSourceMasked();
    
    timerFlag = 1;
    
    Timer_1_ClearInterrupt(isr_var);
}
*/

//Funtion declarations/definitions
//TODO do we need to make a header for good practice?

//---------------------------------------------------
//    Function stubs for the header
//---------------------------------------------------
void fill_data_array();
void baseAzimuth();
void shoulder();
void elbow();
void wristTilt();
void wristRotate();
void send_feedback();
//--------------------------------------------------- END Function Stubs


//to be used for parsing reading/parsing the data from the wiznet
void fill_data_array() //maybe take param: uint8* array
{
    //read one byte at a time
}

//control the turret
void baseAzimuth()
{
    //take instruction from data_array
    //smooth input
    //actuate the turret using PWM
    
    
}

enum shldr_states {shldr_start, shldr_init, shldr_fdbk, shldr_exe} shldr_state;
//control the shoulder
void shoulder()
{
    //take instruction from data_array
    //smooth input
    //actuate the shoulder using PWM
    //get feedback
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
    switch(shldr_state)
    {//switch staatement for state transitions
		case shldr_start: //start
			//next state will be init
            shldr_state = shldr_init;
            break;
        
		case shldr_init: //initialize
			//next state will be feedback
            shldr_state = shldr_fdbk;
            break;
        
		case shldr_fdbk://feedback
			//if position ok relative to average
				//execute
			//else if not ok
				//report problem
            break;
		case shldr_exe://execute
			//next state will be report
            shldr_state = shldr_fdbk;
            break;
    }
			
	//switch statement for state actions
		//start
			//break
		//initialize
			//create smoothing array
		//feedback
			//read feedback
		//execute
			//add the shifted value from main to back of smoothing array
			//calculate average of value in array
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
}

//control the elbow
void elbow()
{
    //take instruction from data_array
    //smooth input
    //actuate the elbow using PWM
    //get feedback
}

enum wristTilt_states {tilt_init = 0, tilt_start, tilt_control, tilt_feedback} wristTilt_state;
//control the tilting motion of the wrist
void wristTilt()
{
    // Overview
    //take instruction from data_array
    //smooth input
    //actuate the tilting using UART
    //get feedback

    //-------------------------- 
    // Dynamixel Servo specific
    // TODO: Set the torque - Requires building an array with bit representation
    // TODO: Set the desired position

    //--------------------------
    // State machine
        // Transistion
    switch(wristTilt_state)
    {
        case tilt_init:
            wristTilt_state = tilt_start;
            break;
        case tilt_start:
            wristTilt_state = tilt_control;
            break;
        case tilt_control:
            break;
        case tilt_feedback:
            break;
    }
        // Action
    switch(wristTilt_state)
    {
        case tilt_init:
            wristTilt_state = tilt_start;
            break;
        case tilt_start:
            // Set the torque - this is a one time thing
            // Set the speed - I think this is a one time thing
            break;
        case tilt_control:
            break;
        case tilt_feedback:
            break;
    }
}

enum wristRotate_states {rotate_init = 0, rotate_start, rotate_control, rotate_feedback} wristRotate_state;
//control the rotating motion of the wrist
void wristRotate()
{
    // Overview
    //take instruction from data_array
    //smooth input
    //actuate the tilting using UART
    //get feedback

    //-------------------------- 
    // Dynamixel Servo specific
    // TODO: Set the torque - Requires building an array with bit representation
    // TOD: Set the desired position

    //--------------------------
    // State machine
        // Transistion
    switch(wristRotate_state)
    {
        case rotate_init:
            wristRotate_state = rotate_start;
            break;
        case rotate_start:
            wristRotate_state = rotate_control;
            break;
        case rotate_control:
            break;
        case rotate_feedback:
            break;
    }
        // Action
    switch(wristRotate_state)
    {
        case rotate_init:
            wristRotate_state = rotate_start;
            break;
        case rotate_start:
            // Set the torque - this is a one time thing
            // Set the speed - I think this is a one time thing
            break;
        case rotate_control:
            break;
        case rotate_feedback:
            break;
    }
}

void send_feedback()
{
    //compile all of the most recent feedback variables into a packet
    //necessary feedback variables: system state, dynamixel read write errors, PID errors
    //TODO define system state
    //send packet via serial to wiznet
}

int main()
{
    //CyGlobalIntEnable;
    
    //start all of our components
    
    //ISR_StartEx(timer_isr);
    
    for(;;)
    {
        //check addresses
        //TODO get the address bytes from Steve
        
        fill_data_array(); //potentially take input &data_array
        baseAzimuth();
        shoulder();
        elbow();
        wristTilt();
        wristRotate();
        
        /*
        while(!timerFlag) //this while loop will periodize our code to the time of longest path
        {
            //Potential solution to how we will want to send feedback
            feedback_count++;
            if(feedback_count == feedback_interval) //sends feeback to base station every 50th
            {                                        //time through the full set of instructions
                send_feedback();
            }
        }
        timerFlag = 0;
        */
    }
}

/* [] END OF FILE */
