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

		// Returns the user's ID on the platform
		uint64_t getUserID();
		// Returns the user's name on the platform
		std::string getUserName();

		// Show the platform's overlay
		void showOverlay();
		// Returns true if the platform's overlay is visible
		bool isOverlayVisible();

	private:
		STEAM_CALLBACK(PlatformModule, onGameOverlayActivated, GameOverlayActivated_t);

	private:
		bool m_overlayActivated = false;
	};

}