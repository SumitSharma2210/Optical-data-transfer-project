const int laserPin = D4;

void setup() {
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);  
  Serial.begin(9600);
}

void loop() {
  delay(5000); 
  digitalWrite(laserPin, HIGH);
  delay(2000); 
  digitalWrite(laserPin, LOW);

  sendData();
}

void sendData() {
  String guard = "0000000000"; 
  String start = "1111";     
  
 
  String message = "Hi";


  String binaryMessage = textToBinary(message);
  Serial.println(binaryMessage);


  String data = guard + start + guard + binaryMessage + start + guard;

 
  for (int i = 0; i < data.length(); i++) {
    if (data[i] == '1') {
      digitalWrite(laserPin, HIGH); 
    } else {
      digitalWrite(laserPin, LOW);   
    }
    delay(1000); 
  }
}


String textToBinary(String text) {
  String binaryString = "";
  
  for (int i = 0; i < text.length(); i++) {
    char character = text[i];
    String binaryChar = String(character, BIN); 

   
    while (binaryChar.length() < 8) {
      binaryChar = "0" + binaryChar;
    }

    binaryString += binaryChar; 
  }

  return binaryString;
}
