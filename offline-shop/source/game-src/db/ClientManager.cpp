# Search

		default:
			sys_err("Unknown header (header: %d handle: %d length: %d)", header, dwHandle, dwLength);
			break;

# Add before

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		case HEADER_GD_OFFLINESHOP:
			RecvPackets(data);
			break;
#endif


# Search

	peer->EncodeWORD(sizeof(tAdminInfo));
	peer->EncodeWORD(vAdmin.size());

	for (size_t n = 0; n < vAdmin.size(); ++n)
	{
		peer->Encode(&vAdmin[n], sizeof(tAdminInfo));
		sys_log(0, "Admin name %s ConntactIP %s", vAdmin[n].m_szName, vAdmin[n].m_szContactIP);
	}


# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	peer->EncodeWORD(sizeof(TOfflineShop));
	std::vector<TOfflineShop> offlineshop;
	offlineshop.clear();

	for (auto it = m_Offlineshop.begin(); it != m_Offlineshop.end(); it++)
	{
		TOfflineShop p;
		memcpy(&p, it->second, sizeof(TOfflineShop));
		offlineshop.push_back(p);
	}
	peer->EncodeWORD(offlineshop.size());
	peer->Encode(&offlineshop[0], sizeof(TOfflineShop) * offlineshop.size());
#endif

# Search

	sys_log(0, "sizeof(tAdminInfo) = %d * %d ", sizeof(tAdminInfo) * vAdmin.size());

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	sys_log(0, "sizeof(TOfflineShop) = %d ", sizeof(TOfflineShop));
#endif

# Search

	sizeof(WORD) + sizeof(WORD) + sizeof(tAdminInfo) * vAdmin.size() +

# Add afer

#ifdef ENABLE_OFFLINESHOP_SYSTEM
		sizeof(WORD) + sizeof(WORD) + sizeof(TOfflineShop) * m_Offlineshop.size() +
#endif

# Search this function


void CClientManager::Destroy()

# Add in

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	for (auto it = m_Offlineshop.begin(); it != m_Offlineshop.end(); ++it) {
		if (it->second) {
			char szQuery[1024];
			snprintf(szQuery, sizeof(szQuery), "UPDATE player.offline_shop_npc SET time = %d WHERE owner_id = %u",it->second->time, it->second->owner_id);
			std::unique_ptr<SQLMsg> pMsg(CDBManager::instance().DirectQuery(szQuery));
			delete it->second;
		}
	}
	m_Offlineshop.clear();
#endif

