#include "ntshengn_platform_module.h"
#include "../Module/utils/ntshengn_dynamic_library.h"
#include "../Module/utils/ntshengn_module_defines.h"

void NtshEngn::PlatformModule::init() {
	if (!SteamAPI_Init()) {
		NTSHENGN_MODULE_ERROR("Steam must be running and you must own a licence to play this game.");
	}

	m_userInfo.id = SteamUser()->GetSteamID().ConvertToUint64();
}

void NtshEngn::PlatformModule::update(float dt) {
	NTSHENGN_UNUSED(dt);

	SteamAPI_RunCallbacks();
}

void NtshEngn::PlatformModule::destroy() {
	SteamAPI_Shutdown();
}

NtshEngn::PlatformUserInfo NtshEngn::PlatformModule::getUserInfo() {
	m_userInfo.name = SteamFriends()->GetPersonaName();
	EPersonaState userState = SteamFriends()->GetPersonaState();
	if (userState == EPersonaState::k_EPersonaStateOffline) {
		m_userInfo.state = PlatformUserState::Offline;
	}
	else if (userState == EPersonaState::k_EPersonaStateOnline) {
		m_userInfo.state = PlatformUserState::Online;
	}
	else if (userState == EPersonaState::k_EPersonaStateBusy) {
		m_userInfo.state = PlatformUserState::Busy;
	}
	else if ((userState == EPersonaState::k_EPersonaStateAway) || (friendState == EPersonaState::k_EPersonaStateSnooze)) {
		m_userInfo.state = PlatformUserState::Away;
	}
	else {
		m_userInfo.state = PlatformUserState::Unknown;
	}

	return m_userInfo;
}

std::vector<NtshEngn::PlatformUserInfo> NtshEngn::PlatformModule::getUserFriendsInfo() {
	size_t friendsCount = SteamFriends()->GetFriendCount(k_EFriendFlagImmediate);
	std::vector<PlatformUserInfo> friends(friendsCount);

	for (size_t i = 0; i < friendsCount; i++) {
		CSteamID friendSteamID = SteamFriends()->GetFriendByIndex(static_cast<int>(i), k_EFriendFlagImmediate);

		friends[i].id = friendSteamID.ConvertToUint64();
		friends[i].name = SteamFriends()->GetFriendPersonaName(friendSteamID);
		EPersonaState friendState = SteamFriends()->GetFriendPersonaState(friendSteamID);
		if (friendState == EPersonaState::k_EPersonaStateOffline) {
			friends[i].state = PlatformUserState::Offline;
		}
		else if (friendState == EPersonaState::k_EPersonaStateOnline) {
			friends[i].state = PlatformUserState::Online;
		}
		else if (friendState == EPersonaState::k_EPersonaStateBusy) {
			friends[i].state = PlatformUserState::Busy;
		}
		else if ((friendState == EPersonaState::k_EPersonaStateAway) || (friendState == EPersonaState::k_EPersonaStateSnooze)) {
			friends[i].state = PlatformUserState::Away;
		}
		else {
			friends[i].state = PlatformUserState::Unknown;
		}
	}

	return friends;
}

void NtshEngn::PlatformModule::showOverlay() {
	SteamFriends()->ActivateGameOverlay("");
	m_overlayActivated = true;
}

bool NtshEngn::PlatformModule::isOverlayVisible() {
	return m_overlayActivated;
}

void NtshEngn::PlatformModule::onGameOverlayActivated(GameOverlayActivated_t* pCallback) {
	m_overlayActivated = pCallback->m_bActive;
}

extern "C" NTSHENGN_MODULE_API NtshEngn::PlatformModuleInterface* createModule() {
	return new NtshEngn::PlatformModule;
}

extern "C" NTSHENGN_MODULE_API void destroyModule(NtshEngn::PlatformModuleInterface* m) {
	delete m;
}