//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �v���g�^�C�v�錾
void KeyInit(void);		// �L�[���̏�����
void KeyCheck(void);	// �L�[�̏�Ԃ��擾
XY GetMousePos(void);	// �}�E�X�̍��W�擾�p

// �L�[����p
enum KEY_ID {
	KEY_SPACE,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UP,
	KEY_E,
	KEY_R,
	KEY_MENU,
	KEY_NORMAL_ATTACK,
	KEY_SPECIAL_ATTACK,
	KEY_MAX
};

// exturn�錾
extern bool keyTrgUp[KEY_MAX];
extern bool keyTrgDown[KEY_MAX];
extern bool keyNow[KEY_MAX];
extern bool keyOld[KEY_MAX];

extern bool mouseTrgUp;
extern bool mouseNow;
extern XY mousePos;