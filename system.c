#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"system.h"

int JudgeHit(int i){
int j = 0;
	if(boss.stts == 0){
		if(i == 0){
			for(j = 0; j < 3; j++){
				if(bullet[i].x>enemy[j].x && bullet[i].x<enemy[j].x+60 && bullet[i].y < enemy[j].y+60 && bullet[i].y > enemy[j].y){
					enemy[j].hp -= 5;
					if(enemy[j].hp <= 0){
						ennum--;
						score += 100;
						exflag = 1;
						explode.dst_rect.x = enemy[j].dst_rect.x;
						explode.dst_rect.y = enemy[j].dst_rect.y;
						enemy[j].dst_rect.x = STORAGE;
						enemy[j].dst_rect.y = STORAGE;
						enemy[j].x = STORAGE;
						enemy[j].y = STORAGE;
						enemy[j].stts = 0;
					}
					return 1;
				}
			} 
			return 0; 
		}
	
		else if(i != 0){
			if(bullet[i].x>player.x && bullet[i].x<player.x+60 && bullet[i].y>player.y && bullet[i].y<player.y+60){
				if(hp.src_rect.w > 0)
					hp.src_rect.w -= 10;
				if(hp.src_rect.w == 70)
					hp.image = IMG_Load("hp2.png");
				if(hp.src_rect.w == 40)
					hp.image = IMG_Load("hp3.png");
				return 1;
			}
			else 
				return 0;
			}
		}
		
	else if(boss.stts == 1){
		if(bullet[0].x>boss.x && bullet[0].x<boss.x+100 && bullet[0].y <= boss.y+150 && bullet[0].y > boss.y){
			boss.hp -= 1;
			if(boss.hp == 0){
				exflag = 1;
				explode.dst_rect.x = boss.dst_rect.x - 80;
				explode.dst_rect.y = boss.dst_rect.y;
				boss.dst_rect.x = STORAGE;
				boss.dst_rect.y = STORAGE;
				boss.x = STORAGE;
				boss.y = STORAGE;
				boss.stts = 0;
			}
			return 1;
		}
		
		else if(i != 0){
			if(bullet[i].x>player.x && bullet[i].x<player.x+60 && bullet[i].y>player.y && bullet[i].y<player.y+60){
				if(hp.src_rect.w > 0)
					hp.src_rect.w -= 10;
				if(hp.src_rect.w == 70)
					hp.image = IMG_Load("hp2.png");
				if(hp.src_rect.w == 40)
					hp.image = IMG_Load("hp3.png");
				return 1;
			}
			else 
				return 0;
		}
	}
	return 0;
}

int JudgeHit2(void){
	int i;
	for(i = 0; i < 3; i++){
		if(abs(leaser.x-enemy[i].x) < 50){
			enemy[i].hp = 0;
			ennum--;
			score += 100;
			exflag = 1;
			explode.dst_rect.x = enemy[i].dst_rect.x;
			explode.dst_rect.y = enemy[i].dst_rect.y;
			enemy[i].dst_rect.x = STORAGE;
			enemy[i].dst_rect.y = STORAGE;
			enemy[i].x = STORAGE;
			enemy[i].y = STORAGE;
			enemy[i].stts = 0;
		}
	}
}

void Store(int i){
	bullet[i].dst_rect.x = STORAGE;
	bullet[i].dst_rect.y = STORAGE;
	bullet[i].x = STORAGE;
	bullet[i].y = STORAGE;
}

void ExplodeInit(void){
	explode.image = IMG_Load("explode.png");
	explode.src_rect.w = 71;
	explode.src_rect.h = 68;
	explode.frame = 0;
	explode.last_frame = 11;
}

void ExplodeInit2(void){
	explode.image = IMG_Load("boexplode.png");
	explode.src_rect.w = 240;
	explode.src_rect.h = 240;
	explode.frame = 0;
	explode.last_frame = 7;
}

void CharaInit(void){
	player.x = 400;
	player.y = 750;
	player.weapon = 1;
	player.src_rect.w = CH_WIDTH;
	player.src_rect.h = CH_HEIGHT;
	player.dst_rect.x = player.x;
	player.dst_rect.y = player.y;
	player.chara = IMG_Load("Player.png");
}

void BulletInit(void){
	int i;
	for(i = 0; i < 4; i++){ 
		bullet[i].src_rect.w = BU_WIDTH;
		bullet[i].src_rect.h = BU_HEIGHT;
		bullet[i].dst_rect.x = STORAGE;
		bullet[i].dst_rect.y = STORAGE;
	}
	bullet[0].image = IMG_Load("Bullet.png");
	for(i = 1; i < 4; i++){
		bullet[i].image = IMG_Load("Bullet2.png");
	}
}

void LeaserInit(void){
	leaser.src_rect.w = 64;
	leaser.src_rect.h = 745;
	leaser.x = STORAGE;
	leaser.y = STORAGE;
	leaser.image = IMG_Load("leaser.png");
}

void EnemyInit(void){
	int i;
	ennum = 3;
	for(i = 0; i < 3; i++){
		enemy[i].src_rect.w = CH_WIDTH;
		enemy[i].src_rect.h = CH_HEIGHT;
		enemy[i].x = rand() % 460 + 190;
		enemy[i].dst_rect.x = enemy[i].x;
		enemy[i].y = 1;
		enemy[i].dst_rect.y = enemy[i].y;
		enemy[i].hp = 10;
		enemy[i].stts = 1;
		if(i == 1){
			while(abs(enemy[i].x-enemy[i-1].x) <= 60){
				enemy[i].x = rand() % 460 + 190;
				enemy[i].dst_rect.x = enemy[i].x;
			}
		}
		else if(i == 2){
			while(abs(enemy[i].x-enemy[i-1].x) <= 60 || abs(enemy[i].x-enemy[i-2].x) <= 60){
				enemy[i].x = rand() % 460 + 190;
				enemy[i].dst_rect.x = enemy[i].x;
			}
		}
	}
	enemy[0].image = IMG_Load("Enemy.png");
	enemy[1].image = IMG_Load("Enemy2.png");
	enemy[2].image = IMG_Load("Enemy3.png");
}

void BossInit(void){
	boss.x = 400;
	boss.y = 1;
	boss.stts = 1;
	boss.hp = 10;
	boss.src_rect.w = 100;
	boss.src_rect.h = 150;
	boss.dst_rect.x = boss.x;
	boss.dst_rect.y = boss.y;
	boss.image = IMG_Load("boss.png");
}

void ProgressInit(void){
	progress.src_rect.w = 0;
	progress.src_rect.h = 30;
	progress.dst_rect.x = 0;
	progress.dst_rect.y = 40;
	progress.image = IMG_Load("progress.png");
}

void HpInit(void){
	hp.src_rect.w = 150;
	hp.src_rect.h = 20; 
	hp.dst_rect.x = 0;
	hp.dst_rect.y = 10;
	hp.image = IMG_Load("hp1.png");
}

int Fire(void *data) {
	int count = 0;
while( loopflag == 0 ){
		if(burstflag == 1){
			if(player.weapon == 1){
				if(bullet[0].dst_rect.x == STORAGE)	{
					bullet[0].x = (player.x + CH_WIDTH / 2) -6;
					bullet[0].dst_rect.x = bullet[0].x;
					bullet[0].y = player.y;
					bullet[0].dst_rect.y = bullet[0].y;
				}
				while(1){
					SDL_Delay(1);
					if( BulletMove(0) == -1)
					break;
				}
				Store(0);
			SDL_Delay(20);
			}
			else if(player.weapon == 2){
				if(leaser.x == STORAGE){
					leaser.x = (player.x + CH_WIDTH / 2) - 6;
					leaser.dst_rect.x = leaser.x;
					leaser.y = 0;
					leaser.dst_rect.y = leaser.y;
				}
			}
		}
		if(player.weapon == 2){
			while(count++ < 50){
				SDL_Delay(1);
				BulletMove(0);
			}
			leaser.dst_rect.x = STORAGE;
			leaser.dst_rect.y = STORAGE;
		}
	}
	return 0;
}

int EnemyAttack(void *data){
	int i;
	while( loopflag == 0 ){
		if(boss.stts == 0){
			for(i = 1; i < 4; i++){
				if(bullet[i].dst_rect.x == STORAGE && enemy[i-1].stts == 1)	{
					bullet[i].x = (enemy[i-1].x + CH_WIDTH / 2);
					bullet[i].dst_rect.x = bullet[i].x;
					bullet[i].y = enemy[i-1].y + CH_HEIGHT;
					bullet[i].dst_rect.y = bullet[i].y;
				}
			while(1){
			SDL_Delay(5);
			if( BulletMove(i) == -1)	
				break;
			}
			Store(i);
			SDL_Delay(20);
			}
		}
		
		else if(boss.stts == 1){
			for(i = 1; i < 4; i++){
				if(bullet[i].dst_rect.x == STORAGE && boss.stts == 1)	{
					bullet[i].x = (boss.x +  boss.src_rect.w / 2);
					bullet[i].dst_rect.x = bullet[i].x;
					bullet[i].y = boss.y + 150;
					bullet[i].dst_rect.y = bullet[i].y;
				}
			while(1){
			SDL_Delay(5);
			if( BulletMove(i) == -1)	
				break;
			}
			Store(i);
			SDL_Delay(20);
			}
		}
	}
	return 0;
}
