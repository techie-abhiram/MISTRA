MISTRA — Multimodal Intelligence & Safety Tracking for Regional Assets
🚧 Project Status

Prototype / In Development

MISTRA is a proposed multimodal safety and decision-support system for open-cast mining HEMM dumpers, designed to improve situational awareness during fog, dust, moisture, and other low-visibility conditions.

🎯 Problem

Dense fog and dust can significantly reduce visibility for mining vehicle operators. Existing systems have demonstrated the use of individual technologies such as IR cameras, radar and GNSS for mining safety.

MISTRA explores a multimodal approach that combines complementary sensing technologies so that the system can remain useful when individual sensing modalities are degraded.

💡 Proposed Solution

MISTRA combines:

🌡️ LWIR Thermal Camera
🔭 SWIR Camera
⚡ Event-Based Camera
📡 77-GHz mmWave Radar
🛰️ RTK-GNSS + IMU
🌫️ Environmental Sensors
🧠 NVIDIA Jetson AGX Orin

Sensor data is synchronized and processed at the edge using sensor fusion and AI-based perception.

System Flow
Environmental Conditions
        ↓
Multimodal Sensors
        ↓
Timestamp Alignment
        ↓
Confidence-Weighted Sensor Fusion
        ↓
Edge AI / TensorRT
        ↓
Risk Assessment
        ↓
GO / SLOW / STOP / HOLD / REROUTE
        ↓
Driver HMI + Mine Control Centre
🛠️ Technologies
NVIDIA Jetson AGX Orin
Python
TensorRT
ROS 2
Sensor Fusion
EKF-based State Estimation
Computer Vision
mmWave Radar
Thermal / SWIR / Event Vision
GNSS / IMU
