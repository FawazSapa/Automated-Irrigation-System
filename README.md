# Automated-Plant-Watering-System
Traditional irrigation practices and manual watering methods employed by agricultural operations and plant hobbyists lack precision and regulation leading to scenarios where water is either wasted through over-irrigation or plants are put at risk due to under-watering.
This calls for an automated system to adapt to the varying needs of plants, providing a solution that aligns with modern expectations of efficiency, sustainability, and technological integration in plant care.This system is designed for enthusiasts looking to integrate technology with gardening, providing both automation and remote monitoring capabilities.


# Circuit Diagram

![Screenshot 2024-04-07 235852](https://github.com/FawazSapa/Automated-Plant-Watering-System/assets/114939768/fe90aaa7-d7a6-44da-8797-5a3259a33089)





##  System Features

### Sensors and Actuators

- **Temperature and Humidity Monitoring**: The DHT-11 sensor is used for tracking the ambient temperature and humidity, essential for maintaining the plant's health.

- **Soil Moisture Measurement**: A soil moisture sensor assesses the water content in the soil, allowing for precise watering to avoid over or under-watering.

- **Water Detection**: Incorporates a water sensor to detect water levels, ensuring the system's watering mechanism operates efficiently.

- **Light Intensity Quantification**: A photoresistor measures the ambient light intensity, vital for adjusting the plant's exposure to light.

- **Display Interface**: Real-time environmental data is displayed on an LCD, offering instant insights into the plant's surroundings.

- **Water Pump Control**: Utilizes a relay to automate the water pump, powered by a 9V battery, based on the logic derived from sensor inputs, ensuring the plant is watered when necessary.

### Connectivity and Control

- ** Integration with ESP32**: To enhance the project's capabilities, we to integrated an ESP32 microcontroller. This will enable IoT connectivity through the Blynk Cloud service, adding a layer of complexity and functionality to our project.We used the alert the system from Bylnk to alert the users through email when critical levels of mositure and water level are reached.

- **Remote Watering via Smartphone**: With the introduction of Blynk Cloud connectivity, users will be able to water their plants remotely with just a click on their smartphone. This feature is designed for users who wish to care for their plants, even when they are not in close proximity.


