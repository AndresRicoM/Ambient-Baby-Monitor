/*

███████╗██╗██╗  ██╗████████╗██╗  ██╗    ███████╗███████╗███╗   ██╗███████╗███████╗
██╔════╝██║╚██╗██╔╝╚══██╔══╝██║  ██║    ██╔════╝██╔════╝████╗  ██║██╔════╝██╔════╝
███████╗██║ ╚███╔╝    ██║   ███████║    ███████╗█████╗  ██╔██╗ ██║███████╗█████╗  
╚════██║██║ ██╔██╗    ██║   ██╔══██║    ╚════██║██╔══╝  ██║╚██╗██║╚════██║██╔══╝  
███████║██║██╔╝ ██╗   ██║   ██║  ██║    ███████║███████╗██║ ╚████║███████║███████╗
╚══════╝╚═╝╚═╝  ╚═╝   ╚═╝   ╚═╝  ╚═╝    ╚══════╝╚══════╝╚═╝  ╚═══╝╚══════╝╚══════╝

Sixth Sense - Mark I

Sixth Sense is an Ambient Baby Monitor that looks for changes in sound intensity using a microphone to 
detect the sound of a baby crying and then changes color to indicate to the babies parents that their 
baby is cryting.

The device seeks to give voice to babies through color, exploring new possibilities of non verbal communication
enhanced by light. 

Future versions will detach the microphone from the light source so that you can turn any lamp, or room into
a communication channel with the baby's room.

This program runs on an arduino Nano receiving signals from a standard Arduino Microphone 

You may find more information on how to build the first version of this concept on:
https://github.com/AndresRicoM/Sixth-Sense

Feel free to expand the idea and to integrate it into more sophisticated lighting systems! 

Andres Rico - 2016
andresrico.xyz

 */


int inPin = A3; //Analog Pin for reading values from microphone. 
int value; //For storing current sensor value. 
int last; //For storing last sensor value. 
int delta; //Detects changes in sensor values. 
int desicion; //Variable for deciding if baby is crying or not. 

int GreenPin = 5; //Control pins for RGB LED
int BluePin = 3;
int RedPin = 7;

int icounter; 
float sum = 0;


void setup() {
  
  Serial.begin(9600); //Setup pins and variables in appropiate modes. 
  pinMode(inPin, INPUT);
  pinMode(GreenPin, OUTPUT);
  pinMode(BluePin, OUTPUT);
  pinMode(RedPin, OUTPUT);
  last = value;
  desicion = 0;

}


void loop()
{
     
  for (icounter = 0; icounter < 100; icounter++) { //Take 100 samples from microphone. 
    value = analogRead(inPin); //Read sensor value. 
    Serial.println(value);
    delay(5);
    delta = abs(value - last); //Get delta from current and last value. 
    Serial.print(delta);
    //Serial.print('\n');
    if (delta > 5)  //If delta is larger than 
    {
      desicion = desicion + 1; //Times that delta has been larger than 5. 
    }
      last = value;
  }

    if (desicion > 10) //If there have been many drastic changes in microphone values, the baby is crying. 
      {
        //Serial.print("Baby is Crying");
       // Serial.print('\n');
        analogWrite (RedPin, 255); //Turn light Pink
        analogWrite (GreenPin, 0);
        analogWrite (BluePin, 40);
        delay(5500);
        desicion = 0;
        last = value;
        
      }
      else
      {
        //Serial.print("Baby is Sleeping");
        //Serial.print('\n');
        analogWrite (RedPin, 0); //Turn light blue
        analogWrite (GreenPin, 230);
        analogWrite (BluePin, 255);
        desicion = 0;
        last = value;
      }
}


