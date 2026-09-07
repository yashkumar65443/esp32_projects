# Smart Traffic Density Detection & IoT System (MATLAB + ThingSpeak)

An automated vision-based traffic density estimation and IoT monitoring system for a 4-way intersection (North, South, East, West). Built with MATLAB Image Processing and integrated with the ThingSpeak IoT platform.

---

## ?? Project Overview
Traditional traffic lights operate on fixed timers regardless of whether roads are congested or empty. This project implements a vision-based density monitoring solution:
1. Captures overhead real-time camera frames of a 4-way intersection.
2. Segments each of the 4 approach directions using a Region-of-Interest (ROI) mask.
3. Applies background subtraction, noise reduction (median filtering), and morphological blob analysis to measure vehicle density.
4. Highlights detected traffic with visual bounding boxes (Red for congested, Cyan for clear).
5. Transmits real-time lane occupancy percentages to the **ThingSpeak IoT Cloud** for remote monitoring.

---

## ??? Hardware Requirements
* **Computer / Laptop**: Running MATLAB (2018b or newer recommended).
* **USB Webcam**: 720p or 1080p camera mounted overhead with a top-down view.
* **4-Way Intersection Model**: Physical model/track with miniature cars for simulation.
* **Internet Connection**: For uploading data to the ThingSpeak Cloud.

---

## ?? Software Prerequisites
* **MATLAB**
* **Image Processing Toolbox**
* **MATLAB Support Package for USB Webcams**
* **ThingSpeak Support Toolbox** (or built-in `thingSpeakWrite` function)

---

## ?? Project Structure
```text
+-- 1.bmp, 2.bmp, 3.bmp, 4.bmp   # Segmented reference background images for each lane
+-- background.bmp               # Full baseline empty-intersection reference frame
+-- mask.bmp                     # Binary mask defining the 4 lane bounding boxes
+-- ex1.m                        # Step 1: Capture baseline background from webcam
+-- ex2.m                        # Step 2: Segment lanes using mask and save individual reference crops
+-- videodetection.m             # Computer vision algorithm (background subtraction & density calculation)
+-- ex3.m                        # Step 3: Real-time loop (live detection + ThingSpeak upload)
+-- .gitignore                   # Ignore MATLAB and OS temporary files
+-- README.md                    # Project documentation
```

---

## ?? How to Run

### Step 1: Baseline Background Acquisition (`ex1.m`)
Ensure the camera is mounted firmly and the intersection has no vehicles. Run `ex1.m` to capture `background.bmp`.
```matlab
run('ex1.m');
```

### Step 2: Lane Segmentation (`ex2.m`)
Ensure `mask.bmp` matches your lane positions. Run `ex2.m` to crop and save the 4 individual lane background images (`1.bmp` to `4.bmp`).
```matlab
run('ex2.m');
```

### Step 3: Live Detection & IoT Logging (`ex3.m`)
Run `ex3.m` to start live processing. This script will:
* Monitor traffic continuously.
* Display real-time bounding boxes around congested lanes.
* Send traffic data to ThingSpeak every 20 seconds.
```matlab
run('ex3.m');
```

> **Note:** Remember to update your ThingSpeak Channel ID and API Write Key in `ex3.m`.

---

## ?? ThingSpeak IoT Integration
The system logs 4 fields representing the normalized traffic area percentage (0–100%) for each approach lane:
* Field 1: North Lane Traffic (%)
* Field 2: South Lane Traffic (%)
* Field 3: East Lane Traffic (%)
* Field 4: West Lane Traffic (%)
