# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offlineshop_manager.h"
#endif


# Search

	DSManager dsManager;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	COfflineShopManager offlineshop_manager;
#endif


# Search

	sys_log(0, "<shutdown> Destroying COXEventManager...");
	OXEvent_manager.Destroy();

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	sys_log(0, "<shutdown> Destroying COfflineShopManager...");
	offlineshop_manager.Initialize();
#endif

