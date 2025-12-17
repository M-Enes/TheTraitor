#include "BatteryPack.h"
#include <sstream>
#include <iomanip>
#include <algorithm>

BatteryPack::BatteryPack(ConnectionType type, const std::string& packName)
    : connectionType(type), name(packName) {
}

void BatteryPack::addBattery(std::shared_ptr<Battery> battery) {
    batteries.push_back(battery);
}

void BatteryPack::removeBattery(int index) {
    if (index >= 0 && index < static_cast<int>(batteries.size())) {
        batteries.erase(batteries.begin() + index);
    }
}

void BatteryPack::clear() {
    batteries.clear();
}

double BatteryPack::getTotalVoltage() const {
    if (batteries.empty()) return 0.0;
    
    if (connectionType == ConnectionType::SERIES) {
        // Series: voltages add up
        double total = 0.0;
        for (const auto& battery : batteries) {
            total += battery->getVoltage();
        }
        return total;
    } else {
        // Parallel: voltage is the same as individual batteries
        return batteries[0]->getVoltage();
    }
}

double BatteryPack::getTotalCapacity() const {
    if (batteries.empty()) return 0.0;
    
    if (connectionType == ConnectionType::SERIES) {
        // Series: capacity is limited by the smallest battery
        double minCapacity = batteries[0]->getCapacity();
        for (const auto& battery : batteries) {
            minCapacity = std::min(minCapacity, battery->getCapacity());
        }
        return minCapacity;
    } else {
        // Parallel: capacities add up
        double total = 0.0;
        for (const auto& battery : batteries) {
            total += battery->getCapacity();
        }
        return total;
    }
}

double BatteryPack::getCurrentCharge() const {
    if (batteries.empty()) return 0.0;
    
    if (connectionType == ConnectionType::SERIES) {
        // Series: current charge is limited by the most depleted battery
        double minCharge = batteries[0]->getCurrentCharge();
        for (const auto& battery : batteries) {
            minCharge = std::min(minCharge, battery->getCurrentCharge());
        }
        return minCharge;
    } else {
        // Parallel: current charges add up
        double total = 0.0;
        for (const auto& battery : batteries) {
            total += battery->getCurrentCharge();
        }
        return total;
    }
}

double BatteryPack::getChargePercentage() const {
    double capacity = getTotalCapacity();
    if (capacity <= 0) return 0.0;
    return (getCurrentCharge() / capacity) * 100.0;
}

ConnectionType BatteryPack::getConnectionType() const {
    return connectionType;
}

std::string BatteryPack::getConnectionTypeString() const {
    return (connectionType == ConnectionType::SERIES) ? "SERIES" : "PARALLEL";
}

std::string BatteryPack::getName() const {
    return name;
}

int BatteryPack::getBatteryCount() const {
    return static_cast<int>(batteries.size());
}

std::shared_ptr<Battery> BatteryPack::getBattery(int index) const {
    if (index >= 0 && index < static_cast<int>(batteries.size())) {
        return batteries[index];
    }
    return nullptr;
}

bool BatteryPack::use(double amount) {
    if (batteries.empty() || amount <= 0) return false;
    
    if (connectionType == ConnectionType::SERIES) {
        // Series: all batteries discharge equally
        for (auto& battery : batteries) {
            if (!battery->use(amount)) {
                return false; // At least one battery couldn't provide enough charge
            }
        }
        return true;
    } else {
        // Parallel: distribute load across batteries proportionally
        double totalCapacity = getTotalCapacity();
        if (totalCapacity <= 0) return false;
        
        for (auto& battery : batteries) {
            double proportion = battery->getCapacity() / totalCapacity;
            double batteryAmount = amount * proportion;
            if (!battery->use(batteryAmount)) {
                return false;
            }
        }
        return true;
    }
}

void BatteryPack::recharge(double amount) {
    if (batteries.empty() || amount <= 0) return;
    
    if (connectionType == ConnectionType::SERIES) {
        // Series: all batteries recharge equally
        for (auto& battery : batteries) {
            battery->recharge(amount);
        }
    } else {
        // Parallel: distribute charge across batteries proportionally
        double totalCapacity = getTotalCapacity();
        if (totalCapacity <= 0) return;
        
        for (auto& battery : batteries) {
            double proportion = battery->getCapacity() / totalCapacity;
            double batteryAmount = amount * proportion;
            battery->recharge(batteryAmount);
        }
    }
}

void BatteryPack::fullRecharge() {
    for (auto& battery : batteries) {
        battery->fullRecharge();
    }
}

std::string BatteryPack::getInfo() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << name << " [" << getConnectionTypeString() << "]\n";
    oss << "Batteries: " << batteries.size() << "\n";
    oss << "Total Voltage: " << getTotalVoltage() << "V\n";
    oss << "Total Capacity: " << getTotalCapacity() << "mAh\n";
    oss << "Charge: " << getChargePercentage() << "%";
    return oss.str();
}
