int temp1Pin = A0;                              //Initialize ADC Channel 0
int temp2Pin = A1;                              //Initialize ADC Channel 1

void setup() {
  Serial.begin(9600);                           //Open USB Serial Port at 9600 baud
}

float temp1 = 0;                                //Initializing variable. Temp1 stores the values recorded from ADC Channel 0
float temp2 = 0;                                //Initializing variable. Temp1 stores the values recorded from ADC Channel 1
unsigned long timer1 = millis();                //Initializing timer. Timer1 holds the current value of millis(). The command millis() returns the number of milliseconds passed since the Arduino was powered. It is reset on power cycle.
unsigned long timer2 = timer1;                  //Initializing timer. Timer2 holds the value of millis() when the last record was taken. Timer2 is only updated after the difference of timer1 and timer2 is greater than 1000 (which corresponds to approximately every second)  
float timeElapsed = timer1 - timer2;            //Initailizing holder variable. This variable holds the difference between Timer1 and Timer2.

void loop() {
  
    timer1 = millis();                         //Update Timer1 to hold the current time
    timeElapsed = timer1 - timer2;             //Update timeElapsed. Timer2 holds the time from the last record.
    delay(10);                                 //Delay to allow variable time to save in memory. Time between reads becomes erratic if removed.
    
    //Serial.println(timeElapsed);             //Debug line for checking if loop is executing
    
    if (timeElapsed > 1000) {                  //Check if 1000 milliseconds have passed.
      temp1 = analogRead(temp1Pin);            //Read the assigned ADC channel on temp1Pin. This is default set to Channel 0
      delay(5);
      temp2 = analogRead(temp2Pin);            //Read the assigned ADC channel on temp2Pin. This is default set to Channel 1

      //temp1 = 155 - temp1*0.1556;            //Calibration Equation. Remove // to convert ADC values to temperature in Celcius
      //temp2 = 155 - temp2*0.1556;            //Calibration Equation. Remove // to convert ADC values to temperature in Celcius
      
      Serial.print(temp1);                     //Send the value of temp1 to the serial port
      Serial.print(",");                       //Send the ASCI character "," to the serial
      Serial.println(temp2);                   //Send the value of temp2 to the serial port
      
      timer2 = timer1;                         //Update timer2 to the current value of timer1. This is important to ensure 
      timer1 = millis();                       //Update timer1 to current time
      timeElapsed = timer1 - timer2;           //Reset timeElapsed for triggering the loop.
      delay(10);
      }
}
