#pragma once

#include "Action.h"

namespace TheTraitor {
	class SecretAction : public Action { 
	public:
		virtual ~SecretAction() = default;
	protected:
		SecretAction() = default;
	};
}