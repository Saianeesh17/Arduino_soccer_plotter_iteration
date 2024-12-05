import serial
import time

# coordinate sets of certain soccer attacks
# coordinates displayed as percentages of the length and width of the pitch (x, y-axis) 
coordinate_sets = {
    1: [(0.10, 0.20), (0.20, 0.45), (0.80, 0.25), (0.40, 0.6)],
    2: [(0.15, 0.30), (0.60, 0.50), (0.90, 0.10), (0.25, 0.75), (0.50, 0.85)],
    3: [(0.05, 0.95), (0.50, 0.20), (0.70, 0.80), (0.85, 0.40)],
    4: [(0.12, 0.22), (0.18, 0.42), (0.75, 0.18)],
    5: [(0.30, 0.50), (0.60, 0.30), (0.70, 0.60), (0.90, 0.80), (0.20, 0.10), (0.40, 0.90)],
}

# Display all available coordinate sets
print("Select a coordinate set to send:")
for key, value in coordinate_sets.items():
    print(f"{key}. Set {key}: {value}")

# Get user input for which set to send
while True:
    try:
        choice = int(input(f"Enter a number between 1 and {len(coordinate_sets)}: "))
        if choice in coordinate_sets:
            break
        else:
            print(f"Invalid choice. Please select a number between 1 and {len(coordinate_sets)}.")
    except ValueError:
        print(f"Invalid input. Please enter a number between 1 and {len(coordinate_sets)}.")

# Choose the corresponding coordinates based on user input
x_coords, y_coords = zip(*coordinate_sets[choice])

# Open the serial port (adjust "COM3" and 9600 as needed for your setup)
arduino = serial.Serial('COM3', 9600)
time.sleep(2)  # Wait for the connection to initialize

# Format and send the arrays with an extra semicolon at the end
data_string = ';'.join(f"{x},{y}" for x, y in zip(x_coords, y_coords)) + ';'
arduino.write((data_string + '\n').encode())  # '\n' indicates end of data

# Wait for Arduino to process and send back data
time.sleep(5)

# Read and print response from Arduino
while arduino.in_waiting > 0:
    print(arduino.readline().decode().strip())

# Close the connection after sending and receiving
arduino.close()
