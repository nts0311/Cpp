#include "Game.h"
#include <iostream>
#include <string>

using namespace std;
using namespace sf;

Game::Game(RenderWindow &window)
	:m_bird(), m_baseTexture(), m_bgTexture(), m_window(window),
	m_isStart(true), m_isOver(false), m_score(0), m_collided(false), m_highestScore(0), m_playedDieSound(false)
{
	m_baseTexture.loadFromFile("sprites//base.png");
	m_bgTexture.loadFromFile("sprites//background-day.png");
	m_background.setTexture(m_bgTexture);
	m_base.setTexture(m_baseTexture);

	m_background.setPosition(0, 0);
	m_base.setPosition(0, 450);

	m_pipeTexture.loadFromFile("sprites//pipe-green.png");

	/*m_pipes.push_back(Pipe(Vector2f(400, 0), m_pipeTexture));
	m_pipes.push_back(Pipe(Vector2f(580, 0), m_pipeTexture));
	m_pipes.push_back(Pipe(Vector2f(760, 0), m_pipeTexture));*/

	initPipes();

	if (!m_font.loadFromFile("sprites//font.ttf"))
	{
		
	}

	m_scoredText.setFont(m_font);
	m_scoredText.setCharacterSize(40);
	m_scoredText.setPosition(288 / 2 - 20, 70);
	m_scoredText.setStyle(Text::Bold);
	
	m_wingSB.loadFromFile("audio//wing.wav");
	m_pointSB.loadFromFile("audio//point.wav");
	m_hitSB.loadFromFile("audio//hit.wav");
	m_dieSB.loadFromFile("audio//die.wav");

	m_wingSound.setBuffer(m_wingSB);
	m_pointSound.setBuffer(m_pointSB);
	m_hitSound.setBuffer(m_hitSB);
	m_dieSound.setBuffer(m_dieSB);
}


Game::~Game()
{
}

void Game::update()
{
	if (!m_collided)
	{
		m_bird.fallDown();
		m_bird.move();
	}
	for (int i = 0; i < m_pipes.size(); i++)
	{
		float currentX = m_pipes[i].getPosition().x;

		if (m_bird.getPosition().x - currentX >= 52 && !m_pipes[i].m_isScored)
		{
			m_score++;
			m_pipes[i].m_isScored = true;
			m_pointSound.play();
		}
		if (currentX <= -52)
		{
			Vector2f prePipePos = m_pipes.back().getPosition();
			m_pipes.erase(m_pipes.begin() + i);
			m_pipes.push_back(Pipe(Vector2f(prePipePos.x + 180, prePipePos.y), m_pipeTexture));
		}
		else if(!m_collided && !m_isOver)
		{
			m_pipes[i].moveLeft();
		}
	}

	m_collided = checkCollision();
	if (m_collided)
	{
		m_isOver = true;
		m_isStart = false;

		if (!m_playedDieSound)
		{
			m_hitSound.play();
			m_dieSound.play();
			m_playedDieSound = true;
		}
		

		if (m_score > m_highestScore)
			m_highestScore = m_score;
	}
}

void Game::updateAnimation(float deltaTime)
{
	//So far, there is only bird flapping animation
	//Will add a ground animation
	m_bird.updateAnimation(deltaTime);
}

void Game::draw()
{
	

	m_window.draw(m_background);
	m_window.draw(m_base);
	m_window.draw(m_bird.getSprite());

	for (int i = 0; i < m_pipes.size(); i++)
	{
		float currentX = m_pipes[i].getPosition().x;
		if (currentX > 288 || currentX < -52)
			continue;

		m_window.draw(m_pipes[i].getDownSprite());
		m_window.draw(m_pipes[i].getUpSprite());
	}

	string s = to_string(m_score);
	m_scoredText.setString(s);
	m_window.draw(m_scoredText);

	if (m_isOver)
	{
		drawScoreBoard();
	}
}

void Game::reset()
{
	m_pipes.clear();
	//m_pipes.resize(3);
	initPipes();
	m_collided = false;
	m_isOver = false;
	m_score = 0;
	m_isStart = true;
	m_bird.getSprite().setPosition(288 / 2 - 70, 512 / 2);
	m_playedDieSound = false;
}

void Game::drawBackground()
{
	
}

Bird & Game::getBird()
{
	// TODO: insert return statement here
	return m_bird;
}

bool Game::checkCollision()
{
	if (m_bird.getPosition().y >= 450)
		return true; 

	for (int i = 0; i < m_pipes.size(); i++)
	{
		Vector2f pos = m_pipes[i].getPosition();
		float gapStart = m_pipes[i].getGapStart();
		float gapWidth = m_pipes[i].getGapWidth();

		RectangleShape r1(Vector2f(46.f, gapStart - 24));
		r1.setPosition(pos.x + 3, pos.y);

		RectangleShape r2(Vector2f(52.f, 24.f));
		r2.setPosition(pos.x, gapStart - 24);

		RectangleShape r3(Vector2f(52.f, 24.f));
		r3.setPosition(pos.x, gapStart + gapWidth);

		RectangleShape r4(Vector2f(46.f, m_pipes[i].getHeight() - gapStart - gapWidth - 24));
		r4.setPosition(pos.x + 3, pos.y + gapStart + gapWidth + 24);

		RectangleShape bird(Vector2f(32.f, 24.f));
		bird.setPosition(m_bird.getPosition());

		if (overlap(r1, bird) || overlap(r2, bird) || overlap(r3, bird) || overlap(r4, bird))
			return true;
	}

	return false;
}

bool Game::isOver()
{
	return m_isOver;
}

bool Game::isStart()
{
	return m_isStart;
}

void Game::playWingSound()
{
	m_wingSound.play();
}

bool Game::contain(RectangleShape & rect, Vector2f & point)
{
	Vector2f rectPos = rect.getPosition();
	Vector2f rectSize = rect.getSize();


	return (point.x >= rectPos.x && point.x <= rectPos.x + rectSize.x)
		&& (point.y >= rectPos.y && point.y <= rectPos.y + rectSize.y);
}

bool Game::overlap(RectangleShape & base, RectangleShape & target)
{
	Vector2f targetPos = target.getPosition();
	Vector2f targetSize = target.getSize();

	Vector2f p1(targetPos.x + targetSize.x, targetPos.y);
	Vector2f p2(targetPos.x, targetPos.y + targetSize.y);
	Vector2f p3(targetPos.x + targetSize.x, targetPos.y + targetSize.y);

	return contain(base, targetPos) || contain(base, p1) || contain(base, p2) || contain(base, p3);
}

void Game::initPipes()
{
	m_pipes.push_back(Pipe(Vector2f(400, 0), m_pipeTexture));
	m_pipes.push_back(Pipe(Vector2f(580, 0), m_pipeTexture));
	m_pipes.push_back(Pipe(Vector2f(760, 0), m_pipeTexture));
}

void Game::drawScoreBoard()
{
	RectangleShape board(Vector2f(200, 100));
	board.setPosition(44, 400);
	board.setFillColor(Color::Cyan);

	string s;

	s = "Your Score: " + to_string(m_score);
	Text ys;
	ys.setFont(m_font);
	ys.setString(s);
	ys.setCharacterSize(24);
	ys.setPosition(50, 55);
	ys.setFillColor(Color::Black);
	string hsstr = "Highest Score: " + to_string(m_highestScore);

	Text hs;
	hs.setFont(m_font);
	hs.setString(hsstr);
	hs.setCharacterSize(24);
	hs.setPosition(50, 90);
	hs.setFillColor(Color::Red);
	
	String g = "Click to continue";
	Text gt;
	gt.setFont(m_font);
	gt.setString(g);
	gt.setCharacterSize(15);
	gt.setPosition(50, 120);
	gt.setFillColor(Color::Black);

	//m_window.draw(board);
	m_window.draw(ys);
	m_window.draw(hs);
	m_window.draw(gt);
}

