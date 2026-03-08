
# Search

		self.RegisterWindow(layer)

# Add after

		self.exPos = (0,0)

# Search

	def SetPosition(self, x, y):
		wndMgr.SetWindowPosition(self.hWnd, x, y)

# Change

	def SetPosition(self, x, y, flag = False):
		if flag == True:
			self.exPos = (x,y)
		wndMgr.SetWindowPosition(self.hWnd, x, y)


# Search 

class ImageBox(Window):


# Add in

	def LoadImageInstance(self, image):
		wndMgr.LoadImageInstance(self.hWnd, image)

# Search

			elif Type == "listbox":
				parent.Children[Index] = ListBox()
				parent.Children[Index].SetParent(parent)
				self.LoadElementListBox(parent.Children[Index], ElementValue, parent)

# Add after


			elif Type == "listbox_new":
				parent.Children[Index] = ListBoxNew()
				parent.Children[Index].SetParent(parent)
				self.LoadElementListBox(parent.Children[Index], ElementValue, parent)


# Search

	self.eventReturn = Window.NoneMethod

# Add after

	self.eventKeyUp = Window.NoneMethod


# Search in editline

	def OnKeyUp(self, key):

# add after

		if self.eventKeyUp != Window.NoneMethod:
			self.eventKeyUp()
			return True

# Add in Editline class

	def SetKeyUpEvent(self, event):
		self.eventKeyUp = event



# Search

		self.bCodePage = FALSE

# Add after

		self.infoMsg = ""
		self.backText=None
		self.isNeedEmpty=True

# Search

		self.candidateWindowClassDict = 0

# Add after

		self.infoMsg = ""
		self.backText=None
		self.isNeedEmpty=False


# Search

	def SetCodePage(self, codePage):
		candidateWindowClass=EditLine.candidateWindowClassDict.get(codePage, EmptyCandidateWindow)
		self.__SetCandidateClass(candidateWindowClass)

# add after

	def SetInfoMessage(self, msg):
		self.infoMsg = msg
		if self.backText == None:
			self.backText = TextLine()
			self.backText.SetParent(self)
			self.backText.SetPosition(0,0)
			self.backText.SetFontColor(128,128,128)

		self.backText.SetText(msg)

		if self.isNeedEmpty:
			if len(self.GetText()) > 0:
				self.backText.Hide()
			else:
				self.backText.Show()
		else:
			self.backText.Show()


# Search

	def OnIMEUpdate(self):

# Change

	def OnIMEUpdate(self):
		snd.PlaySound("sound/ui/type.wav")
		TextLine.SetText(self, ime.GetText(self.bCodePage))
		
		if self.backText:
			if self.isNeedEmpty:
				if len(self.GetText()) > 0:
					self.backText.Hide()
				else:
					self.backText.Show()
			else:
				self.backText.Show()


# Add

def calculateRect(curValue, maxValue):
	try:
		return -1.0 + float(curValue) / float(maxValue)
	except:
		return 0.0

class ListBoxNew(Window):
	def __init__(self, isHorizontal = False):
		Window.__init__(self)
		self.viewItemCount=10
		self.basePos=0
		self.itemHeight=16
		self.itemStep=20
		self.selItem=0
		self.itemList=[]
		self.onSelectItemEvent = lambda *arg: None
		self.itemWidth=100
		self.scrollBar=None
		self.isHorizontal= isHorizontal

	def __del__(self):
		Window.__del__(self)

	def __UpdateSize(self):
		height=self.itemStep*self.__GetViewItemCount()
		pass
		#self.SetSize(self.itemWidth, height)

	def GetItemIndex(self, argItem):
		return self.itemList.index(argItem)

	def GetSelectedItem(self):
		return self.selItem

	def IsEmpty(self):
		if self.__GetItemCount()==0:
			return 1
		return 0

	def __GetViewItemCount(self):
		return self.viewItemCount

	def __GetItemCount(self):
		return len(self.itemList)

	def SetItemStep(self, itemStep):
		self.itemStep=itemStep

	def SetItemSize(self, itemWidth, itemHeight):
		self.itemWidth=itemWidth
		self.itemHeight=itemHeight

	def SetViewItemCount(self, viewItemCount):
		self.viewItemCount=viewItemCount

	def SetSelectEvent(self, event):
		self.onSelectItemEvent = event

	def SelectIndex(self, index):
		if index >= len(self.itemList) or index < 0:
			self.selItem = None
			return
		try:
			self.selItem=self.itemList[index]
		except:
			pass

	def SelectItem(self, selItem):
		self.selItem=selItem
		self.onSelectItemEvent(selItem)

	def RemoveAllItems(self):
		self.selItem=None
		for item in self.itemList:
			item.Destroy()
		self.itemList=[]
		if self.scrollBar:
			self.scrollBar.SetPos(0)

	def GetItems(self):
		return self.itemList

	def RemoveItem(self, delItem):
		if delItem==self.selItem:
			self.selItem=None
		self.itemList.remove(delItem)

	def AppendItem(self, newItem):
		self.itemList.append(newItem)

	def SetScrollBar(self, scrollBar):
		scrollBar.SetScrollEvent(__mem_func__(self.__OnScroll))
		self.scrollBar=scrollBar

	def OnMouseWheel(self, nLen):
		if self.scrollBar:
			if self.scrollBar.IsShow():
				if nLen > 0:
					self.scrollBar.OnUp()
				else:
					self.scrollBar.OnDown()
				return True
		return False

	def __OnScroll(self):
		self.SetBasePos(int(self.scrollBar.GetPos()*self.__GetScrollLen()))

	def __GetScrollLen(self):
		if self.__GetItemCount() == 0:
			return 0
		(lx,ly) = self.itemList[len(self.itemList)-1].exPos
		return ly

	def GetItemViewCoord(self, pos, itemWidth):
		return (0, (pos-self.basePos)*self.itemStep)

	def __IsInViewRange(self, pos):
		if pos<self.basePos:
			return 0
		if pos>=self.basePos+self.viewItemCount:
			return 0
		return 1

	def Render(self,basePos):
		for item in self.itemList:
			(ex,ey) = item.exPos
			if self.isHorizontal:
				item.SetPosition(ex-(basePos),ey)
			else:
				item.SetPosition(ex,ey-(basePos))
			item.OnRender()

	def SetBasePos(self, basePos):
		if self.basePos == basePos:
			return
		self.Render(basePos)
		self.basePos=basePos


class DropdownTree(Window):
	class Item(Window):
		def __init__(self):
			Window.__init__(self)
			self.id = -1
			self.parentId = -1
			self.offset = 0
			self.visible = False
			self.expanded = False
			self.event = None
			self.onCollapseEvent = None
			self.onExpandEvent = None

		def __del__(self):
			Window.__del__(self)

		def Destroy(self):
			self.id = 0
			self.parentId = 0
			self.offset = 0
			self.visible = 0
			self.expanded = 0
			self.event = 0
			self.onCollapseEvent = 0
			self.onExpandEvent = 0
			self.parent = 0

		def SetParent(self, parent):
			Window.SetParent(self, parent)
			self.parent=proxy(parent)

		def SetSize(self, width, height):
			Window.SetSize(self, width, height)

		def GetId(self):
			return self.id

		def SetId(self, id):
			self.id = id

		def GetParentId(self):
			return self.parentId

		def SetParentId(self, parentId):
			self.parentId = parentId
			
		def IsParent(self):
			return self.parentId == -1

		def SetVisible(self, visible):
			self.visible = visible
			
		def IsVisible(self):
			return self.visible
			
		def IsExpanded(self):
			return self.expanded
			
		def Expand(self):
			self.expanded = True
			if self.onExpandEvent:
				self.onExpandEvent()
			
		def Collapse(self):
			self.expanded = False
			if self.onCollapseEvent:
				self.onCollapseEvent()

		def SetOnExpandEvent(self, event):
			self.onExpandEvent = __mem_func__(event)

		def SetOnCollapseEvent(self, event):
			self.onCollapseEvent = __mem_func__(event)

		def SetOffset(self, offset):
			self.offset = offset

		def GetOffset(self):
			return self.offset

		def SetEvent(self, event):
			self.event = event

		def OnSelect(self):
			self.parent.SelectItem(self)

		def OnMouseLeftButtonDown(self):
			self.OnSelect()

	def __init__(self):
		Window.__init__(self)

		self.__curItemId=0
		self.viewItemCount=10
		self.basePos=0
		self.itemHeight=29
		self.isShopSearch=0
		self.itemStep=29
		self.selItem=0
		self.itemList=[]
		self.onSelectItemEvent = lambda *arg: None
		self.itemWidth=185

		self.scrollBar=None
		self.__UpdateSize()
	
	def __del__(self):
		Window.__del__(self)

	def __UpdateSize(self):
		height=self.itemStep*self.__GetViewItemCount()

		#self.SetSize(self.itemWidth, height)
		#self.SetSize(self.itemWidth, 375)

	def IsEmpty(self):
		if len(self.itemList)==0:
			return 1
		return 0

	#def OnMouseWheel(self, nLen):
	#	if self.scrollBar:
	#		self.scrollBar.OnMouseWheel(nLen)
	
	def OnMouseWheel(self, nLen):
		if self.scrollBar:
			if nLen > 0:
				self.scrollBar.OnUp()
			else:
				self.scrollBar.OnDown()
			return True
		return False

	def SetItemStep(self, itemStep):
		self.itemStep=itemStep
		self.__UpdateSize()

	def SetItemSize(self, itemWidth, itemHeight):
		self.itemWidth=itemWidth
		self.itemHeight=itemHeight
		self.__UpdateSize()
	
	def SetViewItemCount(self, viewItemCount):
		self.viewItemCount=viewItemCount
	
	def SetSelectEvent(self, event):
		self.onSelectItemEvent = event

	def SetBasePos(self, basePos):
		for oldItem in self.itemList:
			oldItem.Hide()

		self.basePos=basePos

		skipCount = basePos
		pos = basePos
		for lItem in self.itemList:
			if not lItem.IsVisible():
				continue
			
			if skipCount > 0:
				skipCount -= 1
				continue

			if pos >= (self.basePos+self.viewItemCount):
				break

			(x, y) = self.GetItemViewCoord(pos, lItem.GetWidth())
			lItem.SetPosition(x+lItem.GetOffset(), y)
			lItem.Show()
			pos+=1
		self.UpdateScrollbar()

	def GetItemIndex(self, argItem):
		return self.itemList.index(argItem)

	def GetSelectedItem(self):
		return self.selItem

	def SelectIndex(self, index):
		if index >= len(self.itemList) or index < 0:
			self.selItem = None
			return
		try:
			self.selItem=self.itemList[index]
		except:
			pass

	def ClearItem(self):
		self.selItem=None
		for lItem in self.itemList:
			lItem.Hide()
			lItem.Destroy()
			lItem = 0
		self.itemList=[]
		self.__curItemId = 0

		if self.scrollBar:
			self.scrollBar.SetPos(0)
		self.SetBasePos(0)

	def SelectItem(self, selItem):
		if self.isShopSearch:
			for item in self.itemList:
				if selItem != item:
					self.CloseTree(item, self.itemList)

		self.selItem = selItem
		if selItem.IsExpanded():
			self.CloseTree(selItem, self.itemList)
		else:
			if selItem.event:
				selItem.event()
			self.OpenTree(selItem, self.itemList)
		self.SetBasePos(self.basePos)
		

	def __AppendItem(self, newItem, parentId):
		curItemId = self.__curItemId
		self.__curItemId += 1
		
		newItem.SetParent(self)
		newItem.SetParentId(parentId)
		newItem.SetSize(self.itemWidth, self.itemHeight)
		newItem.SetId(curItemId)

		pos = self.__GetItemCount()
		self.itemList.append(newItem)

		if newItem.IsVisible() and self.__IsInViewRange(pos):
			(x, y)=self.GetItemViewCoord(pos, newItem.GetWidth())
			newItem.SetPosition(x, y)
			newItem.Show()
		else:
			newItem.Hide()

		self.UpdateScrollbar()

		return curItemId

	def AppendItemList(self, dict):
		self.__AppendItemList(-1, dict)
	
	def __AppendItemList(self, parentId, dict):
		for lItem in dict:
			if 'item' in lItem:
				id = self.__AppendItem(lItem['item'], parentId)
				if 'children' in lItem:
					self.__AppendItemList(id, lItem['children'])
				
	def SetScrollBar(self, scrollBar):
		scrollBar.SetScrollEvent(__mem_func__(self.__OnScroll))
		self.scrollBar=scrollBar

	def __OnScroll(self):
		self.SetBasePos(int(self.scrollBar.GetPos()*self.__GetScrollLen()))

	def __GetScrollLen(self):
		scrollLen=self.__GetItemCount()-self.__GetViewItemCount()
		if scrollLen<0:
			return 0

		return scrollLen

	def __GetViewItemCount(self):
		return self.viewItemCount

	def __GetItemCount(self):
		return sum(1 for lItem in self.itemList if lItem.IsVisible())

	def GetItemViewCoord(self, pos, itemWidth):
		return (0, (pos-self.basePos)*self.itemStep)

	def __IsInViewRange(self, pos):
		if pos<self.basePos:
			return 0
		if pos>=self.basePos+self.viewItemCount:
			return 0
		return 1
	
	def UpdateScrollbar(self):
		if self.__GetViewItemCount() < self.__GetItemCount():
			self.scrollBar.SetMiddleBarSize(float(self.__GetViewItemCount())/self.__GetItemCount())
			self.scrollBar.Show()
		else:
			self.scrollBar.Hide()

	def CloseTree(self, curItem, list):
		curItem.Collapse()
		for listboxItem in list:
			if listboxItem.GetParentId() == curItem.GetId():
				listboxItem.SetVisible(False)
				self.CloseTree(listboxItem, list)
		
	def OpenTree(self, curItem, list):
		curItem.Expand()
		for listboxItem in list:
			if listboxItem.GetParentId() == curItem.GetId():
				listboxItem.SetVisible(True)

class LastListItem(DropdownTree.Item):
	def __init__(self, text):
		DropdownTree.Item.__init__(self)
		self.overLine = False

		textLine=TextLine()
		textLine.SetParent(self)
		textLine.SetFontName(localeInfo.UI_DEF_FONT)
		textLine.SetWindowHorizontalAlignLeft()
		textLine.SetPosition(5,5)
		textLine.SetText(text)
		textLine.Show()

		self.textLine = textLine
		self.text = text

	def __del__(self):
		DropdownTree.Item.__del__(self)

	def Destroy(self):
		DropdownTree.Item.Destroy(self)
		self.overLine = 0
		self.textLine = 0
		self.text = 0

	def GetText(self):
		return self.text

	def SetSize(self, width, height):
		DropdownTree.Item.SetSize(self, width-self.GetOffset(), height)

	def OnMouseOverIn(self):
		self.overLine = True

	def OnMouseOverOut(self):
		self.overLine = False

	def OnRender(self):
		if self.overLine and self.parent.GetSelectedItem()!=self:
			x, y = self.GetGlobalPosition()
			grp.SetColor(grp.GenerateColor(1.0, 1.0, 1.0, 0.2))
			grp.RenderBar(x, y, self.GetWidth(), self.GetHeight())
		elif self.parent.GetSelectedItem()==self:
			x, y = self.GetGlobalPosition()
			grp.SetColor(grp.GenerateColor(0.0, 0.0, 1.0, 1.0))
			grp.RenderBar(x, y, self.GetWidth(), self.GetHeight())
		else:
			x, y = self.GetGlobalPosition()
			grp.SetColor(grp.GenerateColor(0.0, 0.0, 0.0, 1.0))
			grp.RenderBar(x, y, self.GetWidth(), self.GetHeight())
