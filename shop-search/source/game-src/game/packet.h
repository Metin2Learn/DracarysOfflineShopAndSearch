# Add

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
typedef struct packet_priv_shop_item_set
{
	BYTE header;
	BYTE count;
#ifdef ENABLE_OFFLINESHOP_SYSTEM
	TOfflineShopItem items[51];
#endif
} TPacketGCShopSearchItemSet;

typedef struct command_shop_search
{
	BYTE	header;
	int		ItemCat;
	BYTE	Value;
	DWORD	itemVnum;
	int		SubCat;
	BYTE	avg[2];
	BYTE	skill[2];
	BYTE	abs[2];
	BYTE	level[2];
	BYTE	refine[2];
	BYTE	sex;
	BYTE	enchant;
	BYTE	alchemy;
	BYTE	character;
} TPacketCGShopSearch;
#endif

# Search

HEADER_GC_QUEST_CONFIRM = 46,

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	HEADER_GC_SHOPSEARCH_SET = 156,
#endif

# Search

HEADER_CG_SHOOT = 54,

# Add after

#ifdef ENABLE_SHOP_SEARCH_SYSTEM
	HEADER_CG_SHOP_SEARCH = 220, //
#endif
