import matplotlib.pyplot as plt
import serial
import time

# Function to plot the data using Matplotlib
def plot_data(data):
    x_values = [point[0] for point in data]
    y_values = [point[1] for point in data]

    plt.plot(x_values, y_values, marker='o', linestyle='-')
    plt.xlabel('X')
    plt.ylabel('Y')
    plt.title('Data From Dump on CC1101')
    plt.grid(True)
    plt.show()

# Function to read data from serial port and extract the relevant part
def read_serial_data():
    while True:
        try:
            ser = serial.Serial('COM10', 1000000, timeout=1)
            print("Serial Port Checked")
            time.sleep(5)  # Wait for 5 seconds to receive all data
            serial_data = ser.read_all().decode('utf-8').strip()
            print("Raw Serial Data:", serial_data)
            if "Dump transition times:" in serial_data:
                start_index = serial_data.find("Dump transition times:") + len("Dump transition times:")
                end_index = serial_data.find("Total time (us):")
                data_str = serial_data[start_index:end_index].strip()
                print("-------------------------------------------")
                print("Extracted Data:", data_str)
                data_values = [int(x) for x in data_str.split(',') if x]
                # Create a list of tuples with corresponding x and y values
                table_data = [(i*5+1, val) for i, val in enumerate(data_values)]
                print("-------------------------------------------")
                print("Table Data:", table_data)
                ser.close()  # Close the serial connection before returning the data
                return table_data
            else:
                print("Error: Data format not recognized. Retrying...")
                ser.close()  # Close the serial connection before retrying
                time.sleep(0.5)  # Wait for 2 seconds before retrying
        except serial.SerialException as e:
            print("Serial port error:", e)
            time.sleep(0.5)  # Wait for 2 seconds before retrying

# Main loop
while True:
    table_data = read_serial_data()

    # Plot data using Matplotlib
    plot_data(table_data)
