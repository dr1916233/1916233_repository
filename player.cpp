//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "player.h"

// �ϐ��錾
int playerImage[PLAYER_IMAGENUM_Y][PLAYER_IMAGENUM_X];

// �v���C���[���̏�����
void PlayerSystemInit(void)
{
	// �v���C���[�̉摜�ǂݍ���
	LoadDivGraph(
		"image/kancho.png",
		PLAYER_IMAGENUM_X * PLAYER_IMAGENUM_Y,
		PLAYER_IMAGENUM_X,
		PLAYER_IMAGENUM_Y,
		PLAYER_IMAGESIZE_X,
		PLAYER_IMAGESIZE_Y,
		*playerImage,
		true
	);
}

// �v���C���[�̃Q�[����������
void PlayerGameInit(void)
{

}

// �v���C���[���̕`��
void PlayerGameDraw(void)
{
	DrawGraph(100, 100, playerImage[0][0], true);
}

// �v���C���[�̐��䏈��
void PlayerControl(void)
{

}



