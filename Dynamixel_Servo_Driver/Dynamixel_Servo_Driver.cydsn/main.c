/* ========================================
 * 2015 BYU Mars Rover
 * Dynamixel Wrist PWM to UART Driver
 * Written by Jake Johnson
 * 
 * Copyright BYU Mars Rover Team, 2015
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * Note: Channel_1, Channel 2 are 5V PWM inputs; tx is 5V servo output
 * Note: This only writes basic movement instructions to the Dynamixel
 *       It does not read the status messages sent by the servos.  
 *       To do that, a tri-state buffer will need to be implemented.
 * 
 *
 * 
 * ========================================
*/
#include <project.h>

// Functon declarations for basic Dynamixel instructions

void ServoGoalPosition( uint8 servoID, uint16 position);
void ServoSpeed( uint8 servoID, uint16 speed);
void ReadRequest(uint8 id, uint16 address, uint8 length);
void UartWriteLED( uint8 ledvalue);
void SetServoTorque( uint8 servoID, uint16 torque);

int main()
{

    // Initializations of the FPGA hardware logic blocks
    UART_1_Start();
    UART_2_Start();
    Timer_1_Start();
    Timer_2_Start();
    
    // Initialize the servo to speed of 100
    
    ServoSpeed(0xFE, 100);
    
    
     CyGlobalIntEnable; // Uncomment this line to enable global interrupts. */
    for(;;)
    {
        
        uint16 timer1 = Timer_1_ReadCapture(); // Read in the latest captured pulse width for channel 1
        if (timer1 >= 1000 && timer1 <= 2000){ // Low pass filter it
            CyDelay(4); // This delay is to wait for the hardware block to send out the data, and the servo to respond
            ServoGoalPosition(0x02, timer1);
            LED_Write(1);
            
        }
        else{
            LED_Write(0);
        }
        uint16 timer2 = Timer_2_ReadCapture();
        if (timer2 >= 1000 && timer2 <= 2000){
            timer2 = (timer2-1000)*3;
            CyDelay(4);
            ServoGoalPosition(0x01, timer2);
        }

        
// This is a piece of code that will reset the torque on the servo to it's maximum value
        
//        UartWriteLED(1);
//        SetServoTorque(0xFE, 0x03FF);       
//        LED_Write(1);
//        CyDelay(1000);
//        ServoGoalPosition(0x02, 1000);
//        LED_Write(0);
//        UartWriteLED(0);
//        CyDelay(1000);
            
        
        
        
        
        
    }
}
    
    void ServoGoalPosition( uint8 servoID, uint16 position){
    uint8 array[9];
    
    array[0] = 0xFF;
    array[1] = 0xFF;
    array[2] = servoID; //this is a broadcast ID.  Change for daisychained servos.
    array[3] = 0x05;
    array[4] = 0x03; //write instruction
    array[5] = 0x1E;
    array[6] = position;
    array[7] = position >> 8;
    array[8] = ~(servoID + 0x05 + 0x1E + array[6] + array[7] + 0x03);
    
    UART_1_PutArray(array, 0x09);
    
}
    
void SetServoTorque( uint8 servoID, uint16 torque){
    uint8 array[9];
    
    array[0] = 0xFF;
    array[1] = 0xFF;
    array[2] = servoID; 
    array[3] = 0x05;
    array[4] = 0x03; //write instruction
    array[5] = 0x0E;
    array[6] = torque;
    array[7] = torque >> 8;
    array[8] = ~(servoID + 0x05 + 0x0E + array[6] + array[7] + 0x03);
    
    UART_1_PutArray(array, 0x09);
    
}    

void ServoSpeed( uint8 servoID, uint16 speed){
    uint8 array[9];
    
    array[0] = 0xFF;
    array[1] = 0xFF;
    array[2] = servoID; //this is a broadcast ID.  Change for daisychained servos.
    array[3] = 0x05;
    array[4] = 0x03; //write instruction
    array[5] = 0x20;
    array[6] = speed;
    array[7] = speed >> 8;
    array[8] = ~(servoID + 0x05 + 0x20 + array[6] + array[7] + 0x03);
    
    UART_1_PutArray(array, 0x09);
    
}

void ReadRequest(uint8 id,uint16 address, uint8 length){ // note that this uses a broadcast ID - it will set the ID of all servos connected.  Make sure to only connect the servo you want to change.
    uint8 array[8];
    
    array[0] = 0xFE;
    array[1] = 0xFE;
    array[2] = id; //this is a broadcast ID.  Change for daisychained servos.
    array[3] = 0x04; //length = number of parameters + 2
    array[4] = 0x02; //write instruction
    array[5] = address;
    array[6] = length;
    array[7]= ~(id + 0x04 + address + length +0x02);
 
    
    UART_1_PutArray(array, 0x08);
    
}

void UartWriteLED( uint8 ledvalue){
    uint8 array[8];
    
    array[0] = 0xFE;
    array[1] = 0xFE;
    array[2] = 0x0FE; //this is a broadcast ID.  Change for daisychained servos.
    array[3] = 0x04;
    array[4] = 0x03; //write instruction
    array[5] = 0x19;
    array[6] = ledvalue;
    array[7] = ~(0x0FE + 0x04 + 0x19 + ledvalue + 0x03);
    
    UART_1_PutArray(array, 0x08);
    
}

/* [] END OF FILE */