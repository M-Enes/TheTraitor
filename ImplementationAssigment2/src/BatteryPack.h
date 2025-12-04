#include "Battery.h"
#include <vector>

/**
 * @brief A class representing a pack of batteries.
 * * This class inherits from the Battery class and manages a collection 
 * of Battery pointers. It calculates voltage, capacity, and charge 
 * based on the connection type (Series or Parallel).
 */
class BatteryPack: public Battery{

public:    
    enum class ConnectionType { SERIES, PARALLEL };

private:

    std::vector<Battery*> cells;
    ConnectionType type;    

public:

    BatteryPack(ConnectionType t);
    void add(Battery* b);
    void use(double hours) override;
    void recharge(double hours) override;
    double getVoltage() const override;
    double getCapacity() const override;
    double getCharge() const override;


};
