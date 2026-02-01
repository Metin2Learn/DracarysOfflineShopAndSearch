# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
#include "offlineshop_manager.h"
#endif




# Search

	case HEADER_DG_RESPOND_CHANNELSTATUS:
		RespondChannelStatus(DESC_MANAGER::instance().FindByHandle(m_dwHandle), c_pData);
		break;

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	case HEADER_DG_OFFLINESHOP:
		COfflineShopManager::Instance().RecvPackets(c_pData);
		break;
#endif

# Search

	CMotionManager::instance().Build();

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	for (DWORD i = 0; i < cache_data.size(); i++)
		COfflineShopManager::Instance().CreateOfflineShop(&cache_data[i]);
#endif

# Search

for (int n = 0; n < adminsize; ++n)
	{
		tAdminInfo& rAdminInfo = *(tAdminInfo*)data;

		gm_new_insert(rAdminInfo);

		data += sizeof(rAdminInfo);
	}

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	if (decode_2bytes(data) != sizeof(TOfflineShop))
	{
		sys_err("offlineshop table size error");
		thecore_shutdown();
		return;
	}
	data += 2;

	size = decode_2bytes(data);
	data += 2;

	std::vector<TOfflineShop> cache_data;
	cache_data.clear();
	cache_data.resize(size);
	thecore_memcpy(&cache_data[0], (TOfflineShop*)data, sizeof(TOfflineShop)* size);

	data += size * sizeof(TOfflineShop);
#endif

# Search

	sys_log(0, "sizeof(TAdminManager) = %d", sizeof(TAdminInfo));

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	sys_log(0, "sizeof(TOfflineShop) = %d", sizeof(TOfflineShop));
#endif

