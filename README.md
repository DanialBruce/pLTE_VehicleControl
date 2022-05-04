Futaba Transmitter 4YVD

Transmitter operating voltage 3,3V  out of 4 x 1,3V = 5,2 V NiMH-battery


Steering, Speed, AUX, GearShift  --potentiometers

Potentiometer voltage:

Trimm potentiometer:
1,3 V .... 2,0 V, center 1,65 V

Stick potentiometer:
0,65 V .... 2,65 V, center 1,65 V

Trim left + Stick left = 0,3 V
Trim right + Stick right = 3,0 v


NXP FRDM K64F microcontroller board

Microcontroller operating voltage VIN(5V..9V) taken from the Futaba + 5,2 V.
Microcontroller ground GND taken from the Futaba - voltage.
( This prevents voltages over microcontroller Vcc to be connected to
microcontroller analog inputs! Otherwise there might be a problem when
microcontroller power is OFF and Futaba power is ON. )


Futaba = used for = K64F microcontroller board

CH1 = Steering = A2, PTB10

CH2 = Speed = A3, PTB11

CH3 = AUX = A4, PTC11

CH4 = GearShift = A5, PTC10

VCC = 5,2 V  =  VIN
GND = 0 V    =  GND