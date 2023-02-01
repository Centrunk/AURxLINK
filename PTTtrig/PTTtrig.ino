const int PTT1=2;//XPR
const int PTT2=7;//XTL
const int PTT3=10;//MTM
const int SNS1=3;//XPR
const int SNS2=6;//XTL
const int SNS3=11;//MTM

int SNS1S=0;
int SNS2S=0;
int SNS3S=0;
bool disable=false;
bool wocD=true;
int i =0;
void setup() {
  // put your setup code here, to run once:
  pinMode(SNS1, INPUT);
  pinMode(SNS2, INPUT);
  pinMode(SNS3, INPUT);
  pinMode(PTT1, OUTPUT);
  pinMode(PTT2, OUTPUT);
  pinMode(PTT3, OUTPUT);

  //digitalWrite(PTT1,LOW);
  //digitalWrite(PTT2,HIGH);
  //digitalWrite(PTT3,HIGH);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  SNS1S = digitalRead(SNS1);
  SNS2S = digitalRead(SNS2);
  SNS3S = digitalRead(SNS3);
  String teststr = Serial.readString();  //read until timeout
  teststr.trim();                        // remove any \r \n whitespace at the end of the String
  if (teststr == "stop") {
    disable = true;
    Serial.println("Disabled");
  }else if (teststr == "start") {
    disable = false;
    Serial.println("Enabled");
  }else if (teststr == "enablewoc") {
    wocD = false;
    Serial.println("WOC Enabled");
  }else if (teststr == "disableewoc") {
    wocD = true;
    Serial.println("WOC Disable");
  }
  if(SNS2S==LOW)
  {
    if(disable==false)
    {
      i=0;
      digitalWrite(PTT1,LOW);
      digitalWrite(PTT3,LOW);
      Serial.println("SNS2S: ACT");
    }else
    {
      digitalWrite(PTT1,HIGH);
      digitalWrite(PTT2,HIGH);
      //digitalWrite(PTT3,HIGH);
      Serial.println("SNS2S: ACT, BUT DISABLED");
    }

    delay(100);
  }
  else if(SNS1S==HIGH)
  {
    if(disable==false)
    {
      if(wocD==false)
      {
        i=0;
        digitalWrite(PTT2,LOW);
        digitalWrite(PTT3,LOW);
        Serial.println("SNS1S: ACT");
      }else
      {
        Serial.println("SNS1S: ACT, But Disabled");
      }
      
    }else
    {
      Serial.println("SNS1S: ACT, But Disabled");
      digitalWrite(PTT1,HIGH);
      digitalWrite(PTT2,HIGH);
      //digitalWrite(PTT3,HIGH);
    }
    
    delay(100);
  }
  else if(SNS3S==LOW)
  {
    if(disable==false)
    {
      i=0;
      digitalWrite(PTT1,LOW);
      digitalWrite(PTT2,LOW);
      Serial.println("SNS3S: ACT");
    }
    else
    {
      Serial.println("SNS3S: ACT, But Disabled");
      digitalWrite(PTT1,HIGH);
      digitalWrite(PTT2,HIGH);
      //digitalWrite(PTT3,HIGH);
   }
    
    delay(100);
  }
  else
  {
    if(i==253)
    {
      i=0;
    }
    i++;
    digitalWrite(PTT1,HIGH);
    digitalWrite(PTT2,HIGH);
    digitalWrite(PTT3,HIGH);
    String myString = String(i);
    Serial.println("No TFK"+myString);
    delay(50);
  }

}
