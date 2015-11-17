#include<stdio.h>
#include<SDL/SDL.h>
#include<SDL/SDL_image.h>
#include"system.h"

int ProgressBar(void *data){
	while(1){
		SDL_Delay(1000);
		if(progress.src_rect.w <= 150)
		progress.src_rect.w += 4;
	}
	return 0;
}

int CharaMove(void *data){
Sint16 x_move, y_move;
while( loopflag == 0 ){
SDL_Delay(20);
x_move = SDL_JoystickGetAxis(joystick, 0);
y_move = SDL_JoystickGetAxis(joystick, 1);
	if(x_move < 0){
		if(player.dst_rect.x > 200){
			player.dst_rect.x -= 10;
			player.x = player.dst_rect.x;
		}
	}
	else if(x_move > 0){
		if(player.dst_rect.x < 640){
			player.dst_rect.x += 10;
			player.x = player.dst_rect.x;
		}
	}
	
	if(y_move < 0){
		if(player.dst_rect.y > 400){
			player.dst_rect.y -= 10;
			player.y = player.dst_rect.y;
		}
	}
	else if(y_move > 0){
		if(player.dst_rect.y < 750){
			player.dst_rect.y += 10;
			player.y = player.dst_rect.y;
		}
	}
	if(SDL_PollEvent(&event))
	switch (event.type) {
		SDL_Delay(20); 
		case SDL_JOYBUTTONDOWN:
			if(event.jbutton.button == 3){
				burstflag = 1;
			}
			else if(event.jbutton.button == 5){
				player.weapon++;
			}
			else if(event.jbutton.button == 7){
				player.weapon--;
			}
			printf("%d\n", player.weapon);
			printf("%d\n", burstflag);
			printf("%d %d\n", leaser.dst_rect.x, leaser.dst_rect.y);
			break;
			
		case SDL_JOYBUTTONUP:
			if(event.jbutton.button == 3)	burstflag = 0;
			else if(event.jbutton.button == 10){
				loopflag++;
			}
			break;
			
		default:
			break;
		}
	}
	return 0;
}

int EnemyMove(void *data){
	int i,j,k=0;
	int dir;
	int co[3] = {0};
	boss.stts = 0;
	Enemy newpos;
	while(loopflag == 0){
	if(boss.stts == 0){
		for(i = 0; i < 3; i++){
		dir = rand() % 4;
		if(ennum == 3)
			SDL_Delay(70);
		else if(ennum == 2)
			SDL_Delay(80);
		else if(ennum == 1)
			SDL_Delay(90);
		else if(ennum == 0)
			SDL_Delay(60);
		if(enemy[i].stts == 1){
			switch(dir){
				case 0:
					if(enemy[i].dst_rect.x < 589){
						newpos.dst_rect.x = enemy[i].dst_rect.x + 30;
						for(j = 0; j < 3; j++){
						if(i!=j) 
						if((abs(newpos.dst_rect.x-enemy[j].x) <= 60 && abs(enemy[i].y-enemy[j].y) <= 60 ))	
							break;
							if(j == 2){
								enemy[i].dst_rect.x = newpos.dst_rect.x;
								enemy[i].x = enemy[i].dst_rect.x;
							}
						}
					}
					break;
		
				case 1:
					if(enemy[i].dst_rect.x > 210){
						newpos.dst_rect.x = enemy[i].dst_rect.x - 30;
						for(j = 0; j < 3; j++){
						if(i!=j)
						if((abs(newpos.dst_rect.x-enemy[j].x) <= 60 && abs(enemy[i].y-enemy[j].y) <= 60 ))
							break;
							if(j == 2){
								enemy[i].dst_rect.x = newpos.dst_rect.x;
								enemy[i].x = enemy[i].dst_rect.x;
							}
						}
					}
					break;
		
				case 2:
					if(enemy[i].dst_rect.y < 300 && enemy[i].dst_rect.y > 0){
						newpos.dst_rect.y = enemy[i].dst_rect.y + 30;
						for(j = 0; j < 3; j++){
						if(i!=j)
							if((abs(newpos.dst_rect.y-enemy[j].y) <= 60 && abs(enemy[i].x-enemy[j].x) <= 60))
								break;
							if(j == 2){
								enemy[i].dst_rect.y = newpos.dst_rect.y;
								enemy[i].y = enemy[i].dst_rect.y;
							}
						}
					}
					break;
			
				case 3:
					if(enemy[i].dst_rect.y > 1 && enemy[i].dst_rect.y < 300){
						newpos.dst_rect.y = enemy[i].dst_rect.y - 30;
						for(j = 0; j < 3; j++){ 
						if(i!=j){
							if((abs(newpos.dst_rect.y-enemy[j].y) <= 60 && abs(enemy[i].x-enemy[j].x) <= 60))
								break;
						}
						if(j == 2){
							enemy[i].dst_rect.y = newpos.dst_rect.y;
							enemy[i].y = enemy[i].dst_rect.y;
						}
					}
				}
				break;
			} 
		}
		else if(enemy[i].stts == 0){
			co[i]++;
			if(co[i] >= 60){
				enemy[i].x = rand() % 460 + 190;
				enemy[i].dst_rect.x = enemy[i].x;
				enemy[i].y = rand() % 210;
				enemy[i].dst_rect.y = enemy[i].y;
				enemy[i].stts = 1;
				enemy[i].hp = 10;
				co[i] = 0;
				ennum++;
				if(i == 0){
					while((abs(enemy[i].x-enemy[i+1].x) <= 60 && abs(enemy[i].y-enemy[i+1].y) <= 60)|| (abs(enemy[i].x-enemy[i+2].x) <= 60 && abs(enemy[i].y-enemy[i+2].y) <= 60))
					enemy[i].x = rand() % 460 + 190;
					enemy[i].dst_rect.x = enemy[i].x;
				}
				else if(i == 1){
					while((abs(enemy[i].x-enemy[i-1].x) <= 60 && abs(enemy[i].y-enemy[i-1].y) <= 60) || (abs(enemy[i].x-enemy[i+1].x) <= 60 && abs(enemy[i].y-enemy[i+1].y) <= 60))
					enemy[i].x = rand() % 460 + 190;
					enemy[i].dst_rect.x = enemy[i].x;
				}
				else if(i == 2){
					while((abs(enemy[i].x-enemy[i-1].x) <= 60 && abs(enemy[i].y-enemy[i-1].y) <= 60) || (abs(enemy[i].x-enemy[i-2].x) <= 60 && abs(enemy[i].y-enemy[i-2].y) <= 60))
					enemy[i].x = rand() % 460 + 190;
					enemy[i].dst_rect.x = enemy[i].x;
				}
					
				}
			}
		}
		k++;
	}
		
		if(k == 1000){
			for(i = 0; i < 3; i++){
				enemy[i].dst_rect.x = STORAGE;
				enemy[i].dst_rect.y = STORAGE;
				enemy[i].x = STORAGE;
				enemy[i].y = STORAGE;
				enemy[i].stts = 0;
				Store(i+1);
			}
		k = 0;
		BossInit();
		ExplodeInit2();
		}
			
		if(boss.stts == 1){
			SDL_Delay(120);
			dir = rand() % 4;
			switch(dir){
				case 0:
				if(boss.x < 580){
					boss.dst_rect.x += 25;
					boss.x = boss.dst_rect.x;
				}
				break;
		
				case 1:
					if(boss.x > 210){
						boss.dst_rect.x -= 25;
						boss.x = boss.dst_rect.x;
					}
				break;
		
				case 2:
					if(boss.y > 0 && boss.y < 211){
						boss.dst_rect.y += 25;
						boss.y = boss.dst_rect.y;
					}
				break;
			
				case 3:
					if(boss.y > 30 && boss.y < 211){
						boss.dst_rect.y -= 25;
						boss.y = boss.dst_rect.y;
					}
				break;
			} 
		}
	}
	return 0;
}

int BulletMove(int i) {
	if(i == 0){
		if(player.weapon == 1){
			if(JudgeHit(i)){
			Store(i);
			return -1;
		}
		else if(bullet[i].dst_rect.y > 0){
			SDL_Delay(10);
			bullet[i].y -= SPEED;
			bullet[i].dst_rect.y = bullet[i].y;
			return 0;
		}
		return -1;
		}
		
		else if(player.weapon == 2){
			if(JudgeHit2() == 1)
			return 0;
		}
	}
	else if(i != 0 && boss.stts == 0){
		if(JudgeHit(i)){
			Store(i);
			return -1;
		}
		else if(bullet[i].dst_rect.y < 740){
			if(enemy[i-1].stts == 0){
				Store(i);
				return -1;
			}
			SDL_Delay(10);
			bullet[i].y += SPEED;
			bullet[i].dst_rect.y = bullet[i].y;
			
			return 0;
		}
		return -1;
	}
	
	else if(i != 0 && boss.stts == 1){
		if(JudgeHit(i)){
			Store(i);
			return -1;
		}
		else if(bullet[i].dst_rect.y < 740){
			if(boss.stts == 0){
				Store(i);
				return -1;
			}
			SDL_Delay(10);
			bullet[i].y += SPEED;
			bullet[i].dst_rect.y = bullet[i].y;
			
			return 0;
		}
		return -1;
	}
	return 0;
}
