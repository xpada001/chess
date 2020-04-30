#ifndef _INVALIDMOVE_H_
#define _INVALIDMOVE_H_

#include <stdexcept>

class InvalidMove: public std::exception {};

class SourceOutOfRange: public InvalidMove {};

class PieceDoesNotExist: public InvalidMove {};

class MovingEnemyPiece: public InvalidMove {};

class CapturingAllyPiece: public InvalidMove {};

class TargetOutOfRange: public InvalidMove {};

class SamePositionMove: public InvalidMove {};

class IllegalMove: public InvalidMove {};

class CheckedMove: public InvalidMove {};

#endif
