/*
 # This sample code is used to test the pH meter V1.0.
 # Editor : YouYou
 # Ver    : 1.0
 # Product: analog pH meter
 # SKU    : SEN0161
*/
#define pH_Pin A0            //pH meter Analog output to Arduino Analog Input 0
#define sm_Pin A1
#define pH_Offset -0.25            //deviation compensate
#define LED 13
#define samplingInterval 20
#define printInterval 800
#define ArrayLength  40    //times of collection
double sm_Offset = 0.00;
int pHArray[ArrayLength];   //Store the average value of the sensor feedback
int smArray[ArrayLength];
int pHArrayIndex=0;
int smArrayIndex=0;
double temp_input = 0.00;
double sm_in_air = 1022.00;
double sm_in_water = 150.00;
void setup(void)
{
  pinMode(LED,OUTPUT);  
  temp_input = 950/((1/sm_in_water)-(1/sm_in_air));
  sm_Offset = -temp_input/sm_in_air;
  Serial.begin(9600);  
  Serial.println("pH and soil moisture meter experiment!");    //Test the serial monitor
}
void loop(void)
{
  static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  static float pHValue,pH_voltage;
  static float smValue,sm_voltage;
  if(millis()-samplingTime > samplingInterval)
  {
      pHArray[pHArrayIndex++]=analogRead(pH_Pin);
      smArray[smArrayIndex++]=analogRead(sm_Pin);
      if(pHArrayIndex==ArrayLength)pHArrayIndex=0;
      if(smArrayIndex==ArrayLength)smArrayIndex=0;
      pH_voltage = avergearray(pHArray, ArrayLength)*5.0/1024;
      sm_voltage = avergearray(smArray, ArrayLength);
      pHValue = 3.5*pH_voltage+pH_Offset;
      smValue = (temp_input/sm_voltage)+sm_Offset;
      //smValue = sm_voltage;  //For use to get initial water and air readings
      samplingTime=millis();
  }
  if(millis() - printTime > printInterval)   //Every 800 milliseconds, print a numerical, convert the state of the LED indicator
  {
	Serial.print("pH Voltage:");
        Serial.print(pH_voltage,2);
        Serial.print("    pH value: ");
	Serial.println(pHValue,2);
        digitalWrite(LED,digitalRead(LED)^1);
        
        Serial.print("soil Moisture Voltage:");
        Serial.print(sm_voltage,2);
        Serial.print("    Moisture Sensor Value:");
        Serial.println(smValue,2);  
        printTime=millis();
        
  }
}
double avergearray(int* arr, int number)
{
  int i;
  int max,min;
  double avg;
  long amount=0;
  if(number<=0)
  {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if(number<5)
  {   //less than 5, calculated directly statistics
    for(i=0;i<number;i++)
    {
      amount+=arr[i];
    }
    avg = amount/number;
    return avg;
  }
  else
  {
    if(arr[0]<arr[1])
    {
      min = arr[0];max=arr[1];
    }
    else
    {
      min=arr[1];max=arr[0];
    }
    for(i=2;i<number;i++)
    {
      if(arr[i]<min)
      {
        amount+=min;        //arr<min
        min=arr[i];
      }
      else 
      {
        if(arr[i]>max)
        {
          amount+=max;    //arr>max
          max=arr[i];
        }
        else
        {
          amount+=arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount/(number-2);
  }//if
  return avg;
}

