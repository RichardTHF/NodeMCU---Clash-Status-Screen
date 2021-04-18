# NodeMCU and 1306 OLED Status Screen

A NodeMCU based status screen using a 1306 OLED Screen to display information about your Clash rule-based tunnel.

![Example](images/example1.png)

##Required libraries
```c
Wire.h
ArduinoJson.h
Arduino_JSON
Adafruit_GFX.h
Adafruit_SSD1306.h
```

##Features
- [x] Displays Proxy Mode (Global/Rule/Direct)
- [x] Display current traffic (Upload and Download speeds)
- [ ] Pagination (in-progress)
- [ ] Total Traffic (in-progress)
- [ ] Current Proxy (in-progress)
- [ ] Button Support
- [ ] Screen burn protection (colour inversion etc)
- [ ] Ability to control Modes and Proxy selections
