#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include "person.h"
#include "chatroom.h"

int main_()
{
  ChatRoom room;

  auto john = room.join(Person{ "john" });
  auto jane = room.join(Person{ "jane" });

  john->say("hi room");
  jane->say("oh, hey john");

  auto simon = room.join(Person{ "simon" });
  simon->say("hi everyone!");

  jane->pm("simon", "glad you could join us, simon");

  getchar();
  return 0;
}
