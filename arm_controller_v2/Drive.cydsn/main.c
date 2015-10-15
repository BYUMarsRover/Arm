#include <project.h>

#define DR_ARR_SIZE 20
#define DL_ARR_SIZE 20
#define DATA_ARRAY_SIZE 22

volatile uint8 timerFlag;

uint16 data_array[DATA_ARRAY_SIZE];

uint8 DR_FLAG;
uint8 DL_FLAG;

CY_ISR(timer_isr)
{
    uint32 isr_var = Timer_1_GetInterruptSourceMasked();
    timerFlag = 1;
    Timer_1_ClearInterrupt(isr_var);
}

//Average function to be used in smoothing our input
uint16 average(uint16* av_array, uint8 num_items)
{
    uint8 i;
    uint32 sum = 0;
    uint16 avg = 0;
    
    for(i = 0; i < num_items; i++)
    {
        sum += av_array[i];
    }
    
    avg = sum/num_items;
    
    return avg;
}

uint16 make_command(int8* info_array, uint8 byte1, uint8 byte2)
{
    uint16 command;
    int16 temp1;
    int16 temp2;
    int16 temp3;
    
    temp1 = (info_array[byte1] << 8) & 0xFF00;
    temp2 = 0x00FF & (info_array[byte2]);
    temp3 = temp1 | temp2;
    command = (temp3/2) + 1500;
    return command;
}

void fill_data_array()
{
    wiznetReadUdpFrame(data_array, DATA_ARRAY_SIZE);
//    uint8 i = 0;
//    for(i = 0; i < TEST_ARRAY_SIZE; i++)
//    {
//        data_array[i] = test_array[i];
//    }
}

int main()
{
    uint8 fs_count = 0;
    
    uint8 DR_cspot;
    uint16 DR_array[DR_ARR_SIZE];

    CyGlobalIntEnable; 
    for(;;)
    {
         if(WIZ_INT_Read()==0) //!WIZ_INT_Read()--put wiznet in as condition if use ISR
        {
            wiznetClearInterrupts();
            fill_data_array();
            DR_FLAG = 1;
            DL_FLAG = 1;
       
            fs_count = 0;
            //wiznet = 0; //for testing
        }
        else
        {
            fs_count += 1;
        }
        
        if(fs_count >= 50)
        {
            uint16 temp_val = 1500;
            for(int i = 0; i < DATA_ARRAY_SIZE; (i+=2))
            {
                data_array[i] = temp_val >> 8;
                data_array[i+1] = temp_val & 0x00FF;
            }
        }
        else
        {
            //BA_cspot = baseAzimuth(BA_cspot, BA_array);
            drive_left();
            drive_right();
        }

        while(!timerFlag){} //this while loop will periodize our code to the time of longest path
        timerFlag = 0;
    }
}

/* [] END OF FILE */
