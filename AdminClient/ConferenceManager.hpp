#include "Conference.hpp"

Struct ConferenceManager {
  ConferenceManager() {temp = NULL;}
  ConferenceManager(Conference* itemp) : temp(itemp) { }
  Conference* temp;
};
