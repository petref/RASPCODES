

// ======================================================= readcounter =========================================================================================
unsigned long readCount(int DTX, int SCKX)
{
  unsigned long Count;
  unsigned char i;
  pinMode(DTX, OUTPUT);
  digitalWrite(DTX,HIGH);
  digitalWrite(SCKX,LOW);
  Count=0;
  pinMode(DTX, INPUT);
  while(digitalRead(DTX));
  for (i=0;i<24;i++)
  {
    digitalWrite(SCKX,HIGH);
    Count=Count<<1;
    digitalWrite(SCKX,LOW);
    if(digitalRead(DTX)) 
    Count++;
  }
  digitalWrite(SCKX,HIGH);
  Count=Count^0x800000;
  digitalWrite(SCKX,LOW);
  return(Count);
}

//============================ end of counter =======================================



//================================= Calibration function ============================================================================================================================
void calibrate(int memcount, int memval, int memsample, int DTX, int SCKX, float valx, long samplex, long countx)
{

  valx = 0;
  samplex = 0;
  countx = 0;

  Serial.print(memcount);
  Serial.print(memval);
  Serial.print(memsample);
  
  lcd.clear();
  lcd.print("Calibrating...");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  for(int i=0;i<100;i++)
  {
    countx=readCount(DTX,SCKX);
    samplex+=countx;   
  }
  samplex/=100;
  lcd.clear();
  lcd.print("Put 100g & wait");
  countx=0;
  delay(3000);
  while(countx > 1000)
  {
    countx=readCount(DTX,SCKX);
    countx=samplex-countx;
    //Serial.println(count);
  }
  lcd.clear();
  lcd.print("Please Wait....");
  delay(2000);
  for(int i=0;i<100;i++)
  {
    countx=readCount(DTX,SCKX);
    valx+=samplex-countx;
    //Serial.println(sample-count);
  }
  valx=valx/100.0;
  valx=valx/100.0;        // put here your calibrating weight
  lcd.clear();
  
  lcd.print(countx);
  delay(200);
  lcd.print(" ");
  delay(200);
  lcd.print(samplex);
  lcd.print(" ");
  delay(200);
  lcd.print(valx);

   EEPROM_writeAnything(memval, valx);
   EEPROM_writeAnything(memsample, samplex);
   EEPROM_writeAnything(memcount,countx);
  
 


}
// End of calibration function ++++++++++++++++++++===========================================================================================
