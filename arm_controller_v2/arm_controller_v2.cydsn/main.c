/* ========================================
 *created by Samuel Bury Jan. 31, 2015
 *last modified date: Jan. 31, 2015
*/
#include <project.h>
#include <time.h>
#include <stdlib.h>

//Initializations of global variables
//TODO should this be global or should we declare it in main and pass a
//////pointer to each function?
uint16 data_array[14]; //stores the parsed instructions from the wiznet
uint8 wiznet;
uint8 new_pack;

#define TEST_ARRAY_SIZE 10

int16 test_array[TEST_ARRAY_SIZE];

#define SERV_ARR_SIZE 20
uint8 serv_arr_cspot;
uint16 servo_array[SERV_ARR_SIZE];
uint8 serv_avg_count = 0;

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

void servo();
void led();
void fill_data_array1();

//--------------------------------------------------- END Function Stubs


//to be used for parsing reading/parsing the data from the wiznet
void fill_data_array() //maybe take param: uint8* array
{
    
    //read one byte at a time
    uint8 c = 0; //UART_1_UartGetChar();
    

    if(c == 'q'){
        data_array[1] = 2000;
    }
    else if(c == 'w'){
        data_array[1] = 1750;
    }
    else if(c == 'e'){
        data_array[1] = 1500;
    }
    else if(c == 'r'){
        data_array[1] = 1250;
    }
    else if(c == 't'){
        data_array[1] = 1000;
    }    
    else if(c == '1'){
        data_array[2] = 1000;
    }
    else if(c == '2'){
        data_array[2] = 5000;
    }
    else if(c == '3'){
        data_array[2] = 10000;
    }
    else if(c == '4'){
        data_array[2] = 15000;
    }
    else if(c == '5'){
        data_array[2] =19000;
    }    
    else if(c == 'j'){
        data_array[3] = 1000;
    }
    else if(c == 'k'){
        data_array[3] = 1500;
    }
    else if(c == 'l'){
        data_array[3] =2000;
    }    

}

void fill_data_array1()
{
    uint8 i = 0;
    for(i = 0; i < TEST_ARRAY_SIZE; i++)
    {
        data_array[i] = test_array[i];
    }
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

enum led_states {l_start,l_different,l_wait} led_state;
void led()
{
    uint16 old = 0;
    switch(led_state)
    {
        case l_start:
            break;
        
        case l_different:
            PWM_1_WriteCompare1(data_array[1]);
            old = data_array[1];
            break;
            
        case l_wait:
            break;
    }
    
    switch(led_state)
    {
        case l_start:
            led_state = l_wait;
            break;
        
        case l_different:
            if(data_array[1] != old)
            {
                led_state = l_different;
            }
            else
            {
                led_state = l_wait;
            }
            break;
            
        case l_wait:
            if(data_array[1] != old)
            {
                led_state = l_different;
            }
            else
            {
                led_state = l_wait;
            }
            break;
    }
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

enum servo_states {s_start,s_different,s_wait} servo_state;
void servo()
{
    uint16 old = 0;
    switch(servo_state){
        case s_start:
            break;
        
        case s_different:
            PWM_1_WriteCompare2(data_array[2]);
            old = data_array[2];
            break;
            
        case s_wait:
            break;
    }
    
    switch(servo_state){
        case s_start:
            servo_state = s_wait;
            break;
        
        case s_different:
            if(data_array[2] != old)
            {
                servo_state = s_different;
            }
            else
            {
                servo_state = s_wait;
            }
            break;
            
        case s_wait:
            if(data_array[2] != old)
            {
                servo_state = s_different;
            }
            else
            {
                servo_state = s_wait;
            }
            break;
    }    
}

//New servo design
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
enum servo1_states {s1_start,s1_init,s1_execute,s1_wait} servo1_state;
void servo1()
{ 
    uint8 i;
    uint16 avg;
    uint16 command;
    
    switch(servo1_state){ //actions
        case s_start:
            break;

        case s1_init:
            for(i = 0; i < SERV_ARR_SIZE; i++)
            {
                servo_array[i] = 1500;
            }
            serv_arr_cspot = 0;
            break;

        case s1_execute:
            command = (((data_array[2] << 8) | data_array[3])/2) + 1500;
            servo_array[serv_arr_cspot] = command;
            if(serv_arr_cspot < (SERV_ARR_SIZE - 1))
            {
                serv_arr_cspot++;
            }
            else
            {
                serv_arr_cspot = 0;
            }
            avg = average(servo_array, 20);
            //servo_array[serv_avg_count] = data_array[2];
            PWM_1_WriteCompare2(avg);
            new_pack = 0;
            break;
            
        case s1_wait:
            break;
    }
    
    switch(servo1_state){ //transitions
        case s1_start:
            servo1_state = s1_init;
            break;
        
        case s1_init:
            servo1_state = s1_wait;
            break;
        
        case s1_execute:
            if(new_pack)
            {
                servo1_state = s1_execute;
            }
            else
            {
                servo1_state = s1_wait;
            }
            break;
        
        case s1_wait:
            if(new_pack)
            {
                servo1_state = s1_execute;
            }
            else
            {
                servo1_state = s1_wait; 
            }
            break;
    }    
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

//enum motor_states {m_start,m_different,m_wait} motor_state;
//void motor(){
//    uint16 old = 0;
//    switch(motor_state){ //state actions
//        case m_start:
//            break;
//        
//        case m_different:
//            PWM_2_WriteCompare1(data_array[1]);
//            old = data_array[3];
//            break;
//            
//        case m_wait:
//            break;
//    }
//    
//    switch(motor_state){ //state transitions
//        case m_start:
//            motor_state = m_wait;
//            break;
//        
//        case m_different:
//            if(data_array[3] != old)
//            {
//                motor_state = m_different;
//            }
//            else
//            {
//                motor_state = m_wait;
//            }
//            break;
//            
//        case m_wait:
//            if(data_array[3] != old)
//            {
//                motor_state = m_different;
//            }
//            else
//            {
//                motor_state = m_wait;
//            }
//            break;
//    }
//}

int main()
{
    CyGlobalIntEnable;
    
    time_t t;
    uint8 counter;
    //start all of our components
    Clock_pwm_Start();
    Clock_counter_Start();
    
    PWM_1_Start();
    //PWM_2_Start();
    
    Timer_1_Start();
    //UART_1_Start();
    
    isr_1_StartEx(timer_isr);
    
    srand((unsigned) time(&t));
    int counter_five = 0;
    for(;;)
    {
        //check addresses
        //TODO get the address bytes from Steve
        
        if(1) //WIZ_INT_Read()
        {
            fill_data_array1(); //potentially take input &data_array
            new_pack = 1;
        }
        
//        baseAzimuth();
//        shoulder();
//        elbow();
//        wristTilt();
//        wristRotate();

        led();
        servo1();
//        servo();
        
        
        while(!timerFlag) //this while loop will periodize our code to the time of longest path
        {
//            //Potential solution to how we will want to send feedback
//            feedback_count++;
//            if(feedback_count == feedback_interval) //sends feeback to base station every 50th
//            {                                        //time through the full set of instructions
//                send_feedback();
//            }
        }
        counter++;
        if(counter == 100)
        {
            for(int i = 0; i < 10; (i+2))
            {
                int16 random_number = rand()%2001 - 1000;
                test_array[i] = random_number >> 8;
                test_array[i+1] = random_number & 0x00FF;
            }
            counter = 0;
        }
        timerFlag = 0;
    }
}

/* [] END OF FILE */
