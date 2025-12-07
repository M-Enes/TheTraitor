#include "Battery.h"
#include <vector>

/**
 * @brief A class representing a pack of batteries.
 * * This class inherits from the Battery class and manages a collection
 * of Battery pointers. It calculates voltage, capacity, and charge
 * based on the connection type (Series or Parallel).
 */
class BatteryPack : public Battery
{

public:
    enum class ConnectionType
    {
        SERIES,
        PARALLEL
    };

private:
    std::vector<Battery *> cells;
    ConnectionType type;

public:
    /**
     * @brief Construct the battery pack with the connection type.
     * @param t Connection type of the battery pack.
     */
    BatteryPack(ConnectionType t);

    /**
     * @brief Adds given battery to the battery pack.
     * @param Battery Battery to add.
     */
    void add(Battery *b);

    /**
     * @brief Decreases charge of all batteries in the battery pack based on a fixed discharge rate.
     * @param hours Number of hours of usage.
     */
    void use(double hours) override;

    /**
     * @brief Increases charge of all batteries in the battery pack based on a fixed recharge rate.
     * @param hours Number of hours of charging.
     */
    void recharge(double hours) override;

    /**
     * @brief Gets the voltage of the battery pack.
     * @return Sum of all voltages if connection type is series,
     * voltage of any cell if connection type is parallel.
     */
    double getVoltage() const override;

    /**
     * @brief Gets the capacity of the battery pack.
     * @return Minimum capacity among cells if connection type is series,
     * sum of capacities if connection type is parallel.
     */
    double getCapacity() const override;

    /**
     * @brief Gets the charge of the battery pack.
     * @return Minimum charge among cells if connection type is series,
     * sum of charges if connection type is parallel.
     */
    double getCharge() const override;
};
