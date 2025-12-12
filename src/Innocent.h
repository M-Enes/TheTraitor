#pragma once

#include "Role.h"

namespace TheTraitor {
	class Innocent : public Role {
	public:
		Innocent();
		std::vector<SecretAction> getSecretActions() override;
	};
}