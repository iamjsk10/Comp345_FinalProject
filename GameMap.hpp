#pragma once
#ifndef GAMEMAP_HPP
#define GAMEMAP_HPP

#include "MapCell.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <functional> // For std::function
#include "Character.hpp"
#include "MapObserver.hpp"

/// <summary>
/// Represents a 2D game map consisting of cells that can be empty, walls, or occupied.
/// Incorporates the observer pattern to notify changes in the map's state.
/// </summary>
class GameMap :public CharacterObserver {
private:
    std::string name;
    int width;  ///< Width of the game map in cells.
    int height; ///< Height of the game map in cells.
    std::vector<std::vector<MapCell>> grid; ///< 2D grid representing the game map.
    int startX = 0, startY = 0, endX = 0, endY = 0;
    std::list<std::function<void(const GameMap&)>> observers; ///< List of observer callbacks.
    std::list<MapObserver*> mapObservers;
public:
    /// Constructs a new GameMap with specified dimensions.
    /// @param w Width of the game map.
    /// @param h Height of the game map.
    GameMap(int w, int h);
    GameMap();
    void setName(std::string name);

    std::string getName() const;

    /// Adds an observer that is notified of changes to the map.
    /// @param observer Function to be called when the map changes.
    void addObserver(std::function<void(const GameMap&)> observer);

    /// Notifies all registered observers of a change in the map.
    void notifyObservers() const;

    /// Sets the type of a cell in the map.
    /// @param x X-coordinate of the cell.
    /// @param y Y-coordinate of the cell.
    /// @param type New type for the cell.
    void setCell(int x, int y, CellType type);

    void setDoor(int x, int y);

    /// Returns the width of the game map.
    /// @return Width of the map.
    int getWidth() const;

    /// Returns the height of the game map.
    /// @return Height of the map.
    int getHeight() const;

    /// Retrieves the type of a cell at specified coordinates.
    /// @param x X-coordinate of the cell.
    /// @param y Y-coordinate of the cell.
    /// @return Type of the cell at the specified coordinates.
    CellType getCellType(int x, int y) const;
    /// <summary>
    /// Setting the starting x-position;
    /// </summary>
    /// <param name="x">New x-postion (0-index)</param>
    void setStartX(int x);
    /// <summary>
    /// Setting the startin y-position
    /// </summary>
    /// <param name="y">New y-postion (0-index)</param>
    void setStartY(int y);
    /// <summary>
    /// Setting the ending x-position;
    /// </summary>
    /// <param name="x">New x-postion (0-index)</param>
    void setEndX(int x);
    /// <summary>
    /// Setting the ending y-position;
    /// </summary>
    /// <param name="y">New y-postion (0-index)</param>
    void setEndY(int y);
    /// <summary>
    /// Retrieving starting x-positon
    /// </summary>
    /// <returns>Current starting x-position</returns>
    int getStartX() const;
    /// <summary>
    /// Retrieving starting y-positon
    /// </summary>
    /// <returns>Current starting y-position</returns>
    int getStartY() const;
    /// <summary>
    /// Retrieving ending x-positon
    /// </summary>
    /// <returns>Current ending x-position</returns>
    int getEndX() const;
    /// <summary>
    /// Retrieving ending y-positon
    /// </summary>
    /// <returns>Current ending y-position</returns>
    int getEndY() const;
    /// <summary>
    /// Retrieving the grid/2d reprensentation of the Map
    /// </summary>
    /// <returns>vecotr of vector of MapCell</returns>
    std::vector<std::vector<MapCell>> getGrid() const;
    /// <summary>
    /// Setting the new grid
    /// </summary>
    /// <param name="grid">vecotr of vector of MapCell</param>
    void setGrid(std::vector<std::vector<MapCell>> grid);
    /// Checks if specified coordinates are within the bounds of the map.
    /// @param x X-coordinate to check.
    /// @param y Y-coordinate to check.
    /// @return True if coordinates are within bounds, false otherwise.
    bool isInBounds(int x, int y) const;
    bool verifyMap() const;
    /// Verifies if there is a path between two points on the map.
    /// @param startX X-coordinate of the start point.
    /// @param startY Y-coordinate of the start point.
    /// @param endX X-coordinate of the end point.
    /// @param endY Y-coordinate of the end point.
    /// @return True if a path exists, false otherwise.
    void characterMoved(const Character& character);
    void observeCharacter(Character& character);
    bool verifyMap(int startX, int startY, int endX, int endY);
    virtual void update(const Character& character);


    void addMapObserver(MapObserver* observer);
    void removeMapObserver(MapObserver* observer);
    void notifyMapObservers() const; // Notify UI or other components

};

#endif // GAMEMAP_HPP