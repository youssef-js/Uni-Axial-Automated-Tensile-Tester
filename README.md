# Uni-Axial Automated Tensile Tester
 ECE 442 Systems Analysis and Design Final Project
 
 The University at Albany’s chemistry department, as part of their educational mission, intends to build a laboratory for undergraduate students where they can gain hands on experience testing various material properties (including tensile strength).  However, due to the extremely high cost of commercial products they have been unable to equip such a laboratory.  

The goal of this project is to build an accurate, low cost, easy to use uniaxial tensile strength tester to support this educational mission. 

 
 
 ### Repository Contents
 
 In the interest of transparency all project reports have been included. Reading through this documentation will provide an individual with information on key milestones that were achieved during the progressive evolution of the product. Specifically the "Reports" folder contains the following: 
 
 * Logical Design Report
 * Physical Design Report
 * Experimental Results Report 

 Furthermore, within the "Presentations" folder viewers have been provided with a final copy of the poster displayed at the undergraduate research conference. As well as the presentation slides utilized within the classroom setting that exemplify the accomplished work within a condensed format.
 
 
 Lastly, in the scenario were an individual may wish to replicate the design we have provided the source code that is used to control the logic behind the device. Stl files have also been included, these can be found within the "Misc" folder. When printed the 3D models will yield the following:
 
 * Clamps
 * LCD Case
 * Keypad Case

Moreover, within the same folder will be a link to a webpage that will contain an appropriate training guide and more information on the apparatus.
 
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
   
   In the context of software dependencies there is none for the traditional user. This apparatus requires no external downloads and is advertised as a complete stand-alone product due to the microSD functionality allowing for an individual to interact with data from the device in the form of a txt file. As such, appropriate data analysis can be performed at the users discretion, it is anticipated that for chemistry students excel will be the preferred tool.
   
However, when initially setting up the device one must upload the source code onto the microcontroller. The first step is to download the Arduino IDE, the appropriate link is found below:

Link: https://www.arduino.cc/en/software

Next, it is important that the required libraries for the provided Arduino source code are properly configured. The procedure for doing so is concisely formatted below:


   Utilize Link --> Press "Code" Button --> Download the ZIP --> Extract files into the "libraries" folder for Arduino.


   -HX711_ADC Library
   
   Link: https://github.com/olkal/HX711_ADC
   
   -LiquidCrystal_I2C Library
  
   Link: https://github.com/johnrickman/LiquidCrystal_I2C
   
   -Keypad Library
  
   Link: https://github.com/Chris--A/Keypad
   
   -EEPROM Library
  
   Link: N/A (Built into Arduino IDE)
   
   -Wire Library
  
   Link: N/A (Built into Arduino IDE)
   
   -SD and SPI Library
  
   Link: N/A (Built into Arduino IDE)


Syntax to reference libraries:

(Provided for the readers understanding, these lines of code have already been included within the source code and there is no need for the user to make any additions.)
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

At this stage the setup in terms of software has been completed. Please download the source code provided within this repository and upload to the microcontroller to begin using the apparatus.

### Personnel and Funding

This project is completely funded by the Center For Undergraduate Research And Creative Engagement (CURCE). The designers applied for a $500 award and were subsequently granted the sum after passing the validation process. 

Designers

1. Youssef Jalwaj Soubai

2. Mazin Chater

3. Jaden Pharoah

Faculty Mentors/Support

1. Jonathan Muckell

2. Mike Denmark

Special thanks to Professor Chen, Feldblyun, Yeung, and the University at Albany’s Chemistry Department for sponsoring this project. 

Developed in ECE442: Systems Analysis & Design in the Electrical & Computer Engineering Department. 

