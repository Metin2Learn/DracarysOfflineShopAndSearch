# Search


		Set(HEADER_GC_DRAGON_SOUL_REFINE, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCDragonSoulRefine), STATIC_SIZE_PACKET));

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		Set(HEADER_GC_OFFLINE_SHOP, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShop), DYNAMIC_SIZE_PACKET));
		Set(HEADER_GC_OFFLINE_SHOP_SIGN, CNetworkPacketHeaderMap::TPacketType(sizeof(TPacketGCShopSign), STATIC_SIZE_PACKET));
#endif
