#include "ntshengn_platform_module.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Module/utils/ntshengn_module_defines.h"

void NtshEngn::PlatformModule::init() {
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::PlatformModule::update(float dt) {
	NTSHENGN_UNUSED(dt);
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::PlatformModule::destroy() {
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

uint64_t NtshEngn::PlatformModule::getUserID() {
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

    return 0;
}

std::string NtshEngn::PlatformModule::getUserName() {
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

    return std::string();
}

void NtshEngn::PlatformModule::showOverlay() {
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::PlatformModule::isOverlayVisible() {
    NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

    return false;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::PlatformModuleInterface* createModule() {
    return new NtshEngn::PlatformModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::PlatformModuleInterface* m) {
    delete m;
}