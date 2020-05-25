//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

//#pragma once

// 定数
#define ITEM_MAX 19		// アイテムの最大数
#define ITEM_SIZE_X	32	
#define ITEM_SIZE_Y 32

#define PORTION_HEAL	100

// アイテムの種類
enum ITEM_TYPE
{
	ITEM_TYPE_HARDSTONE,			// ID： 0 硬い石
	ITEM_TYPE_SOFTSTONE,			// ID： 1 柔らかい石
	ITEM_TYPE_DIAMOND,				// ID： 2 ダイアモンド
	ITEM_TYPE_AMETHYST,				// ID： 3 アメジスト
	ITEM_TYPE_EMERALD,				// ID： 4 エメラルド
	ITEM_TYPE_SAPPHIRE,				// ID： 5 サファイア
	ITEM_TYPE_RUBY,					// ID： 6 ルビー
	ITEM_TYPE_TOPAZ,				// ID： 7 トパーズ
	ITEM_TYPE_IRON,					// ID： 8 鉄
	ITEM_TYPE_GOLD,					// ID： 9 金
	ITEM_TYPE_WOODLOG,				// ID：10 木の幹
	ITEM_TYPE_WOODBRANCH,			// ID：11 木の枝
	ITEM_TYPE_HEALPORTION,			// ID：12 回復ポーション
	ITEM_TYPE_SPEEDUPPORTION,		// ID：13 スピードアップポーション
	ITEM_TYPE_ANTIDOTEPORTION,		// ID：14 毒消しポーション
	ITEM_TYPE_ANTIFREEZEPORTION,	// ID：15 凍結解除ポーション
	ITEM_TYPE_ANTIBURNPORTION,		// ID：16 火傷解除ポーション
	ITEM_TYPE_WHITEDOUGI,			// ID：17 白の道着
	ITEM_TYPE_BRAVEDOUGI,			// ID：18 勇者の道着
	ITEM_TYPE_NON,			
	ITEM_TYPE_MAX
};

// アイテムの状態
enum ITEM_STATE
{
	ITEM_STATE_INVENTORY,
	ITEM_STATE_DROP,
	ITEM_STATE_NON,
	ITEM_STATE_MAX
};

// アイテムの属性
enum ITEM_ATTRIBUTE
{
	ITEM_ATTRIBUTE_ACTIVE,
	ITEM_ATTRIBUTE_PASSIVE,
	ITEM_ATTRIBUTE_MATERIAL,
	ITEM_ATTRIBUTE_ARMOR,
	ITEM_ATTRIBUTE_MAX
};


// 構造体

// アイテム用構造体
struct ITEM
{
	ITEM_STATE state;
	ITEM_TYPE type;
	ITEM_ATTRIBUTE attribute;
	int imageIndex;
	XY pos;
};

// インベントリ用構造体
struct INVENTORY
{
	ITEM_TYPE itemType;
	int num;
	int imageIndex;
};

// プロトタイプ宣言
void ItemSystemInit(void);
void ItemGameInit(int invMax);
void ItemGameDraw(XY mapPos);
void ItemControl(void);
void UpdateInventoryList(int max);
bool AddInventoryList(int index);
void DeleteInventoryList(int index);
XY GetItemPos(int index);
INVENTORY* GetInventoryPointer(void);
void DeleteItem(int index);
int InventoryItemDraw(void);
bool UseItem(CHARACTER* player, int index);



