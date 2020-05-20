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
int inventoryListCnt;	// インベントリ配列の最後のインデックス保持用
int itemImage[128];		// アイテムの画像用
int inventoryMax;		// インベントリの最大値
// アイテムのシステム初期化
void ItemSystemInit(void)
{
	// ------------------------------------
	//			  画像の読み込み 
	// ------------------------------------

	// 石関係アイテムの画像読み込み
	LoadDivGraph("image/item/item_stone.png", 128, 16, 8, 32, 32, itemImage);

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
}

// アイテムのゲーム初期化
void ItemGameInit(int invMax)
{
	// インベントリの最大値用変数
	inventoryMax = invMax;

	// プレイヤーインベントリを作成
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * invMax);
	for (int list = 0; list < invMax; list++)
	{
		inventoryList[list].itemType = ITEM_TYPE_MAX;
		inventoryList[list].num = 0;
	}

	// アイテム確認用配置
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		item[itemCnt] = itemMaster[itemCnt];
		item[itemCnt].state = ITEM_STATE_DROP;
		item[itemCnt].pos = { 40 * itemCnt + 50 ,200};
	}
}

// アイテムのゲーム描画
void ItemGameDraw(XY mapPos)
{
	for (int itemCnt = 0; itemCnt < ITEM_MAX; itemCnt++)
	{
		DrawGraph(
			item[itemCnt].pos.x - mapPos.x,
			item[itemCnt].pos.y - mapPos.y,
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
	INVENTORY* inventoryListCopy = (INVENTORY*)malloc(sizeof inventoryList);
	
	// コピーにインベントリ内のアイテム移動
	//inventoryListCopy = inventoryList;
	for (int listCnt = 0; listCnt < inventoryMax; listCnt++)
	{
		inventoryListCopy[listCnt] = inventoryList[listCnt];
	}

	// リストの作り直し
	free(inventoryList);
	inventoryList = (INVENTORY*)malloc(sizeof(INVENTORY) * max);

	// コピーに保存した情報を新しいリストに挿入
	for (int listCnt = 0; listCnt < inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt].itemType = inventoryListCopy[listCnt].itemType;
		inventoryList[listCnt].num = inventoryListCopy[listCnt].num;
	}

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
	for (int listCnt = 0; listCnt < insertIndex; listCnt++)
	{
		if (insertItem.type > inventoryList[listCnt].itemType && insertItem.type < inventoryList[listCnt + 1].itemType)
		{
			insertIndex = listCnt + 1;
			break;
		}
	}

	// 挿入位置から後ろに全部1つずらす
	for (int listCnt = inventoryListCnt; listCnt > insertIndex; listCnt--)
	{
		inventoryList[listCnt + 1] = inventoryList[listCnt];
	}
	
	// リストに挿入
	inventoryList[insertIndex].itemType = insertItem.type;
	inventoryList[insertIndex].num += 1;
	item[index].state = ITEM_STATE_INVENTORY;
	
	// インベントリにアイテムが入ってるスロット数を更新
	inventoryListCnt += 1;

	return true;
}

// 指定した配列のインデックスを削除し並び替え
void DeleteInventoryList(int index)
{
	// 引数で渡されたインデックスを消す。
	for (int listCnt = index; listCnt > inventoryListCnt; listCnt++)
	{
		inventoryList[listCnt] = inventoryList[listCnt + 1];
	}

	// 一番後ろのリストを削除
	inventoryList[inventoryListCnt].itemType = ITEM_TYPE_MAX;
	inventoryList[inventoryListCnt].num = 0;

	// インベントリにアイテムが入ってるスロット数を更新
	inventoryListCnt -= 1;
}

// アイテムの配列から該当アイテムを削除
void DeleteItem(int index)
{
	// アイテムをずらして削除
	for (int sortHead = index; sortHead < ITEM_MAX; sortHead++)
	{
		item[sortHead] = item[sortHead + 1];
	}

	// 最後の配列を削除
	for (int head = index; head < ITEM_MAX; head++)
	{
		if (item[head].type != ITEM_TYPE_NON && item[head + 1].type == ITEM_TYPE_NON)
		{
			item[head].imageIndex = 0;
			item[head].pos = { 0,0 };
			item[head].state = ITEM_STATE_NON;
			item[head].type = ITEM_TYPE_NON;
		}
	}
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


