// Define constants
#define menuButton 2
#define menuSelect 3
#define menuSave 4
#define debounceTimeout 50

int menuButtonPreviousState = LOW;
int menuSelectPreviousState = LOW;
int menuSavePreviousState = LOW;

// Define variables
long int lastDebounceTime;
bool lightSensor = true;
bool tempSensor = true;

// Menu options
char * menuOptions[] = {"Check Temp", "Check Light"};
bool featureSetting[] = {false,false};
bool menuMode = false;
bool menuNeedsPrint = false;
int optionSelected = 0;

// Setup function
void setup() {  
  pinMode(menuSelect, INPUT);
  pinMode(menuSave, INPUT);
  pinMode(menuSelect, INPUT);
  Serial.begin(9600);
}
// Function to return the current selected option
char *ReturnOptionSelected(){
  char *menuOption = menuOptions[optionSelected];
  // Return optionSelected
  return menuOption;
}

// Function to return status of current selected option
char *ReturnOptionStatus(){
  bool optionSetting = featureSetting[optionSelected];
  char *optionSettingVal;
  if (optionSetting == false){
    optionSettingVal = "False";
  }else{
    optionSettingVal = "True";
  }
  // Return optionSetting
  return optionSettingVal;
}

// Function to toggle current option
bool ToggleOptionSelected(){
  featureSetting[optionSelected] = !featureSetting[optionSelected];
  return true;
}

// The main loop
void loop()  {
    // Read the buttons
  int menuButtonPressed = digitalRead(menuButton);
    int menuSelectPressed = digitalRead(menuSelect);
    int menuSavePressed = digitalRead(menuSave);
  // Get the current time
  long int currentTime = millis();
  
  if(menuButtonPressed == LOW && menuSelectPressed == LOW && menuSavePressed == LOW){
    //Reset the count time while button is not pressed
    lastDebounceTime = currentTime;
    menuButtonPreviousState = LOW;
    menuSelectPreviousState = LOW;
    menuSavePreviousState = LOW;
  }
  if(((currentTime - lastDebounceTime) > debounceTimeout)){
    // If the timeout is reached, button pressed!</p><p>    // menuButton is pressed, provide logic
    // Only fires when the button has previously been released
    if((menuButtonPressed == HIGH) && (menuButtonPreviousState == LOW)){
  
      if(menuMode == false){
        menuMode = true;
        // Let the user know
        Serial.println("Menu is active");
      }else if (menuMode == true && optionSelected < 1){
        // Change option if menu is active
        optionSelected = optionSelected + 1;
      }else if (menuMode == true && optionSelected >= 1){
        // Reset option
        optionSelected = 0;
      }
  
      // Print the menu
      menuNeedsPrint = true;
      // Toggle the button prev. state to only display menu 
      // if the button is released and pressed again
      menuButtonPreviousState = menuButtonPressed; // Would be HIGH
    }
    // menuSelect is pressed, provide logic
    if((menuSelectPressed == HIGH) && (menuSelectPreviousState == LOW)){
      if(menuMode){
        // Change the selected option
        // At the moment, this is just true/false 
        // but could be anything
        bool toggle = ToggleOptionSelected();
            if(toggle){
        menuNeedsPrint = true;
        }else{
          Serial.print("Something went wrong. Please try again");
        }
      }
      // Toggle state to only toggle if released and pressed again
      menuSelectPreviousState = menuSelectPressed;
    }
    if((menuSavePressed == HIGH) && (menuSavePreviousState == LOW)){
      // Exit the menu
      // Here you could do any tidying up
      // or save to EEPROM
      menuMode = false;
      Serial.println("Menu exited");
  
      // Toggle state so menu only exits once
      menuSavePreviousState = menuSavePressed;
      }
    }
    // Print the current menu option active, but only print it once
    if(menuMode && menuNeedsPrint){
      // We have printed the menu, so unless something 
      // happens, no need to print it again
      menuNeedsPrint = false;
      char *optionActive = ReturnOptionSelected();
      char *optionStatus = ReturnOptionStatus();
      Serial.print("Selected: "); 
      Serial.print(optionActive);
      Serial.print(": ");
      Serial.print(optionStatus); 
      Serial.println();
    }
  }
