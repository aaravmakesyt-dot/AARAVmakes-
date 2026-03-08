// ESP-32 Touch Reveal Code

// Sensor: GPIO 4 (Foil)

// LED: GPIO 2 (Internal Blue LED)


void setup() {

  Serial.begin(115200);

  pinMode(2, OUTPUT); // Internal LED

}


void loop() {

  // Read the secret touch pin

  int touchValue = touchRead(4); 

  

  // High value = No touch. Low value = Touching foil.

  if (touchValue < 30) { 

    digitalWrite(2, HIGH); // Turn LED ON

  } else {

    digitalWrite(2, LOW);  // Turn LED OFF

  }


 

  Serial.println(touchValue); 

  delay(10); 

}

 
