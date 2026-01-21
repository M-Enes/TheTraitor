#pragma once

#include <string>
#include <vector>

namespace TheTraitor {
	class Action;
	class SecretAction;

	class Role {
	public:
		Role() = delete;
		virtual ~Role() = default;
		std::string getName() const;
		std::vector<Action*> getPublicActions() const;
		virtual std::vector<SecretAction*> getSecretActions() const = 0;
	protected:
		Role(std::string name);
	private:
		std::string name;
	};

	class Traitor : public Role {
	public:
		Traitor();
		std::vector<SecretAction*> getSecretActions() const override;
	};

	class Innocent : public Role {
	public:
		Innocent();
		std::vector<SecretAction*> getSecretActions() const override;
	};
}