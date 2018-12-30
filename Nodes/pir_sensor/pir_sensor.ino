void setup() {
  // put your setup code here, to run once:
  pinMode(0, INPUT);
  Serial.begin(115200);
  while(!Serial){}
  Serial.println("Started");
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1000);
  if(digitalRead(0))
  {
    Serial.println("detected");
  }
  else
  {
    Serial.println("NOT detected");
  }  
}
