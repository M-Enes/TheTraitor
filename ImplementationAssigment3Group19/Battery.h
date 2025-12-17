#ifndef BATTERY_H
#define BATTERY_H

#include <string>

class Battery {
private:
    double voltage;        // Nominal voltage (V)
    double capacity;       // Total capacity (mAh)
    double currentCharge;  // Current charge level (mAh)
    std::string type;      // Battery type (e.g., "Li-ion", "NiMH")

public:
    // Constructor
    Battery(double volt, double cap, const std::string& batteryType = "Li-ion");
    
    // Getters
    double getVoltage() const;
    double getCapacity() const;
    double getCurrentCharge() const;
    double getChargePercentage() const;
    std::string getType() const;
    
    // Methods
    bool use(double amount);      // Use battery (returns false if insufficient charge)
    void recharge(double amount); // Recharge battery
    void fullRecharge();          // Fully recharge battery
    bool isEmpty() const;         // Check if battery is empty
    bool isFull() const;          // Check if battery is full
    
    // Display info
    std::string getInfo() const;
};

#endif // BATTERY_H
