#include "BatteryPack.h"

BatteryPack::BatteryPack(ConnectionType t) : Battery(0, 0, 0), type(t)
{
}

void BatteryPack::add(Battery *b)
{
    // nullptr check for safety
    if (b == nullptr)
    {
        return;
    }

    cells.push_back(b);
}

void BatteryPack::use(double hours)
{
    // if negative hours given, do nothing
    if (hours < 0)
    {
        return;
    }

    for (Battery *b : cells)
    {
        b->use(hours);
    }
}

void BatteryPack::recharge(double hours)
{
    // if negative hours given, do nothing
    if (hours < 0)
    {
        return;
    }

    for (Battery *b : cells)
    {
        b->recharge(hours);
    }
}

double BatteryPack::getVoltage() const
{
    // if there is no battery, returns 0
    if (cells.empty())
    {
        return 0;
    }

    if (type == ConnectionType::SERIES)
    {
        double sumOfVoltages = 0;

        for (Battery *b : cells)
        {
            sumOfVoltages += b->getVoltage();
        }

        return sumOfVoltages;
    }
    else
    {
        return cells[0]->getVoltage();
    }
}

double BatteryPack::getCapacity() const
{
    // if there is no battery, returns 0
    if (cells.empty())
    {
        return 0;
    }

    if (type == ConnectionType::SERIES)
    {
        double minCapacity = cells[0]->getCapacity();

        for (int i = 1; i < cells.size(); i++)
        {
            double capacity = cells[i]->getCapacity();
            if (capacity < minCapacity)
            {
                minCapacity = capacity;
            }
        }

        return minCapacity;
    }
    else
    {
        double sumOfCapacities = 0;

        for (Battery *b : cells)
        {
            sumOfCapacities += b->getCapacity();
        }

        return sumOfCapacities;
    }
}

double BatteryPack::getCharge() const
{
    // if there is no battery, returns 0
    if (cells.empty())
    {
        return 0;
    }

    if (type == ConnectionType::SERIES)
    {
        double minCharge = cells[0]->getCharge();

        for (int i = 1; i < cells.size(); i++)
        {
            double charge = cells[i]->getCharge();
            if (charge < minCharge)
            {
                minCharge = charge;
            }
        }

        return minCharge;
    }
    else
    {
        double sumOfCharges = 0;

        for (Battery *b : cells)
        {
            sumOfCharges += b->getCharge();
        }

        return sumOfCharges;
    }
}
