<h1>ESP8266 Thermostat</h1>


<h2>Description</h2>
This project is a simple IoT thermostat prototype built using an ESP8266 NodeMCU, a BMP180 temperature and pressure sensor, and a few basic components like LEDs, a button, and a potentiometer.

It continuously reads temperature and pressure data from the sensor and uses that information to simulate how a basic thermostat would behave. Depending on the temperature, the system switches between normal operation and a safety mode, with LEDs showing the current state. There’s also a physical button that can force the system into safety mode for manual override.

The ESP8266 connects to WiFi and runs a small web server, allowing you to view live sensor readings from a browser. It also provides a simple web interface where temperature thresholds can be adjusted, as well as a JSON endpoint for accessing the data programmatically.

Overall, the project demonstrates how hardware sensors, embedded control logic, and a web interface can be combined to build a basic but functional IoT monitoring and control system.
<br />


<h2>Languages and Tools Used</h2>

- <b>C / C++ (Arduino Framework) – Core firmware logic for ESP8266</b> 
- <b>ESP8266WiFi Library – Handles WiFi connectivity</b>
- <b>ESP8266WebServer Library – Runs the embedded web server</b>
- <b>Wire (I2C Library) – Communication with the BMP180 sensor</b>
- <b>Adafruit BMP085 Unified Library – Temperature and pressure sensor readings</b>
- <b>Adafruit Sensor Library – Standardized sensor data handling</b>


<h2>Hardware Used </h2>

- <b>NodeMCU ESP82660</b> (21H2)
- <b>BMP180 Sensor</b> (21H2)
- <b>LED (x2)</b> (21H2)
- <b>Push Button</b> (21H2)
- <b>Potentiometer</b> (21H2)
- <b>Resistors (220Ω)</b> (21H2)
- <b>Breadboard & Jumper Wires</b> (21H2)

<h2>Program walk-through:</h2>

<h3>WiFi Initialization</h3>
<p align="center">
ESP8266 connects to the configured WiFi network and prints the assigned IP address to allow web access.<br/><br/>
<img src="./images/wifi.png" width="80%" alt="WiFi Initialization"/>
</p>

<br/>

<h3>Sensor Initialization</h3>
<p align="center">
Initializes the BMP180 sensor using I2C communication and prepares temperature and pressure readings.<br/><br/>
<img src="./images/sensor.png" width="80%" alt="Sensor Initialization"/>
</p>

<br/>

<h3>Thermostat Control Logic</h3>
<p align="center">
Processes temperature readings and decides system state (ON/OFF/Safety Mode) based on configured thresholds.<br/><br/>
<img src="./images/control.png" width="80%" alt="Thermostat Control Logic"/>
</p>

<br/>

<h3>Web Server Endpoints</h3>
<p align="center">
Hosts a web interface and API endpoints for live monitoring and adjusting temperature thresholds.<br/><br/>
<img src="./images/webserver.png" width="80%" alt="Web Server Endpoints"/>
</p>

<br/>

<h3>Safety Features</h3>
<p align="center">
Implements emergency button override and automatic shutdown when temperature exceeds safety limits.<br/><br/>
<img src="./images/safety.png" width="80%" alt="Safety Features"/>
</p>

<br/>

<h3>📸 Hardware Setup</h3>
<p align="center">
Physical prototype showing ESP8266, BMP180 sensor, LEDs, and control components used in the system.<br/><br/>
<img src="./images/hardware.png" width="80%" alt="Hardware Setup"/>
<img src="./images/hardware.png" width="80%" alt="Hardware Setup"/>
</p>
