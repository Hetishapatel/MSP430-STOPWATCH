# MSP430-STOPWATCH
The code is for MSP430 witten in Embedded C.
The system is simple stopwatch which counts upto 9 seconds and it increaments in steps of 0.1 sec
The controlling input is simple switch, on first switch press the stopwatch starts and on second switch press it stops and on third press it resets.
It is implemented using timer interrupt and  external interrupt.
The switch press causes the external interrupt. The switch ISR accounts for debouncing of the switch using delay. and update the count of switch press and if the switchpress is eqaul to 1 then it starts the timer.
The timer causes interrupt every milisecond and the ISR update the count of time. If the variable count reaches 0.1 sec limit the values to be displayed are updated. 
Two seven segment LEDs are used to display the precision of 0.1 sec
