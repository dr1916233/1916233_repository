//----------------------------------
//	IsekaiKanchoProject
//	By ゲヱム道館門下生
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"

// 変数宣言
int menuImage[MENU_TYPE_MAX];		// メニュー画像用

// UIのシステム初期化
void UiSystemInit(void)
{
	// 画像の読み込み
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);
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
}