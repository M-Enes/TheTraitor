
/**
 * @brief A base class representing a battery.
 * * This class manages basic battery properties such as voltage, 
 * capacity, and current charge level. It also handles discharging 
 * and recharging logic based on fixed rates.
 */
class Battery{

    protected: 
        /** @brief The rate at which the battery discharges per hour (mAh/h). */
        static constexpr double DISCHARGE_RATE = 100;

        /** @brief The rate at which the battery recharges per hour (mAh/h). */
        static constexpr double RECHARGE_RATE = 150;

    private:
     double voltage;  /**< voltage in volts(V). */
     double capacity; /**< T capacity in mAh (mAh). */
     double charge;   /**< currect charge in mAh (mAh). */

    public:
        Battery(double v, double c, double initial);

        /**
        * @brief Decreases charge based on a fixed discharge rate.
        * @param hours Number of hours of usage.
        */
        virtual void use(double hours);

        /**
        * @brief Increases charge based on a fixed recharge rate.
        * @param hours Number of hours of charging.
        */
        virtual void recharge(double hours);

        /**
        * @brief Gets the voltage of the battery.
        * @return The voltage value.
        */
        virtual double getVoltage() const;

        /**
        * @brief Gets the maximum capacity of the battery.
        * @return The capacity value.
        */
        virtual double getCapacity() const;

        /**
        * @brief Gets the current charge level of the battery.
        * @return The current charge value.
        */
        virtual double getCharge() const;

        /**
        * @brief gives the charge in percent relative to the capacity
        * @return The charge percentage as a value between 0.0 and 100.0.
        */
        virtual double getPercent() const;

        /**
        * @brief Destroys the Battery object.
        */
        virtual ~Battery();

};
