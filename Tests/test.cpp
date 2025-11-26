#include "pch.h"

const int HEIGHT = 25;
const int WIDTH = 40;
const int tileSize = 18;

#include"../16_SFML_Games/Grid.h"
#include"../16_SFML_Games/Player.h"

#include "../16_SFML_Games/SnakeGame.h"


TEST(Grid, HasWallsAndInterior) {

	Grid grid;

	EXPECT_EQ(Grid::tile::WALL, grid.cell(0, 0));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(24, 39));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(10, 10));

}

TEST(Grid, CreateNewWall) {

	Grid grid;

	grid.newWall(10, 10);
	EXPECT_EQ(Grid::tile::NEW_WALL, grid.cell(10, 10));

}


TEST(Grid, GridsIsClearedExceptForWalls) {

	Grid grid;

	grid.newWall(10, 10);

	grid.clear();
	EXPECT_EQ(Grid::tile::WALL, grid.cell(0, 0));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(24, 39));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(10, 10));

}

//------------------------
//|                      |
//|                      |
//|         filled       |
//|                      |
//|                      |
//|----------------------|
//|                      |
//|                      |
//|         not filled   |
//|                      |
//|                      |
//------------------------

TEST(Grid, GridsIsFilledWithHorizWall) {

	Grid grid;

	for(int i=1;i<WIDTH-1;i++)
		grid.newWall(10, i);

	grid.markConnectedCellsNotToBeFilled(11, 1);

	grid.fillEmptyCells();

	EXPECT_EQ(Grid::tile::WALL, grid.cell(1, 1));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(9, 38));

	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(11, 1));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(23, 38));

}

//------------------------
//|                      |
//|                      |
//|        not filled    |
//|                      |
//|                      |
//|-------------         |
//|            |         |
//|            |         |
//|   filled   |         |
//|            |         |
//|            |         |
//------------------------

TEST(Grid, GridsIsFilledWithHorizAndVertWall) {

	Grid grid;

	for (int x = 1; x < 10; x++)
		grid.newWall(10, x);
	for (int y = 10; y < HEIGHT-1; y++)
		grid.newWall(y, 10);

	grid.markConnectedCellsNotToBeFilled(2, 2);

	grid.fillEmptyCells();

	EXPECT_EQ(Grid::tile::WALL, grid.cell(11, 1));
	EXPECT_EQ(Grid::tile::WALL, grid.cell(23, 9));

	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(1, 1));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(9, 38));
	EXPECT_EQ(Grid::tile::EMPTY, grid.cell(23, 38));


}


TEST(Player, ConstrainedHorizontallyRight) {

	Player p;

	p.x = 10, p.y = 10;

	p.goRight();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(10, p.y);
	EXPECT_EQ(WIDTH-1, p.x);
}

TEST(Player, ConstrainedHorizontallyLeft) {

	Player p;

	p.x = 10, p.y = 10;

	p.goLeft();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(10, p.y);
	EXPECT_EQ(0, p.x);
}

TEST(Player, ConstrainedVerticallyUp) {

	Player p;

	p.x = 10, p.y = 10;

	p.goUp();

	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(0, p.y);
	EXPECT_EQ(10, p.x);
}

TEST(Player, ConstrainedDiagonallyFast) {

	Player p;

	p.x = 10, p.y = 10;
	p.dx = 5;
	p.dy = 6;

	
	for (int i = 0; i < 100; i++)
		p.move();

	EXPECT_EQ(HEIGHT-1, p.y);
	EXPECT_EQ(WIDTH-1, p.x);
}

TEST(SnakeGame, MovesRight) 
{
	SnakeGame game;

	game.setLenght(4);
	game.setHead(5, 5);
	game.setDirection(SnakeGame::Direction::Right);

	game.update();

	auto head = game.getSegment(0);
	EXPECT_EQ(6, head.x);
	EXPECT_EQ(5, head.y);
}

TEST(SnakeGame, MovesUp)
{
	SnakeGame game;

	game.setLenght(4);
	game.setHead(5, 5);
	game.setDirection(SnakeGame::Direction::Up);

	game.update();

	auto head = game.getSegment(0);
	EXPECT_EQ(5, head.x);
	EXPECT_EQ(4, head.y);
}

TEST(SnakeGame, WrapsRightEdge)
{
	SnakeGame game;

	game.setLenght(4);
	game.setHead(game.GRID_WIDTH, 5);
	game.setDirection(SnakeGame::Direction::Right);

	game.update();

	auto head = game.getSegment(0);
	EXPECT_EQ(0, head.x);
}

TEST(SnakeGame, EatsFruitIncreasesLenght)
{
	SnakeGame game;

	game.setLenght(3);
	game.setHead(4, 4);
	game.setDirection(SnakeGame::Direction::Right);
	game.setFruit(5, 4);

	game.update();

	EXPECT_EQ(4, game.getLength());
}

TEST(SnakeGame, SelfCollisionShortensSnake)
{
	SnakeGame game;

	game.setLenght(4);
	game.setSegment(0, 5, 5);
	game.setSegment(1, 6, 5);
	game.setSegment(2, 6, 6);
	game.setSegment(3, 5, 6);

	game.setDirection(SnakeGame::Direction::Down);

	game.update();

	EXPECT_EQ(2, game.getLength());
}