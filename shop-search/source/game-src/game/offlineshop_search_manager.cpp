#include "stdafx.h"

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#ifdef ENABLE_SHOP_SEARCH_SYSTEM
#include "utils.h"
#include "config.h"
#include "desc.h"
#include "char.h"
#include "item_manager.h"
#include "packet.h"
#include "offline_shop_search.h"
#include "offlineshop_manager.h"


void COfflineShopManager::SaveInMemory(OFFLINE_SHOP_ITEM* item)
{
	TItemTable * table = ITEM_MANAGER::instance().GetTable(item->vnum);
	if (!table){return;}
	if(table->bType == ITEM_WEAPON)
		m_itemMapWeapon.insert(std::make_pair(item->id, item));
	else if(table->bType == ITEM_ARMOR || table->bType == ITEM_BELT || table->bType == ITEM_PENDANT)
		m_itemMapEquipment.insert(std::make_pair(item->id, item));
	else if(table->bType == ITEM_COSTUME)
	{
		if(table->bSubType == COSTUME_MOUNT || table->bSubType == COSTUME_PET)
			m_itemMapPets.insert(std::make_pair(item->id, item));
		else
			m_itemMapCostume.insert(std::make_pair(item->id, item));
	}
	else if(table->bType == ITEM_DS || (table->bType == ITEM_MATERIAL && table->bSubType == MATERIAL_DS_REFINE_NORMAL))
		m_itemMapDragonsoul.insert(std::make_pair(item->id, item));
	else if(table->bType == ITEM_SKILLBOOK || table->dwVnum == 70037)
		m_itemMapBook.insert(std::make_pair(item->id, item));
	else
		m_itemMapOther.insert(std::make_pair(item->id, item));
}

void COfflineShopManager::RemoveInMemory(OFFLINE_SHOP_ITEM* item)
{
	TItemTable * table = ITEM_MANAGER::instance().GetTable(item->vnum);
	if (!table){return;}
	if(table->bType == ITEM_WEAPON)
	{
		auto it = m_itemMapWeapon.find(item->id);
		if(it!=m_itemMapWeapon.end())
			m_itemMapWeapon.erase(it);
	}

	else if(table->bType == ITEM_ARMOR || table->bType == ITEM_PENDANT || table->bType == ITEM_BELT)
	{
		auto it = m_itemMapEquipment.find(item->id);
		if(it!=m_itemMapEquipment.end())
			m_itemMapEquipment.erase(it);
	}
	else if(table->bType == ITEM_COSTUME)
	{
		if(table->bSubType == COSTUME_PET || table->bSubType == COSTUME_MOUNT)
		{
			auto it2 = m_itemMapPets.find(item->id);
			if(it2!=m_itemMapPets.end())
				m_itemMapPets.erase(it2);
		}
		else
		{
			auto it = m_itemMapCostume.find(item->id);
			if(it!=m_itemMapCostume.end())
				m_itemMapCostume.erase(it);
		}
	}
	else if(table->bType == ITEM_DS || (table->bType == ITEM_MATERIAL && table->bSubType == MATERIAL_DS_REFINE_NORMAL))
	{
		auto it2 = m_itemMapDragonsoul.find(item->id);
		if(it2!=m_itemMapDragonsoul.end())
			m_itemMapDragonsoul.erase(it2);
	}
	else if(table->bType == ITEM_SKILLBOOK || table->dwVnum == 70037)
	{
		auto it = m_itemMapBook.find(item->id);
		if (it != m_itemMapBook.end())
			m_itemMapBook.erase(it);
	}
	else
	{
		auto it = m_itemMapOther.find(item->id);
		if (it != m_itemMapOther.end())
			m_itemMapOther.erase(it);
	}
}

bool ComparePrice(OFFLINE_SHOP_ITEM* i, OFFLINE_SHOP_ITEM* j)
{
	return (i->price < j->price);
}

bool CompareCount(OFFLINE_SHOP_ITEM* i, OFFLINE_SHOP_ITEM* j)
{
	return (i->count < j->count);
}

bool getFilter(TPacketCGShopSearch* pinfo, TItemTable* table, OFFLINE_SHOP_ITEM* item)
{
	if (pinfo->level[0] != 0) // min level
	{ 
		for (int x = 0; x < ITEM_LIMIT_MAX_NUM; ++x)
		{
			if (table->aLimits[x].bType == LIMIT_LEVEL)
			{
				if (table->aLimits[x].lValue < pinfo->level[0])
				{ 
					//sys_err("step 1");
					return false;
					
				} 
			}
		}
	}
	if (pinfo->level[1] != 120) // max level
	{
		for (int x = 0; x < ITEM_LIMIT_MAX_NUM; ++x)
		{
			if (table->aLimits[x].bType == LIMIT_LEVEL)
			{
				if (table->aLimits[x].lValue > pinfo->level[1])
				{
					//sys_err("step 2 %d", pinfo->level[1]);
					return false;
					
				}
			}
		}
	}

	if (table->sAddonType == -1)
	{
		if (pinfo->avg[0] != 0)
		{
			if (item->aAttr[0].bType == APPLY_NORMAL_HIT_DAMAGE_BONUS)
			{
				if (item->aAttr[0].sValue < pinfo->avg[0]) {
					//sys_err("step 3");
					return false;
				}
					
			}
		}

		if (pinfo->avg[1] != 80)
		{
			if (item->aAttr[0].bType == APPLY_NORMAL_HIT_DAMAGE_BONUS)
			{
				if (item->aAttr[0].sValue > pinfo->avg[1]) {
					//sys_err("step 4");
					return false;
				}
			}
		}

		if (pinfo->skill[0] != 0)
		{
			if (item->aAttr[1].bType == APPLY_SKILL_DAMAGE_BONUS)
			{
				if (item->aAttr[1].sValue < pinfo->skill[0]) {
					//sys_err("step 5");
					return false;
				}
					
			}
		}

		if (pinfo->skill[1] != 40)
		{
			if (item->aAttr[1].bType == APPLY_SKILL_DAMAGE_BONUS)
			{
				if (item->aAttr[1].sValue > pinfo->skill[1]) {
					//sys_err("step 6");
					return false;
				}
					
			}
		}
	}

	if (table->bType == ITEM_COSTUME && table->bSubType==COSTUME_ACCE)
	{
		if (pinfo->abs[0] != 0)
		{
			if (item->alSockets[0] < pinfo->abs[0]) {
				//sys_err("step x6x");
				return false;
			}
		}
		if (pinfo->abs[1] != 40)
		{
			if (item->alSockets[0] > pinfo->abs[1]) {
				//sys_err("step 6x");
				return false;
			}
		}
	}


	if (pinfo->sex != 0)
	{
		if (pinfo->sex == 1) { if (IS_SET(table->dwAntiFlags, ITEM_ANTIFLAG_FEMALE)) { 
			//sys_err("step 7"); 
			return false; } }
		if (pinfo->sex == 2) { if (IS_SET(table->dwAntiFlags, ITEM_ANTIFLAG_MALE)) { 
			//sys_err("step 8"); 
			return false; } }
	}

	if (pinfo->enchant != 0)
	{
		if (pinfo->enchant == 1) { if (item->aAttr[0].bType >= 1) { 
			//sys_err("step 9"); 
			return false; } }
		if (pinfo->enchant == 2) { if (item->aAttr[0].bType < 1) { 
			//sys_err("step 10"); 
			return false; } }
	}

	if (table->bType == ITEM_DS)
	{
		if (pinfo->alchemy != 0 && table->bSubType != pinfo->alchemy) {
			//sys_err("step 11"); 
			return false; }
	}

	if (pinfo->character != 0)
	{
		if (pinfo->character == 1)//warrior
		{
			if (table->dwAntiFlags & ITEM_ANTIFLAG_WARRIOR) {
				//sys_err("step 12");
				return false;
			}
				
		}
		else if (pinfo->character == 2)//assassin
		{
			if (table->dwAntiFlags & ITEM_ANTIFLAG_ASSASSIN) {
				//sys_err("step 13");
				return false;
			}
		}
		else if (pinfo->character == 3)//shaman
		{
			if (table->dwAntiFlags & ITEM_ANTIFLAG_SHAMAN) {
				//sys_err("step 14");
				return false;
			}
				
		}
		else if (pinfo->character == 4)//sura
		{
			if (table->dwAntiFlags & ITEM_ANTIFLAG_SURA) {
				//sys_err("step 15");
				return false;
			}
		}
	}
	return true;
}

bool COfflineShopManager::getMap(TPacketCGShopSearch* pinfo, std::unordered_map<DWORD, OFFLINE_SHOP_ITEM*>::iterator& it, std::unordered_map<DWORD, OFFLINE_SHOP_ITEM*>::iterator& itend)
{
	if (pinfo->Value == 0) // button type&subtype search...
	{
		if (pinfo->ItemCat == 0)
		{
			it = m_itemMapWeapon.begin();
			itend = m_itemMapWeapon.end();
		}
		else if (pinfo->ItemCat == 1)
		{
			it = m_itemMapEquipment.begin();
			itend = m_itemMapEquipment.end();
		}
		else if (pinfo->ItemCat == 2)
		{
			it = m_itemMapCostume.begin();
			itend = m_itemMapCostume.end();
		}
		else if (pinfo->ItemCat == 3)
		{
			it = m_itemMapDragonsoul.begin();
			itend = m_itemMapDragonsoul.end();
		}
		else if (pinfo->ItemCat == 4)
		{
			it = m_itemMapOther.begin();
			itend = m_itemMapOther.end();
		}
		else if (pinfo->ItemCat == 5)
		{
			it = m_itemMapBook.begin();
			itend = m_itemMapBook.end();
		}
		else if (pinfo->ItemCat == 6)
		{
			it = m_itemMapPets.begin();
			itend = m_itemMapPets.end();
		}
		else
			return false;
	}
	else
		return false;
	return true;
}

void COfflineShopManager::SearchItem(LPCHARACTER ch, const char * data, bool bVnum)
{
	if(!ch || !data)
		return;
	TPacketCGShopSearch* pinfo = (TPacketCGShopSearch *)data;
	bVnum = pinfo->itemVnum != 0 ? true : false;
	if ((pinfo->ItemCat < ITEM_NONE || pinfo->ItemCat > ITEM_PENDANT)
		|| (pinfo->avg[0] < 0 || pinfo->avg[0] > 80)
		|| (pinfo->avg[1] < 0 || pinfo->avg[1] > 80)
		|| (pinfo->skill[0] < 0 || pinfo->skill[0] > 40)
		|| (pinfo->skill[1] < 0 || pinfo->skill[1] > 40)
		|| (pinfo->abs[0] < 0 || pinfo->abs[0] > 40)
		|| (pinfo->abs[1] < 0 || pinfo->abs[1] > 40)
		|| (pinfo->level[0] < 0 || pinfo->level[0] > PLAYER_MAX_LEVEL_CONST)
		|| (pinfo->level[1] < 0 || pinfo->level[1] > PLAYER_MAX_LEVEL_CONST)
		|| (pinfo->refine[0] < 0 || pinfo->refine[0] > 200)
		|| (pinfo->refine[1] < 0 || pinfo->refine[1] > 200)
		|| (pinfo->sex < 0 || pinfo->sex > 2)
		|| (pinfo->enchant < 0 || pinfo->enchant > 2)
		|| (pinfo->alchemy < 0 || pinfo->alchemy > 7)
		)
		return;

	std::vector<OFFLINE_SHOP_ITEM*> sendItems;
	std::unordered_map<DWORD, OFFLINE_SHOP_ITEM*>::iterator it;
	std::unordered_map<DWORD, OFFLINE_SHOP_ITEM*>::iterator itend;

	if (bVnum)
	{
		it = m_itemMap.begin();
		for (; it != m_itemMap.end(); ++it)
		{
			if (sendItems.size() >= 50)
			{
				break;
			}
			OFFLINE_SHOP_ITEM* item = it->second;
			if (!item)
				continue;
			if (pinfo->itemVnum == 50300)
			{
				if (!(item->vnum == pinfo->itemVnum && pinfo->Value == item->alSockets[0]))
					continue;
			}
			else if(pinfo->Value != 0)
			{
				if(!(pinfo->itemVnum-pinfo->Value <= item->vnum && pinfo->itemVnum >= item->vnum))
					continue;
			}
			else
			{
				if (item->vnum != pinfo->itemVnum)
					continue;
			}

			TItemTable* table = ITEM_MANAGER::instance().GetTable(item->vnum);
			if (!table)
				continue;
			if (getFilter(pinfo, table, item))
				sendItems.push_back(item);
		}
	}
	else
	{
		if (getMap(pinfo, it, itend))
		{
			for (; it != itend; ++it)
			{
				if (sendItems.size() >= 50)
				{
					break;
				}
				OFFLINE_SHOP_ITEM* item = it->second;
				if (!item)
					continue;
				TItemTable* table = ITEM_MANAGER::instance().GetTable(item->vnum);
				if (!table)
					continue;
				if (getFilter(pinfo, table, item))
					sendItems.push_back(item);
			}
		}
	}

	if (sendItems.size() > 0)
	{
		std::stable_sort(sendItems.begin(), sendItems.end(), ComparePrice);
		std::stable_sort(sendItems.begin(), sendItems.end(), CompareCount);
		TPacketGCShopSearchItemSet pack;
		pack.header = HEADER_GC_SHOPSEARCH_SET;
		pack.count = sendItems.size();
		for (BYTE j = 0; j < sendItems.size(); j++)
		{
			OFFLINE_SHOP_ITEM*& item = sendItems[j];
			if (item->vnum == 0)
				continue;
			pack.items[j].vnum = item->vnum;
			pack.items[j].price = item->price;
			pack.items[j].count = item->count;
			pack.items[j].display_pos = item->pos;
			pack.items[j].owner_id = item->owner_id;
			pack.items[j].status = 0;
			thecore_memcpy(&pack.items[j].alSockets, &item->alSockets, sizeof(pack.items[j].alSockets));
			thecore_memcpy(&pack.items[j].aAttr, &item->aAttr, sizeof(pack.items[j].aAttr));
			strlcpy(pack.items[j].szBuyerName, item->szOwnerName, sizeof(pack.items[j].szBuyerName));
#ifdef ENABLE_CHANGELOOK_SYSTEM
			pack.items[j].transmutation = item->transmutation;
#endif
#ifdef ENABLE_NEW_NAME_ITEM
			strlcpy(pack.items[j].name, item->name, sizeof(pack.items[j].name));
#endif
#ifdef ENABLE_PERMA_ITEM
			pack.items[j].perma = item->perma;
#endif
		}
		ch->GetDesc()->Packet(&pack, sizeof(TPacketGCShopSearchItemSet));
	}

	/*
	if (bVnum)
		sys_log(0, "SHOP_SEARCH: CharName: %s Search: Cat: %d SubCat: %d MaxRefine: %d MinLevel: %d MaxLevel: %d Enchant : %d alchemySub: %d Sex: %d Value: %d itemVnum: %d ", ch->GetName(), pinfo->ItemCat, pinfo->SubCat, pinfo->MaxRefine,pinfo->MinLevel,pinfo->MaxLevel,pinfo->Enchant,pinfo->alchemySub,pinfo->Sex,pinfo->Value,pinfo->itemVnum);
	else
		sys_log(0, "SHOP_SEARCH: CharName: %s Search: Cat: %d SubCat: %d MaxRefine: %d MinLevel: %d MaxLevel: %d Enchant : %d alchemySub: %d Sex: %d Value: %d  ", ch->GetName(), pinfo->ItemCat, pinfo->SubCat, pinfo->MaxRefine,pinfo->MinLevel,pinfo->MaxLevel,pinfo->Enchant,pinfo->alchemySub,pinfo->Sex,pinfo->Value);
	*/
}

void COfflineShopManager::ClearItem(DWORD id)
{
	auto it = m_itemMap.find(id);
	if (it != m_itemMap.end()) {
		OFFLINE_SHOP_ITEM* item = it->second;
		RemoveInMemory(item);
		m_itemMap.erase(it);
		M2_DELETE(item);
	}
}

void COfflineShopManager::InsertItem(OFFLINE_SHOP_ITEM* p)
{
	auto it = m_itemMap.find(p->id);
	if (it != m_itemMap.end()){
		sys_err("wtf have 2 id in game? item id %u",p->id);
		return;
	}
	OFFLINE_SHOP_ITEM* item = new OFFLINE_SHOP_ITEM;
	thecore_memcpy(item, p, sizeof(OFFLINE_SHOP_ITEM));
	m_itemMap.insert(std::make_pair(p->id, item));
	SaveInMemory(item);
}

#endif
#endif

