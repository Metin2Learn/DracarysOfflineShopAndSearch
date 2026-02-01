
# Add

if app.ENABLE_OFFLINESHOP_SYSTEM:
	import constInfo



# Search


	if app.ENABLE_WOLFMAN:
		AFFECT_DATA_DICT[chr.AFFECT_RED_POSSESSION] = ("Purpurwolfseele", "d:/ymir work/ui/skill/wolfman/red_possession" + END_STRING + ".sub",),
		AFFECT_DATA_DICT[chr.AFFECT_BLUE_POSSESSION] = ("Indigowolfseele", "d:/ymir work/ui/skill/wolfman/blue_possession" + END_STRING + ".sub",),

# Add after

	if app.ENABLE_OFFLINESHOP_SYSTEM:
		AFFECT_DATA_DICT[chr.NEW_AFFECT_DECORATION] = (localeInfo.NEW_AFFECT_DECORATION, "d:/ymir work/ui/game/offlineshop/decoration.dds")
