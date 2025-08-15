#pragma once
#include "../Common/modules/ntshengn_platform_module_interface.h"

namespace NtshEngn {

	class PlatformModule : public PlatformModuleInterface {
	public:
		PlatformModule() : PlatformModuleInterface("NutshellEngine Default Platform Module") {}

		void init();
		void update(float dt);
		void destroy();

		// Returns the user's information on the platform
		PlatformUserInfo getUserInfo();

		// Returns the list of the user's friends on the platform
		std::vector<PlatformUserInfo> getUserFriendsInfo();

		// Unlocks achievement with identifier achievementID
		void unlockAchievement(const std::string& achievementID);
		// Locks achievement with identifier achievementID
		void lockAchievement(const std::string& achievementID);
		// Returns true if the achievement with identifier achievementID has been unlocked by the user, else, returns false
		bool isAchievementUnlocked(const std::string& achievementID);

		// Show the platform's overlay
		void showOverlay();
		// Returns true if the platform's overlay is visible, else, returns false
		bool isOverlayVisible();
	};

}