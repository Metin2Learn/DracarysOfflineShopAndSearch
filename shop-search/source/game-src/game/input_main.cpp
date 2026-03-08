# Add


#ifdef ENABLE_SHOP_SEARCH_SYSTEM
void CInputMain::ShopSearch(LPCHARACTER ch, const char* data, bool bName)
{
	if (!ch || !data)
		return;
	if (ch->CanSearch())
		return;
	COfflineShopManager::instance().SearchItem(ch, data, bName);
}
#endif


# Search


	case HEADER_CG_CLIENT_VERSION:
		Version(ch, c_pData);
		break;

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	case HEADER_CG_SHOP_SEARCH:
		ShopSearch(ch, c_pData, false);
		break;
#endif
