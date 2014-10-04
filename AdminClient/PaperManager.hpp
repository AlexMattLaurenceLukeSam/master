#include "Paper.hpp"

Struct PaperManager {
  PaperManager() {temp = NULL;}
  PaperManager(Paper* itemp) : temp(itemp) { }
  Paper* temp;
};
