# Search

	if (!InitializeLandTable())
	{
		sys_err("InitializeLandTable FAILED");
		return false;
	}

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	if (!InitializeOfflineShop())
	{
		sys_err("InitializeOfflineShop FAILED");
		return false;
	}
#endif