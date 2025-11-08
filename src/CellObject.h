#ifndef CELLOBJECT_H
#define CELLOBJECT_H

#include <string>
#include <vector>

// Forward-declare Cell to avoid circular include.
class Cell;

enum class Category {Enemy, Player, Item};

class CellObject {
  protected:
    int r = 0;
    int c = 0;
    std::string color = "\e[0;37m";
    const std::string RESET = "\e[0m";

  public:
    virtual std::string getName() = 0;

    virtual char getChar() = 0;

    virtual std::string getColorChar();

	  virtual ~CellObject() = default;

    virtual Category getCtgy() = 0;

    virtual std::vector<int> getCord();

    virtual void setCord(int r, int c);
};

#endif
