//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define PLAYER_IMAGENUM_X 4			// �v���C���[�摜��X�����̐�
#define PLAYER_IMAGENUM_Y 4			// �v���C���[�摜��Y�����̐�
#define PLAYER_IMAGESIZE_X 32		// �v���C���[�摜��X�����̃T�C�Y
#define PLAYER_IMAGESIZE_Y 32		// �v���C���[�摜��Y�����̃T�C�Y
#define PLAYER_SIZE_X 20			// �v���C���[��X�������T�C�Y
#define PLAYER_SIZE_Y 32			// �v���C���[��Y�������T�C�Y
#define PLAYER_OFFSET_X 6	// �v���C���[��X�����̗]���T�C�Y
#define PLAYER_LIFE_DEF	100			// �v���C���[�̃f�t�H���gHP
#define PLAYER_SPEED_DEF 3			// �v���C���[�̃f�t�H���g�ړ����x
#define PLAYER_ATTACK_DEF	10		// �v���C���[�̃f�t�H���g�U����
#define PLAYER_INVENTORY_DEF 8		// �v���C���[�̃f�t�H���g�C���x���g����

// --------------------
// �\����
// --------------------

// �v���g�^�C�v�錾

void PlayerSystemInit(void);	// �v���C���[���̏�����
int PlayerGameInit(void);		// �v���C���[�̃Q�[���֌W�̏�����
void PlayerGameDraw(XY mapPos);		// �v���C���[�̃Q�[���`��
XY_F PlayerControl(XY chipNum, XY_F mapPos);	// �v���C���[�̐��䏈��
CHARACTER* GetPlayerPointer(void);		// �v���C���[�̃|�C���^���擾
CHARACTER GetPlayer(void);		// �v���C���[�̏����擾
void PlayerAttack(void);			// �v���C���[�̍U������
