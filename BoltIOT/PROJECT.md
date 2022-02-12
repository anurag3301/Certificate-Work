# Live Insta Following/Follower Counter
Now visualize Insta Following/Follower Counter using Arduino and Bolt and a live running python script.
### Demo Video:	[YouTube.com](https://www.youtube.com/watch?v=2r1-H5duhEg&feature=emb_logo)

### For complete detail explainantio please refer my [Hackster page](https://www.hackster.io/anuragkumar07102003/live-insta-following-follower-counter-7c0464)

![alt text](https://i.ibb.co/xHfqn3d/CO40w-JWJ1-Y.jpg)


## Things used in this project
1. Bolt IoT Bolt WiFi Module
2. USB-A to Mini-USB Cable
3. Arduino UNO
4. USB-A to B Cable
5. 16×2 Liquid Crystal Display
6. I2C Serial Interface Adapter Module
7. Male/Male Jumper Wires
8. Male/Female Jumper Wires

## Software apps and online services
1. Arduino IDE
2. Bolt IoT Bolt Cloud
3. Ubuntu Core

## Story

### 1. Introduction
So in this project, we are going show live Instagram Account followers and following count. The workflow of the project is first we run a python script on a running system or a server. The python script fetches the following and follower count for the Instagram server through an HTTP request. Then the number is being sent to the bolt cloud using the Bolt API. The data is then sent to the particular Bolt module according to the provided Bolt ID. Then the data is sent to Arduino Board through UART and then the Arduino shows the count on the LCD screen. Here for the demo, I have used an LCD display but you can visualize the count as you want using the Arduino.

### For complete detail explainantio please refer my [Hackster page](https://www.hackster.io/anuragkumar07102003/live-insta-following-follower-counter-7c0464)

## Schematics 
### Arduino-LCD   
![Arduino Schematics](https://i.ibb.co/4WcgqFT/layout-1eqyr1yg8s-7lr-MGpu-QP3.jpg)

### Arduino Bolt
![Arduino Bolt Schematics](https://i.ibb.co/TBLdKBg/bolt-arduino-bb-avaeoipuov-i-Ven-Zr5-Omt.png)


## Python Code
```py
import requests
import json
import time
from boltiot import Bolt

bolt_api_key = "XXXXXXXXXXXXXXXXXXXXXXXXXXX"  # Replace the string with the API key 
device_id = "BOLTXXXXXX"    # Replace the string with your Bolt ID
insta_username = "anurag_3301" # Replace it with your Instagram Username 

mybolt = Bolt(bolt_api_key, device_id)      # Connecting to the cloud using the API key and Bolt ID
response = mybolt.serialBegin('9600')       # Establishing UART Communication with 9600 baud rate
print(response)     # Printing the response for troubleshooting 

# This function takes the Insta Username as argument and returns a dictionary with following and follower count
def get_insta_count(username):
    url = 'https://www.instagram.com/' + username + "/?__a=1"   # creating the url for request
    r = requests.get(url)       # request for data for the username 
    data = json.loads(r.text)   # loading the data as JSON
    # now return in form of a dictionary 
    return {"followers":data["graphql"]["user"]["edge_followed_by"]["count"] , "following": data["graphql"]["user"]["edge_follow"]["count"]}

while True:
    data = get_insta_count(insta_username) # calling the get_insta_count function for data
    followers = str(data["followers"])  # extrating the followers count
    following = str(data["following"])  # extrating the following count
    send = followers + "$" + following  # creating a string with followers and following count seperated by '$'
    response = mybolt.serialWrite(send) # Sending the data to arduino though UART line
    print(response)     # response for troubleshooting
    time.sleep(60)      # updating every minute 
```


## Arduino Code

```cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup(){
    lcd.begin();
    lcd.backlight();
    lcd.print("");
    Serial.begin(9600);
    Serial.setTimeout(50);
}

void loop(){
    String inString = "";
    String val[2] = {"", ""};
    if (Serial.available() > 0){
        lcd.clear();
        inString = Serial.readString();
        int index = 0;
        for (int i = 0; i < inString.length(); i++){
            if (inString[i] == '$'){
                index = 1;
                continue;
            }
            val[index] += inString[i];
        }
        lcd.setCursor(0, 0);
        lcd.print("Followers " + val[0]);
        lcd.setCursor(0, 1);
        lcd.print("Following " + val[1]);
    }
}
```

