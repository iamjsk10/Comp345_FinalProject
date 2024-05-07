// MapObserver.hpp

#pragma once

class MapObserver {
public:
    virtual ~MapObserver() = default;
    virtual void updateMapDisplay() = 0;
};
