//----------------------------------	
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

#include "DxLib.h"
#include "main.h"
#include "enemy.h"

// �ϐ��錾
CHARACTER enemyMaster[ENEMY_TYPE_MAX];	// �G�̕ϐ�
CHARACTER enemy[ENEMY_MAX];				// �G�̑���
int enemyImage[ENEMY_TYPE_MAX][16];		// �G�̉摜�̎��

// �G�̏�����
void EnemySystemInit(void)
{
	for (int cnt = 0; cnt < ENEMY_TYPE_MAX; cnt++)
	{
		enemyMaster[cnt].offsetSize = { 0,0 };	// �G�̏����I�t�Z�b�g�T�C�Y
		enemyMaster[cnt].animCnt = 0;			// �G�̏����A�j���[�V�����J�E���g
		enemyMaster[cnt].life = enemyMaster[cnt].lifeMax;	// �G�̏������C�t
		enemyMaster[cnt].dir = DIR_DOWN;		// �G�̏�������
		enemyMaster[cnt].type = CHARA_ENEMY;
		enemyMaster[cnt].moveFlag = true;
	}

	//------------------------------------------------------------------------------------------
// �X���C��

	enemyMaster[ENEMY_TYPE_SLIME].size = { 32,32 };				// �X���C���̃T�C�Y
	enemyMaster[ENEMY_TYPE_SLIME].offsetSize = { 3,7 };			// �X���C���̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_SLIME].lifeMax = 2;					// �X���C���̃��C�t
	enemyMaster[ENEMY_TYPE_SLIME].moveSpeed = 1;				// �X���C���̃X�s�[�h
	enemyMaster[ENEMY_TYPE_SLIME].enemyType = ENEMY_TYPE_SLIME;	// �G�̎�ނ��X���C���ɃZ�b�g

	LoadDivGraph("image/character/�X���C��fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_SLIME]);		// �X���C���̕`��
	//------------------------------------------------------------------------------------------
	// �S�u����

	enemyMaster[ENEMY_TYPE_GOBLIN].size = { 32,32 };				// �S�u�����̃T�C�Y
	enemyMaster[ENEMY_TYPE_GOBLIN].offsetSize = { 3,7 };			// �S�u�����̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_GOBLIN].lifeMax = 2;						// �S�u�����̃��C�t
	enemyMaster[ENEMY_TYPE_GOBLIN].moveSpeed = 2;					// �S�u�����̃X�s�[�h
	enemyMaster[ENEMY_TYPE_GOBLIN].enemyType = ENEMY_TYPE_GOBLIN;	// �G�̎�ނ��S�u�����ɃZ�b�g

	LoadDivGraph("image/character/�S�u����fin��.png",
		16, 4, 4, 32, 32, enemyImage[ENEMY_TYPE_GOBLIN]);			// �S�u�����̕`��
	//------------------------------------------------------------------------------------------
	// �I�[�N

	enemyMaster[ENEMY_TYPE_OAK].size = { 41,41 };			// �I�[�N�̃T�C�Y
	enemyMaster[ENEMY_TYPE_OAK].offsetSize = { 3,7 };		// �I�[�N�̃I�t�Z�b�g�T�C�Y
	enemyMaster[ENEMY_TYPE_OAK].lifeMax = 4;				// �I�[�N�̃��C�t
	enemyMaster[ENEMY_TYPE_OAK].moveSpeed = 1;				// �I�[�N�̃X�s�[�h
	enemyMaster[ENEMY_TYPE_OAK].enemyType = ENEMY_TYPE_OAK;	// �G�̎�ނ��I�[�N�ɃZ�b�g

	LoadDivGraph("image/character/�I�[�Nfin��.png",
		16, 4, 4, 41, 41, enemyImage[ENEMY_TYPE_OAK]);		// �I�[�N�̕`��
	//------------------------------------------------------------------------------------------

}

// �G�̃Q�[�����Ƃ̏�����
void EnemyGameInit(void)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		int rnd = GetRand(ENEMY_TYPE_MAX - 1);
		enemy[en] = enemyMaster[rnd];

		//enemy[en].pos.x += enemy[en].size.x * en;

		// �X�N���[���̃����_���Ȉʒu�ŏo��
		enemy[en].pos.x = GetRand(SCREEN_SIZE_X - 1);
		enemy[en].pos.y = GetRand(SCREEN_SIZE_Y - 1);
	}

}

// �G�̐��䏈��
void EnemyControl(XY playerPos, int cnt)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		enemy[en].animCnt++;

		if (enemy[en].lifeMax > 0)
		{
			switch (enemy[en].enemyType)
			{

				// X�ړ�
			case 	ENEMY_TYPE_SLIME:
			case	ENEMY_TYPE_OAK:
				if (!enemy[en].moveFlag)
				{
					if (MoveEnemyX(&enemy[en], playerPos) == 0)
					{
						MoveEnemyY(&enemy[en], playerPos);
					}
				}
				break;

				// Y�ړ�
			case	ENEMY_TYPE_GOBLIN:
				if (!enemy[en].moveFlag)
				{
					if (MoveEnemyY(&enemy[en], playerPos) == 0)
					{
						MoveEnemyX(&enemy[en], playerPos);
					}
				}
			default:
				break;
			}
			// �G�̈ړ����[�h�̐؂�ւ�
			if (enemy[en].moveFlag && GetRand(100) == 0)
			{
				enemy[en].moveFlag = false;
			}
			else if (!enemy[en].moveFlag && GetRand(360) == 0)
			{
				enemy[en].moveFlag = true;
			}
		}
	}
}

// �G�̕`��
void EnemyGameDraw(XY mapPos)
{
		for (int en = 0; en < ENEMY_MAX; en++)
		{
				DrawGraph(
					enemy[en].pos.x - mapPos.x,
					enemy[en].pos.y - mapPos.y,
					enemyImage[enemy[en].enemyType][enemy[en].dir * 4 + enemy[en].animCnt / 10 % 4],
					true);
		}

	//DrawCircle(320, 240, 150, GetColor(255,255,255), false);
}


//�@�G���ړ�������֐��Q X�ړ�
int MoveEnemyX(CHARACTER *enemy, XY playerPos)
{
	int speed = (*enemy).moveSpeed;
	int diff = playerPos.x - (*enemy).pos.x;

	if (diff >= 0)
	{
		// �E
		speed = (diff < speed) ? diff : speed;
		(*enemy).pos.x += speed;
		(*enemy).dir = DIR_RIGHT;
	}
	else
	{
		// ��
		speed = (-diff < speed) ? -diff : speed;
		(*enemy).pos.x -= speed;
		(*enemy).dir = DIR_LEFT;
	}

	return speed;
}

// �G���ړ�������֐��Q Y�ړ�
int MoveEnemyY(CHARACTER *enemy, XY playerPos)
{
	int speed = (*enemy).moveSpeed;
	int diff = playerPos.y - (*enemy).pos.y;

	if (diff >= 0)
	{
		// ��
		speed = (diff < speed) ? diff : speed;
		(*enemy).pos.y += speed;
		(*enemy).dir = DIR_DOWN;
	}
	else
	{
		// ��
		speed = (-diff < speed) ? -diff : speed;
		(*enemy).pos.y -= speed;
		(*enemy).dir = DIR_UP;
	}
	return speed;
}



XY GetEnemyPos(int en)
{

	return { (int)enemy[en].pos.x,(int)enemy[en].pos.y };
}

XY GetEnemySize(int en)
{

	return enemy[en].size;
}

void EnemyRad(void)
{
	//17+26= 43/2= 21.5= 21
}