#pragma once

#include <string>
#include <vector>

#include "Action.h"
#include "SecretAction.h"

namespace TheTraitor {
	class Role {
	public:
		Role() = delete;
		std::string getName();
		std::vector<Action> getPublicActions();  
		virtual std::vector<TheTraitor::SecretAction> getSecretActions() = 0;
	protected:
		Role(std::string name); 
	private:
		std::string name;
	};
}