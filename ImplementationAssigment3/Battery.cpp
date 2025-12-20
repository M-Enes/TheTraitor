#include "Battery.h"
#include <algorithm>
#include <sstream>
#include <iomanip>

Battery::Battery(double volt, double cap, const std::string& batteryType)
    : voltage(volt), capacity(cap), currentCharge(cap), type(batteryType) {
    // Start fully charged
}

double Battery::getVoltage() const {
    return voltage;
}

double Battery::getCapacity() const {
    return capacity;
}

double Battery::getCurrentCharge() const {
    return currentCharge;
}

double Battery::getChargePercentage() const {
    return (currentCharge / capacity) * 100.0;
}

std::string Battery::getType() const {
    return type;
}

bool Battery::use(double amount) {
    if (amount <= 0) return false;
    
    if (currentCharge >= amount) {
        currentCharge -= amount;
        return true;
    }
    return false; // Insufficient charge
}

void Battery::recharge(double amount) {
    if (amount <= 0) return;
    
    currentCharge = std::min(currentCharge + amount, capacity);
}

void Battery::fullRecharge() {
    currentCharge = capacity;
}

bool Battery::isEmpty() const {
    return currentCharge <= 0.01; // Consider empty if < 0.01 mAh
}

bool Battery::isFull() const {
    return currentCharge >= capacity - 0.01; // Consider full if within 0.01 mAh
}

std::string Battery::getInfo() const {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2);
    oss << type << " " << voltage << "V " << capacity << "mAh";
    oss << " (" << getChargePercentage() << "%)";
    return oss.str();
}
