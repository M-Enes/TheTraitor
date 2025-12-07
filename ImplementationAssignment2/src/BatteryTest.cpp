#include <iostream>
#include "Battery.h"
#include "BatteryPack.h"
#include <cmath>

inline bool compareDouble(double first, double second)
{
    return std::fabs(first - second) <= 1e-5;
}

bool seriesBatteryPackTest()
{

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

    if (!compareDouble(pack.getVoltage(), 11.1))
        return false;
    if (pack.getCapacity() != 2000)
        return false;
    if (pack.getCharge() != 1500)
        return false;

    pack.use(1.0);

    std::cout << "After 1 hour use:\n";
    std::cout << "Charge: " << pack.getCharge() << "\n\n";

    if (pack.getCharge() != 1400)
        return false;

    pack.recharge(1.0);

    std::cout << "After 1 hour recharge:\n";
    std::cout << "Charge: " << pack.getCharge() << "\n";

    if (pack.getCharge() != 1550)
        return false;

    return true;
}

bool parallelBatteryPackTest()
{

    Battery b1(3.7, 2000, 1500);
    Battery b2(3.7, 2000, 1800);
    Battery b3(3.7, 2000, 2000);

    BatteryPack pack(BatteryPack::ConnectionType::PARALLEL);
    pack.add(&b1);
    pack.add(&b2);
    pack.add(&b3);

    std::cout << "Initial:\n";
    std::cout << "Voltage: " << pack.getVoltage() << "\n";
    std::cout << "Capacity: " << pack.getCapacity() << "\n";
    std::cout << "Charge: " << pack.getCharge() << "\n\n";

    if (!compareDouble(pack.getVoltage(), 3.7))
        return false;
    if (pack.getCapacity() != 6000)
        return false;
    if (pack.getCharge() != 5300)
        return false;

    pack.use(1.0);

    std::cout << "After 1 hour use:\n";
    std::cout << "Charge: " << pack.getCharge() << "\n\n";

    if (pack.getCharge() != 5000)
        return false;

    pack.recharge(1.0);

    std::cout << "After 1 hour recharge:\n";
    std::cout << "Charge: " << pack.getCharge() << "\n";

    if (pack.getCharge() != 5400)
        return false;

    return true;
}

int main()
{

    constexpr int totalTestCaseCount = 2;
    int passedTestCaseCount = 0;

    bool isPassed = false;

    std::cout << "=== SERIES TEST ===" << '\n';
    isPassed = seriesBatteryPackTest();
    passedTestCaseCount += (isPassed) ? 1 : 0;
    std::cout << "=== END OF SERIES TEST ===" << '\n';

    std::cout << "=== PARALLEL TEST ===" << '\n';
    isPassed = parallelBatteryPackTest();
    passedTestCaseCount += (isPassed) ? 1 : 0;
    std::cout << "=== END OF PARALLEL TEST ===" << '\n';

    std::cout << passedTestCaseCount << " of " << totalTestCaseCount << " test cases passed." << '\n';

    return 0;
}
