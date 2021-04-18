# NodeMCU and 1306 OLED Status Screen

A NodeMCU based status screen using a 1306 OLED Screen to display information about your Clash rule-based tunnel.

![Example](https://raw.githubusercontent.com/RichardTHF/NodeMCU---Clash-Status-Screen/main/image/example1.png)

### Required libraries
```c
Wire.h
ArduinoJson.h
Arduino_JSON
Adafruit_GFX.h
Adafruit_SSD1306.h
```

### Features
- [x] Displays Proxy Mode (Global/Rule/Direct)
- [x] Display current traffic (Upload and Download speeds)
- [ ] Pagination (in-progress)
- [ ] Total Traffic (in-progress)
- [ ] Current Proxy (in-progress)
- [ ] Button Support
- [ ] Screen burn protection (colour inversion etc)
- [ ] Ability to control Modes and Proxy selections

### Setup

Create a file called `config.h` and input the following code. Replace the URL details with your Clash proxy information.

```c
const char* ssid     = "YOUR SSID";
const char* password = "YOUR WIFI PASSWORD";

const char* serverName = "http://10.0.0.1:9090/configs";
const char* serverName2 = "http://10.0.0.1:9090/traffic";
```

Connect your NodeMCU Prototype board to your commputer and connect the SSD1306 as follows
```
SDA - D2
SCL - D1 
VCC - 3V3
GND - GND
```
