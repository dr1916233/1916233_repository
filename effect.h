//----------------------------------
//	IsekaiKanchoProject
//	By �Q�������ٖ剺��
//----------------------------------

//#pragma once//----------------------------------
// �萔�錾
#define SWORDEFFECT_MAX 16

// �G�t�F�N�g�̎��
enum EFFECT_TYPE
{
	EFFECT_TYPE_FIRESWORD,
	EFFECT_TYPE_MAX
};

// �\����
struct EFFECT
{
	EFFECT_TYPE type;
	XY pos;
	XY imageSize;
	int* image;
	int imageIndex;
};


// �v���g�^�C�v�錾
void SceneChange(SCENE_ID sceneID, int brightCnt, bool fade);	// �V�[���̃t�F�[�h�C��/�A�E�g����(SCENE_ID �V�[��ID, int 1�t���[�����Ƃ̉�����)
void EffectInit(void);
void SwordEffect(XY mapPos, int frameCnt);
void EffectGameDraw(XY mapPos, int frameCnt);
void CreateGameEffect(EFFECT_TYPE type, XY pos);

// extern�錾
extern SCENE_ID scnID;
extern bool FadeOutFlag;
extern bool FadeInFlag;
extern bool gameFadeOutFlag;