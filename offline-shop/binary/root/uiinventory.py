# Search

			self.wndItem = self.GetChild("ItemSlot")

# Add after

			if app.ENABLE_OFFLINESHOP_SYSTEM:
				self.OffButton = self.GetChild2("OffButton")
				self.OffButton.SetEvent(ui.__mem_func__(self.ClickOfflineShopButton))
			else:
				self.GetChild2("OffButton").Hide()


# Search

		self.wndItem=None

# Add after

		if app.ENABLE_OFFLINESHOP_SYSTEM:
			self.OffButton = None

# Search

	def SetInventoryPage(self, page):

# Add before

	if app.ENABLE_OFFLINESHOP_SYSTEM:
		def ClickOfflineShopButton(self):
			if self.interface:
				if self.interface.dlgOfflineShopPanel:
					if self.interface.dlgOfflineShopPanel.IsShow():
						self.interface.dlgOfflineShopPanel.CloseReal()
						return
				if self.interface.offlineShopBuilder:
					if self.interface.offlineShopBuilder.IsShow():
						self.interface.offlineShopBuilder.CloseReal()
						return
				net.SendOfflineShopButton()