#include<SDL/SDL.h>
#include <SDL/SDL_image.h>

#define SPEED 15
#define STORAGE 900
#define CH_WIDTH 60
#define CH_HEIGHT 60
#define BU_WIDTH 16
#define BU_HEIGHT 64

//爆発エフェクト
typedef struct{
	SDL_Surface *image;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	int frame;
	int last_frame;
} Explode;

//プレイヤーキャラの構造体
typedef struct {
	int x;
	int y;
	int weapon;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *chara;
} Player;

//銃の構造体
typedef struct {
	int x;
	int y;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *image;
} Bullet;

//レーザーの構造体
typedef struct {
	int x;
	int y;
	int frame;
	int lastframe;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *image;
} Leaser;

//敵の構造体
typedef struct {
	int x;
	int y;
	int hp;
	int stts;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *image;
} Enemy;	

//ボスの構造体
typedef struct {
	int x;
	int y;
	int stts;
	int hp;
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *image;
} Boss;

//SPゲージの構造体
typedef struct {
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *image;
} Progress;

//HPバーの構造体
typedef struct {
	SDL_Rect src_rect;
	SDL_Rect dst_rect;
	SDL_Surface *image;
} HP;

Explode explode;
Player player;
Bullet bullet[4];
Leaser leaser;
Enemy enemy[3];
Boss boss;
Progress progress;
HP hp;

//変数
SDL_Surface *mainwindow, *strings;
SDL_Event event;
SDL_Joystick *joystick;
extern int loopflag;
extern int burstflag;
extern int score;
extern int exflag;
extern int ennum;

//system.c
extern int JudgeHit(int i);
extern int JudgeHit2(void);
extern void Store(int i);
extern void ExplodeInit(void);
extern void ExplodeInit2(void);
extern void CharaInit(void);
extern void BulletInit(void);
extern void LeaserInit(void);
extern void EnemyInit(void);
extern void BossInit(void);
extern void ProgressInit(void);
extern void HpInit(void);
extern int Fire(void *data);
extern int EnemyAttack(void *data);

//window_ui.c
extern int ProgressBar(void *data);
extern int CharaMove(void *data);
extern int EnemyMove(void *data);
extern int BulletMove(int i);
