## Build & Run Commands

```bash
# Navigate to project directory
cd "/home/neo/Desktop/GITHUB MYZ21/ImplementationAssigment3Group19"

# Build the project
mkdir -p build
cd build
cmake ..
make

# Run the application
./ImplementationAssigment3Group19
```

## Quick Tutorial

### Step 1: Create Batteries
1. Click **"Create Battery"** button
2. Enter voltage: `3.7` V
3. Enter capacity: `2000` mAh
4. Enter type: `Li-ion`
5. Click OK

Repeat to create more batteries (try different values like 3.7V/3000mAh, 1.5V/1500mAh)

### Step 2: Create a SERIES Pack
1. Click **"Create Pack"** button
2. Select: `SERIES`
3. Enter name: `Series Pack 1`
4. Click OK

### Step 3: Create a PARALLEL Pack
1. Click **"Create Pack"** button
2. Select: `PARALLEL`
3. Enter name: `Parallel Pack 1`
4. Click OK

### Step 4: Add Batteries to Packs
1. Click **"Add Battery to Pack"** button
2. Select a battery from dropdown
3. Select a pack from dropdown
4. Click OK
5. Repeat to add more batteries

### Step 5: Test Functionality

**To Use (Discharge) a Battery/Pack:**
1. Select a battery or pack from the list
2. Click **"Use"** button
3. Enter amount: `100` mAh
4. Watch the charge level decrease in the visualization

**To Recharge:**
1. Select a battery or pack
2. Click **"Recharge"** button
3. Enter `0` for full recharge OR specific amount (e.g., `500`)
4. Watch the charge level increase

## Understanding the Visualization

### Individual Batteries (Left side)
- Green fill = Healthy charge (>60%)
- Yellow fill = Medium charge (20-60%)
- Red fill = Low charge (<20%)
- Label shows: B1, B2, B3, etc.
- Percentage shown below

### Battery Packs (Right side)

**SERIES Pack (Vertical)**
```
┌─────────────┐
│ SERIES      │
│  ┌───┐      │
│  │ B1│ 75%  │
│  └─┬─┘      │
│    │        │
│  ┌─┴─┐      │
│  │ B2│ 75%  │
│  └─┬─┘      │
│    │        │
│  ┌─┴─┐      │
│  │ B3│ 75%  │
│  └───┘      │
│ 11.1V, 75%  │
└─────────────┘
```
- Voltages ADD UP (3x 3.7V = 11.1V)
- Capacity = smallest battery
- Batteries stack vertically

**PARALLEL Pack (Horizontal)**
```
┌─────────────────────┐
│    PARALLEL         │
│ ┌───┐─┌───┐─┌───┐  │
│ │ B1│ │ B2│ │ B3│  │
│ │80%│ │80%│ │80%│  │
│ └───┘ └───┘ └───┘  │
│   3.7V, 80%         │
└─────────────────────┐
```
- Voltage = same as one battery (3.7V)
- Capacities ADD UP (3x 2000mAh = 6000mAh)
- Batteries arrange horizontally

## Key Features to Demonstrate

1. **SERIES Pack Behavior:**
   - Create 3 identical batteries (3.7V, 2000mAh)
   - Add to SERIES pack
   - Total voltage = 11.1V (3 × 3.7V)
   - Capacity = 2000mAh (limited by individual battery)
   - Use 500mAh → all batteries discharge equally

2. **PARALLEL Pack Behavior:**
   - Create 3 identical batteries (3.7V, 2000mAh)
   - Add to PARALLEL pack
   - Total voltage = 3.7V (same as one)
   - Capacity = 6000mAh (3 × 2000mAh)
   - Use 600mAh → distributed across batteries

3. **Mixed Batteries:**
   - Add different capacity batteries to a pack
   - SERIES: limited by smallest
   - PARALLEL: sum of all capacities

## Information Panel

Click on any battery or pack to see:
- Type / Name
- Voltage
- Capacity
- Current charge
- Charge percentage
- Status (FULL/EMPTY)

## Tips

- Always select a battery/pack before using Use or Recharge
- Enter `0` in recharge for instant full charge
- Watch colors change as batteries discharge
- SERIES good for higher voltage
- PARALLEL good for higher capacity
- You can create as many batteries and packs as you want
- Use "Clear All" to start fresh

## Common Use Cases

**Laptop Battery (SERIES):**
- 3 cells in series
- Each 3.7V, 3000mAh
- Total: 11.1V, 3000mAh

**Power Bank (PARALLEL):**
- 4 cells in parallel
- Each 3.7V, 2500mAh
- Total: 3.7V, 10000mAh

**Electric Vehicle (SERIES + PARALLEL concept):**
- Create multiple packs to simulate

