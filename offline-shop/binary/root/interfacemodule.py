# Add

if app.ENABLE_OFFLINESHOP_SYSTEM:
	import uiOfflineShopBuilder
	import uiOfflineShop
	import chr
	import net

# Search

	self.mallPageDlg = None

# Add after

		if app.ENABLE_OFFLINESHOP_SYSTEM:
			self.dlgOfflineShop=None
			self.dlgOfflineShopPanel=None
			self.offlineShopBuilder=None



# Search

		if self.wndItemSelect:
			self.wndItemSelect.Destroy()

# Add after

		if app.ENABLE_OFFLINESHOP_SYSTEM:
			if self.dlgOfflineShop:
				self.dlgOfflineShop.Hide()
				self.dlgOfflineShop.Destroy()
				del self.dlgOfflineShop

			if self.dlgOfflineShopPanel:
				self.dlgOfflineShopPanel.Hide()
				self.dlgOfflineShopPanel.Destroy()
				del self.dlgOfflineShopPanel

			if self.offlineShopBuilder:
				self.offlineShopBuilder.Hide()
				self.offlineShopBuilder.Destroy()
				del self.offlineShopBuilder



# Add


	if app.ENABLE_OFFLINESHOP_SYSTEM:
		def OpenOfflineShopDialog(self, vid, isOwner):
			self.wndInventory.Show()
			self.wndInventory.SetTop()

			if isOwner:
				self.OpenOfflineShopPanel()
			else:
				if self.dlgOfflineShop==None:
					self.MakeOfflineShop()

				if self.dlgOfflineShop:
					self.dlgOfflineShop.Open(vid)
					self.dlgOfflineShop.SetCenterPosition()
					self.dlgOfflineShop.SetTop()

		def OpenOfflineShopPanel(self):
			if self.dlgOfflineShopPanel==None:
				self.MakeOfflineShopPanel()
			self.dlgOfflineShopPanel.Open()
			self.dlgOfflineShopPanel.SetTop()
			self.dlgOfflineShopPanel.SetCenterPosition()

		#def OpenOfflineShopInputNameDialog(self):
		#	import uiOfflineShop
		#	self.inputDialog = uiOfflineShop.OfflineShopInputDialog()
		#	self.inputDialog.SetAcceptEvent(ui.__mem_func__(self.OpenOfflineShopBuilder))
		#	self.inputDialog.SetCancelEvent(ui.__mem_func__(self.CloseOfflineShopInputNameDialog))
		#	self.inputDialog.Open()
		#
		#def CloseOfflineShopInputNameDialog(self):
		#	self.inputDialog.Close()
		#	self.inputDialog = None
		#	return True

		def OpenOfflineShopBuilder(self):
			#if (not self.inputDialog):
			#	return True
			#if (not len(self.inputDialog.GetTitle())):
			#	return True
			#if (self.inputDialog.GetType() < 0 or self.inputDialog.GetType() == 0):
			#	return True
			#self.CloseOfflineShopInputNameDialog()

			if self.offlineShopBuilder==None:
				self.MakeOfflineShopBuilder()
			self.offlineShopBuilder.Open(".....")
			self.offlineShopBuilder.SetTop()

		def DisappearOfflineShop(self, vid):
			uiOfflineShopBuilder.HideADBoardWithKey(vid)

		def AppearOfflineShop(self, vid, text):
			type = 0
			if text[0].isdigit():
				type = int(text[0])
				text = text[1:]
			if uiOfflineShopBuilder.ShowADBoardWithKey(vid) == False:
				board = uiOfflineShopBuilder.OfflineShopAdvertisementBoard(type)
				board.Open(vid, text)
			else:
				uiOfflineShopBuilder.UpdateADText(vid,type,text)

		def MakeOfflineShopBuilder(self):
			self.offlineShopBuilder = uiOfflineShopBuilder.OfflineShopBuilder()
			#self.offlineShopBuilder.SetItemToolTip(self.tooltipItem)
			self.offlineShopBuilder.Hide()

		def MakeOfflineShop(self):
			self.dlgOfflineShop = uiOfflineShop.OfflineShopDialog()
			self.dlgOfflineShop.LoadDialog()
			#self.dlgOfflineShop.SetItemToolTip(self.tooltipItem)
			self.dlgOfflineShop.Hide()

		def MakeOfflineShopPanel(self):
			self.dlgOfflineShopPanel = uiOfflineShop.OfflineMyShop()
			self.dlgOfflineShopPanel.LoadWindow()
			#self.dlgOfflineShopPanel.SetItemToolTip(self.tooltipItem)

		def AppendLogOfflineShopPanel(self,name, date, itemvnum, itemcount, price):
			if self.dlgOfflineShopPanel==None:
				self.MakeOfflineShopPanel()
			self.dlgOfflineShopPanel.AppendLog(name, date, itemvnum, itemcount, price)
		
		def AppendLogOfflineShopPanelFirst(self,name, date, itemvnum, itemcount, price):
			if self.dlgOfflineShopPanel==None:
				self.MakeOfflineShopPanel()
			self.dlgOfflineShopPanel.AppendLogFirst(name, date, itemvnum, itemcount, price)

