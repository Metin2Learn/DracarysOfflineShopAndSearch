# Search


		Set(HEADER_GC_DRAGON_SOUL_REFINE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
		Set(HEADER_GC_SHOPSEARCH_SET, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSearchItemSet), STATIC_SIZE_PACKET));
#endif
