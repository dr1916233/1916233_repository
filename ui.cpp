//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"

// �ϐ��錾
int menuImage[MENU_TYPE_MAX];		// ���j���[�摜�p
int itemboxImage[2];

// UI�̃V�X�e��������
void UiSystemInit(void)
{
	// �摜�̓ǂݍ���
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);

	itemboxImage[0] = LoadGraph("image/ui/item_box.png", true);
	itemboxImage[1] = LoadGraph("image/ui/item_box_lock.png", true);
}

// UI�̃Q�[��������
void UiGameInit(void)
{

}

// UI�̐���
void UiControl(void)
{

}

// UI�̕`��
void UiGameDraw(void)
{
	// ���j���[��ʂ̕`��
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