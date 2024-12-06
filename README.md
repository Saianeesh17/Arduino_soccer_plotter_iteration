The purpose of this project is to map soccer attacks given x,y coordinates (the ball position) during certain intervals of the attack.
The python code contains some example data of random soccer attacks I mapped out manually by watching some youtube clips.
The circuit diagram to set up the circuit is as follows:
![image](https://github.com/user-attachments/assets/ee3f90b1-c60c-4abf-8a60-414a2da5ed3f)

The ball detection and models are based off of the following repository:
https://github.com/Hmzbo/Football-Analytics-with-Deep-Learning-and-Computer-Vision


Installation and setup for streamlit cv app:
1. Download anaconda from the following link, we will use its terminal to install dependencies: https://www.anaconda.com/download
2. Install the required libraries listed in the file `requirement.txt`, you can use the command `conda env create -f environment.yml` to create the conda env I use but make sure the pytorch installation is compatible with your machine.
3. Use the command `cd` to change directory to the streamlit web app.
4. Use the command `streamlit run main.py` to start the application.

The parts for this project have been 3d printed.

To run this project, you will need to download the python code which is found in the coordinatesToArduino.py file, and install the serial library using the following command:
`pip install pyserial`

you will then need to flash the code within the .ino file to an arduino of your choice

Run the arduino first connected to the COM port of your choice and make sure to edit the python program to accomodate the appropriate com port.
Then run the python program and choose which attack you want to simulate using the plotter.

It should run on the arduino.
