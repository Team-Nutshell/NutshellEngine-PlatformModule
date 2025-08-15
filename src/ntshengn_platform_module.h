#pragma once
#include "../Common/modules/ntshengn_platform_module_interface.h"
#include "../external/sdk/public/steam/steam_api.h"

namespace NtshEngn {

	class PlatformModule : public PlatformModuleInterface {
	public:
		PlatformModule() : PlatformModuleInterface("NutshellEngine Steam Platform Module") {}

		void init();
		void update(float dt);
		void destroy();

		// Returns the user's information on the platform
		PlatformUserInfo getUserInfo();

		// Returns the list of the user's friends on the platform
		std::vector<PlatformUserInfo> getUserFriendsInfo();

		// Show the platform's overlay
		void showOverlay();
		// Returns true if the platform's overlay is visible
		bool isOverlayVisible();

	private:
		STEAM_CALLBACK(PlatformModule, onGameOverlayActivated, GameOverlayActivated_t);

	private:
		PlatformUserInfo m_userInfo;

		bool m_overlayActivated = false;
	};

}