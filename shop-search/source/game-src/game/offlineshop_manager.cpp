# Add

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
#include "offline_shop_search.h"
#endif


# Search

	HasOfflineShop(CHARACTER_MANAGER::Instance().FindByPID(offlineshop->owner_id));

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		for (DWORD i = 0; i < OFFLINE_SHOP_HOST_ITEM_MAX_NUM; ++i)
		{
			if (pkOfflineShop->m_data.items[i].vnum == 0 || pkOfflineShop->m_data.items[i].status != 0)
				continue;
			InsertItem(&pkOfflineShop->m_data.items[i]);
		}
#endif

# Search

	thecore_memcpy(&pkOfflineShop->m_data.items[item->pos], item, sizeof(OFFLINE_SHOP_ITEM));

# Add after


#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	InsertItem(&pkOfflineShop->m_data.items[item->pos]);
#endif


# Search

void COfflineShopManager::RemoveItemReal(OFFLINE_SHOP_ITEM* item)
{
	if (!item)
		return;
	LPOFFLINESHOP pkOfflineShop = FindOfflineShopPID(item->owner_id);
	if (!pkOfflineShop)
		return;
	...
}

# Add like this


void COfflineShopManager::RemoveItemReal(OFFLINE_SHOP_ITEM* item)
{
	if (!item)
		return;
	LPOFFLINESHOP pkOfflineShop = FindOfflineShopPID(item->owner_id);
	if (!pkOfflineShop)
		return;
#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	ClearItem(pkOfflineShop->m_data.items[item->pos].id);
#endif
	...
}


# Search

	pkOfflineShop->BroadcastUpdateItem(item->item.pos,false, item->log_index);

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	ClearItem(item->item.id);
#endif


# Search


	for (auto it = m_Map_pkOfflineShopByNPC.begin(); it != m_Map_pkOfflineShopByNPC.end(); it++)
		if (it->second)
			M2_DELETE(it->second);
	m_Map_pkOfflineShopByNPC.clear();

# Add before

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	if (m_pShopTimeEvent)
		event_cancel(&m_pShopTimeEvent);
	m_pShopTimeEvent = NULL;
	
	m_itemMapWeapon.clear();
	m_itemMapEquipment.clear();
	m_itemMapCostume.clear();
	m_itemMapDragonsoul.clear();
	m_itemMapOther.clear();
	m_itemMapPets.clear();
	m_itemMapBook.clear();

	for (auto it = m_itemMap.begin(); it != m_itemMap.end(); it++)
		if (it->second)
			M2_DELETE(it->second);
	m_itemMap.clear();
#endif