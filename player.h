//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �萔�錾
#define PLAYER_IMAGENUM_X 4	// �v���C���[�摜��X�����̐�
#define PLAYER_IMAGENUM_Y 4	// �v���C���[�摜��Y�����̐�
#define PLAYER_IMAGESIZE_X	32	// �v���C���[�摜��X�����̃T�C�Y
#define PLAYER_IMAGESIZE_Y	32	// �v���C���[�摜��Y�����̃T�C�Y

#define PLAYER_LIFE_DEF	100	// �v���C���[�̃f�t�H���gHP
#define PLAYER_SPEED_DEF	3	// �v���C���[�̃f�t�H���g�ړ����x

// --------------------
// �\����
// --------------------



// �v���g�^�C�v�錾

void PlayerSystemInit(void);	// �v���C���[���̏�����
void PlayerGameInit(void);		// �v���C���[�̃Q�[���֌W�̏�����
void PlayerGameDraw(void);		// �v���C���[�̃Q�[���`��
XY PlayerControl(void);		// �v���C���[�̐��䏈��