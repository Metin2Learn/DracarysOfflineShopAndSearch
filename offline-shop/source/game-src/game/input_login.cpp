#Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offlineshop_manager.h"
#endif

# Search

	marriage::CManager::instance().Login(ch);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	COfflineShopManager::Instance().HasOfflineShop(ch);
#endif

