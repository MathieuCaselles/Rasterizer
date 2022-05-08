#include <SFML/Graphics.hpp>
#include <math.h>

static const float PI = 3.14159265359f;

/// <summary>
/// Return a unnormalized vector perpendicular to the direction
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
inline sf::Vector2f Perpendicular(const sf::Vector2f& dir)
{
    sf::Vector2f perp = sf::Vector2f(dir.y, -dir.x);
    return perp;
}

/// <summary>
/// Return dot product between a and b
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
inline float Dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

/// <summary>
/// Return length of a vector2f
/// </summary>
/// <param name="a"></param>
/// <returns></returns>
inline float Length(const sf::Vector2f& a)
{
    return sqrtf(Dot(a, a));
}

/// <summary>
/// Normalize a 2D vector
/// </summary>
/// <param name="a">Vector to normalize</param>
/// <returns>normalized vector</returns>
inline sf::Vector2f Normalize(const sf::Vector2f& a)
{
    return a / Length(a);
}
/// <summary>
/// Rotate a 2D Direction vector with an angle in degree
/// </summary>
/// <param name="dir"></param>
/// <param name="angleInDegree">rotation angle</param>
/// <returns></returns>
inline sf::Vector2f RotateVector(const sf::Vector2f& dir, float angleInDegree)
{
    sf::Transform rotation;
    rotation.rotate(angleInDegree);
    return rotation.transformPoint(dir);
}
/// <summary>
/// Clamp a sf::vector2f between min and max
/// </summary>
/// <param name="pos"></param>
/// <param name="min"></param>
/// <param name="max"></param>
/// <returns>clamped vector</returns>
inline sf::Vector2f ClampVector(const sf::Vector2f& pos, const sf::Vector2f& min, const sf::Vector2f& max)
{
    sf::Vector2f res;

    res.x = (pos.x > max.x) ? max.x : (pos.x < min.x) ? min.x : pos.x;
    res.y = (pos.y > max.y) ? max.y : (pos.y < min.y) ? min.y : pos.y;

    return res;
}



inline float RadianToDegree(float r)
{
    return r * 180.0f / PI;
}

inline float DegreeToRadian(float d)
{
    return d * PI / 180.0f;
}


inline float GetSignAngleBetweenVector(const sf::Vector2f& perpendicularVector1, const  sf::Vector2f& vector2) {
    return Dot(perpendicularVector1, vector2) >= 0.0f ? 1.0f : -1.0f;
}


// Return the oriented angle in degree between 2 segment
// Positive mean shortest angle is left side
// negative mean shortest angle is right side
inline float GetAngleBetweenVector(const sf::Vector2f& vector1, const  sf::Vector2f& vector2)
{
    // Normalize them
    sf::Vector2f currentSegment = vector1 / Length(vector1);
    sf::Vector2f nextSegment = vector2 / Length(vector2);

    // Get The Perpendicular to orient the Angle correctly (right or left)
    sf::Vector2f perpendicularCurrent = Perpendicular(currentSegment);

    // Angle
    float dot = Dot(currentSegment, nextSegment);
    dot = fmaxf(dot, -1.0f);
    dot = fminf(dot, 1.0f);

    // Sign with perpendicular
    float sign = GetSignAngleBetweenVector(perpendicularCurrent, nextSegment);

    // Convert to degree and orient it with the sign
    float angle = sign * RadianToDegree(acosf(dot));

    return angle;
}

inline const sf::Vector2f GetInverseVector(const sf::Vector2f& vector) {
    return { -vector.x, -vector.y };
}

inline sf::Vector2f FloorfVector(const sf::Vector2f& vector) {
    return { floorf(vector.x), floorf(vector.y) };
}

inline float GetDistanceBetween2Points(const sf::Vector2f& point1, const sf::Vector2f& point2)
{
    return sqrtf(powf(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
    return sqrtf(powf(point2.x - point1.x, 2) + pow(point2.y - point1.y, 2));
}

inline float NormalizeFloat(float value, float max, float min = 0.f)
{
    return (value - min) / (max - min);
}

inline float ClampFloat(const float& value, const float& min, const float& max) {
    return (value > max) ? max : (value < min) ? min : value;
}