
#define DistanceEn_Pin 2
#define relay0 A0
 
int i = 0;
long unsigned distance = 0;
long unsigned currentMillis;
long unsigned previousMillis;
long unsigned previousMillis1;
uint8_t distanceValue[4] = {0,0,0,0};
int sensorBlockProtection = 0;
int counter = 0;

void setup() 
{
  pinMode(relay0, OUTPUT);
  digitalWrite(relay0, HIGH);
  Serial.begin(9600);
  pinMode(DistanceEn_Pin,OUTPUT);
  digitalWrite(DistanceEn_Pin,1);
  
  
}
 
void Distance()
{
  unsigned long currentMillis = millis();
  while( Serial.read() >= 0 );         //清空串口缓存
  digitalWrite(DistanceEn_Pin,0);      //超声波使能开
  while(Serial.available() <= 4)       //等待超声波窗口数据
  { 
  }
  distanceValue[0] = Serial.read();    //提取数据
  if( distanceValue[0] == 0xff )       //判断是否为超声波模块数据
  {
    for(i = 1;i <= 3;i ++)
    {
      distanceValue[i] = Serial.read();
    }
   }
 
  digitalWrite(DistanceEn_Pin,1);       //超声波使能关
 
  distance = distanceValue[1] * 256 + distanceValue[2];                   //数据处理，计算距离
  if((distanceValue[3] == distanceValue[1] + distanceValue[2] - 1))       //数据和校验，可去掉
  {
//    Serial.print("The distance is : ");
//    Serial.print(distance);
//    Serial.println(" mm");

    if ( distance > 30) {
        
       if ((sensorBlockProtection == 0)  && (distance < 380))  {
          digitalWrite(relay0, LOW);
          delay(300);
           counter++;       
       } else {
          digitalWrite(relay0, HIGH);
          previousMillis = currentMillis;
//          Serial.print(currentMillis);
//          Serial.print(previousMillis);
//          Serial.print(currentMillis-previousMillis);
//          Serial.println();
       }

       Serial.println(counter);

       if(counter == 100) {
        digitalWrite(relay0, HIGH);
        sensorBlockProtection = 1;
       } 
       if( distance >400){
        sensorBlockProtection = 0;
        counter = 0;
       }
  
    }
    
  }
}
 
void loop() 
{
  Distance();
}
