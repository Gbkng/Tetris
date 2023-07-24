#include "map.hpp"

namespace tetris {

std::string logicTypeToStr(LogicType type) {
  switch (type) {
  case Void:
    return "Void";
    break;
  case Wall:
    return "Wall";
    break;
  case GameOver:
    return "GameOver";
    break;
  case Bottom:
    return "Bottom";
    break;
  case Square:
    return "Square";
    break;
  case T:
    return "T";
    break;
  case L:
    return "L";
    break;
  case InversedL:
    return "InversedL";
    break;
  case Bar:
    return "Bar";
    break;
  case S:
    return "S";
    break;
  case Z:
    return "Z";
    break;
  case OutOfBound:
    return "OutOfBound";
    break;
  default:
    assert(false && "Conversion from LogicType to str not handled.");
    return "";
    break;
  }
}

} // namespace tetris
