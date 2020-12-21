void setup() {

  Serial.begin(9600);

}

void loop() {

  Serial.write("1");
  delay(2000);
  Serial.write("0");
  delay(2000);

}
