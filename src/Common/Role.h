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

	class Traitor : public Role {
	public:
		Traitor();
		std::vector<SecretAction*> getSecretActions() override;
	};

	class Innocent : public Role {
	public:
		Innocent();
		std::vector<SecretAction*> getSecretActions() override;
	};
}