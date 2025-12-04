#include "Battery.h"
#include <iostream>


Battery::Battery(double v, double c, double initialCharge){
    voltage = v;
    capacity = c;

    if(initialCharge < 0){
        charge = 0;
    }
    else if(initialCharge > capacity){
        charge = capacity;
    }
    else{
        charge = initialCharge;
    }

}

void Battery::use(double hours){

    charge = charge - hours*DISCHARGE_RATE;

    if(charge < 0){
        charge = 0;
    }
}

void Battery::recharge(double hours){
    charge = charge + hours*RECHARGE_RATE;

    if(charge > capacity){
        charge = capacity;
    }
}

double Battery::getVoltage() const {
    return voltage; 
}

double Battery::getCapacity() const {
    return capacity; 
}

double Battery::getCharge() const {
    return charge; 
}

double Battery::getPercent() const {
    
    //for secure code
    if (capacity == 0) return 0;
    
    return (charge/capacity)*100; 
}

Battery::~Battery(){
    
}