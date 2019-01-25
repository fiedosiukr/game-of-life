class Game {
public:
	Game(int size, int cellSize);
	~Game();
	void display();
	void update();

private:
	bool ** cells;
	bool ** updatedCells;
	int size, cellSize;

	void fillCells();
	void randomizeCells();
	bool inCells(int i, int j);
	int calculateNeighbours(int i, int j);
};
