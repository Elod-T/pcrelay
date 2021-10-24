# ESP8266 pc relay!
This is an easy project based on the esp8266 board and a relay. It can work with both Amazon Alexa and the Google Assistant!
## Hardware requirements:
- your favorite esp8266 board (I recommend getting a Wemos D1 Mini, [AliExpress link](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20211024110219&SearchText=wemos+d1+mini))
- a relay board (for a more compact and easy setup, you can get the Relay Shield for the Wemos D1 Mini, [AliExpress link](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20211024110238&SearchText=wemos+d1+mini+relay+shield))
- some jumper cables (at least 2 pcs female-male and 2pcs male-male, but it depends on your setup, [AliExpress link](https://www.aliexpress.com/wholesale?catId=0&initiative_id=SB_20211024110311&SearchText=jumper+cables))

## Software requirements:
- Arduino ide or any kind of firmware flasher(for example EspTool)

## Wiring:
If you have the Wemos D1 Mini and the Relay shield you can just simply follow this diagram. ***Warning: perform these instruction ONLY when you unplug your pc from the wall!*** (*I do not take responsibility for injuries*) You have to unplug your existing power switch cables from your pc's motherboard and connect it to the relay's **common and normally open** pins (the order of the cable doesn't matter). I did this with 2 male-male jumper cables. After that you have to connect your motherboard's power switch pins to the same 2 pins on the relay as before (the order of the cable doesn't matter too). And finally you have to put the relay shield on the top of the Wemos board, be careful with it's orinetation.

![Created with https://www.circuitlab.com/](https://user-images.githubusercontent.com/33983644/138607924-18d4d973-6607-43ed-bf93-de4bcf599ddd.png)

(D1, GND and 5V are already connected because of the shield)

If you have a regular relay and esp8266 board you have to perform the exact same steps as above. After that you have to connect the relay to the board with 3 jumper cables.
- 5V -> 5V
- GND -> GND
- D1 -> D1 (any port of your choice)

## Code:
Make sure to replace the ***CAPITALIZED*** texts in the pcrelay.ino file. If you want you can customize the relay port (*do not change for the Wemos*), and the intervallum it pushes the button for by default.

## Flasing:
First you have to install the CH340G drivers on your system (only on Windows and Mac). And then install the esp8266 board using [this](https://github.com/esp8266/Arduino) tutorial. In Arduino Ide change your board to Wemos D1 Mini and leave the other options on default. Hit upload and you are good to go! If you have chosen the OTA version you have to do this once, after that you can upload firmware wirelessly!

## Usage:
Your board connects to the wifi, and then to the mqtt broker(if you don't have one check out [CloudMqtt](https://www.cloudmqtt.com/)) and subscribes to the topic. If it receives any form of "ON" or "OFF" it is going to do the same thing: turn on the relay, wait (default: 1 seconds) and then turn off the relay. If it receives a number it does the same thing but it wait the number received (max 10). This feature is useful when your pc frozes and you want to force it to turn off (for example 10 seconds wait time will definitely turn off any pc). Be careful with force shutdown because it is basically equal to unplugging your pc from the wall, so you can lose data.

## Update:
If you have the OTA version just download the newest pcrelay.ino file, compile it with your config. And then go to http://your.esp.8266.ip/update and then upload your compiled firmware. If you have the version without the OTA (TODO) just simply flash it like it is the first time.

## TODO
- [x] Working project with basic functionality
- [x] OTA update functionality
- [ ] Optional version without OTA update

### Thank you
if you if you've made it through! This is my first GitHub repo, so any help, comment, critique is appriciated!
