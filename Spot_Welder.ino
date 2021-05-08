// CODE BY MATTIAS FLOYD

int trigger = 4; // assigns pin for variable pwm
int button= 7; //Pin for button
int tm = 50; //inical preset value for time delay for contactor on time
#define inputCLK 5 //a pin for rotary incoder knob 
#define inputDT 6  //b pin for rotary encoder knob
#define noise 9 // sound pin
int counter = 0; 
int currentStateCLK;
int previousStateCLK; 
String encdir ="";

void setup()  // setup loop
{
  pinMode(trigger, OUTPUT); // declares pin 12 as output
  Serial.begin(9600); //Starts Serial
     // Set encoder pins as inputs  
   pinMode (inputCLK,INPUT);
   pinMode (inputDT,INPUT);
     // Assign to previousStateCLK variable
   previousStateCLK = digitalRead(inputCLK);
   tone(noise, 3000, 200);

}
void loop()
{
   String in = "";


  while (Serial.available()<=0) //Checks for no serial input
  {
   
       // Read the current state of inputCLK
   currentStateCLK = digitalRead(inputCLK);
    
   // If the previous and the current state of the inputCLK are different then a pulse has occured
   if (currentStateCLK != previousStateCLK){ 
       
     // If the inputDT state is different than the inputCLK state then 
     // the encoder is rotating counterclockwise
     if (digitalRead(inputDT) != currentStateCLK) { 
      if (counter >> 1) {
         counter --;
       tone(noise, 2000, 10);
      }
      else {
        tone(noise, 2500, 200);
      }
       encdir ="CCW";
       tm = counter;
     } else {
       // Encoder is rotating clockwise
       counter ++;
       tone(noise, 3000, 10);
       encdir ="CW";
      tm = counter;
     }
     Serial.print("Direction: ");
     Serial.print(encdir);
     Serial.print(" -- Value: ");
     Serial.println(counter);
   } 
   // Update previousStateCLK with the current state
   previousStateCLK = currentStateCLK; 
   
    if (digitalRead(button) >> 0) {
       Serial.println("   ");    //This Section Displays the values over serial
       Serial.print("Contact!");
      tone(noise, 2500, 100); // play tone for alert
      delay(350);  //time so it's not just instant
      digitalWrite(trigger, HIGH); // sets pin 12 HIGH for contactor
      delay(tm);
      digitalWrite(trigger, LOW); //sets pin 12 LOW for contactor
    
      while (!(digitalRead(button) <= 0)) { //wait until button is depressed
        delay (10);
  }
    }
  }

  
   if (Serial.available()>0) //Checks for serial Input
  {
  
    while (Serial.available()>0) //loop while serial is being inputed
    {
  in += char(Serial.read()); //puts the serial charecters into the String 
  delay(250);
  }
   int val = in.toInt(); //converts the input string into a integer
   tm = val;
  }

  

  Serial.println("   ");    //This Section Displays the values over serial
  Serial.print("Time: ");
  Serial.print(tm);
  Serial.print("ns");
  
  
 delay(5); //delay for smoothness 


 
}
