# Add


#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offline_shop.h"
#include "offlineshop_manager.h"
int CInputMain::MyOfflineShop(LPCHARACTER ch, const char* c_pData, size_t uiBytes)
{
	TPacketCGMyOfflineShop* p = (TPacketCGMyOfflineShop*)c_pData;
	int iExtraLen = p->bCount * sizeof(TOfflineShopItemTable);
	if (uiBytes < sizeof(TPacketCGMyOfflineShop) + iExtraLen)
		return -1;
	COfflineShopManager::instance().OpenMyOfflineShop(ch, p->szSign, (TOfflineShopItemTable*)(c_pData + sizeof(TPacketCGMyOfflineShop)), p->bCount, p->shopVnum, p->shopTitle);
	return (iExtraLen);
}
int CInputMain::OfflineShop(LPCHARACTER ch, const char* data, size_t uiBytes)
{
	TPacketCGShop* p = (TPacketCGShop*)data;
	if (uiBytes < sizeof(TPacketCGShop))
		return -1;
	if (!ch || !ch->GetDesc())
		return -1;
	const char* c_pData = data + sizeof(TPacketCGShop);
	uiBytes -= sizeof(TPacketCGShop);
	switch (p->subheader)
	{
	case SHOP_SUBHEADER_CG_END:
		COfflineShopManager::instance().StopShopping(ch);
		break;
	case SHOP_SUBHEADER_CG_BUY:
		COfflineShopManager::instance().Buy(ch, p->vid, p->pos);
		break;
	case SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP:
		COfflineShopManager::instance().DestroyOfflineShop(ch);
		break;
	case SHOP_SUBHEADER_CG_ADD_ITEM:
	{
		if (uiBytes < sizeof(TOfflineShopAddItem))
			return -1;
		TOfflineShopAddItem* pTable = (TOfflineShopAddItem*)(c_pData);
		COfflineShopManager::instance().AddItem(ch, pTable->bDisplayPos, pTable->bPos, pTable->lPrice);
		return (sizeof(TOfflineShopAddItem));
	}
	case SHOP_SUBHEADER_CG_REMOVE_ITEM:
	{
		if (uiBytes < sizeof(BYTE))
			return -1;
		BYTE bPos = *c_pData;
		COfflineShopManager::instance().RemoveItem(ch, bPos);
		return (sizeof(BYTE));
	}
	case SHOP_SUBHEADER_CG_OPEN_SLOT:
	{
		if (uiBytes < sizeof(BYTE))
			return -1;
		BYTE bPos = *c_pData;
		COfflineShopManager::instance().OpenSlot(ch, bPos);
		return (sizeof(BYTE));
	}
	case SHOP_SUBHEADER_CG_CHECK:
		COfflineShopManager::instance().HasOfflineShop(ch);
		break;
	case SHOP_SUBHEADER_CG_CHANGE_TITLE:
		COfflineShopManager::instance().ChangeTitle(ch, p->title);
		break;
	case SHOP_SUBHEADER_CG_TAKE_MONEY:
		COfflineShopManager::instance().WithdrawMoney(ch);
		break;
	case SHOP_SUBHEADER_CG_CHANGE_DECORATION:
	{
		if (uiBytes < sizeof(TShopDecoration))
			return -1;
		TShopDecoration* decoration = (TShopDecoration*)(c_pData);
		COfflineShopManager::instance().ChangeDecoration(ch, decoration);
		return (sizeof(TShopDecoration));
	}
	break;
	case SHOP_SUBHEADER_CG_LOG_REMOVE:
		COfflineShopManager::instance().ShopLogRemove(ch);
		break;
	case SHOP_SUBHEADER_CG_BUTTON:
		COfflineShopManager::instance().OpenOfflineShop(ch);
		break;
	case SHOP_SUBHEADER_CG_GET_ITEM:
		COfflineShopManager::instance().GetBackItem(ch);
		break;
	case SHOP_SUBHEADER_CG_ADD_TIME:
		COfflineShopManager::instance().ShopAddTime(ch);
		break;
	case SHOP_SUBHEADER_CG_OPEN_WITH_VID:
		COfflineShopManager::instance().OpenOfflineShopWithVID(ch, p->vid);
		break;
	default:
		sys_err("CInputMain::OfflineShop : Unknown subheader %d : %s", p->subheader, ch->GetName());
		break;
	}

	return 0;
}
#endif



# Search


	case HEADER_CG_CLIENT_VERSION:
		Version(ch, c_pData);
		break;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	case HEADER_CG_OFFLINE_SHOP:
		if ((iExtraLen = OfflineShop(ch, c_pData, m_iBufferLeft)) < 0)
			return -1;
		break;
	case HEADER_CG_MY_OFFLINE_SHOP:
		if ((iExtraLen = MyOfflineShop(ch, c_pData, m_iBufferLeft)) < 0)
			return -1;
		break;
#endif

