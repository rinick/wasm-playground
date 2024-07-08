#ifndef F1ORCE_H
#define F1ORCE_H

struct Force {

};

struct Relation {
    float frendly;
    float given; // sent food
    float givenC; // sent food change
    float allied; // alied days;
};

extern struct Relation forces[16];
extern struct Relation relations[16][16];

extern "C" {
    void initForces();
}

#endif // F1ORCE_H
