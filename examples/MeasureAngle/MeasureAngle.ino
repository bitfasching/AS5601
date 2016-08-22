/**
 * Measure Angle
 * with AS5601 Magnet Rotary Sensor
 */


#include <Arduino.h>
#include <AS5601.h>


AS5601 Sensor;


void setup()
{
    delay( 1000 );
    Serial.begin( 115200 );
    Serial.println( F("Angle Measurement with AS5601") );
}


void loop()
{
    Serial.print( F("Magnitude: ") );
    Serial.print( Sensor.getMagnitude() );

    Serial.print( F(" | Raw angle: ") );
    Serial.print( Sensor.getRawAngle() );

    Serial.print( F(" | Clean angle: ") );
    Serial.print( Sensor.getAngle() );

    if ( Serial.read() == '0' )
    {
        Sensor.setZeroPosition();
        Serial.print( F(" | Zero position set!") );
    }

    Serial.println();

    delay( 50 );
}
