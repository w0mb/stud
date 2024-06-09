#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "map.h"
#include <iostream>
#include <string.h>


using namespace sf;
using namespace std;


float offsetX=0, offsetY=0;

int score = 0;

class Player {
private:
	FloatRect rect;
	float dx, dy;
	bool onGround;
	float currentFrame;
	Sprite sprite;
	Sound jump, money, mario_smert;
public:
	Player(){}
	Player(Texture& image) 
	{
		sprite.setTexture(image);
		rect = FloatRect(2 * 32, 9 * 32, 35, 48);

		dx = dy = 0.1;
		currentFrame = 0;
	}
	
	void setMario_smert(Sound mario_smert) {
		this->mario_smert = mario_smert;
	}
	void setJump(Sound jump) {
		this->jump = jump;
	}
	void setMoney(Sound money) {
		this->money = money;
	}

	Sprite getSprite() {
		return sprite;
	}

	void setRect(FloatRect rect) {
		this->rect = rect;
	}
	FloatRect getRect() {
		return rect;
	}


	void setDX(float dx) {
		this->dx = dx;
	}
	float getDX() {
		return dx;
	}

	void setDY(float dy) {
		this->dy = dy;
	}
	float getDY() {
		return dy;
	}


	void setOnGround(bool onGround){
		this->onGround = onGround;
	}
	bool getOnGround(){
		return onGround;
	}

   void update(float time)
   {	

	 rect.left += dx * time;	
	 Collision(0);

	 if (!onGround) dy=dy+0.0005*time;
	 rect.top += dy*time;
	 onGround=false;
     Collision(1);
  
	 
	  currentFrame += 0.005*time;
	  if (currentFrame > 6) currentFrame -=6 ;

	  if (dx>0) sprite.setTextureRect(IntRect(40*int(currentFrame),244,40,50));
	  if (dx<0) sprite.setTextureRect(IntRect(40*int(currentFrame)+40,244,-40,50));
	 

	  sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	  dx=0;
   }



   void Collision(int dir)
   {
     for (int i = rect.top/32 ; i<(rect.top+rect.height)/32; i++)
	  for (int j = rect.left/32; j<(rect.left+rect.width)/32; j++)
		{ 
	  	 if (TileMap[i][j]=='B') 
		   { 
	        if ((dx>0) && (dir==0)) rect.left =  j*32 -  rect.width; 
		    if ((dx<0) && (dir==0)) rect.left =  j*32 + 32;
			if ((dy>0) && (dir==1))  { rect.top =   i*32 -  rect.height;  dy=0;   onGround=true; }
			if ((dy<0) && (dir==1))  { rect.top = i*32 + 32;   dy=0;}
		   }
		 
		 if (TileMap[i][j]=='0') 
		 { 
			money.play();
			TileMap[i][j]=' ';
			score++;
		 }	 
		 if (TileMap[i][j] == 'G')
		 {
			 cout << "GAME OVER" << endl;
			 cout << "SCORE: " << score << endl;
			 mario_smert.play();
			 system("pause");
			 exit(0);
		 }
		 if (TileMap[i][j] == 'X')
		 {
			 cout << "CONGRATULATION !!!" << endl;
			 cout << "Score: " << score << endl;
			 system("pause");
			 exit(0);
		 }
    	}  
   }
};

class Enemy : public Player{
private:
	FloatRect rect;
	float dx, dy;
	float currentFrame;
	Sprite sprite;
	bool life;
public:
	Enemy() {

	}
	void set(Texture &image, int x, int y) {
		sprite.setTexture(image);
		rect = FloatRect(x, y, 32, 32);

		dx = 0.005;
		currentFrame = 0;
		life = true;
	}

	void setLife(bool life) {
		this->life = life;
	}
	bool getLife() {
		return life;
	}
	Sprite getSprite() {
		return sprite;
	}

	void setRect(FloatRect rect) {
		this->rect = rect;
	}
	FloatRect getRect() {
		return rect;
	}

	void update(float time)
	{
		if (dx > 0) rect.left += dx * time;
		
		Collision();

		currentFrame += 0.003 * time;
		if (currentFrame > 6) currentFrame -= 6;

		if (dx > 0) sprite.setTextureRect(IntRect(40 * int(currentFrame), 244, 40, 50));

		if (!life) sprite.setTextureRect(IntRect(274, 1203, 58, 15));


		sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
	}



	void Collision()
	{
		for (int i = rect.top / 32; i < (rect.top + rect.height) / 32; i++)
			for (int j = rect.left / 32; j < (rect.left + rect.width) / 32; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					if (dx > 0) rect.left = j * 32 - rect.width;
					if (dx < 0) rect.left = j * 32 + rect.width;
				}
			}
	}
	~Enemy() {

	}
};

class Music_abstr{
public:
	virtual void music_play() = 0;
};

class Quiet_music : public Music_abstr {
public:
	void music_play() override {
		cout << "quiet music (10)" << endl;
		Music music;
		music.openFromFile("music/saundtrek.ogg");
		music.setVolume(10);
		music.play();
	}
};

class Loud_music : public Music_abstr {
public:
	void music_play() override {
		cout << "quiet music (50)" << endl;
		Music music;
		music.openFromFile("music/saundtrek.ogg");
		music.setVolume(50);
		music.play();
	}
};

class Music_play {
public:
	void music_play(Music_abstr *quiet_music) {
		quiet_music->music_play();
	}
};

int main()
{
	setlocale(0,"");
    RenderWindow window( VideoMode(600, 400), "Kursach!");

	Quiet_music quiet_music;
	Loud_music loud_music;

	Music_abstr* music;

	int a = 0;
	cout << "Громкий звук или нет?(1/0)" << endl;
	cin >> a;

	if(a == 1){ music = &loud_music; }
	else { music = &quiet_music; }

	music->music_play();

	Texture texture_person;
	texture_person.loadFromFile("images/fang.png");

	Image map_image;
	map_image.loadFromFile("images/TileSet.png");
	Texture map;
	map.loadFromImage(map_image);

	RectangleShape tile( Vector2f(32,32));

	SoundBuffer smert_buffer;
	smert_buffer.loadFromFile("music/mario-smert.ogg");
	Sound mario_smert(smert_buffer);
	mario_smert.setVolume(10);

	SoundBuffer money_buffer;
	money_buffer.loadFromFile("music/money.ogg");
	Sound money(money_buffer);
	money.setVolume(10);

	SoundBuffer jump_buffer;
	jump_buffer.loadFromFile("music/jump.ogg");
	Sound jump(jump_buffer);
	jump.setVolume(10);

	Music music1;
	music1.openFromFile("music/saundtrek.ogg");
	if (a == 1) music1.setVolume(50);
	else if (a == 0) music1.setVolume(10);
	music1.play();


	Player person(texture_person);
	person.setJump(jump);
	person.setMoney(money);
	person.setMario_smert(mario_smert);
	Enemy enemy;
	enemy.set(texture_person, 17 * 32, 14.5 * 32);


	Clock clock;
	float currentFrame = 0;


    while (window.isOpen())
    {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time/500;
		
		if (time>20) time = 20;

		Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)

                window.close();
        }

	    if (Keyboard::isKeyPressed(Keyboard::Left)) 
		{
			person.setDX(-0.1);

		}

	    if (Keyboard::isKeyPressed(Keyboard::Right)) 
		{
			person.setDX(0.1);
		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) 
		{
			if (person.getOnGround()) { person.setDY(-0.35); person.setOnGround(false);}
		}
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			if (person.getOnGround()) { person.setDY(0.35); person.setOnGround(false); }
			
			
		}


		person.update(time);
		enemy.update(time);

		if (person.getRect().intersects(enemy.getRect())) {
			if (person.getDY() > 0) { enemy.setDX(0); person.setDY(-0.45); enemy.setLife(false); }
			else {
				person.getSprite().setTextureRect(IntRect(274, 1203, 58, 15));
				mario_smert.play();
				music1.pause();
				cout << "GAME OVER" << endl;
				cout << "SCORE: " << score << endl;
				system("pause");	
				exit(1);
			}
		}

		if (person.getRect().left>200) offsetX = person.getRect().left - 200;
        offsetY = person.getRect().top - 200;


		window.clear(Color::White);


		 for (int i=0; i<H; i++)
			 for (int j=0; j<W ; j++)
				{ 
				 if (TileMap[i][j] == 'B') {
					 tile.setTexture(&map);
					 tile.setTextureRect(IntRect(326,305,23,25));
				 }

				 if (TileMap[i][j] == '0') { 
					 tile.setTexture(&map);
					 tile.setTextureRect(IntRect(86, 35, 23, 25));
				 }

				 if (TileMap[i][j] == 'G') {
					 tile.setTexture(&map);
					 tile.setTextureRect(IntRect(62, 132, 20, 20));
				 }

				 if (TileMap[i][j] == ' ') { 
					 tile.setTexture(&map);
					 tile.setTextureRect(IntRect(98, 118, 1, 1));
				 }

				 if (TileMap[i][j] == 'X') {
					 tile.setTexture(&map);
					 tile.setTextureRect(IntRect(110, 35, 19, 12));
				 }

				 if (TileMap[i][j] == 'L') {
					 tile.setTexture(&map);
					 tile.setTextureRect(IntRect(110, 47, 19, 11));
				 }

		          tile.setPosition(j*32-offsetX,i*32 - offsetY) ; 
		          window.draw(tile);
	       	 }

		window.draw(person.getSprite());
		window.draw(enemy.getSprite());
        window.display();
    }

    return 0;
}