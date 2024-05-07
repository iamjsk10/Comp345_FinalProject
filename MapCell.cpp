#include "MapCell.hpp"

MapCell::MapCell() : type(CellType::Empty) {}

// Constructor that allows initializing with a specific CellType
MapCell::MapCell(CellType t) : type(t) {}

void MapCell::setType(CellType t) {
    type = t;
}

CellType MapCell::getType() const {
    return type;
}