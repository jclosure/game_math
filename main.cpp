#include <iostream>
#include <cmath>
#include <sstream>
#include <string>

class Vector
{
public:
    Vector() {}
    Vector(float X, float Y)
    {
        x = X;
        y = Y;
    }

    float x, y;
    float Length() const;
    float LengthSqr() const;

    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;

    Vector operator*(float s) const;
    Vector operator/(float s) const;

    Vector Normalized() const;

    float Dot(const Vector& v);

    const std::string toString() const
    {
        std::ostringstream buffer;
        buffer << std::fixed << "(" << x << ", " << y <<  ")" << std::endl;
        return buffer.str();
    }
};

float Vector::Length() const
{
    float length;
    length = sqrt((x * x) + (y * y));
    return length;
}

float Vector::LengthSqr() const
{
    float lengthSqr;
    lengthSqr = (x * x) + (y * y);
    return lengthSqr;
}

Vector Vector::operator+(const Vector &v) const
{
    return Vector(x + v.x, y + v.y);
}

Vector Vector::operator-(const Vector &v) const
{
    return Vector(x - v.x, y - v.y);
}

Vector Vector::operator*(float s) const
{
    Vector scaled;
    scaled.x = x * s;
    scaled.y = y * s;
    return scaled;
}

Vector Vector::operator/(float s) const
{
    Vector scaled;
    scaled.x = x / s;
    scaled.x = x / s;
    return scaled;
}

Vector Vector::Normalized() const
{
    Vector norml;
    norml = (*this) / Length();
    return norml;
}

float Vector::Dot(const Vector& b) {
    return (x * b.x) + (y * b.y);
}

class Player {
public:
    Vector position;
    Vector velocity;
    Vector gravity;

    const std::string toString() const
    {
        std::ostringstream buffer;
        buffer << std::fixed << "Player Position" << position.toString() << std::endl;
        buffer << std::fixed << "Player Velocity" << velocity.toString() << std::endl;
        buffer << std::fixed << "Player Gravity"  << gravity.toString() << std::endl;
        return buffer.str();
    }

    void Update(float dt);
};

void Player::Update(float dt)
{
    // new position is position + velocity scaled by the amount of time between updates
    position = position + velocity * dt;
    // new velocity is velocity + gravity scaled by the amount of time between updates (speeding up)
    velocity = velocity + gravity * dt;
}

inline float get_timestamp()
{
    std::chrono::time_point<std::chrono::steady_clock> ts = std::chrono::steady_clock::now();
    return 1.0f * std::chrono::duration_cast<std::chrono::microseconds>(ts.time_since_epoch()).count();
}

int main(int argc, char** args)
{
    Player player1;
    player1.position = Vector(2, 2);
    player1.velocity = Vector(2, 1);
    player1.gravity = Vector(0, -2);

    float curTime = 0;
    float prevTime = get_timestamp();

    // simple draw loop
    while (true)
    {
        prevTime = curTime;
        curTime = get_timestamp();
        float dt = curTime - prevTime;

        std::cout << "Delta: " << dt << std::endl;

        player1.Update(dt);

        std::cout << player1.toString();

        // exit when we hit the ground
        if (player1.position.y <= 0)
        {
            std::cout << "Hit the ground at velocity: " << player1.velocity.toString() << std::endl;
            break;
        }
    }

    return 0;
}