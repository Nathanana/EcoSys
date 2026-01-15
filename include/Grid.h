#include <vector>
#include "Entity.h"

class Grid {
private:
    int width, height;
    std::vector<std::vector<EntityType>> cells;

public:
    Grid(int w, int h);
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    EntityType get(int x, int y) const;
    void set(int x, int y, EntityType type);
    
    bool isValid(int x, int y) const;
    std::vector<std::pair<int, int>> getNeighbors(int x, int y) const;
};