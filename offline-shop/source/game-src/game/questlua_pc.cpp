# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offlineshop_manager.h"
#endif

# Search

	int pc_compare_map_to_dungeon(lua_State* L)

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	int pc_has_offlineshop(lua_State* L)
	{
		LPCHARACTER ch = CQuestManager::instance().GetCurrentCharacterPtr();
		lua_pushboolean(L, COfflineShopManager::Instance().HasOfflineShop(ch) ? 1 : 0);
		return 1;
	}
#endif


#Search

			{ NULL,			NULL			}

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
			{ "has_offlineshop", pc_has_offlineshop },
#endif