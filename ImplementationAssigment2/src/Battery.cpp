#include "Battery.h"
#include <iostream>

Battery::Battery(double v, double c, double initialCharge)
{
    if (v < 0)
    {
        v = 0;
    }

    if (c < 0)
    {
        c = 0;
    }

    voltage = v;
    capacity = c;

    if (initialCharge < 0)
    {
        charge = 0;
    }
    else if (initialCharge > capacity)
    {
        charge = capacity;
    }
    else
    {
        charge = initialCharge;
    }
}

void Battery::use(double hours)
{
    // if negative hours given, do nothing
    if (hours < 0)
    {
        return;
    }

    charge = charge - hours * DISCHARGE_RATE;

    if (charge < 0)
    {
        charge = 0;
    }
}

void Battery::recharge(double hours)
{
    // if negative hours given, do nothing
    if (hours < 0)
    {
        return;
    }

    charge = charge + hours * RECHARGE_RATE;

    if (charge > capacity)
    {
        charge = capacity;
    }
}

double Battery::getVoltage() const
{
    return voltage;
}

double Battery::getCapacity() const
{
    return capacity;
}

double Battery::getCharge() const
{
    return charge;
}

double Battery::getPercent() const
{

    // for secure code
    if (capacity == 0)
        return 0;

    return (charge / capacity) * 100;
}

Battery::~Battery()
{
}