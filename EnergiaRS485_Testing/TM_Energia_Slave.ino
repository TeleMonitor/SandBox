//TelemonitorSlaveSkl.ino

//Code for Slave Stations
String Str;
const String ThisDEV = "D"; // Put the Unique Device name or ID here
const int RSm = P2_6 ; // RS-485 mode select pin (HI TX, LOW RX)

void setup() {
  
  Serial.begin(9600);
  pinMode(RSm, OUTPUT);
  pinMode(P1_0, OUTPUT);
  digitalWrite(RSm, LOW);
  digitalWrite(P1_0, HIGH);
}

/*-------------------------------------------Sensors Function-----------------------------------*/

String Sensor1()
{
  return String(analogRead(A3)); //Here analog is only for example
}

String Sensor2()
{
  return String(analogRead(A2));
}
/*------------------------------------------Read Self ---------------------------------------*/
String Self(String full_dev_arg)
{
  String dev_arg = full_dev_arg.substring(0,full_dev_arg.indexOf(" "));
  if(dev_arg.equalsIgnoreCase("Sensor1"))
  {
    return Sensor1();
  }else if(dev_arg.equalsIgnoreCase("Sensor2"))
  {
    return Sensor2();
  }else if(dev_arg.equalsIgnoreCase("LED1_on"))
  {
    digitalWrite(P1_0, HIGH);
    return String("ON");
  }else if(dev_arg.equalsIgnoreCase("LED2_off"))
  {
    digitalWrite(P1_0, LOW);
    return String("OFF");
  }else
  return ("This is : " + ThisDEV);
}

/*----------------------------------------Action-----------------------------------------------*/

void Action(){
   String tdev = Str.substring(0,Str.indexOf(" "));

        if (tdev.equalsIgnoreCase(ThisDEV)) 
        {          
          digitalWrite(RSm, HIGH);
          Serial.println(Self(Str.substring(tdev.length()+1 , Str.length())));
          Serial.flush();
          delay(1);
          digitalWrite(RSm, LOW);
        } 
}

void loop() 
{
   if(Serial.available() > 0)
   {
   Str = Serial.readString();
   Action();
   }
}

