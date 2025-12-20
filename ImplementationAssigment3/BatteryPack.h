#ifndef BATTERYPACK_H
#define BATTERYPACK_H

#include "Battery.h"
#include <vector>
#include <memory>
#include <string>

enum class ConnectionType {
    SERIES,
    PARALLEL
};

class BatteryPack {
private:
    std::vector<std::shared_ptr<Battery>> batteries;
    ConnectionType connectionType;
    std::string name;

public:
    // Constructor
    BatteryPack(ConnectionType type, const std::string& packName = "Battery Pack");
    
    // Battery management
    void addBattery(std::shared_ptr<Battery> battery);
    void removeBattery(int index);
    void clear();
    
    // Getters
    double getTotalVoltage() const;
    double getTotalCapacity() const;
    double getCurrentCharge() const;
    double getChargePercentage() const;
    ConnectionType getConnectionType() const;
    std::string getConnectionTypeString() const;
    std::string getName() const;
    int getBatteryCount() const;
    std::shared_ptr<Battery> getBattery(int index) const;
    
    // Methods
    bool use(double amount);      // Use battery pack
    void recharge(double amount); // Recharge battery pack
    void fullRecharge();          // Fully recharge all batteries
    
    // Display info
    std::string getInfo() const;
};

#endif // BATTERYPACK_H
