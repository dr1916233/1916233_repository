//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------
#include "DxLib.h"
#include "main.h"
#include "item.h"
#include "keycheck.h"

// 定数宣言
#define ITEM_CREATE_MAX ITEM_MAX + 1

// 変数宣言
ITEM itemMaster[ITEM_TYPE_MAX];	// アイテムの情報保持用
ITEM item[ITEM_CREATE_MAX];	// アイテム用
INVENTORY* inventoryList; // インベントリ内のアイテム制御用
INVENTORY armorInventory;	// アーマー用のインベントリ
int inventoryListCnt;	// インベントリ配列の最後のインデックス保持用
int itemImage[128+20+2+1];		// アイテムの画像用
int inventoryMax;		// インベントリの最大値
ITEM_TYPE playerArmor;	// プレイヤーが着てる防具判定用
int selectArmorImage[3];	// プレイヤーがどの装備を着ているかの表示用

// アイテムのシステム初期化
void ItemSystemInit(void)
{
	// ------------------------------------
	//			  画像の読み込み 
	// ------------------------------------

	// 石関係アイテムの画像読み込み
	LoadDivGraph("image/item/item_stone.png", 128, 16, 8, 32, 32, itemImage);
	// ポーション関係アイテムの画像読み込み
	LoadDivGraph("image/item/item_portion.png", 20, 10, 2, 32, 32, &itemImage[128]);
	// 防具アイテムの画像読み込み
	itemImage[149] = LoadGraph("image/item/item_whiteDougi.png",true);
	itemImage[150] = LoadGraph("image/item/item_braveDougi.png",true);
	selectArmorImage[0] = LoadGraph("image/character/naked_kancho_view.png", true);
	selectArmorImage[1] = LoadGraph("image/character/dougi_kancho_view.png", true);
	selectArmorImage[2] = LoadGraph("image/character/brave_kancho_view.png", true);

	// ------------------------------------
	//		   アイテム情報初期化
	// ------------------------------------

	// 硬い石の情報初期化
	itemMaster[ITEM_TYPE_HARDSTONE].imageIndex = 89;
	itemMaster[ITEM_TYPE_HARDSTONE].type = ITEM_TYPE_HARDSTONE;
	itemMaster[ITEM_TYPE_HARDSTONE].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// 柔らかい石の情報初期化
	itemMaster[ITEM_TYPE_SOFTSTONE].imageIndex = 90;
	itemMaster[ITEM_TYPE_SOFTSTONE].type = ITEM_TYPE_SOFTSTONE;
	itemMaster[ITEM_TYPE_SOFTSTONE].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// ダイアモンドの情報初期化
	itemMaster[ITEM_TYPE_DIAMOND].imageIndex = 8;
	itemMaster[ITEM_TYPE_DIAMOND].type = ITEM_TYPE_DIAMOND;
	itemMaster[ITEM_TYPE_DIAMOND].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// アメジストの情報初期化
	itemMaster[ITEM_TYPE_AMETHYST].imageIndex = 12;
	itemMaster[ITEM_TYPE_AMETHYST].type = ITEM_TYPE_AMETHYST;
	itemMaster[ITEM_TYPE_AMETHYST].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// エメラルドの情報初期化
	itemMaster[ITEM_TYPE_EMERALD].imageIndex = 11;
	itemMaster[ITEM_TYPE_EMERALD].type = ITEM_TYPE_EMERALD;
	itemMaster[ITEM_TYPE_EMERALD].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// サファイアの情報初期化
	itemMaster[ITEM_TYPE_SAPPHIRE].imageIndex = 9;
	itemMaster[ITEM_TYPE_SAPPHIRE].type = ITEM_TYPE_SAPPHIRE;
	itemMaster[ITEM_TYPE_SAPPHIRE].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// ルビーの情報初期化
	itemMaster[ITEM_TYPE_RUBY].imageIndex = 13;
	itemMaster[ITEM_TYPE_RUBY].type = ITEM_TYPE_RUBY;
	itemMaster[ITEM_TYPE_RUBY].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// トパーズの情報初期化
	itemMaster[ITEM_TYPE_TOPAZ].imageIndex = 14;
	itemMaster[ITEM_TYPE_TOPAZ].type = ITEM_TYPE_TOPAZ;
	itemMaster[ITEM_TYPE_TOPAZ].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// 鉄の情報初期化
	itemMaster[ITEM_TYPE_IRON].imageIndex = 88;
	itemMaster[ITEM_TYPE_IRON].type = ITEM_TYPE_IRON;
	itemMaster[ITEM_TYPE_IRON].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// 金の情報初期化
	itemMaster[ITEM_TYPE_GOLD].imageIndex = 87;
	itemMaster[ITEM_TYPE_GOLD].type = ITEM_TYPE_GOLD;
	itemMaster[ITEM_TYPE_GOLD].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// 木の幹の情報初期化
	itemMaster[ITEM_TYPE_WOODLOG].imageIndex = 115;
	itemMaster[ITEM_TYPE_WOODLOG].type = ITEM_TYPE_WOODLOG;
	itemMaster[ITEM_TYPE_WOODLOG].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// 木の枝の情報初期化
	itemMaster[ITEM_TYPE_WOODBRANCH].imageIndex = 113;
	itemMaster[ITEM_TYPE_WOODBRANCH].type = ITEM_TYPE_WOODBRANCH;
	itemMaster[ITEM_TYPE_WOODBRANCH].attribute = ITEM_ATTRIBUTE_MATERIAL;

	// 回復ポーション情報初期化
	itemMaster[ITEM_TYPE_HEALPORTION].imageIndex = 128;
	itemMaster[ITEM_TYPE_HEALPORTION].type = ITEM_TYPE_HEALPORTION;
	itemMaster[ITEM_TYPE_HEALPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// スピードアップポーション情報初期化
	itemMaster[ITEM_TYPE_SPEEDUPPORTION].imageIndex = 131;
	itemMaster[ITEM_TYPE_SPEEDUPPORTION].type = ITEM_TYPE_SPEEDUPPORTION;
	itemMaster[ITEM_TYPE_SPEEDUPPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// 毒消しポーション情報初期化
	itemMaster[ITEM_TYPE_ANTIDOTEPORTION].imageIndex = 132;
	itemMaster[ITEM_TYPE_ANTIDOTEPORTION].type = ITEM_TYPE_ANTIDOTEPORTION;
	itemMaster[ITEM_TYPE_ANTIDOTEPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// 凍結解除ポーション情報初期化
	itemMaster[ITEM_TYPE_ANTIFREEZEPORTION].imageIndex = 129;
	itemMaster[ITEM_TYPE_ANTIFREEZEPORTION].type = ITEM_TYPE_ANTIFREEZEPORTION;
	itemMaster[ITEM_TYPE_ANTIFREEZEPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// 火傷解除ポーション情報初期化
	itemMaster[ITEM_TYPE_ANTIBURNPORTION].imageIndex = 130;
	itemMaster[ITEM_TYPE_ANTIBURNPORTION].type = ITEM_TYPE_ANTIBURNPORTION;
	itemMaster[ITEM_TYPE_ANTIBURNPORTION].attribute = ITEM_ATTRIBUTE_ACTIVE;

	// 白の道着情報初期化
	itemMaster[ITEM_TYPE_WHITEDOUGI].imageIndex = 149;
	itemMaster[ITEM_TYPE_WHITEDOUGI].type = ITEM_TYPE_WHITEDOUGI;
	itemMaster[ITEM_TYPE_WHITEDOUGI].attribute = ITEM_ATTRIBUTE_ARMOR;

	// 勇者の道着情報初期化
	itemMaster[ITEM_TYPE_BRAVEDOUGI].imageIndex = 150;
	itemMaster[ITEM_TYPE_BRAVEDOUGI].type = ITEM_TYPE_BRAVEDOUGI;
	itemMaster[ITEM_TYPE_BRAVEDOUGI].attribute = ITEM_ATTRIBUTE_ARMOR;

	// アイテム初期化用
	itemMaster[ITEM_TYPE_NON].attribute = ITEM_ATTRIBUTE_MAX;
}

// アイテムのゲーム初期化
void ItemGameInit(int invMax)
{
	// インベントリの最大値用変数
	inventoryMax = invMax;

	// プレイヤーの防具情報初期化
	playerArmor = ITEM_TYPE_MAX;

	// プレイヤーインベントリを作成
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * invMax);
	for (int list = 0; list < invMax; list++)
	{
		inventoryList[list].itemType = ITEM_TYPE_NON;
		inventoryList[list].num = 0;
		inventoryList[list].imageIndex = 0;
	}

	// アーマー用インベントリ初期化
	armorInventory.imageIndex = 0;
	armorInventory.itemType = ITEM_TYPE_NON;
	armorInventory.num = 1;

	// アイテム確認用配置

	for (int itemCnt = 0; itemCnt < ITEM_CREATE_MAX; itemCnt++)
	{
		item[itemCnt].type = ITEM_TYPE_NON;
		item[itemCnt].state = ITEM_STATE_NON;
		item[itemCnt].pos = {0,0};
	}

	for (int itemCnt = 0; itemCnt < 2; itemCnt++)
	{
		item[itemCnt] = itemMaster[ITEM_TYPE_WHITEDOUGI + itemCnt];
		item[itemCnt].state = ITEM_STATE_DROP;
		item[itemCnt].pos = { 40 * itemCnt + 50 ,200 };
	}
}

// アイテムのゲーム描画
void ItemGameDraw(XY mapPos)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		DrawGraph(
			item[itemCnt].pos.x - mapPos.x,
			item[itemCnt].pos.y - mapPos.y + SCREEN_OFFSET_Y,
			itemImage[item[itemCnt].imageIndex],
			true
		);
	}

	for (int cnt = 0; cnt < inventoryMax; cnt++)
	{
		DrawFormatString(10, 18 * cnt + 10, GetColor(255, 255, 255), "個数：%d", inventoryList[cnt].num);
	}
}

// アイテムのコントロール
void ItemControl(void)
{
	if (keyTrgUp[KEY_E])
	{
		//AddInventoryList(item[0], 0);
	}

	if (keyTrgUp[KEY_R])
	{
		UpdateInventoryList(20);
	}
}

// プレイヤーのインベントリのリストを更新
void UpdateInventoryList(int max)
{
	// リストのコピーを作成
	INVENTORY* inventoryListCopy = (INVENTORY*)malloc(sizeof(INVENTORY) * inventoryMax);
	
	// コピーにインベントリ内のアイテム移動
	//inventoryListCopy = inventoryList;
	for (int listCnt = 0; listCnt < inventoryMax; listCnt++)
	{
		inventoryListCopy[listCnt] = inventoryList[listCnt];
	}
	
	// リストの作り直し
	free(inventoryList);
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * max);

	// 新しいリストの初期化
	for (int listCnt = 0; listCnt < max; listCnt++)
	{
		inventoryList[listCnt].itemType = ITEM_TYPE_NON;
		inventoryList[listCnt].num = 0;
		inventoryList[listCnt].imageIndex = 0;
	}

	// コピーに保存した情報を新しいリストに挿入
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt].itemType = inventoryListCopy[listCnt].itemType;
		inventoryList[listCnt].num = inventoryListCopy[listCnt].num;
		inventoryList[listCnt].imageIndex = inventoryListCopy[listCnt].imageIndex;
	}

	// インベントリの最大値を更新
	inventoryMax = max;

	// コピーのメモリを開放
	free(inventoryListCopy);
}

bool AddInventoryList(int index)
{
	ITEM insertItem = item[index];

	// リストの一番最後にアイテムがあればfalseを返してアイテム取得不可にする
	if (inventoryList[inventoryMax -1].num > 0)
	{
		return false;
	}
	
	// アイテム挿入位置保存用
	int insertIndex = inventoryListCnt;
	
	// リストにすでに持っているアイテムがあれば数を増やす
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		if (insertItem.type == inventoryList[listCnt].itemType)
		{
			inventoryList[listCnt].num++;
			item[index].state = ITEM_STATE_INVENTORY;
			return true;
		}
	}

	// 持ってないアイテムの場合はID順に並べて追加
	//for (int listCnt = 0; listCnt < insertIndex; listCnt++)
	//{
	//	if (insertItem.type > inventoryList[listCnt].itemType && insertItem.type < inventoryList[listCnt + 1].itemType)
	//	{
	//		insertIndex = listCnt + 1;
	//		break;
	//	}
	//}

	// 挿入位置から後ろに全部1つずらす
	/*for (int listCnt = inventoryListCnt; listCnt > insertIndex; listCnt--)
	{
		inventoryList[listCnt + 1] = inventoryList[listCnt];
	}*/
	
	// リストに挿入
	inventoryList[insertIndex].itemType = insertItem.type;
	inventoryList[insertIndex].num += 1;
	inventoryList[insertIndex].imageIndex = insertItem.imageIndex;
	item[index].state = ITEM_STATE_INVENTORY;
	
	// インベントリにアイテムが入ってるスロット数を更新
	inventoryListCnt += 1;

	return true;
}

// 指定した配列のインデックスを削除し並び替え
void DeleteInventoryList(int index)
{
	// 引数で渡されたインデックスを消す。
	//for (int listCnt = index; listCnt > inventoryListCnt; listCnt++)
	//{
	//	inventoryList[listCnt] = inventoryList[listCnt + 1];
	//}

	for (int listCnt = index; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt] = inventoryList[listCnt + 1];
	}

	// 一番後ろのリストを削除
	inventoryList[inventoryListCnt].itemType = ITEM_TYPE_MAX;
	inventoryList[inventoryListCnt].num = 0;

	// インベントリにアイテムが入ってるスロット数を更新
	inventoryListCnt -= 1;
}

// アイテムの生成
int CreateItem(ITEM_TYPE type, XY pos)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		if (item[itemCnt].type == ITEM_TYPE_NON)
		{
			item[itemCnt] = itemMaster[type];
			item[itemCnt].pos = pos;
			return itemCnt;
		}
	}

	return -1;
}

// アイテムの配列から該当アイテムを削除
void DeleteItem(int index)
{
	//// アイテムをずらして削除
	//for (int sortHead = index; sortHead < ITEM_MAX; sortHead++)
	//{
	//	item[sortHead] = item[sortHead + 1];
	//}

	//// 最後の配列を削除
	//for (int head = index; head < ITEM_MAX; head++)
	//{
	//	if (item[head].type != ITEM_TYPE_NON && item[head + 1].type == ITEM_TYPE_NON)
	//	{
	//		item[head].imageIndex = 0;
	//		item[head].pos = { 0,0 };
	//		item[head].state = ITEM_STATE_NON;
	//		item[head].type = ITEM_TYPE_NON;
	//	}
	//}

	item[index].attribute = ITEM_ATTRIBUTE_MAX;
	item[index].imageIndex = -1;
	item[index].type = ITEM_TYPE_NON;
	item[index].state = ITEM_STATE_NON;
	item[index].pos = { -32,-32 };
}

// アイテムインベントリのアドレス取得用
INVENTORY* GetInventoryPointer(void)
{
	return inventoryList;
}

// アイテムの座標取得用
XY GetItemPos(int index)
{
	return item[index].pos;
}

// 指定された座標にインベントリ内アイテムを描画させる
int InventoryItemDraw(void)
{
	for (int invCnt = 0; invCnt < inventoryListCnt; invCnt++)
	{
		DrawGraph(611 + (4 + 38) * (invCnt % 4), 189 + (invCnt/4*40),itemImage[inventoryList[invCnt].imageIndex],true);
	}

	// プレイヤーの選択中防具のビュー描画
	int imageIndex = 0;
	if (playerArmor == ITEM_TYPE_WHITEDOUGI)
	{
		imageIndex = 1;
		DrawGraph(185 + 250, 90 + 150, itemImage[149], true);
	}
	if (playerArmor == ITEM_TYPE_BRAVEDOUGI)
	{
		imageIndex = 2;
		DrawGraph(185 + 250, 90 + 150, itemImage[150], true);
	}

	DrawGraph(200 + 100,  150 + 55, selectArmorImage[imageIndex], true);

	return inventoryMax;
}

// アイテムの使用
bool UseItem(CHARACTER* player,int index)
{
	if (itemMaster[inventoryList[index].itemType].attribute == ITEM_ATTRIBUTE_MATERIAL ||
		itemMaster[inventoryList[index].itemType].attribute == ITEM_ATTRIBUTE_PASSIVE ||
		itemMaster[inventoryList[index].itemType].attribute == ITEM_ATTRIBUTE_MAX) return false;
	//(*player)
	switch (inventoryList[index].itemType)
	{
	case ITEM_TYPE_HEALPORTION:
		/*if ((*player).life < (*player).lifeMax) (*player).life += PORTION_HEAL;
		if ((*player).life > (*player).lifeMax) (*player).life = (*player).lifeMax;*/

		(*player).lifeMax += PORTION_HEAL;
		break;
	case ITEM_TYPE_SPEEDUPPORTION:
		(*player).moveSpeed += 10;
		break;
	case ITEM_TYPE_ANTIDOTEPORTION:
		break;
	case ITEM_TYPE_ANTIFREEZEPORTION:
		break;
	case ITEM_TYPE_ANTIBURNPORTION:
		break;
	case ITEM_TYPE_WHITEDOUGI:
		playerArmor = inventoryList[index].itemType;
		if (armorInventory.itemType == ITEM_TYPE_NON) armorInventory = inventoryList[index];
		else
		{
			int index = CreateItem(armorInventory.itemType, { -32,-32 });
			AddInventoryList(index);
			DeleteItem(index);
			armorInventory = inventoryList[index];
		}
		break;
	case ITEM_TYPE_BRAVEDOUGI:
		playerArmor = inventoryList[index].itemType;
		if (armorInventory.itemType == ITEM_TYPE_NON) armorInventory = inventoryList[index];
		else
		{
			int index = CreateItem(armorInventory.itemType, { -32,-32 });
			AddInventoryList(index);
			DeleteItem(index);
			armorInventory = inventoryList[index];
		}
		break;
	default:
		break;
	}

	return true;
}
