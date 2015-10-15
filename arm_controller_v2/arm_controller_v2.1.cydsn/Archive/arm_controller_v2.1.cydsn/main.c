/* ========================================
 *created by Samuel Bury Jan. 31, 2015
 *last modified date: Jan. 31, 2015
*/
#include <project.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

//Initializations of global variables
//TODO should this be global or should we declare it in main and pass a
//////pointer to each function?
#define DATA_ARRAY_SIZE 14
uint16 data_array[DATA_ARRAY_SIZE]; //stores the parsed instructions from the wiznet

uint8 wiznet; //bool indicating wiznet interupt high or low
uint8 new_pack; //bool indicating a new pack of instructions to carry out

#define NUM_OF_SM 2
uint8 fin_exec; //counts

#define TEST_ARRAY_SIZE 10
int16 test_array[TEST_ARRAY_SIZE];

#define ELBW_ARR_SIZE 20
uint8 elbw_arr_cspot;
uint16 elbow_array[ELBW_ARR_SIZE];

#define BA_ARR_SIZE 20
uint8 BA_arr_cspot;
uint16 baseAz_array[BA_ARR_SIZE];

uint16 feedback_count;
uint8 timerFlag; //used in the timer_isr

//this ISR will be used to set our timeFlag according to our timer component
///set to the time of the longest path for our code
//TODO test how long it takes code to run before really implementing this
CY_ISR(timer_isr)
{
    uint32 isr_var = Timer_1_GetInterruptSourceMasked();
    timerFlag = 1;
    Timer_1_ClearInterrupt(isr_var);
}


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
void fill_data_array()
{
    uint8 i = 0;
    for(i = 0; i < TEST_ARRAY_SIZE; i++)
    {
        data_array[i] = test_array[i];
    }
}

enum shldr_states {shldr_start, shldr_init, shldr_fdbk, shldr_exe} shldr_state;
//control the shoulder
void shoulder()
{
    //take instruction from data_array
    //smooth input
    //actuate the shoulder using PWM
    //get feedback
    
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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
    /*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
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
}

enum wristRotate_states {rotate_init = 0, rotate_start, rotate_control, rotate_feedback} wristRotate_state;
//control the rotating motion of the wrist
void wristRotate()
{
    //Overview
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
}

void send_feedback()
{
    //compile all of the most recent feedback variables into a packet
    //necessary feedback variables: system state, dynamixel read write errors, PID errors
    //TODO define system state
    //send packet via serial to wiznet
}


//Average function to be used in smoothing our input
uint16 average(uint16* array, uint8 num_items)
{
    uint8 i;
    uint32 sum = 0;
    uint16 avg = 0;
    
    for(i = 0; i < num_items; i++)
    {
        sum += array[i];
    }
    
    avg = sum/num_items;
    
    return avg;
}


//control the elbow
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum elbow_states {elbw_start,elbw_init,elbw_execute,elbw_wait} elbow_state;
void elbow()
{ 
    //take instruction from data_array
    //smooth input
    //actuate the elbow using PWM
    //get feedback
    uint8 i;
    uint16 avg;
    uint16 command;
    
    switch(elbow_state){ //actions
        case elbw_start:
            break;

        case elbw_init:
            for(i = 0; i < ELBW_ARR_SIZE; i++)
            {
                elbow_array[i] = 1500;
            }
            elbw_arr_cspot = 0;
            break;

        case elbw_execute:
            command = (((data_array[2] << 8) | data_array[3])/2) + 1500;
            elbow_array[elbw_arr_cspot] = command;
            if(elbw_arr_cspot < (ELBW_ARR_SIZE - 1))
            {
                elbw_arr_cspot++;
            }
            else
            {
                elbw_arr_cspot = 0;
            }
            avg = average(elbow_array, ELBW_ARR_SIZE);
            PWM_3_WriteCompare(avg);
            fin_exec++;
            break;
            
        case elbw_wait:
            break;
    }
    
    switch(elbow_state){ //transitions
        case elbw_start:
            elbow_state = elbw_init;
            break;
        
        case elbw_init:
            elbow_state = elbw_wait;
            break;
        
        case elbw_execute:
            if(new_pack)
            {
                elbow_state = elbw_execute;
            }
            else
            {
                elbow_state = elbw_wait;
            }
            break;
        
        case elbw_wait:
            if(new_pack)
            {
                elbow_state = elbw_execute;
            }
            else
            {
                elbow_state = elbw_wait; 
            }
            break;
    }    
}

//control the turret
enum baseAzimuth_states {BA_start,BA_init,BA_execute,BA_wait} baseAzimuth_state;
void baseAzimuth()
{ 
    //take instruction from data_array
    //smooth input
    //actuate the turret using PWM
    uint8 i;
    uint16 avg;
    uint16 command;
    
    switch(baseAzimuth_state){ //actions
        case BA_start:
            break;

        case BA_init:
            for(i = 0; i < BA_ARR_SIZE; i++)
            {
                baseAz_array[i] = 1500;
            }
            BA_arr_cspot = 0;
            break;

        case BA_execute:
            command = (((data_array[4] << 8) | data_array[5])/2) + 1500;
            baseAz_array[BA_arr_cspot] = command;
            if(BA_arr_cspot < (BA_ARR_SIZE - 1))
            {
                BA_arr_cspot++;
            }
            else
            {
                BA_arr_cspot = 0;
            }
            avg = average(baseAz_array, BA_ARR_SIZE);
            
            PWM_2_WriteCompare(avg);
            fin_exec++;
            break;
            
        case BA_wait:
            break;
    }
    
    switch(baseAzimuth_state){ //transitions
        case BA_start:
            baseAzimuth_state = BA_init;
            break;
        
        case BA_init:
            baseAzimuth_state = BA_wait;
            break;
        
        case BA_execute:
            if(new_pack)
            {
                baseAzimuth_state = BA_execute;
            }
            else
            {
                baseAzimuth_state = BA_wait;
            }
            break;
        
        case BA_wait:
            if(new_pack)
            {
                baseAzimuth_state = BA_execute;
            }
            else
            {
                baseAzimuth_state = BA_wait; 
            }
            break;
    }    
}

int main()
{  
    CyGlobalIntEnable;
    
    //Define variables
    time_t t;
    uint8 counter;
    
    //start all of our components
    Clock_pwm_Start();
    Clock_counter_Start();
    
    //PWM_1_Start();
    PWM_2_Start();
    
    PWM_2_WriteCompare(1500); //Initialize our motor drivers
    CyDelay(10000);
    
    PWM_3_Start();
    
    Timer_1_Start();
    
    isr_1_StartEx(timer_isr);
    
    //helpers for generating random arrays
    srand((unsigned) time(&t));
    
    for(;;)
    {
        //check addresses
        //TODO get the address bytes from Steve
        
        if(wiznet) //WIZ_INT_Read()
        {
            fill_data_array();
            new_pack = 1;
            fin_exec = 0;
        }
        
        baseAzimuth();
//        shoulder();
        elbow();
//        wristTilt();
//        wristRotate();

        if(fin_exec == NUM_OF_SM)
        {
            new_pack = 0;
        }
        
        while(!timerFlag){} //this while loop will periodize our code to the time of longest path
        timerFlag = 0;
        
        counter++;
        
        if(counter == 100)
        {
            for(int i = 0; i < 10; (i+=2))
            {
                int16 random_number = rand()%2001 - 1000;
                test_array[i] = random_number >> 8;
                test_array[i+1] = random_number & 0x00FF;
            }
            counter = 0;
            wiznet = 1;
        }
        
//            //Potential solution to how we will want to send feedback
//            feedback_count++;
//            if(feedback_count == feedback_interval) //sends feeback to base station every 50th
//            {                                        //time through the full set of instructions
//                send_feedback();
//            }
    }
}

/* [] END OF FILE */
