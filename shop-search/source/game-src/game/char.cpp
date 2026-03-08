# Add


#ifdef ENABLE_SHOP_SEARCH_SYSTEM
bool CHARACTER::CanSearch()
{
	time_t now = get_global_time();
	if (GetProtectTime("offlineshop.search") > get_global_time())
	{
		ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_OLD_TIME"), GetProtectTime("offlineshop.search")-now);
		return true;
	}
	SetProtectTime("offlineshop.search", now + 1);
	return false;
}
#endif