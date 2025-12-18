#pragma once

#include "Role.h"

namespace TheTraitor {
	class Traitor : public Role {
	public:
		Traitor();
		std::vector<SecretAction*> getSecretActions() override;
	};
}