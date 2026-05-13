import serial
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
import collections
import sys

# --- CONFIGURATION ---
PORT = 'COM8' # Matches your ESP32
BAUD = 921600

# Track the amplitude of a single Wi-Fi subcarrier
SUBCARRIER_TO_PLOT = 15 
MAX_POINTS = 200 # How much time history to show on the screen

# A queue to hold our live data points for the graph
data_queue = collections.deque(np.zeros(MAX_POINTS), maxlen=MAX_POINTS)

try:
    ser = serial.Serial(PORT, BAUD, timeout=1)
    print(f"Successfully connected to {PORT}")
except Exception as e:
    print(f"\n[ERROR] Could not connect to {PORT}.")
    print("Please make sure the Arduino Serial Monitor is CLOSED.")
    print(e)
    sys.exit(1)

# Set up the graph aesthetics
fig, ax = plt.subplots(figsize=(10, 5))
line, = ax.plot(data_queue, color='#00ffcc', linewidth=2)
ax.set_ylim(0, 100) # Amplitude usually hovers between 10 and 60
ax.set_title("Live Wi-Fi Disturbance Monitor (ESP32 CSI)", fontsize=14, color='white')
ax.set_ylabel("Subcarrier Amplitude", color='white')
ax.set_xlabel("Time (Last 200 Packets)", color='white')
ax.set_facecolor('#1e1e1e')
fig.patch.set_facecolor('#121212')
ax.tick_params(colors='white')
ax.grid(True, color='#333333', linestyle='--')

def update(frame):
    # Read all available lines from the ESP32
    while ser.in_waiting:
        try:
            line_str = ser.readline().decode('utf-8', errors='ignore').strip()
            
            # Make sure it's a valid data line
            if line_str.startswith("CSI,"):
                parts = line_str.split(',')
                
                # Calculate the exact array index for the subcarrier we want to plot
                base_index = 3 + (SUBCARRIER_TO_PLOT * 2)
                
                if len(parts) > base_index + 1:
                    # Grab the Imaginary and Real parts of the radio wave
                    imaginary = int(parts[base_index])
                    real = int(parts[base_index + 1])
                    
                    # Calculate the physical Amplitude
                    amplitude = np.sqrt(imaginary**2 + real**2)
                    
                    # Add the new amplitude to our graph
                    data_queue.append(amplitude)
                    
        except Exception:
            pass # Ignore random corrupted data chunks
            
    # Update the graph line
    line.set_ydata(data_queue)
    return line,

print("Starting live plot... Wave your hand between the phone and ESP32!")

# Run the animation
ani = animation.FuncAnimation(fig, update, interval=20, blit=True, cache_frame_data=False)
plt.show()

ser.close()
