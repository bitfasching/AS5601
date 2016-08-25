# AS5601 Library for Arduino

A wrapper for driving the cheap but great magnetic rotary sensor [AS5601](http://ams.com/eng/Products/Magnetic-Position-Sensors/Angle-Position-On-Axis/AS5601) over I²C on an Arduino. The library aims to offer clean high-level access to the sensor's capabilities and to provide convenience functions for common tasks. The current implementation supports only a subset of the sensor's functionality, more functions may be added in future versions.


## Quick Start

Initialize the driver, which sets up the I²C bus:
```
AS5601 Sensor;
```

Find out if the magnet is in range:
```
if ( Sensor.magnetDetected() ) { … }
```

Query the sensor to get the magnet's current angle:
```
int angle = Sensor.getAngle();
```


## Reference

### Static Properties

The sensor's register addresses are available as static constants as specified in the datasheet. The struct *ByteRegister* includes the 8-bit registers, *WordRegister* contains the starting addresses of the 16-bit registers.

### Low-Level Instance Methods

###### readRaw8( *registerAddress* )
- Reads 8 bits from a register at the specified address.
- *registerAddress* `unsigned char` The address to read from. For example, AS5601::ByteRegister::STATUS.
- Returns the read byte as `unsigned char`.

###### readRaw16( *registerStartAddress* )
- Reads 16 bits from a register, starting at the specified address.
- *registerStartAddress* `unsigned char` The address to begin reading from. For example, AS5601::WordRegister::ANGLE.
- Returns the read word as `unsigned int`.

###### writeRaw8( *registerAddress*, *value* )
- Writes 8 bits to a register at the specified address.
- *registerAddress* `unsigned char` The address to write to. For example, AS5601::ByteRegister::ABN.

###### writeRaw16( *registerStartAddress*, *value* )
- Writes 16 bits to a register, starting at the specified address.
- *registerAddress* `unsigned char` The address to begin writing to. For example, AS5601::WordRegister::ZPOS.

### Higher-Level Instance Methods

###### magnetDetected()
- Queries the sensor's status register to find out whether a magnet's presence is detected.
- Returns *true* or *false* as `bool`.

###### getMagnitude()
- Reads the current magnetic magnitude measurement from the sensor.
- Returns a 12-bit value as `unsigned int`.

###### getGain()
- Reads the AGC's current gain setting from the sensor.
- Returns an 8-bit value as `unsigned char`.

###### getRawAngle()
- Reads the current raw angle estimation from the sensor.
- Returns a 12-bit value as `unsigned int`.

###### setZeroPosition( *rawAngle* )
- Sets the sensor's zero-compensation value to the specified angle.
- *rawAngle* `unsigned int` An integer angle ∈ [0,4095] as returned by *getRawAngle()*. Can be omitted for convenience to use the sensor's current raw angle.

###### setResolution( *angleSteps* )
- Configures the sensor's angle output resolution. (Note: This does not seem to change the values returned by *getAngle()* but probably affects the sensor's A/B output.)
- *angleSteps* `unsigned int` An integer number of angle steps in a full circle. Supported values are 8, 16, 32, …, 2048.

###### getAngle()
- Reads the filtered and zero-compensated angle estimation from the sensor. See also *setZeroPosition()*.
- Returns a 12-bit value as `unsigned int`.

Functionality not covered by the above higher-level methods can be easily added using the low-level communication methods. The already included register address maps facilitate this. In any case, giving the [datasheet](http://ams.com/eng/content/download/659003/1738497/343455) a read is highly recommended to understand how the sensor works.
