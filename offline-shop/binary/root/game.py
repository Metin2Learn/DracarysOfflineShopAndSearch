# Add

if app.ENABLE_OFFLINESHOP_SYSTEM:
	import uiOfflineShopBuilder
	import shop


# search

		self.interface = interfaceModule.Interface()


# add after

		constInfo.SetGameInstance(self)
		constInfo.SetInterfaceInstance(self.interface)


# Search

		self.KillFocus()


# add after

		constInfo.SetInterfaceInstance(None)
		constInfo.SetGameInstance(None)


# Search

		wndMgr.Unlock()

# Add after

		if app.ENABLE_OFFLINESHOP_SYSTEM:
			uiOfflineShopBuilder.Clear()
			shop.Clear()


# Search

		self.serverCommander=stringCommander.Analyzer()

# Add before

		if app.ENABLE_OFFLINESHOP_SYSTEM:
			serverCommandList.update({"OpenBackAllItem" : self.OpenBackAllItem })
			serverCommandList.update({"OpenOfflineShop" : self.OpenOfflineShop })
			serverCommandList.update({"RefreshOfflineShop" : self.RefreshOfflineShop })
			serverCommandList.update({"OpenOfflineShopPanel" : self.OpenOfflineShopPanel })
			serverCommandList.update({"ClearOfflineShopLog" : self.ClearOfflineShopLog })
			serverCommandList.update({"AppendShopLog" : self.AppendShopLog })


# Add


	if app.ENABLE_OFFLINESHOP_SYSTEM:
		def StartOfflineShop(self, vid, isOwner):
			if self.interface:
				self.interface.OpenOfflineShopDialog(vid, isOwner)
		def StartOfflineShopPanel(self):
			if self.interface:
				self.interface.OpenOfflineShopPanel()

		def ClearOfflineShopLog(self):
			if self.interface:
				if self.interface.dlgOfflineShopPanel:
					if self.interface.dlgOfflineShopPanel.GetChild("ListBox"):
						self.interface.dlgOfflineShopPanel.GetChild("ListBox").RemoveAllItems()

		def AppendShopLog(self, name, date, itemvnum, itemcount, price):
			self.interface.AppendLogOfflineShopPanel(name, date, itemvnum, itemcount, price)

		def AppendShopLogFirst(self, name, date, itemvnum, itemcount, price):
			self.interface.AppendLogOfflineShopPanelFirst(name, date, itemvnum, itemcount, price)

		def EndOfflineShop(self):
			if self.interface:
				if self.interface.dlgOfflineShop:
					if self.interface.dlgOfflineShop.IsShow():
						self.interface.dlgOfflineShop.Close()
				if self.interface.dlgOfflineShopPanel:
					if self.interface.dlgOfflineShopPanel.IsShow():
						self.interface.dlgOfflineShopPanel.Close()
				if self.interface.offlineShopBuilder:
					if self.interface.offlineShopBuilder.IsShow():
						self.interface.offlineShopBuilder.Close()
		def RefreshOfflineShop(self):
			if self.interface:
				if self.interface.dlgOfflineShop:
					self.interface.dlgOfflineShop.Refresh()
				if self.interface.dlgOfflineShopPanel:
					if self.interface.dlgOfflineShopPanel.IsShow():
						self.interface.dlgOfflineShopPanel.Refresh()
				if self.interface.offlineShopBuilder:
					if self.interface.offlineShopBuilder.IsShow():
						self.interface.offlineShopBuilder.Refresh()
		def OpenOfflineShop(self):
			if self.interface:
				self.interface.OpenOfflineShopBuilder()
		def OpenBackAllItem(self):
			backItem = uiCommon.QuestionDialog()
			backItem.SetText(localeInfo.OFFLINESHOP_GET_BACK_ITEMS) # HELLO WORLD
			backItem.SetAcceptText(localeInfo.UI_ACCEPT)
			backItem.SetCancelText(localeInfo.UI_DENY)
			backItem.SetAcceptEvent(lambda arg=TRUE: self.__AnswerGetBackItems(arg))
			backItem.SetCancelEvent(lambda arg=FALSE: self.__AnswerGetBackItems(arg))
			backItem.Open()
			self.partyRequestQuestionDialog=backItem

		def __AnswerGetBackItems(self, answer):
			if not self.partyRequestQuestionDialog:
				return
			if answer:
				net.SendGetBackItems()
			self.partyRequestQuestionDialog.Close()
			self.partyRequestQuestionDialog = None

		def OpenOfflineShopPanel(self):
			if self.interface:
				self.interface.OpenOfflineShopPanel()
		def BINARY_OfflineShop_Appear(self, vid, text):	
			if (chr.GetInstanceType(vid) == chr.INSTANCE_TYPE_NPC):
				if self.interface:
					self.interface.AppearOfflineShop(vid, text)
			
		def BINARY_OfflineShop_Disappear(self, vid):
			if (chr.GetInstanceType(vid) == chr.INSTANCE_TYPE_NPC):
				if self.interface:
					self.interface.DisappearOfflineShop(vid)
