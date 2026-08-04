# Particles (multiple) object

### Common

* Texture - the particle texture being used, relative to textures/sprites/particles
* Origin - the origin of the particles
* Random shift x/y - a randomization factor on each axis for where the particle's origin is
* Time since birth (float) - how many seconds the particles have existed for, used to destroy itself once the allotted time has elapsed
* Destroy time (float) - how many seconds the particles will exist for until they're destroyed
* Count - the number of particles
* Particles (private) - a list of particle objects that will be updated and rendered

### Circle

* Velocity (float)
* Velocity random amount

### Arc

* Velocity (float)
* Velocity random amount
* Radians/degrees option (enum) for arc angle
* Arc start/end

### Area

* Min x/y, max x/y
* x/y velocity
* x/y velocity random amount

## Particle (individual) object

* x, y - the position of the particle
* delta x, delta y - the delta in each direction the particle will move in over time, this will be chosen randomly upon creation given the particles speed and a random angle from the origin
