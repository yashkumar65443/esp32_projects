# IoT Neural Network Classification (MATLAB + ThingSpeak)

An end-to-end edge-to-cloud Machine Learning classification system using MATLAB's Deep Learning / Neural Network Toolbox and the ThingSpeak IoT Cloud platform.

---

## ?? Architecture & Overview

This system demonstrates a distributed AIoT (Artificial Intelligence of Things) pipeline:

```text
[ex1.m: Offline Training] --> Model weights saved to net.mat
[ex2.m: IoT Sensor Node]  --> Transmits Sepal/Petal features to ThingSpeak Channel
[ex3.m: Cloud Analytics]  --> Fetches telemetry & performs real-time neural inference
```

The classifier is trained on the classic **Fisher's Iris dataset** ($150$ samples, $4$ numerical features):
* **Field 1 (SL)**: Sepal Length
* **Field 2 (SW)**: Sepal Width
* **Field 3 (PL)**: Petal Length
* **Field 4 (PW)**: Petal Width

The Artificial Neural Network (`patternnet` with 10 hidden neurons) predicts the target flower species:
* **Class 1**: *Iris Setosa*
* **Class 2**: *Iris Versicolour*
* **Class 3**: *Iris Virginica*

---

## ?? Project Structure

```text
+-- net.mat     # Saved neural network model weights
+-- ex1.m       # Step 1: Local model training and evaluation
+-- ex2.m       # Step 2: Edge node simulation (feature capture + ThingSpeak upload)
+-- ex3.m       # Step 3: ThingSpeak MATLAB Analysis (cloud inference pipeline)
+-- .gitignore  # Ignore MATLAB autosaves and OS metadata
+-- README.md   # Project documentation
```

---

## ??? Prerequisites

* **MATLAB** (R2018b or later)
* **Deep Learning Toolbox** (formerly Neural Network Toolbox)
* **ThingSpeak Support Toolbox** (or built-in `thingSpeakWrite` / `thingSpeakRead`)
* A free **ThingSpeak account** with a 4-field channel configured

---

## ?? Step-by-Step Execution Guide

### 1. Train the Neural Network (`ex1.m`)
Trains the pattern recognition network locally using backpropagation and saves the trained model to `net.mat`:
```matlab
run('ex1.m');
```

### 2. Transmit Sensor Data to ThingSpeak (`ex2.m`)
Simulates an edge node sending the 4 morphological measurements to your ThingSpeak channel:
1. Open `ex2.m` and replace the placeholders:
   ```matlab
   thingSpeakWrite(YOUR_CHANNEL_ID, {sl, sw, pl, pw}, 'WriteKey', 'YOUR_WRITE_KEY');
   ```
2. Run the script:
   ```matlab
   run('ex2.m');
   ```

### 3. Real-Time Cloud Inference (`ex3.m`)
Deploy this script inside **ThingSpeak** $\rightarrow$ **Apps** $\rightarrow$ **MATLAB Analysis**:
1. Paste the contents of `ex3.m` into the ThingSpeak code editor.
2. Replace `YOUR_CHANNEL_ID` and `YOUR_READ_KEY`.
3. Click **Save and Run** or attach a **TimeControl** trigger to run inference automatically as new telemetry arrives.
