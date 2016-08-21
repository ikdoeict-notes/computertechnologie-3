word temperatuur[]={0x3B47,0x0C87,0x000F,0x0007,0xF387};
int weight[] = {128,64,32,16,8,4,2,1};
float flWeight[] = {0.5,0.25,0.125,0.0625};
int realValue = 0;
float flValue = 0.0;
void setup() 
{
  Serial.begin(9600);
  for(int x = 0;x<sizeof(temperatuur);x++)
  {
    for(int i = 0;i<sizeof(weight);i++)
    {
      realValue += weight[i] * bitRead(temperatuur[x],i+1);
    }
    Serial.println(x);
    Serial.print("Real Value : ");
    Serial.println(realValue);
    
    for(int i = 0;i<sizeof(flWeight);i++)
    {
      flValue += flWeight[i] * bitRead(temperatuur[x],i+10);
    }
    flValue += realValue;
    Serial.print("Float Value : ");
    Serial.println(flValue);
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
}
