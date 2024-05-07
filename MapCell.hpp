#pragma once
#ifndef MAPCELL_HPP
#define MAPCELL_HPP

enum class CellType {
    Empty,
    Wall,
    chest,
    character,
    Enemy,
    Door
    // Extend as needed with additional cell types.
};

class MapCell {
private:
    CellType type; // The type of the cell.

public:
    // Default constructor. Initializes the cell as empty.
    MapCell();

    // Constructor that allows initializing with a specific CellType
    explicit MapCell(CellType t);

    // Sets the type of the cell.
    void setType(CellType t);

    // Gets the current type of the cell.
    CellType getType() const;
};

#endif // MAPCELL_HPP