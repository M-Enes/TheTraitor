## Overview
This is a Qt-based graphical user interface (GUI) application for managing batteries and battery packs. The application extends Assignment 2's Battery System with visual representation and interactive controls.

## Features

### Battery Management
- **Create Individual Batteries**: Define voltage, capacity, and battery type
- **Create Battery Packs**: Choose between SERIES or PARALLEL connections
- **Add Batteries to Packs**: Combine individual batteries into packs
- **Use Batteries/Packs**: Discharge batteries by specifying the amount (mAh)
- **Recharge Batteries/Packs**: Recharge batteries (full or partial)
- **Visual Representation**: Real-time graphical display using QPainter

### Connection Types
1. **SERIES Connection**:
   - Voltages add up
   - Capacity is limited by the smallest battery
   - Batteries are stacked vertically in the visualization
   - All batteries discharge/charge equally

2. **PARALLEL Connection**:
   - Voltage remains the same as individual batteries
   - Capacities add up
   - Batteries are arranged horizontally in the visualization
   - Load is distributed proportionally

## How to Build

```bash
cd /home/neo/Desktop/GITHUB\ MYZ21/ImplementationAssigment3Group19
mkdir -p build
cd build
cmake ..
make
```

## How to Run

```bash
./build/ImplementationAssigment3Group19
```

## User Interface

### Control Panel (Left Side)
- **Battery Actions Group**:
  - `Create Battery`: Creates a new battery with custom voltage, capacity, and type
  - `Create Pack`: Creates a new battery pack (SERIES or PARALLEL)
  - `Add Battery to Pack`: Adds an existing battery to a pack
  - `Use`: Discharge selected battery/pack
  - `Recharge`: Recharge selected battery/pack
  - `Clear All`: Remove all batteries and packs

- **Individual Batteries List**: Shows all created batteries
- **Battery Packs List**: Shows all created battery packs
- **Information Panel**: Displays detailed information about selected item

### Visualization Panel (Right Side)
- Individual batteries are displayed on the left
- Battery packs are displayed on the right
- **Color Coding**:
  - Green: > 60% charge
  - Yellow: 20-60% charge
  - Red: < 20% charge
- **SERIES packs**: Batteries stacked vertically with connecting lines
- **PARALLEL packs**: Batteries arranged horizontally with connecting lines

## Usage Example

1. **Create a Battery**:
   - Click "Create Battery"
   - Enter voltage (e.g., 3.7V)
   - Enter capacity (e.g., 2000 mAh)
   - Enter type (e.g., "Li-ion")

2. **Create Another Battery**:
   - Repeat step 1 with different values

3. **Create a Battery Pack**:
   - Click "Create Pack"
   - Select connection type (SERIES or PARALLEL)
   - Enter a name for the pack

4. **Add Batteries to Pack**:
   - Click "Add Battery to Pack"
   - Select a battery from the list
   - Select a pack to add it to

5. **Use the Pack**:
   - Select the pack from the "Battery Packs" list
   - Click "Use"
   - Enter the amount to discharge (mAh)
   - Watch the visualization update

6. **Recharge**:
   - Select a battery or pack
   - Click "Recharge"
   - Enter amount (0 for full recharge)

## Class Structure

### Battery Class (`Battery.h`, `Battery.cpp`)
- Properties: voltage, capacity, current charge, type
- Methods: `use()`, `recharge()`, `fullRecharge()`, getters

### BatteryPack Class (`BatteryPack.h`, `BatteryPack.cpp`)
- Properties: list of batteries, connection type, name
- Methods: `addBattery()`, `use()`, `recharge()`, `getTotalVoltage()`, `getTotalCapacity()`

### MainWindow Class (`mainwindow.h`, `mainwindow.cpp`)
- GUI implementation using Qt Widgets
- QPainter for custom battery visualization
- Slots for all user interactions

## Technical Details

- **Framework**: Qt 5/6 with Widgets module
- **Build System**: CMake
- **C++ Standard**: C++17
- **Graphics**: QPainter for custom rendering

## Visual Representation Details

### Individual Battery Display
- Rectangle representing battery body
- Small rectangle on top representing terminal
- Filled area showing charge level (color-coded)
- Label (B1, B2, etc.)
- Percentage display

### Battery Pack Display
- Dashed blue border around pack
- Pack name and connection type label
- Individual batteries within the pack
- Connection lines between batteries
- Total voltage and charge percentage

## Notes

- All batteries start fully charged when created
- The information panel updates automatically when you select items
- You can create multiple batteries and packs
- Visual representation updates in real-time after each action


