# Add

#ifdef ENABLE_OFFLINESHOP_SYSTEM
typedef struct packet_offline_shop_item
{
	DWORD		vnum;
	long long	price;
	int			count;
	BYTE		display_pos;
	long		alSockets[ITEM_SOCKET_MAX_NUM];
	TPlayerItemAttribute aAttr[ITEM_ATTRIBUTE_MAX_NUM];
	BYTE		status;
	char		szBuyerName[CHARACTER_NAME_MAX_LEN+1];
#ifdef ENABLE_CHANGELOOK_SYSTEM
	DWORD		transmutation;
#endif
	DWORD		owner_id;
} TOfflineShopItem;
typedef struct SPacketGCShopSign
{
	BYTE	bHeader;
	DWORD	dwVID;
	char	szSign[SHOP_SIGN_MAX_LEN + 1];
} TPacketGCShopSign;
typedef struct SPacketCGMyOfflineShop
{
	BYTE	bHeader;
	char	szSign[SHOP_SIGN_MAX_LEN + 1];
	BYTE	bCount;
	DWORD	shopVnum;
	BYTE	shopTitle;
} TPacketCGMyOfflineShop;
typedef struct packet_offline_shop_start
{
	DWORD	owner_vid;
	TOfflineShopItem items[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	DWORD	m_dwDisplayedCount;
	char			title[SHOP_SIGN_MAX_LEN + 1];
	long long	price;
	DWORD	m_dwRealWatcherCount;
	ShopLog			log[OFFLINE_SHOP_HOST_ITEM_MAX_NUM];
	long long		flag;
	int						time;
	DWORD			type;
	bool			IsOwner;
} TPacketGCOfflineShopStart;
typedef struct packet_offline_shop_update_item
{
	BYTE						pos;
	TOfflineShopItem			 item;
	DWORD						m_dwDisplayedCount;
	DWORD			m_dwRealWatcherCount;
	char			title[SHOP_SIGN_MAX_LEN + 1];
	long long	price;
	ShopLog			log;
	long long		flag;
	int					time;
	DWORD			type;
} TPacketGCOfflineShopUpdateItem;
#endif

# Search


	SHOP_SUBHEADER_GC_SOLD_OUT

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	SHOP_SUBHEADER_GC_REFRESH_MONEY,
	SHOP_SUBHEADER_GC_CHECK_RESULT,
	SHOP_SUBHEADER_GC_REFRESH_DISPLAY_COUNT,
	SHOP_SUBHEADER_GC_REALWATCHER_COUNT,
	SHOP_SUBHEADER_GC_REFRESH_COUNT,
	SHOP_SUBHEADER_GC_CHANGE_TITLE,
#endif

# Search

typedef struct command_shop
{
	BYTE	header;
	BYTE	subheader;
} TPacketCGShop;

# Change


typedef struct command_shop
{
	BYTE	header;
	BYTE	subheader;
#ifdef ENABLE_OFFLINESHOP_SYSTEM
	char	title[50 + 1];
	DWORD	vid;
	BYTE	pos;
#endif
} TPacketCGShop;

# Search

SHOP_SUBHEADER_CG_SELL

# add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	SHOP_SUBHEADER_CG_ADD_ITEM,
	SHOP_SUBHEADER_CG_REMOVE_ITEM,
	SHOP_SUBHEADER_CG_DESTROY_OFFLINE_SHOP,
	SHOP_SUBHEADER_CG_CHECK,
	SHOP_SUBHEADER_CG_BUTTON,
	SHOP_SUBHEADER_CG_CHANGE_TITLE,
	SHOP_SUBHEADER_CG_TAKE_MONEY,
	SHOP_SUBHEADER_CG_LOG_REMOVE,
	SHOP_SUBHEADER_CG_CHANGE_DECORATION,
	SHOP_SUBHEADER_CG_OPEN_SLOT,
	SHOP_SUBHEADER_CG_GET_ITEM,
	SHOP_SUBHEADER_CG_ADD_TIME,
	SHOP_SUBHEADER_CG_OPEN_WITH_VID,
#endif

# Search

HEADER_GC_QUEST_CONFIRM = 46,

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	HEADER_GC_OFFLINE_SHOP = 47,
	HEADER_GC_OFFLINE_SHOP_SIGN = 48,
#endif


# Search

HEADER_CG_SHOOT = 54,

# Add after

#ifdef ENABLE_OFFLINESHOP_SYSTEM
	HEADER_CG_OFFLINE_SHOP = 57,
	HEADER_CG_MY_OFFLINE_SHOP = 58,
#endif

