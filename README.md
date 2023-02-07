# Part 4: Occupancy Detection and Alert System
The code functions as a rudimentary occupancy alert system with the following behavior:
- After being turned on, the system blinks the Green Led once every 3 seconds to show it is in the "Armed" mode (3 seconds on/3 seconds off).
- When the occupancy sensor detects someone, it is represented by pressing the left push button switch, which is connected to P4.1 on the MSP430FR2355 Board. This will output a Logic 1, and the system will move into a "Warning" mode, where the Green Led stops blinking, and the Red LED blinks once per second (500ms on, 500ms off).
- The possibility of the occupancy detector still showing someone there after 10 seconds is representented by the holding or letting go of the left push button switch. The system indicates this with the Red Led constantly staying on, and moving into the "ALERT" mode.
- If the right push button switch connected to P2.3 is pressed, indicating the room is now empty, then the system will go back to the "Armed" mode. Pressing the 2.3 button is the only way for the system to go back to the "Armed" state from the "ALERT" state.
