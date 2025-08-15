#include "ntshengn_platform_module.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Module/utils/ntshengn_module_defines.h"
#include "../external/sdk/public/steam/steam_api.h"

void NtshEngn::PlatformModule::init() {
	if (!SteamAPI_Init()) {
		NTSHENGN_MODULE_ERROR("Steam must be running and you must own a licence to play this game.");
	}
}

void NtshEngn::PlatformModule::update(float dt) {
	NTSHENGN_UNUSED(dt);

	SteamAPI_RunCallbacks();
}

void NtshEngn::PlatformModule::destroy() {
	SteamAPI_Shutdown();
}

extern "C" NTSHENGN_MODULE_API NtshEngn::PlatformModuleInterface* createModule() {
	return new NtshEngn::PlatformModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::PlatformModuleInterface* m) {
	delete m;
}