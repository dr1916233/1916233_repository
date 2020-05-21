//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"

// 変数宣言
int menuImage[MENU_TYPE_MAX];		// メニュー画像用
int itemboxImage[2];

// UIのシステム初期化
void UiSystemInit(void)
{
	// 画像の読み込み
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);

	itemboxImage[0] = LoadGraph("image/ui/item_box.png", true);
	itemboxImage[1] = LoadGraph("image/ui/item_box_lock.png", true);
}

// UIのゲーム初期化
void UiGameInit(void)
{

}

// UIの制御
void UiControl(void)
{

}

// UIの描画
void UiGameDraw(void)
{
	// メニュー画面の描画
	DrawGraph(20, 150, menuImage[MENU_TYPE_CRAFT], true);
	DrawGraph(250, 150, menuImage[MENU_TYPE_STATUS], true);
	DrawGraph(600, 150, menuImage[MENU_TYPE_INVENTORY], true);
	int lockIndex = InventoryItemDrawMain();

	for (int invCnt = 0; invCnt < ITEMBOX_MAX; invCnt++)
	{
		if (invCnt < lockIndex)
		{
			DrawGraph(611 + (4 + 38) * (invCnt % 4) - 2, 189 + (invCnt / 4 * 40) - 2, itemboxImage[0], true);
		}
		else
		{
			DrawGraph(611 + (4 + 38) * (invCnt % 4) - 2, 189 + (invCnt / 4 * 40) - 2, itemboxImage[1], true);
		}
		
	}
}