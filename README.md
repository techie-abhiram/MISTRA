# MISTRA — Multimodal Intelligence & Safety Tracking for Regional Assets
**SIH 2026 | PS ID: SIH26007 | Smart Automation | Hardware**

## About
MISTRA is a proposed safety-assistance system for HEMM dumpers operating in open-cast iron ore mines under fog, dust, moisture, and low-visibility conditions.
The system combines multiple sensors, edge computing, sensor fusion, and safety decision logic to provide vehicle advisories such as:
**GO / SLOW / STOP / HOLD / REROUTE**

## Proposed System
MISTRA explores a heterogeneous sensing architecture using:
* LWIR thermal camera
* SWIR camera
* Event-based camera
* 77 GHz mmWave radar
* RTK-GNSS + IMU
* Environmental sensors
* NVIDIA Jetson AGX Orin
* Confidence-aware sensor fusion
* Edge AI processing
* Driver HMI and wireless telemetry

## System Flow

```text
Sensors
   ↓
Timestamp Alignment
   ↓
Confidence Assessment
   ↓
Confidence-Weighted EKF Fusion
   ↓
AI Detection & Tracking
   ↓
Risk Assessment
   ↓
GO / SLOW / STOP / HOLD / REROUTE
   ↓
Driver HMI + Fleet Telemetry
```

## Prototype
The repository currently contains an **ESP32-S3 based safety-node prototype** using:
* HC-SR04 ultrasonic sensor
* IR proximity sensor
* LM35 temperature sensor
* Green / Yellow / Red status LEDs
* Piezo buzzer

The prototype demonstrates basic sensor acquisition and safety-state logic for:
* GO
* SLOW
* STOP
* CRITICAL STOP
* SENSOR ERROR

## Development Status
**Status: Prototype / In Development**
Current work includes system architecture, component-level simulation, embedded safety-node development, hardware selection, and prototype planning.
Physical hardware integration and field validation are planned for later stages.

## Technical Report
The detailed technical feasibility, architecture, hardware, power, risk, and implementation plan is available in:
`report/MISTRA_Feasibility_Report.pdf`

## Project Context
**Application:** Open-cast iron ore mining
**Target Vehicle:** HEMM dumper
**Problem Environment:** Fog, dust, moisture, and low visibility
**Compute Platform:** NVIDIA Jetson AGX Orin
**Embedded Prototype:** ESP32-S3
## Team
**Team:** Aveng6rs
