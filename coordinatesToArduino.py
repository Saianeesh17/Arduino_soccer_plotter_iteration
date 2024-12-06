import serial
import time
import math

# Function to read the coordinates from a text file
def read_coordinates_from_file(file_path):
    coordinates = []
    with open(file_path, 'r') as file:
        for line in file.readlines():
            if line.strip():  # Skip empty lines
                parts = line.split(',')
                if len(parts) == 3:  # Ensure valid format
                    try:
                        # Extract x and y as floats
                        x = float(parts[1])
                        y = float(parts[2])
                        coordinates.append((x, y))
                    except ValueError:
                        print(f"Invalid line: {line.strip()}")
    return coordinates

# Function to select 5 coordinates at regular intervals
def select_regular_intervals(coordinates, num_points=5):
    if len(coordinates) < num_points:
        print(f"Not enough coordinates ({len(coordinates)}) to select {num_points} points.")
        return coordinates  # Return all if less than required
    interval = len(coordinates) / num_points
    selected = [coordinates[math.floor(i * interval)] for i in range(num_points)]
    return selected

# Function to convert coordinates to percentages and make them whole numbers
def convert_to_percentage(coordinates, max_x, max_y):
    return [(round((x / max_x) * 100), round((y / max_y) * 100)) for x, y in coordinates]

# Input file containing coordinates
file_path = "Streamlit web app/ball_positions.txt"

# Maximum values for x and y
max_x = 314
max_y = 546

# Read and process the coordinates
coordinates = read_coordinates_from_file(file_path)
selected_coordinates = select_regular_intervals(coordinates, num_points=5)
converted_coordinates = convert_to_percentage(selected_coordinates, max_x, max_y)

print(f"Converted coordinates (percentages): {converted_coordinates}")

# Ensure coordinates are valid
if not converted_coordinates:
    print("No valid coordinates selected.")
    exit()

# Split into x and y arrays
x_coords, y_coords = zip(*converted_coordinates)

# Open the serial port (adjust "COM3" and 9600 as needed for your setup)
arduino = serial.Serial('COM3', 9600)
time.sleep(2)  # Wait for the connection to initialize

# Format and send the arrays with an extra semicolon at the end
data_string = ';'.join(f"{x},{y}" for x, y in zip(x_coords, y_coords)) + ';'
arduino.write((data_string + '\n').encode())  # '\n' indicates end of data

# Wait for Arduino to process and send back data
time.sleep(10)

# Read and print response from Arduino
while arduino.in_waiting > 0:
    print(arduino.readline().decode().strip())

# Close the connection after sending and receiving
arduino.close()
