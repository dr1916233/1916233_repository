//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------

// �v���g�^�C�v�錾
void KeyInit(void);		// �L�[���̏�����
void KeyCheck(void);	// �L�[�̏�Ԃ��擾

// �L�[����p
enum KEY_ID {
	KEY_SPACE,
	KEY_DOWN,
	KEY_RIGHT,
	KEY_LEFT,
	KEY_UP,
	KEY_E,
	KEY_R,
	KEY_MAX
};

// exturn�錾
extern bool keyTrgUp[KEY_MAX];
extern bool keyTrgDown[KEY_MAX];
extern bool keyNow[KEY_MAX];
extern bool keyOld[KEY_MAX];