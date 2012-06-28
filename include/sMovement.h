
#ifndef _SMOVEMENT_H_
#define _SMOVEMENT_H_

/**
* Enumeration: direction
* North, East, South, West
* Purpose: Set Enemy image during directional movement.
*/
enum direction{
    North = 0,
    East,
    South,
    West
};

/**
* Struct: MM - "Movement"
* Purpose: Used to make predefined path. Movement struct
* keeps track of distance left (m_dist) in a direction (m_dir).
*/
typedef struct MM {
    int m_dir;
    float m_dist;

} Movement;


#endif /* _SMOVEMENT_H_ */
