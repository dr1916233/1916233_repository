//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "ui.h"

// �ϐ��錾
int menuImage[MENU_TYPE_MAX];		// ���j���[�摜�p

// UI�̃V�X�e��������
void UiSystemInit(void)
{
	// �摜�̓ǂݍ���
	menuImage[MENU_TYPE_CRAFT] = LoadGraph("image/ui/ui_craft.png",true);
	menuImage[MENU_TYPE_STATUS] = LoadGraph("image/ui/ui_status.png", true);
	menuImage[MENU_TYPE_INVENTORY] = LoadGraph("image/ui/ui_inventory.png", true);
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
}