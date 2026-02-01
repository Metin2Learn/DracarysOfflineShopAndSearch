
# Search

		self.isShopItem = FALSE

# Add after

		if app.ENABLE_OFFLINESHOP_SYSTEM:
			self.isOfflineShopItem = False


# Search

	def ClearToolTip(self):
		self.isShopItem = FALSE
		self.isSafeBoxItem = False
		self.toolTipWidth = self.TOOL_TIP_WIDTH
		ToolTip.ClearToolTip(self)

# Add after

	if app.ENABLE_OFFLINESHOP_SYSTEM:
		def SetOfflineShopBuilderItem(self, invenType, invenPos, offlineShopIndex):
			self.ClearToolTip()
			itemVnum = player.GetItemIndex(invenType, invenPos)
			if (itemVnum == 0):
				return
			item.SelectItem(itemVnum)
			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(player.GetItemMetinSocket(invenPos, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(player.GetItemAttribute(invenPos, i))
			self.AddItemData(itemVnum, metinSlot, attrSlot,0,0,0,invenType,invenPos)
			price = shop.GetOfflineShopItemPriceReal(invenType, invenPos)
			if price > 0:
				self.AppendPrice(price)

		def SetOfflineShopItem(self, slotIndex):
			itemVnum = shop.GetOfflineShopItemID(slotIndex)
			if (itemVnum == 0):
				return
			price = shop.GetOfflineShopItemPrice(slotIndex)
			self.ClearToolTip()
			metinSlot = []
			for i in xrange(player.METIN_SOCKET_MAX_NUM):
				metinSlot.append(shop.GetOfflineShopItemMetinSocket(slotIndex, i))
			attrSlot = []
			for i in xrange(player.ATTRIBUTE_SLOT_MAX_NUM):
				attrSlot.append(shop.GetOfflineShopItemAttribute(slotIndex, i))
			if app.WJ_CHANGELOOK_SYSTEM:
				transmutation = shop.GetOfflineShopItemTransmutation(slotIndex)
				if not transmutation:
					transmutation = 0
				self.AddItemData(itemVnum, metinSlot, attrSlot, 0, 0, 0, player.INVENTORY, -1, -1, transmutation)
			else:
				self.AddItemData(itemVnum, metinSlot, attrSlot)
			if price > 0:
				self.AppendPrice(price)
			if shop.GetOfflineShopItemStatus(slotIndex) == 1:
				self.AppendTextLine(localeInfo.OFFLINE_SHOP_ITEM_SOLD, self.DISABLE_COLOR)
				self.AppendTextLine(localeInfo.OFFLINE_SHOP_ITEM_SOLD2 % (shop.GetOfflineShopItemBuyerName(slotIndex)), self.DISABLE_COLOR)
