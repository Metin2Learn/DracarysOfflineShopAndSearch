
# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offlineshop_manager.h"
#endif

/

# Search

	CloseSafebox();

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		if(GetOfflineShop())
			COfflineShopManager::Instance().StopShopping(this);
#endif

# Done