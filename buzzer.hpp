#include <Arduino.h>


const int buzzerPin = 8;

void setupBuzzer(){
    pinMode(buzzerPin, OUTPUT);
}

void surprised(){
    tone(buzzerPin, 1200, 80); //tone has pin, frequency and duration as parameters
    delay(300);
    tone(buzzerPin, 1400, 80);
    noTone(buzzerPin); //noTone = no tone (obvious, right?)
}

void happy(){
    for(int i = 0; i < 5; i++){
        tone(buzzerPin, 600, 60);
        delay(300);
    }
    

    noTone(buzzerPin);  
}

void sad(){
    tone(buzzerPin, 700, 100);
    for(int j = 0; j < 3; j++){
        for(int i = 695; i > 600; i -= 5){
            tone(buzzerPin, i, 20);
            delay(20);
        } 
    }
    noTone(buzzerPin);
}

void angry(){
    for (int i = 0; i < 10; i++) {
        tone(buzzerPin, 150); 
        delay(20);
        tone(buzzerPin, 170);
        delay(20);
    }
    noTone(buzzerPin);
}


