#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include"system.h"

char buf[32];
int loopflag = 0;
int burstflag = 0;
int score = 0;
int exflag = 0;
int ennum = 0;

SDL_Thread *thr1, *thr2, *thr3, *thr4, *thr5;

int main(int args,char *argp[]) {
	
	
	SDL_Rect a = {700, 0, 260, 800}; 
	SDL_Rect e = {0, 0, 190, 800};
	
	//背景の初期化
	SDL_Surface *back;
	SDL_Rect src_rect = {0, 0, 515, 800};
	SDL_Rect dst_rect = {190, 0};
	int frame = 63;
	int last_frame = 0;
	
	int i,j;
	/* 乱数初期化 */
    srand(time(NULL));
    
    //背景画像の読み込み
    back = IMG_Load("background.png");

	ExplodeInit();

	//プレイヤーの初期化
	CharaInit();
	
	//武器の初期化
	BulletInit();
	
	LeaserInit();
	
	//敵の初期化
	EnemyInit();
	
	//ボスの初期化
	//BossInit();
	
	//プログレスバーの初期化
	ProgressInit();
	
	//HPバーの初期化
	HpInit();
	
	if(SDL_Init(SDL_INIT_EVERYTHING|SDL_INIT_JOYSTICK) < 0) {
		printf("failed to initialize SDL.\n");
		exit(-1);
	}
	
	// ウィンドウ生成（600*800、1677万色）
	if((mainwindow = SDL_SetVideoMode(1000, 800, 32, SDL_SWSURFACE)) == NULL) {
		printf("failed to initialize videomode.\n");
		exit(-1);
	}
	
	TTF_Font* font;// TrueTypeフォントデータへのポインタ 
    SDL_Color black = {0x00, 0x00, 0x00};// フォントの色を指定するための構造体（黒色)
    TTF_Init();// TrueTypeフォントを用いるための初期化
    font = TTF_OpenFont("kochi-gothic-subst.ttf", 24); // kochi-gothic-substフォントを24ポイントで使用（読み込み）
	
	joystick=SDL_JoystickOpen(0);	// ジョイスティックを開いて構造体に割り当てる（有効にする）．ここではジョイスティックは1つとして引数に0を指定
	SDL_JoystickEventState(SDL_ENABLE);	// ジョイスティック関連のイベントを取得可能にする

	// ジョイスティックが開けなかったら
	if(!joystick) {
		printf("failed to open joystick.\n");
		exit(-1);
	}
	
	while(1){
		if(SDL_PollEvent(&event))
		if(event.type == SDL_JOYBUTTONDOWN)
			if(event.jbutton.button == 11)
			break;
		SDL_Flip(mainwindow);
	}
	
	thr1 = SDL_CreateThread(Fire,NULL);
	thr2 = SDL_CreateThread(CharaMove, NULL);
	thr3 = SDL_CreateThread(ProgressBar, NULL);
	thr4 = SDL_CreateThread(EnemyMove, NULL);
	thr5 = SDL_CreateThread(EnemyAttack, NULL);
	
	SDL_FillRect(mainwindow, &a,  0x00ff00ff);
	SDL_FillRect(mainwindow, &e,  0x00000000);
	
	while(loopflag == 0){
		sprintf(buf, "SCORE %d", score);
		strings = TTF_RenderUTF8_Blended(font, buf, black);
		SDL_Rect c = {0, 0, strings->w, strings->h};
		SDL_Rect d = {760, 0};
		SDL_BlitSurface(back, &src_rect, mainwindow, &dst_rect);
		src_rect.y = 25 * frame--;
		if(frame == last_frame){
			frame = 65;
			src_rect.y = 0;
			j++;
			if(j % 2 == 1) 
			back = IMG_Load("background2.png");
			if(j % 2 == 0) 
			back = IMG_Load("background.png");
		}
		SDL_FillRect(mainwindow, &a, 0x00ff00ff);
		SDL_FillRect(mainwindow, &e,  0x00000000);
		SDL_BlitSurface(strings, &c, mainwindow, &d);
		SDL_BlitSurface(player.chara, &player.src_rect, mainwindow, &player.dst_rect);
		if(player.weapon == 1 && bullet[0].x != STORAGE)
		SDL_BlitSurface(bullet[0].image, &bullet[0].src_rect, mainwindow, &bullet[0].dst_rect);
		else if(player.weapon == 2 && leaser.x != STORAGE)
		SDL_BlitSurface(leaser.image, &leaser.src_rect, mainwindow, &leaser.dst_rect);
		
		if(boss.stts == 0)
		for(i = 1; i < 4; i++){
			SDL_BlitSurface(bullet[i].image, &bullet[i].src_rect, mainwindow, &bullet[i].dst_rect);
			SDL_BlitSurface(enemy[i-1].image, &enemy[i-1].src_rect, mainwindow, &enemy[i-1].dst_rect);
		}
		
		if(exflag == 1){
			SDL_BlitSurface(explode.image, &explode.src_rect, mainwindow, &explode.dst_rect);
			explode.src_rect.x = explode.src_rect.w * explode.frame++;
			if(explode.frame == explode.last_frame){
				exflag = 0;
				explode.frame = 0;
			}
		}
		if(boss.stts == 1){
			SDL_BlitSurface(boss.image, &boss.src_rect, mainwindow, &boss.dst_rect);
			for(i = 1; i < 4; i++){
				SDL_BlitSurface(bullet[i].image, &bullet[i].src_rect, mainwindow, &bullet[i].dst_rect);
			}
		}
		SDL_BlitSurface(progress.image, &progress.src_rect, mainwindow, &progress.dst_rect);
		SDL_BlitSurface(hp.image, &hp.src_rect, mainwindow, &hp.dst_rect);
		SDL_Flip(mainwindow);	// 画面にアニメーションを表示（反映）
		SDL_Delay(5);
	} 
	SDL_FreeSurface(mainwindow);	//　ウィンドウの解放
	SDL_Quit();	// SDLの利用終了
	return 0;
}
