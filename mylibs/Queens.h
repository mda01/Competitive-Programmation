//
// Created by mdano on 05/10/2020.
//

#ifndef DRAFT_QUEENS_H
#define DRAFT_QUEENS_H

#include <vector>
#include <cmath>

using namespace std;

class Queens {
public:
    struct Coordinate {
        int x, y;
    };

    static long long countQueens(int queenNumber, const vector<Coordinate> &places) {
        if (queenNumber == 8) {
            return places.size();
        } else {
            long long counter = 0;
            for (const Coordinate &place: places) {
                vector<Coordinate> newPlaces;
                for (const Coordinate nextPlace: places) {
                    if (nextPlace.x > place.x && nextPlace.y != place.y &&
                        abs(nextPlace.x - place.x) != abs(nextPlace.y - place.y)) {
                        newPlaces.push_back(nextPlace);
                    }
                }
                if (!newPlaces.empty())
                    counter += countQueens(queenNumber + 1, newPlaces);
            }
            return counter;
        }
    }
};


#endif //DRAFT_QUEENS_H
