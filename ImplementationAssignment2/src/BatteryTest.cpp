#include <iostream>
#include "Battery.h"
#include "BatteryPack.h"

int main() {

    Battery b1(3.7, 2000, 1500);
    Battery b2(3.7, 2000, 1800);
    Battery b3(3.7, 2000, 2000);

    BatteryPack pack(BatteryPack::ConnectionType::SERIES);
    pack.add(&b1);
    pack.add(&b2);
    pack.add(&b3);

    std::cout << "Initial:\n";
    std::cout << "Voltage: " << pack.getVoltage() << "\n";
    std::cout << "Capacity: " << pack.getCapacity() << "\n";
    std::cout << "Charge: " << pack.getCharge() << "\n\n";

    pack.use(1.0);

    std::cout << "After 1 hour use:\n";
    std::cout << "Charge: " << pack.getCharge() << "\n\n";

    pack.recharge(1.0);

    std::cout << "After 1 hour recharge:\n";
    std::cout << "Charge: " << pack.getCharge() << "\n";
    
    return 0;
}
