# HTS221
Arduino library to support the HTS221 capacitive digital sensor for relative humidity and temperature

## API

This sensor uses I2C to communicate. It is then required to create a TwoWire interface before accessing to the sensors:  

  dev_i2c = new TwoWire(I2C2_SDA, I2C2_SCL);  
  dev_i2c->begin();  

An instance can be created and enbaled following the procedure below:  

  For the humidity sensor:  

    HumTemp = new HTS221Sensor (dev_i2c);  
    HumTemp->Enable();  

The access to the sensor values is done as explained below:  

  Read humidity and temperature.  

    HumTemp->GetHumidity(&humidity);  
    HumTemp->GetTemperature(&temperature);  

## Documentation

You can find the source files at  
https://github.com/stm32duino/HTS221

The HTS221 datasheet is available at  
http://www.st.com/content/st_com/en/products/mems-and-sensors/humidity-sensors/hts221.html
