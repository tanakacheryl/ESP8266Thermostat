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

<p align="center">
Launch the utility: <br/>
<img src="https://i.imgur.com/62TgaWL.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Select the disk:  <br/>
<img src="https://i.imgur.com/tcTyMUE.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Enter the number of passes: <br/>
<img src="https://i.imgur.com/nCIbXbg.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Confirm your selection:  <br/>
<img src="https://i.imgur.com/cdFHBiU.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Wait for process to complete (may take some time):  <br/>
<img src="https://i.imgur.com/JL945Ga.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Sanitization complete:  <br/>
<img src="https://i.imgur.com/K71yaM2.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
<br />
<br />
Observe the wiped disk:  <br/>
<img src="https://i.imgur.com/AeZkvFQ.png" height="80%" width="80%" alt="Disk Sanitization Steps"/>
</p>

<!--
 ```diff
- text in red
+ text in green
! text in orange
# text in gray
@@ text in purple (and bold)@@
```
--!>
