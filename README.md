The purpose of this project is to map soccer attacks given x,y coordinates (the ball position) during certain intervals of the attack.
The python code contains some example data of random soccer attacks I mapped out manually by watching some youtube clips.
The circuit diagram to set up the circuit is as follows:
![image](https://github.com/user-attachments/assets/ee3f90b1-c60c-4abf-8a60-414a2da5ed3f)

The parts for this project have been 3d printed.

To run this project, you will need to download the python code, and install the serial library using the following command:
pip install serial

you will then need to flash the code within the .ino file to an arduino of your choice

Run the arduino first connected to the COM port of your choice and make sure to edit the python program to accomodate the appropriate com port.
Then run the python program and choose which attack you want to simulate using the plotter.

It should run on the arduino.
