#pragma once

#include <string>
#include <vector>

namespace TheTraitor {
	class Action;
	class SecretAction;

	class Role {
	public:
		Role() = delete;
		std::string getName();
		std::vector<Action*> getPublicActions();
		virtual std::vector<SecretAction*> getSecretActions() = 0;
	protected:
		Role(std::string name);
	private:
		std::string name;
	};
}