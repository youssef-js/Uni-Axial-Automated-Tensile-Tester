# Uni-Axial Automated Tensile Tester
 ECE 442 Systems Analysis and Design Final Project
 
 
 ### Repository Contents
 
 
  ### System Parts
  
  The system was designed with the intention of being completely reproducible by any individual with the desire to do so. As such for the convenience of the prospective designer, the utilized components and their respective links are compiled below:
  
  1. Drive System

     * Eco-Worthy 300mm Stroke Linear Actuator
  
       Link: https://www.amazon.com/dp/B00NM8H5SW?ref=ppx_yo2ov_dt_b_product_details&th=1
       
     * L298N Motor Driver
  
       Link: https://www.amazon.com/dp/B014KMHSW6?psc=1&ref=ppx_yo2ov_dt_b_product_details
      
     * Wall Mounted AC to DC Adapter
  
       Link: https://www.amazon.com/dp/B087NPBC1W?ref=ppx_yo2ov_dt_b_product_details&th=1
    
  2. User Interface
  
     * 20x4 LCD Display
  
       Link: https://www.amazon.com/dp/B08V4WB3Y1?ref=ppx_yo2ov_dt_b_product_details&th=1
       
     * 4x4 Matrix Keypad 
  
       Link: https://www.adafruit.com/product/3844?gclid=Cj0KCQjw06OTBhC_ARIsAAU1yOWN-53pa0KvsjR3zv9O0FhG5_UUUdQQNal-UVi3GDCMKE0uApMlhS8aAhVsEALw_wcB
      
     * Adafruit MicroSD Card Breakout Board
  
       Link: https://www.amazon.com/dp/B00NAY2NAI?psc=1&ref=ppx_yo2ov_dt_b_product_details
  
  3. Data Collection
  
     * HX711 Load Cell Amplifier
  
       Link: https://www.amazon.com/dp/B07MTYT95R?psc=1&ref=ppx_yo2ov_dt_b_product_details
       
     * S-type Beam High-Precision Load Cell
  
       Link: https://www.amazon.com/gp/product/B0785MXVYK/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1
       
     * Arduino Mega 
  
       Link: https://www.amazon.com/ELEGOO-ATmega2560-ATMEGA16U2-Projects-Compliant/dp/B01H4ZDYCE/ref=asc_df_B01H4ZLZLQ/?tag=hyprod20&linkCode=df0&hvadid=309743296044&hvpos=&hvnetw=g&hvrand=5459596528536033104&hvpone=&hvptwo=&hvqmt=&hvdev=c&hvdvcmdl=&hvlocint=&hvlocphy=9004731&hvtargid=pla-490931309987&th=1
       
  4. Store-Bought Components
  
     * Wood, Wood Screws, L Brackets, Magnets, Assorted Bolts/Nuts/Washers. 
  
       Store: Lowes
       
     * Load Cell Bolts
  
       Store: ACE Hardware

  
 ### Itemized Expenses
  
| Category      | Item          | Price |
| ------------- |:-------------:| -----:|
| Drive System  |Linear Actuator|$42.99 |
|               |L298N Driver   | $6.99 |
|               | AC-DC Adapter | $7.98 |
|               |               |       |
| User Interface| 20x4 LCD      | $6.33 |
|               | 4x4 Keypad    | $5.95 |
|               |MicroSD Board  | $9.56 |
|               |               |       |
|Data Collection|HX711 Amplifier| $1.99 |
|               |Load Cell      |$51.91 |
|               |               |       |
|Store-Bought   |All-Inclusive  |$30.00 |
|               |               |       |
|Grand Total    |-------------  |$163.70|


**Arduino Mega cost not included, the microcontroller was provided to the class by the instructor and therefore does not qualify as an expense.

      
  
  
   ### Software Dependencies
   
   In the context of software dependencies there is none for the traditional user. This apparatus requires no external downloads and should 
   
   utilizes the use of a microSD breakout board, as such once a test has been executed the respective data will be stored as a txt file on the microSD. The
   
   
   
   Required Libraries for Arduino Code
   
   Utilize Link --> Press Code --> Download the ZIP --> Extract files into the "libraries" folder for Arduino.
   
   HX711_ADC Library
   Link: https://github.com/olkal/HX711_ADC
   
   LiquidCrystal_I2C Library
   Link: https://github.com/johnrickman/LiquidCrystal_I2C




Use the following include statements to account for


```C
// Load cell
#include <HX711_ADC.h>
#include <EEPROM.h>

// LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Keypad
#include <Keypad.h>

// SD Card
#include <SD.h>
#include <SPI.h>
```
