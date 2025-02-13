bool flag = false;
int counter = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int analogValue = analogRead(A0);


  if (analogValue > 500) {
    flag = true;
  }


  if (!flag) {
    return;
  }


  if (flag) {
    receiveData(flag);
  }
}

void receiveData(bool &flag) { 
  delay(2000); 
  String data = "";

  while (flag) {
    delay(500);

  
    if (analogRead(A0) > 600) {
      data += "1";
    } else if (analogRead(A0) < 400) {
      data += "0";
    }

 
    if (data.length() > 0) {
      char lastChar = data.charAt(data.length() - 1);

      if (lastChar == '0') {
        counter++;
        if (counter > 12) {
          flag = false;
        }
      } else if (lastChar == '1') {
        counter = 0;
      }
    }

    delay(499);
    Serial.println(data);
  }


  String extractedData = extractMeaningfulData(data);

  Serial.println("Extracted Data is coming:");
  Serial.println(extractedData);
  Serial.println("Extracted Data received");
}

String extractMeaningfulData(String data) {

  String startPattern1 = "11110000000000";
  String startPattern2 = "110000000000"; 
  String endPattern = "0000000000";      

  int startPos = -1;


  if (data.indexOf(startPattern1) != -1) {
    startPos = data.indexOf(startPattern1) + startPattern1.length(); 
  }
 
  else if (data.indexOf(startPattern2) != -1) {
    startPos = data.indexOf(startPattern2) + startPattern2.length(); 
  }

 
  if (startPos != -1) {
    int endPos = data.indexOf(endPattern, startPos); 

    
    if (endPos != -1) {
      return data.substring(startPos, endPos);
    }
  }

  return ""; 
}
