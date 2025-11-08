#ifndef CELL_H
#define CELL_H
#include "CellObject.h"
#include "Info.h"
#include "Observer.h"
#include "Subject.h"
#include <vector>

class Cell : public Subject, public Observer {
	const int r;            // Cell row
	const int c;            // Cell column
	const Type type;        // Type of Cell (eg. floor, door)
	int chamberNumber;      // Cell chamber Number
	int chamberOffset;
	CellObject *cellObject; // Keeps track of what is occuping the cell.

  public:
	// Constructor
	Cell(int r, int c, Type type, int chamberNumber = -1,
		int chamberOffset = 0, CellObject *cellobject = nullptr);

	~Cell();

	// Gets the info of the cell
	Info getInfo() const override;

	std::string getColorChar() const;

	// Set the item on the tile
	void setObject(CellObject *o);

	// Returns the tile's item
	CellObject *getObject();

	// Remove the bject from the Cell after consumption, this does
	//   not delete the object from memory.
	void removeObject();

	// Takes in the chamber number and spreads it across the Cells of the 
	//   entire chamber.
	void spreadChamberNumber(int cn, int *cs,
							 std::vector<std::vector<Cell*>> &vacantChamberCells);
	
	//void setChamberSize(int chamberSize);

	void setChamberOffset(int co);

	std::vector<int> getCord();

	void notify(const Subject &whoNotified) override;
};

#endif
