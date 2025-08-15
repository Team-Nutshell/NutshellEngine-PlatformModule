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

NtshEngn::PlatformUserInfo NtshEngn::PlatformModule::getUserInfo() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return PlatformUserInfo();
}

std::vector<NtshEngn::PlatformUserInfo> NtshEngn::PlatformModule::getUserFriendsInfo() {
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return std::vector<PlatformUserInfo>();
}

void NtshEngn::PlatformModule::unlockAchievement(const std::string& achievementID) {
	NTSHENGN_UNUSED(achievementID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

void NtshEngn::PlatformModule::lockAchievement(const std::string& achievementID) {
	NTSHENGN_UNUSED(achievementID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();
}

bool NtshEngn::PlatformModule::isAchievementUnlocked(const std::string& achievementID) {
	NTSHENGN_UNUSED(achievementID);
	NTSHENGN_MODULE_FUNCTION_NOT_IMPLEMENTED();

	return false;
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