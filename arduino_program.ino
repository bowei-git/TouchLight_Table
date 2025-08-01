const int P_resistor = A0; //讀取光敏電阻腳位
int light; //光敏電阻數值

int brightness = 0; 
int fadeAmount = 5;

#define LEDR 11
#define LEDG 10
#define LEDB 9

void setup() 
{  
  pinMode(P_resistor, INPUT);
  Serial.begin(9600); 
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);
}

int r = 0;
int g = 0;
int b = 0;

#define ENVLight 408 //自訂義環境光源值

void loop()
{
  light=analogRead(P_resistor);
  Serial.println(light);

  if((ENVLight-light)>100&&light>200) //當物品放在桌子上會有呼吸燈
  {
    delay(1000); 
    light=analogRead(P_resistor); //持續一秒後即可確認並非意外遮擋
    if((ENVLight-light)>100&&light>200)
    {
      for( ;brightness>=0; brightness = brightness + fadeAmount)//呼吸燈效果
      {
        analogWrite(LEDR, 0);
        analogWrite(LEDG, brightness);
        analogWrite(LEDB, brightness);
        delay(30);          
        if (brightness >= 255)
        {                       
          fadeAmount = -fadeAmount;
          delay(1000);
        }
      }
      brightness = 0; 
      fadeAmount = 5;
      for(light=analogRead(P_resistor); ; light=analogRead(P_resistor)) //物品在桌子上後會不斷讀取數值直到物品離開桌面
      {
        if(light<200) //切換為夜間模式
          break;
        if(abs(ENVLight-light)<35)
        {
          for( ;brightness>=0; brightness = brightness + fadeAmount)
          {
            analogWrite(LEDR, 0);
            analogWrite(LEDG, brightness);
            analogWrite(LEDB, brightness);
            delay(30);
            if (brightness >= 255)
            {                       
              fadeAmount = -fadeAmount;
              delay(1000);
            }
          }
          brightness = 0; 
          fadeAmount = 5;
          break;
        }
      }
    }
  }
  else if(light<200)
  {
    for(;light<200;) //夜間燈光效果
    {
      r = random(0, 255);
      g = random(0, 255);
      b = random(0, 255);
      analogWrite(LEDR, r);
      analogWrite(LEDG, g);
      analogWrite(LEDB, b);
      delay(2000);
      analogWrite(LEDR, 0);
      analogWrite(LEDG, 0);
      analogWrite(LEDB, 0);
      delay(250);
      light=analogRead(P_resistor);
      delay(250);
    }
    analogWrite(LEDR, 0);
    analogWrite(LEDG, 0);
    analogWrite(LEDB, 0);
  }
}
