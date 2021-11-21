#include "GO.h"

GO::GO(vec2 center, Shape shape)
{
    this->center = center;
    this->shape = shape;
    shape.setCenter(center);
    physics = DEFAULT_PHYSICS;
}
void GO::setDeltaTime(int deltaTime)
{
    this->deltaTime = deltaTime;
}
void GO::setCenter(vec2 center)
{
    this->center = center;
}
void GO::setPhysics(Physics physics)
{
    this->physics = physics;
}
void GO::setMoveMethod(MoveMethod moveMethod)
{
    this->moveMethod = moveMethod;
}
void GO::setMoving(bool moving)
{
    this->moving = moving;
}
void GO::setVisible(bool visible)
{
    this->visible = visible;
}
void GO::SetDest(vec2 dest)
{
    destination = dest;
    setMoving(true);
}

vec2 GO::getCenter()
{
    return center;
}
Physics GO::getPhysics()
{
    return physics;
}
MoveMethod GO::getMoveMethod()
{
    return moveMethod;
}
bool GO::isMoving()
{
    return moving;
}
bool GO::isColliding()
{
    return colliding;
}
bool GO::isVisible()
{
    return visible;
}

void GO::Translate(double x, double y)
{
    center.x += x;
    center.y += y;
}
void GO::Translate(vec2 delta)
{
    center += delta;
}

void GO::ApplyForce(vec2 force)
{
    physics.velocity += force;
}

// Update should be called every frame.
// It should move the object and draw to screen. (Only if visible)
void GO::update(SDL_Plotter &g)
{
    colliding = false;
    // check if the object is moving
    // if it is moving, cover up the old "frame" and draw new one
    // if it has reached its destination, isMoving = false
    // still draw things that aren't moving
    if (isMoving() || moveMethod == PHYSICS)
    {
        shape.setColor(BLANK);
        shape.draw(g, center);

        // Linear movement
        if (moveMethod == LINEAR)
        {
            vec2 linear = destination - getCenter();
            linear = linear.normalized();
            center += (linear*1.2);
        }
        // Ease movement
        else if (moveMethod == EASE)
        {
            setCenter(center.lerp(destination, .25 * deltaTime));
        }
        // Physics movement
        else if (moveMethod == PHYSICS)
        {
            center += physics.velocity * deltaTime;
        }
        if ((center - destination).sqrMagnitude() < 0.5)
        {
            setMoving(false);
        }
    }
    if (visible)
    {
        shape.setColor(RED);
        shape.draw(g, center);
    }
}

// Use their shapes to check collision and apply force if they are.
// The GameController will call this function for you if it thinks the two are colliding.
void GO::CheckCollision(GO& other)
{
    if (physics.canCollide && other.physics.canCollide)
    {
        if (shape.isColliding(other.shape))
        {
            Collide(other);
            other.Collide(*this);
        }
    }
}

//Called if is colliding.
void GO::Collide(GO& other)
{
    if(moveMethod == PHYSICS) {
        vec2 normal = other.shape.getCollisionAxis(shape).normalized();
        vec2 relativeVelocity = physics.velocity - other.physics.velocity;
        double normalVelocity = normal.dot(relativeVelocity);
        if (normalVelocity > 0)
        {
            normal = normal * -1;
            normalVelocity = normal.dot(relativeVelocity);
        }
        double e = (physics.bounce + other.physics.bounce) / 2;
        double j = -(1 + e) * normalVelocity;
        double impulse = j / (physics.mass + other.physics.mass);
        vec2 impulsePerMass = normal * impulse;
        physics.velocity += impulsePerMass * physics.mass;
    }
    colliding = true;
}