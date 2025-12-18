#include <iostream>

#include "GameManager.h"

TheTraitor::GameManager::GameManager() : currentPhaseIndex(0) {

}

void TheTraitor::GameManager::update() {
    
}

void TheTraitor::GameManager::processAction(ActionPacket actionPacket) {
    
}

void TheTraitor::GameManager::goToNextPhase() {
    currentPhaseIndex = (currentPhaseIndex + 1) % phases.size();
    resetCurrentPhaseTimer();
}

void TheTraitor::GameManager::resetCurrentPhaseTimer() {
    currentPhaseTimer = std::clock();
}