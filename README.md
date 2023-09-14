# Debounce

This Arduino program will use a pin change interrupt to debounce a mechanical button/switch connected to a GPIO
pin. It is assumed that the button is connected to ground. An internal pullup resistor will be 
enabled to prevent a "floating" input. Using a normally-open pushbutton, the normal state on the 
input pin will be high, going low when the button is pressed (high to low transistion). The number of button 
presses is output to the serial port.
