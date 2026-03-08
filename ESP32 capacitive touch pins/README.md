# ESP32 Capacitive Touch Pins

Turn any ESP32 GPIO into a touch sensor using just a piece of foil!

##🎬 [Watch the Video](https://www.youtube.com/watch?v=0JiCZEFWqxs)

## Hardware
- ESP32 Dev Board
- Small piece of aluminum foil
- Jumper wire

## Wiring
1. Tape foil to one end of a jumper wire
2. Plug the other end into GPIO 4
- That's it!

## How it works
The ESP32 has built in capacitive touch sensing on certain pins.
When you touch the foil, your body capacitance changes the reading
on GPIO 4, triggering the onboard LED on GPIO 2.

## Usage
1. Upload the code
2. Open Serial Monitor at 115200 baud
3. Touch the foil — LED turns on!
4. Watch the touch values change in Serial Monitor

🎬 [Watch the Video](https://www.youtube.com/watch?v=0JiCZEFWqxs)
