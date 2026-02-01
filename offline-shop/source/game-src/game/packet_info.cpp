# Search

	Set(HEADER_CG_DRAGON_SOUL_REFINE, sizeof(TPacketCGDragonSoulRefine), "DragonSoulRefine", false);

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	Set(HEADER_CG_OFFLINE_SHOP, sizeof(TPacketCGShop), "OfflineShop", true);
	Set(HEADER_CG_MY_OFFLINE_SHOP, sizeof(TPacketCGMyOfflineShop), "MyOfflineShop", true);
#endif
