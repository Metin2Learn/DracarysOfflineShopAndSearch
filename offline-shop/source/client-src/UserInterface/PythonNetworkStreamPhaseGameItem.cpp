# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
bool CPythonNetworkStream::SendOfflineShopEndPacket()
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop packet_shop;
	packet_shop.header = HEADER_CG_OFFLINE_SHOP;
	packet_shop.subheader = SHOP_SUBHEADER_CG_END;

	if (!Send(sizeof(packet_shop), &packet_shop))
	{
		Tracef("SendOfflineShopEndPacket Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopBuyPacket(DWORD vid, BYTE bPos)
{
	if (!__CanActMainInstance())
		return true;

	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_BUY;
	PacketShop.vid = vid;
	PacketShop.pos = bPos;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopBuyPacket Error\n");
		return false;
	}
	//TraceError("SendOfflineShopBuyPacket vid=%d sub=%d",vid,bPos);
	return SendSequence();
}

bool CPythonNetworkStream::SendAddOfflineShopItem(TItemPos bDisplayPos, BYTE bPos, long long lPrice)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_ADD_ITEM;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendAddOfflineShopItem Error\n");
		return false;
	}

	TOfflineShopAddItem pTable;

	pTable.bDisplayPos = bDisplayPos;
	pTable.bPos = bPos;
	pTable.lPrice = lPrice;
	if (!Send(sizeof(TOfflineShopAddItem), &pTable))
	{
		Tracef("SendAddOfflineShopItem Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendRemoveOfflineShopItem(BYTE bPos)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_REMOVE_ITEM;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendRemoveOfflineShopItem Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendRemoveOfflineShopItem Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendOpenShopSlot(BYTE bPos)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_OPEN_SLOT;

	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOpenShopSlot Error\n");
		return false;
	}

	if (!Send(sizeof(BYTE), &bPos))
	{
		Tracef("SendOpenShopSlot Packet Error\n");
		return false;
	}

	return SendSequence();
}

bool CPythonNetworkStream::SendGetBackItems()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_GET_ITEM;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOpenShopSlot Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendAddTime()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_ADD_TIME;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOpenShopSlot Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendDestroyOfflineShop()
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendDestroyOfflineShop Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendTakeOfflineMoney()
{
	static DWORD s_LastTime = timeGetTime() - 5001;
	if (timeGetTime() - s_LastTime < 5000)
		return true;
	s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_TAKE_MONEY;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendRefreshOfflineShopMoney Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopChangeTitle(const char* title)
{
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHANGE_TITLE;
	strcpy(PacketShop.title, title);
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopChangeTitle Packet Error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopCheck()
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
		//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHECK;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopButton()
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_BUTTON;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopRemoveLogs()
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_LOG_REMOVE;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopCheck Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineOpenWithVID(DWORD vid)
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_OPEN_WITH_VID;
	PacketShop.vid = vid;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineOpenWithVID Packet error\n");
		return false;
	}
	return SendSequence();
}

bool CPythonNetworkStream::SendOfflineShopChangeDecoration(const char* sign, DWORD vnum, DWORD type)
{
	//static DWORD s_LastTime = timeGetTime() - 5001;
	//if (timeGetTime() - s_LastTime < 5000)
	//	return true;
	//s_LastTime = timeGetTime();
	TPacketCGShop PacketShop;
	PacketShop.header = HEADER_CG_OFFLINE_SHOP;
	PacketShop.subheader = SHOP_SUBHEADER_CG_CHANGE_DECORATION;
	if (!Send(sizeof(TPacketCGShop), &PacketShop))
	{
		Tracef("SendOfflineShopChangeDecoration Packet error\n");
		return false;
	}

	TShopDecoration p;
	snprintf(p.sign, sizeof(p.sign), sign);
	p.vnum = vnum;
	p.type = type;
	if (!Send(sizeof(TShopDecoration), &p))
	{
		Tracef("SendOfflineShopChangeDecoration Packet Error\n");
		return false;
	}

	return SendSequence();
}
#endif

