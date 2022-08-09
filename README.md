# TeeterTotter
A TeeterTotter with LED chase lights along each side.

Simple circuit, simple code, super cool effect.  Uses [FastLED](https://github.com/FastLED/FastLED).

~15' teeter totter, wooden, with some channels routed down each side.  Run an addressable (APA102) strip down each side.  Wire strips together in parallel.

Link potentiometer to pivot point in whatever way seems best.

Wire up as below:

![Fritzing diagram](/TeeterTotter-WiringFritzing-2.png)

Upload code, and bam, profit.

## Notes:

Arduino was mounted on one end of the teeter totter to be as close to the start of the LED strips as possible.  A long cable was run to the potentiometer in the middle.

The first 15 sec (configurable at top of code) of the program runs a callibration routine - move the teeter totter to its maximum values during this time to lock in the range.  This must happen as the exact resistance/current read via the Arduino's ADC will vary depending on the length of the wire used to hook up the potentiometer among other things.

I used a 10K ohm potentiometer.


