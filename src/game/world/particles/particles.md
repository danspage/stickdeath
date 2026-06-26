# particles (multiple) object

* texture - the particle texture being used, relative to images/sprites/particles
* x, y - the origin of the particles
* random shift x, random shift y - an optional randomization factor for where the particle's origin is
* delta x, delta y - how far in each direction from the origin the particles will spread
* speed - how quickly the particles will move towards the delta
* count - the number of particles
* timeSinceBirth - how many seconds (float) the particles have existed for, used to destroy itself once the allotted time has elapsed
* particles (private) - a list of particle objects that will be updated and rendered

## particle (individual) object

* texture - the particle texture being used, relative to images/sprites/particles
* delta x, delta y - the delta in each direction the particle will move in over time, this will be chosen randomly upon creation given the particles speed and a random angle from the origin
