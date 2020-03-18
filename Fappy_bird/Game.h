#pragma once
#include "Bird.h"
#include "Pipe.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Game
{
public:
	Game(RenderWindow &window);
	~Game();

private:
	Bird m_bird;

	vector<Pipe> m_pipes;

	Texture m_bgTexture;
	Texture m_baseTexture;
	Texture m_pipeTexture;

	Sprite m_background;
	Sprite m_base;

	RenderWindow &m_window;

	bool m_isStart;
	bool m_isOver;
	bool m_collided;
	bool m_playedDieSound;

	int m_score;
	int m_highestScore;

	Font m_font;
	Text m_scoredText;

	SoundBuffer m_wingSB;
	SoundBuffer m_pointSB;
	SoundBuffer m_hitSB;
	SoundBuffer m_dieSB;

	Sound m_wingSound;
	Sound m_pointSound;
	Sound m_hitSound;
	Sound m_dieSound;

public:
	void update();
	void updateAnimation(float deltaTime);
	void draw();
	void reset();

	void drawBackground();
	Bird& getBird();

	bool checkCollision();

	bool isOver();
	bool isStart();

	void playWingSound();

private:
	bool contain(RectangleShape &rect, Vector2f &point);
	bool overlap(RectangleShape &base, RectangleShape &target);
	void initPipes();
	void drawScoreBoard();
};

