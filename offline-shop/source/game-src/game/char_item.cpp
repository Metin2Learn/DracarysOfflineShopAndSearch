
# Search

			if (item->GetSubType() == USE_SPECIAL)
			{
				...
			}

# Add in

#ifdef ENABLE_OFFLINESHOP_SYSTEM
				if (item->GetVnum() == 71221)
				{
					if(FindAffect(AFFECT_DECORATION))
					{
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_ALREADY_HAVE_DECORATION"));
						return false;
					}
					else
					{
						AddAffect(AFFECT_DECORATION, POINT_NONE, 0, AFF_NONE, 60*60*24*item->GetValue(0), 0, true); // 1 Gun
						ChatPacket(CHAT_TYPE_INFO, LC_TEXT("OFFLINE_SHOP_DECORATION_DAY"),item->GetValue(0));
						item->SetCount(item->GetCount()-1);
					}
				}
#endif

# Done

