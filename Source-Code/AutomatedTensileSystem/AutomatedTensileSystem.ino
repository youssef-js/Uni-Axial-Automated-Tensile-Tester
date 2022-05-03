
// Load cell
#include <HX711_ADC.h>
#include <EEPROM.h>

// LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Keypad
#include <Keypad.h>
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'t', '0', '#', 'D'}
};

// Keypad mappings
byte rowPins[ROWS] = {26, 27, 28, 29}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {22, 23, 24, 25}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

char inByte;

// SD Card
#include <SD.h>
#include <SPI.h>
File myFile;
int pinCS = 53;
int counter = 0;

// Time Functionality to calculate actuator distance
unsigned long Reference_Time = 0;
unsigned long Current_Time = 0;
unsigned long Time_Difference = 0;
double Retract_Distance = 0.0;

// HX711
const int HX711_DT = 7; //mcu > HX711 dout pin
const int HX711_SCK = 6; //mcu > HX711 sck pin
HX711_ADC LoadCell(HX711_DT, HX711_SCK);
unsigned long t = 0;

// Pin mappings of motor driver
const int Extend = 5; // Extend is in 1
const int Retract = 4; //

// FSM Flags & States
int calibrateFlag = 0;
int runFlag = 0;
int stopFlag = 0;
int endCalibrateFlag = 0;

enum userActions { START, MENU, CALIBRATE, RUN };
userActions state;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();

  // Load cell startup calibration
  LoadCell.begin();
  LoadCell.setReverseOutput(); //For strain
  float calibrationValue; // calibration value (see example file "Calibration.ino")
  calibrationValue = -88.16;

  // Load cell startup
  unsigned long stabilizingtime = 2000; // precision right after power-up can be improved by adding a few seconds of stabilizing time
  boolean _tare = true; //set this to false if you don't want tare to be performed in the next step
  LoadCell.start(stabilizingtime, _tare);
  if (LoadCell.getTareTimeoutFlag()) {
    Serial.println("Timeout, check MCU>HX711 wiring and pin designations");
    while (1);
  }
  else {
    LoadCell.setCalFactor(calibrationValue); // set calibration value (float)
    Serial.print('\t');
  }

  // Actuator pin setup & initialization
  pinMode(Extend, OUTPUT);
  pinMode(Retract, OUTPUT);
  digitalWrite(Extend, LOW);
  digitalWrite(Retract, LOW);

  keypad.addEventListener(keypadEvent); // Add an event listener for this keypad

  //SD Card Initialization
  pinMode(pinCS, OUTPUT);

  if (SD.begin())
  {
    Serial.println("SD card is ready to use.");
  } else
  {
    Serial.println("SD card initialization failed");
    return;
  }

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Actuator movements
void delayActuator() {
  digitalWrite(Retract, LOW);
  digitalWrite(Extend, LOW);
  delay(3000);
}

void stopActuator() {
  digitalWrite(Retract, LOW);
  digitalWrite(Extend, LOW);
}

void extendActuator() {
  digitalWrite(Retract, LOW);
  digitalWrite(Extend, HIGH);
  delay(42000);
}

void retractActuator() {
  digitalWrite(Retract, HIGH);
  digitalWrite(Extend, LOW);
}

// Prints base menu screen 
void printMenu() {
  lcd.clear();
  lcd.print("Auto Tensile Tester");
  lcd.setCursor(0, 1);
  lcd.print("------------------------");
  lcd.setCursor(0, 2);
  lcd.print("A)Calibrate");
  lcd.setCursor(0, 3);
  lcd.print("B)Run Test");
}

// Gets instantaneous data reading of load cell
double readLoadCell() {

  static boolean newDataReady = 0;
  float cell = 0;

  // Check for new data/start next conversion:
  if (LoadCell.update()) newDataReady = true;

  // get smoothed value from the dataset:
  if (newDataReady) {
    if (millis() > t) {
      cell = LoadCell.getData();
      newDataReady = 0;
      t = millis();
      delay(100);
    }
  }
  return cell;
}

// Gets keypad input
int obtainCalibrationDigit(int scale) {
  char digit = ' ';
  const int EMPTY_CHAR = 0;
  do {
    digit = keypad.getKey();
    delay(100);
    Serial.print(digit);

    int ascii = (int) digit;
    //lcd.print(ascii);
    Serial.println(ascii);
  } while (digit == EMPTY_CHAR);  //ASCII value 0 for empty character

  return (((digit - 48) * scale));
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void calibrate() {

  Serial.println("Start calibration:");
  Serial.println("Send 't' from serial monitor to set the tare offset.");

  retractActuator();
  lcd.clear();
  lcd.print("CALIBRATE STATE");
  lcd.setCursor(0, 1);
  lcd.print("--------------------");
  lcd.setCursor(0, 2);
  lcd.print("Wait 10 seconds for");
  lcd.setCursor(0, 3);
  lcd.print("retraction period.");
  delay(15000);
  stopActuator();

  lcd.clear();
  lcd.print("CALIBRATE STATE");
  lcd.setCursor(0, 1);
  lcd.print("--------------------");
  lcd.setCursor(0, 2);
  lcd.print("Press '*' to set");
  lcd.setCursor(0, 3);
  lcd.print("the tare offset.");

  boolean _resume = false;
  while (_resume == false) {

    LoadCell.update();
    Serial.println("Infinite Loop");

    inByte = keypad.getKey();
    int ascii = (int) inByte;
    Serial.println(inByte);
    if (inByte == 't') {
      LoadCell.tareNoDelay();
    }
    if (LoadCell.getTareStatus() == true) {
      _resume = true;
    }

    delay(100);
  }

  Serial.println("Place known mass on load cell");
  Serial.println("Enter known mass (g):");

  lcd.clear();
  lcd.print("Place known mass");
  lcd.setCursor(0, 2);
  lcd.print("Enter known mass (g)");
  lcd.setCursor(0, 3);
  lcd.print("Using four digits");

  float known_mass = 0;
  _resume = false;

  while (_resume == false) {

    Serial.println("Infinite Loop2");

    LoadCell.update();
    delay(100);

    int sum = obtainCalibrationDigit(1000);
    sum = sum + obtainCalibrationDigit(100);
    sum = sum + obtainCalibrationDigit(10);
    sum = sum + obtainCalibrationDigit(1);
    known_mass = sum;

    Serial.println("KNOWN_MASS: ");
    Serial.println(known_mass);

    if (known_mass != 0) {
      Serial.print("Known mass is: ");
      Serial.println(known_mass);
      _resume = true;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 2);
  lcd.print("User Input: ");
  lcd.print(known_mass);

  delay(1000);

  LoadCell.refreshDataSet(); //refresh the dataset to be sure that the known mass is measured correct
  float newCalibrationValue = (-1) * LoadCell.getNewCalibration(known_mass); //get the new calibration value
  LoadCell.setCalFactor(newCalibrationValue);

  lcd.clear();

  Serial.print("New calibration value has been set to: ");

  lcd.print("New calibration set to: ");
  lcd.setCursor(0, 2);
  lcd.print(newCalibrationValue);
  Serial.print("new calibration set to: ");
  Serial.println(newCalibrationValue);
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("End of calibration");

  lcd.setCursor(0, 2);
  lcd.print("Remove Mass!");
  delay(3000);

  digitalWrite(Retract, LOW);
  digitalWrite(Extend, HIGH);
  delay(15000);
  stopActuator();

  Serial.println(newCalibrationValue);
  Serial.println("End calibration");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {

  double loadcell = 0;

  if (runFlag == 1) {
    loadcell = readLoadCell();
    Current_Time = millis();
    Time_Difference = (Current_Time - Reference_Time);
    Retract_Distance = ( (double) Time_Difference) * (0.000659); //rate = 30cm/46,000 milliseconds

    Serial.print(loadcell);
    Serial.print('\t');
    Serial.print(Retract_Distance);
    Serial.print('\n');


    //SD Card
    // if the file opened okay, write to it:
    if (myFile) {
      myFile.print(loadcell);
      myFile.print('\t');
      myFile.print(Retract_Distance);
      myFile.print('\n');
    }
    // if the file didn't open, print an error:
    else {
      Serial.println("error opening test.txt");
      lcd.clear();
      lcd.setCursor(0, 1);
      lcd.print("Error opening file");
      lcd.setCursor(0, 2);
      lcd.print("for SD Card");
      lcd.setCursor(0, 3);
      lcd.print("Press 'c' to stop");

    }

    if (inByte == 's') {
      Serial.println("-----------STOP FLAG-----------");
      lcd.clear();
      lcd.print("STOP INITIATED");
      lcd.setCursor(0, 1);
      lcd.print("--------------------");
      lcd.setCursor(0, 2);
      lcd.print("Extending back to");
      lcd.setCursor(0, 3);
      lcd.print("starting position.");
      stopFlag = 1;
    }
  }

  else if (calibrateFlag == 1) {
    calibrate();
    endCalibrateFlag = 1;
  }


  FSM();

  //Poll KeyPad
  char key = keypad.getKey();
  Serial.print("key: ");
  Serial.println(key);
  //delay(100);

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FSM() {

  // Transitions
  switch (state) {
    case START:
      printMenu();
      state = MENU;
      break;

    case MENU:

      delay(100);


      if (inByte == 'r') {
        Serial.println("RUN STATE");

        lcd.clear();
        lcd.print("RUN STATE");
        lcd.setCursor(0, 1);
        lcd.print("--------------------");
        lcd.setCursor(0, 2);
        lcd.print("Press 'c' to stop");
        lcd.setCursor(0, 3);
        lcd.print("when break occurs.");
        lcd.setCursor(0, 4);

        delayActuator();
        retractActuator();
        
        // Create/Open file
     
        char filename[32] = "test";
        char cntStr[16];
        itoa(counter, cntStr, 10);
        counter++;
        strcat(filename, cntStr);
        strcat(filename, ".txt");
        
        myFile = SD.open(filename, FILE_WRITE);
        Reference_Time = millis(); //Obtain Time when run starts
        state = RUN;
        Serial.println("State is run");
      }
      else if (inByte == 'c') {
        state = CALIBRATE;
      }
      else {
        // If no state change
        state = MENU;
      }
      break;

    case CALIBRATE:
      if (endCalibrateFlag == 1) {
        endCalibrateFlag = 0;
        calibrateFlag = 0;

        printMenu();

        state = MENU;
      }
      break;

    case RUN:
      // If test is concluded
      if (stopFlag == 1) {
        stopFlag = 0;
        runFlag = 0;
        myFile.close(); // close the file for SD card
        delayActuator(); // Stops the actuator and waits 3s
        extendActuator(); // Extends back to bottom position
        stopActuator(); // Stops actuator

        printMenu();

        state = MENU;
      }
      // If no state change
      else {
        state = RUN;
      }
      break;

  }

  // Actions
  switch (state) {
    case START:
      break;

    case MENU:
      break;

    case CALIBRATE:
      calibrateFlag = 1;
      break;

    case RUN:
      runFlag = 1;
      break;
  }
}


// Taking care of some special events.
void keypadEvent(KeypadEvent key) {
  //Serial.println("INSIDE keyPad Event");
  switch (keypad.getState()) {
    case PRESSED:
      if (key == 'A') {
        inByte = 'c';
      }
      if (key == 'B') {
        inByte = 'r';
      }
      if (key == 'C') {
        inByte = 's';
      }
      if (key == '*') {
        inByte = 't';
      }
      break;
  }
}
