#pragma once

#include "Action.h"

namespace TheTraitor {
	class SecretAction : public virtual Action { 
	public:
		SecretAction() = delete;
	protected:
		SecretAction();
	};
}