#pragma once

#include <string>

namespace TheTraitor {
    class Phase {
        private:
            std::string name;
            int durationTimeSeconds;
        public:
            Phase(std::string name, int durationTimeSeconds);
            Phase();
            std::string getName();
            int getDurationTimeSeconds();
    };
}