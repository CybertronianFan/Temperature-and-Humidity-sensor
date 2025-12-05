#include <LiquidCrystal.h>
#include <DHT.h>

//initialise lcd
LiquidCrystal lcd(7,8,9,10,11,12); // the digital pins in order of what they are connected to on the LCD (RS, E, D4, D5, D6, D7)

// Initialise module 
#define DHTPIN 2 //The signal pin of the module is conencted to D2
#define DHTTYPE DHT11 //This tells the library the type of module I am using 
DHT dht(DHTPIN, DHTTYPE); //creates a DHT object using the pin and type

void setup() {
  lcd.begin(16,2); //tells the library the lcd has 16 columns and 2 rows 
  dht.begin(); //tells the libary to initialize communication with the sensor 
  lcd.print("Starting..."); //Some text when the code is beginning
  delay(1000); //small delay
}

void loop() {
  float humidity = dht.readHumidity(); //reads the current humidity from the sensor, stores it in a variable called "humidity" as a float percentage 
  float temperature = dht.readTemperature(); //reads the current temperature from the sensor, stores it in a variable called "temperature" in celcius as a float 

  if (isnan(humidity) || isnan(temperature)) { //isnan() checks if the reading is not a number. If it it then there is an error. The 2 vertical lines are the "or" operator in Arduino IDE
    lcd.clear(); //removes previous text
    lcd.print("Read Error!"); //displays read error if humidity or temperature is not a number 
    delay(2000); //small delay 
    return; //stop the loop here and try again
  }

  // Display temperature and humidity (runs only if sensor reading was successful)
  lcd.clear(); //removes previous text
  lcd.setCursor(0,0); //moves the cursor to the top left (Column 0, Row 0)
  lcd.print("Temp: "); //writes the label for the temperature 
  lcd.print(temperature); //prints the measured temperature
  lcd.write(223); //code for ASCII character 223, which is the degrees symbol
  lcd.print("C"); //adds the unit celsius

  lcd.setCursor(0,1); //moves the cursor to the bottom left (column 0, row 1)
  lcd.print("Hum: "); //writes the label for the humidity
  lcd.print(humidity); //prints the measured humidity 
  lcd.print(""); //prints the label for humidity as a percentage

  delay(2000); // makes a small delay before the next reading 
}
