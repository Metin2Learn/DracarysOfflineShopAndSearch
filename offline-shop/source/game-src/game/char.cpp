
# Add 

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offline_shop.h"
#include "offlineshop_manager.h"
#endif

/

# Search

	m_pkPartyRequestEvent = NULL;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	m_pkOfflineShop = NULL;
	isOfflineShopPanelOpen = false;
	m_protection_Time.clear();
#endif


# Search

		if (m_pkExchange)
			m_pkExchange->Cancel();

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		if (GetOfflineShop())
			COfflineShopManager::Instance().StopShopping(this);
#endif

# Search


if (entity->IsType(ENTITY_CHARACTER) && GetDesc())

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	if (IsOfflineShopNPC())
	{
		LPOFFLINESHOP shop = GetOfflineShop();
		if (shop)
		{
			TPacketGCShopSign p;
			p.bHeader = HEADER_GC_OFFLINE_SHOP_SIGN;
			p.dwVID = GetVID();
			strlcpy(p.szSign, shop->GetShopSign(), sizeof(p.szSign));
			d->Packet(&p, sizeof(TPacketGCShopSign));
		}
	}
#endif


# Search

tab.horse = GetHorseData();

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	tab.shopFlag = GetOfflineShopFlag();
#endif

# Search


if (GetParty() != NULL)
	{
		GetParty()->UpdateOfflineState(GetPlayerID());
	}

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	if (GetOfflineShop())
	{
		GetOfflineShop()->RemoveGuest(this);
		SetOfflineShop(NULL);
	}
#endif

# Search

	SetXYZ(t->x, t->y, t->z);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	SetOfflineShopFlag(t->shopFlag);
#endif


# Search

	pkChrCauser->SetQuestNPCID(GetVID());

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	if (IsOfflineShopNPC())
	{
		if (pkChrCauser->CanOpenOfflineShop())
			return;
		GetOfflineShop()->AddGuest(pkChrCauser, this);
		return;
	}
#endif

# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
void CHARACTER::SetProtectTime(const std::string& flagname, int value)
{
	itertype(m_protection_Time) it = m_protection_Time.find(flagname);
	if (it != m_protection_Time.end())
		it->second = value;
	else
		m_protection_Time.insert(make_pair(flagname, value));
}
int CHARACTER::GetProtectTime(const std::string& flagname) const
{
	itertype(m_protection_Time) it = m_protection_Time.find(flagname);
	if (it != m_protection_Time.end())
		return it->second;
	return 0;
}


bool CHARACTER::CheckWindows(bool bChat)
{
	if (GetExchange() || GetShop() || GetSafebox() || GetCube() || IsAcceWindowOpen()|| GetOfflineShop() || GetOfflineShopPanel()|| GetChangeLook())
	{
		if(bChat)
			ChatPacket(CHAT_TYPE_INFO, LC_TEXT("CLOSE_OTHER_WINDOWS"));
		return true;
	}
	return false;
}

bool CHARACTER::CanAddItemShop()
{
	time_t now = get_global_time();
	if (GetProtectTime("offlineshop.additem") > get_global_time())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.additem") - now);
		return true;
	}
	SetProtectTime("offlineshop.additem", now + 1);

	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		sys_log(0, "COfflineShopManager::AddItem: adding item with timed event xD %s:%d", GetName(), GetPlayerID());
		return true;
	}
	else if (!GetOfflineShop())
	{
		sys_log(0, "COfflineShopManager::AddItem: adding item without panel <?> %s:%d", GetName(), GetPlayerID());
		return true;
	}
	return false;
}

bool CHARACTER::CanDestroyShop()
{
	time_t now = get_global_time();
	if (GetProtectTime("offlineshop.destroy") > get_global_time())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.destroy") - now);
		return true;
	}
	
	SetProtectTime("offlineshop.destroy", now + 3);
	if (!GetOfflineShop())
		return true;
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	return false;
}

bool CHARACTER::CanRemoveItemShop()
{
	time_t now = get_global_time();
	if (GetProtectTime("offlineshop.remove") > get_global_time())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.remove")-now);
		return true;
	}
	SetProtectTime("offlineshop.remove", now + 1);
	if (!GetOfflineShop())
		return true;
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	return false;
}


bool CHARACTER::CanCreateShop()
{
	if (!GetOfflineShopPanel())
		return true;
	SetOfflineShopPanel(false);
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.create") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.create")-time);
		return true;
	}
	SetProtectTime("offlineshop.create", time + 10);
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	if (GetGold() < 2000000)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_CREATE_YANG"),2000000);
		return true;
	}
	else if (GetDungeon())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_CANT_CREATE_IN_DUNGEON"));
		return true;
	}
	else if (COfflineShopManager::Instance().HasOfflineShop(this) == true)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_ALREADY_HAVE_SHOP"));
		return true;
	}
	return false;
}

bool CHARACTER::CanRemoveLogShop()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.log") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.log") - time);
		return true;
	}
	SetProtectTime("offlineshop.log", time + 30);

	return false;
}

bool CHARACTER::CanWithdrawMoney()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.money") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.money") - time);
		return true;
	}
	SetProtectTime("offlineshop.money", time + 5);
	return false;
}

bool CHARACTER::CanOpenShopPanel()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.panel") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.panel") - time);
		return true;
	}
	SetProtectTime("offlineshop.panel", time + 5);
	if (CheckWindows(true))
		return true;
	return false;
}

bool CHARACTER::CanOpenOfflineShop()
{
	if (m_pkTimedEvent)
		return true;
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.offlineshop") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.offlineshop") - time);
		return true;
	}
	SetProtectTime("offlineshop.offlineshop", time + 1);
	if (CheckWindows(true))
		return true;
	return false;
}

bool CHARACTER::CanChangeTitle()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.title") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.title") - time);
		return true;
	}
	SetProtectTime("offlineshop.title", time + 10);
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	if (!FindAffect(AFFECT_DECORATION))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_DECORATION"));
		return true;
	}
		
	return false;
}

bool CHARACTER::CanBuyItemOfflineShop()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.buy") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.buy") - time);
		return true;
	}
	SetProtectTime("offlineshop.buy", time + 1);
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	return false;
}
bool CHARACTER::CanChangeDecoration()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.decoration") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.decoration") - time);
		return true;
	}
	SetProtectTime("offlineshop.decoration", time + 10);
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	if (!FindAffect(AFFECT_DECORATION))
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_DECORATION"));
		return true;
	}
	return false;
}

bool CHARACTER::CanGetBackItems()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.back") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.back") - time);
		return true;
	}
	SetProtectTime("offlineshop.back", time + 5);
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	return false;
}

bool CHARACTER::CanAddTimeShop()
{
	time_t time = get_global_time();
	if (GetProtectTime("offlineshop.time") > time)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.time") - time);
		return true;
	}
	SetProtectTime("offlineshop.time", time + 10);
	if (m_pkTimedEvent)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_BUG_WITH_TIMED_EVENT"));
		event_cancel(&m_pkTimedEvent);
		return true;
	}
	if (GetGold() < 20000000)
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_CREATE_YANG"),2000000);
		return true;
	}
		
	return false;
}

#endif