#pragma once
#include "../Common/modules/ntshengn_platform_module_interface.h"

namespace NtshEngn {

	class PlatformModule : public PlatformModuleInterface {
	public:
		PlatformModule() : PlatformModuleInterface("NutshellEngine Default Platform Module") {}

		void init();
		void update(float dt);
		void destroy();
	};

}