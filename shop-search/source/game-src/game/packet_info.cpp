# Search

	Set(HEADER_CG_DRAGON_SOUL_REFINE, sizeof(TPacketCGDragonSoulRefine), "DragonSoulRefine", false);

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	Set(HEADER_CG_SHOP_SEARCH, sizeof(TPacketCGShopSearch), "ShopSearch", false);
#endif
