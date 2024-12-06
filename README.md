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

Parts and accessories:

Stepper motor: https://www.amazon.ca/Stepper-28BYJ-48-ULN2003-Driver-Module/dp/B07XXSNCHL?dib=eyJ2IjoiMSJ9.Y9eoblvkG6YKALD-6F70GNXEqJsKJo30tm3wScPPvw7Ohf4mlvk8V0uiYNImD7-SVKpq88Vhuc3zxz4EwqpOoHDRS4fSz0SAE5OT1dlKAtxQrnQgc7bSIPXT7W6IFTNB5AkACGAKhaECass-XeR1HJct_1nHOtqEsjNYgUpR4J4is7HvoKGB5oIOAXpLPtWfIJ79mnZdDWWcDQHe8DTJ_-Gr8iwJjm4NbO_cUIWK-vhw0DKx0INGsPDLZ89MqmaIVRLMAWlbeQvugyyUy0eFBjDSLnQU1MUEDbkMg0hrtQI.cUgR6HR76_EQKipVuoYAnSQb0ntLA8St5weSkSgkNDs&dib_tag=se&keywords=stepper+motor+arduino&qid=1731012747&sr=8-8

Magnets: https://www.amazon.ca/LOVIMAG-Neodymium-Adhesive-Whiteboard-Scientific/dp/B0CQQ1714T?crid=1FBWIOQ7A5UM7&dib=eyJ2IjoiMSJ9.xpHVat2h-htjNqyBiShC2SrogZn1CVAF94KTBCQxi6HotRl36VkBaai4nyXdkHWlsNWGqeZJsj7F1Bam3zOhzUMr7DvgIJC7IWcTzjurCM8jPQsqeSQEDWXnxCrrdbyEZHtE2fujn51BrZZpNL5O8kUPknOPXRJVt1sXFOyVh6i61NImSumpVQA0AhgcbDdQjvxT17qJSK3jPlKXbshuP3Cv-P0P35jyjweCj5XMdwXie3gQG7GjoD-qYKpnw7MSaqtNfmLe3aKODCAhGiXJBrL2gdhmXi4OJXw3qJnlyzo.diTR0K0kk9S8hTwBHTDO6Q3BrYuJ5PxHbJX1Rhq7NgA&dib_tag=se&keywords=magnets&qid=1730473147&sprefix=magnets%2Caps%2C122&sr=8-35&th=1

Inspiration for plotter design:
https://www.youtube.com/watch?v=og1506q67mo&t=46s

Video explaining computer vision code in more detail:
https://www.youtube.com/watch?v=yJWAtr3kvPU&list=LL&index=2&t=1024s
