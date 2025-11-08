#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H

#include <vector>
#include <iostream>
#include "Observer.h"
#include "Subject.h"

class TextDisplay: public Observer {
    // 2D array which store all the ascii values
    std::vector<std::vector<std::string>> theDisplay;

  public:
    TextDisplay();
    friend std::ostream& operator<< (std::ostream& out, TextDisplay& td);
    void notify(const Subject& whoNotified) override;
};

std::ostream& operator<< (std::ostream& out, TextDisplay& td);

#endif
