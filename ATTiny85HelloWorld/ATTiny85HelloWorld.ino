int led = 1; // led is on digital pin 0
int button = 0; //button is on digital pin 0
int state = 0; // state variable for the state machine
int time = 0; // varaible needed for the timer which is being used for the debouncer

int buttonState; //variable that stores the state of the button so either HIGH or LOW
int lastButtonState = LOW; // want the button to start of in a LOW state
int ledState = HIGH; 
//int counter = 0; 

unsigned long lastDebounceTime = 0; // variables that help the debouncer work 
unsigned long debounceDelay = 50; // delay for the debouncer

void setup() {
  time = 0; // making sure the timer starts at 0
  state = 1; // initial state is 1
  pinMode(led, OUTPUT); //setup the led as an output
  pinMode(button, INPUT); //setup the button as an input
  
}



void loop() {
  int stateLook = digitalRead(button); //variable that will convert the readings from the button into a certain state
  
  if (buttonState != lastButtonState){
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the stateLook is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (stateLook != buttonState) {
      buttonState = stateLook;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
      }
    }
  }
  digitalWrite(led, ledState);

  
  lastButtonState = stateLook;
  switch (state)
  {
    case 1:
     digitalWrite(led, LOW);
      if(buttonState == HIGH){
      state = 2;
    }
      break;
    case 2:
    digitalWrite(led,HIGH);
    if(buttonState == HIGH){
      state = 3;
    }
      break;
    case 3:
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
    if(buttonState == HIGH){
      state = 1;
    }
     break;
  }
}
 /* if(buttonState == HIGH){
    counter = counter+1;
  }
  if(counter == 3 && buttonState == HIGH){
    counter = -1; 
  }
  

  if(counter == 0 && buttonState == LOW){
   off();
  } 
  
  if(counter == 1 && buttonState == LOW){
    on();
  }
  
  if(counter == 2 && buttonState == LOW){
    ledblink();
  }
  */
  

//this function is the first/initial state in which the led is off
void off(){
  digitalWrite(led, LOW);
}
//this function is the second state in which the led stays on
void on(){
  digitalWrite(led,HIGH);
    
}
//this function is the third state where the led blinks every 100ms
void ledblink(){
  digitalWrite(led,!digitalRead(led));
  delay(100);
}
