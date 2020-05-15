//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "keycheck.h"

// �ϐ��錾
CHARACTER player;
int playerImage[PLAYER_IMAGENUM_Y][PLAYER_IMAGENUM_X];

// �v���C���[���̏�����
void PlayerSystemInit(void)
{
	// �v���C���[�̉摜�ǂݍ���
	LoadDivGraph(
		"image/character/kancho.png",
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
	// �v���C���[��񏉊���
	player.animCnt = 0;
	player.animCnt = 10;
	player.dir = DIR_DOWN;
	player.lifeMax = PLAYER_LIFE_DEF;
	player.life = player.lifeMax;
	player.moveSpeed = PLAYER_SPEED_DEF;
	player.pos = { 100.0f,100.0f };
	player.size = { 32,32 };
	player.type = CHARA_PLAYER;
	player.visible = true;
}

// �v���C���[���̕`��
void PlayerGameDraw(XY mapPos)
{
	player.animCnt++;
	DrawGraph(player.pos.x - mapPos.x, player.pos.y - mapPos.y, playerImage[player.dir][player.animCnt / 10 % 4], true);
	DrawFormatString(50, 100, GetColor(255, 255, 255), "�v���C���[�̃`�b�v : %d,%d", (int)player.pos.x / 32, (int)player.pos.y / 32);
}

// �v���C���[�̐��䏈��
XY PlayerControl(XY chipNum, XY mapPos)
{
	XY playerPosRec = { (int)player.pos.x, (int)player.pos.y };
	DIR playerDirRec = player.dir;

	player.dir = DIR_MAX;

	// �L�[�����擾����
	if (keyNow[KEY_DOWN]) player.dir = DIR_DOWN;
	if (keyNow[KEY_RIGHT]) player.dir = DIR_RIGHT;
	if (keyNow[KEY_LEFT]) player.dir = DIR_LEFT;
	if (keyNow[KEY_UP]) player.dir = DIR_UP;

	// �ړ��ʌv�Z�p
	XY camDiff = { 0,0 };
	// �ړ�����W�ۑ��p
	XY playerPosCopy;
	playerPosCopy.x = player.pos.x;
	playerPosCopy.y = player.pos.y;

	// �ړ�����
	switch (player.dir)
	{
	case DIR_DOWN:
		playerPosCopy.y += player.moveSpeed;
		if (IsPassMain(playerPosCopy))
		{
			if (player.pos.y < chipNum.y * 32 - 32) player.pos.y += player.moveSpeed;
			if (mapPos.y + SCREEN_SIZE_Y < chipNum.y * 32 && player.pos.y > 100) camDiff.y += player.moveSpeed;
		}
		break;
	case DIR_RIGHT:
		playerPosCopy.x += player.moveSpeed;
		if (IsPassMain(playerPosCopy))
		{
			if (player.pos.x < chipNum.x * 32 - 32) player.pos.x += player.moveSpeed;
			if (mapPos.x + SCREEN_SIZE_X < chipNum.x * 32 && player.pos.x > 100) camDiff.x += player.moveSpeed;
		}
		break;
	case DIR_LEFT:
		playerPosCopy.x -= player.moveSpeed;
		if (IsPassMain(playerPosCopy))
		{
			if (player.pos.x > 0) player.pos.x -= player.moveSpeed;
			if (mapPos.x > 0 && player.pos.x < chipNum.x * 32 - 100) camDiff.x -= player.moveSpeed;
		}
		break;
	case DIR_UP:
		playerPosCopy.y -= player.moveSpeed;
		if (IsPassMain(playerPosCopy))
		{
			if (player.pos.y > 0) player.pos.y -= player.moveSpeed;
			if (mapPos.y > 0 && player.pos.y < chipNum.y * 32 - 100) camDiff.y -= player.moveSpeed;
		}
		break;
	default:
		player.dir = playerDirRec;
		break;
	}

	

	return camDiff;
}




