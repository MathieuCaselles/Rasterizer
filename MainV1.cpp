#include "Common.h"

const float FLOAT_MAX = std::numeric_limits<float>::max();

std::ostream& operator<<(std::ostream& os, const sf::Vector2f& vector2D)
{
    os << "[" << vector2D.x << ", " << vector2D.y << ']';
    return os;
}
std::ostream& operator<<(std::ostream& os, const sf::Vector2i& vector2D)
{
    os << "[" << vector2D.x << ", " << vector2D.y << ']';
    return os;
}

std::ostream& operator<<(std::ostream& os, const sf::Vector2u& vector2D)
{
    os << "[" << vector2D.x << ", " << vector2D.y << ']';
    return os;
}

/// <summary>
/// Draw a one pixel width vertical line in the specified image.
/// </summary>
/// <param name="image"></param>
/// <param name="column">Abscisse of the line  </param>
/// <param name="rowStart">Starting height of the line </param>
/// <param name="rowEnd">Ending height of the line  </param>
/// <param name="color"></param>
void drawVerticalLine(sf::Image& image, int x, int yStart, int yEnd, const sf::Color& color)
{
    for (int y = yStart; y <= yEnd; y++)
    {
        image.setPixel(x, y, color);
    }
}


/// <summary>
/// Draw a empty or filled rectangle in the specified image
/// </summary>
/// <param name="image"></param>
/// <param name="origin">top left point of the rectangle </param>
/// <param name="size">width and height of the rectangle </param>
/// <param name="color"></param>
/// <param name="filled">if true rect will be filled with color </param>
/// 
void drawRect(sf::Image& image, const sf::Vector2i& origin, const sf::Vector2i& size, const sf::Color& color, bool filled = true)
{
  
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; !filled && x > 0 && x < size.x - 1 ? x += size.x - 1 : ++x)
        {
            image.setPixel(origin.x + x, origin.y + y, color);
        }
    }
}


/// <summary>
///  The World map
/// >0 is a wall
/// </summary>

static const int g_mapWidth = 24;
static const int g_mapHeight = 24;

const sf::Color g_Color[6] = { sf::Color::White, sf::Color::Red, sf::Color::Yellow, sf::Color::Magenta, sf::Color::Green, sf::Color::Black };

int g_worldMap[g_mapWidth][g_mapHeight] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


// MAP TEST
//static const int g_mapWidth = 6;
//static const int g_mapHeight = 6;

//int g_worldMap[g_mapWidth][g_mapHeight] =
//{
//  {1,1,1,1,1,1},
//  {1,0,0,0,0,1},
//  {1,0,0,2,0,1},
//  {1,0,0,0,0,1},
//  {1,0,0,0,0,1},
//  {1,1,1,1,1,1},
//};


//calculate ray direction from abscisse in normalized 0-1 and camera direction
inline sf::Vector2f GetRayDir(float x,const sf::Vector2f& camDir)
{
    sf::Vector2f rightVec = Perpendicular(camDir);
    //x-coordinate in camera space -1.0f to 1.0f
    float camX = (2.0f * x) - 1.0f; 
    sf::Vector2f rayDir = camDir + rightVec * 0.66f*camX;
    return Normalize(rayDir);
}





/// <summary>
/// Return rotation sign (-1 right, 1 left, 0 no rotation) and position delta vector based on current inputs
/// </summary>
/// <param name="deltaPos">(Out) position delta vector</param>
/// <returns>rotation sign</returns>
float GetCameraMovementFromInput(float& deltaPos)
{
    float angle = 0.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        // move left...
        angle -= 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        // move right...
        angle += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        deltaPos += 1;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        deltaPos -= 1;
    }
    return angle;
}




inline int getAreaValue(sf::Vector2f area){
    return g_worldMap[(int)floorf(area.x)][(int)floorf(area.y)];
}

const sf::Vector2f GetFirstAreaFound(const sf::Vector2f& cameraPosition, const sf::Vector2f& rayDirection) {
    const float reducedDistance = 100.f; //allows you not to miss any area in map
    const sf::Vector2f& rayDirectionReduced = rayDirection / reducedDistance;

    sf::Vector2f nextArea = sf::Vector2f(
        cameraPosition.x + rayDirectionReduced.x,
        cameraPosition.y + rayDirectionReduced.y
    );


    while (getAreaValue(nextArea) == 0)
    {
        nextArea = {
            nextArea.x + rayDirectionReduced.x,
            nextArea.y + rayDirectionReduced.y
        };
    }

    return nextArea;
}




enum SideOfTheSquare {
    TOP , 
    RIGHT, 
    BOTTOM, 
    LEFT,
    TOP_LEFT ,
    TOP_RIGHT,
    BOTTOM_RIGHT,
    BOTTOM_LEFT
};

const SideOfTheSquare GetImpactedSide(const sf::Vector2f& area, const sf::Vector2f& vector) {
    const float angleBewteenAbscissaAndVector = abs(GetAngleBetweenVector({1, 0}, vector));
    if (vector.x < 0 && vector.y < 0) {
        const sf::Vector2f normalizeVectorAreaToTopLeft = Normalize(FloorfVector(area) - area);
        const float angleBewteenAbscissaAndAreaTopLeft = abs(GetAngleBetweenVector({ 1, 0 }, normalizeVectorAreaToTopLeft));
        if (angleBewteenAbscissaAndVector < angleBewteenAbscissaAndAreaTopLeft)
        {
            return TOP;
        }
        if (angleBewteenAbscissaAndVector > angleBewteenAbscissaAndAreaTopLeft)
        {
            return LEFT;
        }
        return TOP_LEFT;
    }

    if (vector.x >= 0 && vector.y < 0) {
        const sf::Vector2f normalizeVectorAreaToTopRight = Normalize(sf::Vector2f( floorf(area.x + 1.f), floorf(area.y) ) - area);
        const float angleBewteenAbscissaAndAreaTopRight = abs(GetAngleBetweenVector({ 1, 0 }, normalizeVectorAreaToTopRight));
        if (angleBewteenAbscissaAndVector < angleBewteenAbscissaAndAreaTopRight)
        {
            return RIGHT;
        }
        if (angleBewteenAbscissaAndVector > angleBewteenAbscissaAndAreaTopRight)
        {
            return TOP;
        }
        return TOP_RIGHT;
    }
    if (vector.x >= 0 && vector.y >= 0) {
        const sf::Vector2f normalizeVectorAreaToBottomRight = Normalize(sf::Vector2f(floorf(area.x + 1.f), floorf(area.y + 1.f)) - area);
        const float angleBewteenAbscissaAndAreaBottomRight = abs(GetAngleBetweenVector({ 1, 0 }, normalizeVectorAreaToBottomRight));
        if (angleBewteenAbscissaAndVector < angleBewteenAbscissaAndAreaBottomRight)
        {
            return RIGHT;
        }
        if (angleBewteenAbscissaAndVector > angleBewteenAbscissaAndAreaBottomRight)
        {
            return BOTTOM;
        }
        return BOTTOM_RIGHT;
    }

    const sf::Vector2f normalizeVectorAreaToBottomLeft = Normalize(sf::Vector2f(floorf(area.x), floorf(area.y + 1.f)) - area);
    const float angleBewteenAbscissaAndAreaBottomLeft = abs(GetAngleBetweenVector({ 1, 0 }, normalizeVectorAreaToBottomLeft));
    if (angleBewteenAbscissaAndVector < angleBewteenAbscissaAndAreaBottomLeft)
    {
        return BOTTOM;
    }
    if (angleBewteenAbscissaAndVector > angleBewteenAbscissaAndAreaBottomLeft)
    {
        return LEFT;
    }
    return BOTTOM_LEFT;
}


const float GetSizeOfAdjacentSide(const SideOfTheSquare& side, const sf::Vector2f& area) {
    switch (side)
    {
        case TOP:
            return area.y - floorf(area.y);

        case RIGHT:
            return floorf(area.x + 1) - area.x;

        case BOTTOM:
            return floorf(area.y + 1) - area.y;

        default:
            return area.x - floorf(area.x);
    }
}


const sf::Vector2f GetImpactWallInArea(const SideOfTheSquare& side, const sf::Vector2f& area, float sizeAdjacentSide, float sizeOpposeSide) {
    switch (side)
    {
        case TOP:
            return { area.x - sizeOpposeSide, floorf(area.y) };

        case RIGHT:
            return { ceilf(area.x), area.y - sizeOpposeSide };

        case BOTTOM:
            return { area.x + sizeOpposeSide, ceilf(area.y) };

        default:
            return { floorf(area.x), area.y + sizeOpposeSide };
    }
}


const sf::Vector2f GetImpactedWallOfArea(const sf::Vector2f& area, const sf::Vector2f& rayDirection) {
    const sf::Vector2f rayDirectionInverted = GetInverseVector(rayDirection);
    const SideOfTheSquare impactedSide = GetImpactedSide(area, rayDirectionInverted);

    sf::Vector2f directionToImpactedSize;
    switch (impactedSide)
    {
        case TOP_LEFT:
            return FloorfVector(area);
        case TOP_RIGHT:
            return { floorf(area.x + 1.f), floorf(area.y) };
        case BOTTOM_RIGHT:
            return { floorf(area.x + 1.f), floorf(area.y + 1.f) };
        case BOTTOM_LEFT:
            return { floorf(area.x), floorf(area.y + 1.f) };
        case TOP:
            directionToImpactedSize = { 0.f, -1.f };
            break;
        case RIGHT:
            directionToImpactedSize = { 1.f, 0.f };
            break;

        case BOTTOM:
            directionToImpactedSize = { 0.f, 1.f };
            break;

        default:
            directionToImpactedSize = { -1.f, 0.f };
    }


    float angle = GetAngleBetweenVector(directionToImpactedSize, rayDirectionInverted);
    const float sizeAdjacentSide = GetSizeOfAdjacentSide(impactedSide, area);
    const float sizeOpposeSide = sizeAdjacentSide * tanf(DegreeToRadian(angle));

    return GetImpactWallInArea(impactedSide, area, sizeAdjacentSide, sizeOpposeSide);
}





// Solution start 
// ------------------------------------------------------------------
static const float g_fov = 66.f;  // It's the result if I print the angle between GetRayDir(0, cameraDirection) and GetRayDir(1,cameraDirection)
static const float g_halfFov = g_fov / 2.f;
static const sf::Vector2i g_projectionPlane = { 1920, 1080 };

const sf::Vector2i g_centerprojectionPlane = g_projectionPlane / 2;
const float g_distanceToProjectionPlane = g_centerprojectionPlane.x / std::tanf(DegreeToRadian(g_halfFov));


void RasterizeScene(const sf::Vector2f& cameraPosition, const sf::Vector2f& cameraDirection, sf::Image& raster, const int* worldMap, int W, int H)
{
    for (float column = 0.f; column < g_projectionPlane.x; ++column)
    {
        const sf::Vector2f rayDirection = GetRayDir(NormalizeFloat(column, g_projectionPlane.x - 1), cameraDirection);
        const sf::Vector2f area = GetFirstAreaFound(cameraPosition, rayDirection);
        const sf::Vector2f wall = GetImpactedWallOfArea(area, rayDirection);

        const float angleThatCausesDistortion = (g_fov / 2) * ((2 * NormalizeFloat(column, g_projectionPlane.x - 1)) - 1);
        const float correctionDistortion = cosf(DegreeToRadian(angleThatCausesDistortion));
        float distanceToWall = GetDistanceBetween2Points(cameraPosition, wall) * correctionDistortion;

        const float heightWall = 1.f / distanceToWall * g_distanceToProjectionPlane;
        const int startY = g_centerprojectionPlane.y - heightWall / 2;

        drawVerticalLine(
            raster, 
            g_projectionPlane.x - 1 - column, // because get ray dir draws rays from right to left
            ClampFloat(startY, 0, g_projectionPlane.y - 1), 
            ClampFloat(startY + heightWall - 1, 0, g_projectionPlane.y - 1), 
            g_Color[getAreaValue(area)]
        );
    }
}
// -------------------------------------------------------------------
// Solution End 



int main()
{
    sf::Vector2i resolutionScreen = g_projectionPlane;
    sf::RenderWindow window(sf::VideoMode(resolutionScreen.x, resolutionScreen.y), "SFML Raycaster");

    // Vertical sync to don't waste energy running over 60 FPS
    window.setVerticalSyncEnabled(true);

    // select the font
    sf::Font font;
    if (!font.loadFromFile("arialbi.ttf"))
    {
        return 0;
    }

    sf::Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(20); // in pixels, not points!
    text.setFillColor(sf::Color::Black);

    // Image
    sf::Image raster;
    raster.create(window.getSize().x, window.getSize().y, sf::Color::Black);

    sf::Texture rasterTex;
    rasterTex.loadFromImage(raster);
    sf::Sprite test(rasterTex);

    const sf::Color floorColor(75, 43, 43);

    // Initial Camera position
    sf::Vector2f camPos(22, 12);
    // Initial camera direction vector
    sf::Vector2f camDir(-1.f, 0.f);
    // Camera rotation in speed in degree per second
    const float rotationSpeed = 45.0f;

    // Camera movement speed in m per second
    const float movementSpeed = 1.0f;

    // Main loop    
    sf::Clock clock;
    sf::Time fixedPhysic = sf::microseconds(16666);
    sf::Time updateTime;
    while (window.isOpen())
    {
        // Update delta time
        sf::Time elapsed = clock.restart();
        if (elapsed.asSeconds() > 0.1f)
            elapsed = sf::seconds(0.1f);
        updateTime += elapsed;

        // Grab inputs events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                {
                }
            }
        }

        // Get inputs
        float deltaPos = 0.0f;
        float rotationSign = GetCameraMovementFromInput(deltaPos);

        // Update Logic and physics at fixed timesteps
        while (updateTime >= fixedPhysic)
        {
            // Update physics
            camDir = RotateVector(camDir, rotationSign * rotationSpeed * fixedPhysic.asSeconds());
            camDir = Normalize(camDir);
            camPos += camDir * deltaPos * movementSpeed * fixedPhysic.asSeconds();

            // Clamp world position
            camPos = ClampVector(camPos, sf::Vector2f(0, 0), sf::Vector2f(g_mapWidth, g_mapHeight));

            updateTime -= fixedPhysic;
        }
       
        // Rendering
        window.clear(sf::Color(0, 128, 0));

        {
            // Fill image with blue color for sky
            drawRect(raster, sf::Vector2i(0, 0), { resolutionScreen.x, resolutionScreen.y / 2 }, sf::Color::Blue);
            //Fill image with brown color for floor
            drawRect(raster, sf::Vector2i(0, resolutionScreen.y / 2), { resolutionScreen.x, resolutionScreen.y / 2 }, floorColor);

            RasterizeScene(camPos, camDir, raster, reinterpret_cast<int*>(g_worldMap), g_mapWidth, g_mapHeight);
            // Update texture from image
            rasterTex.loadFromImage(raster);
        }

        text.setString("Camera Position : (" + std::to_string(camPos.x) + ", " + std::to_string(camPos.y) 
            + ")\nCamera Rotation : (" + std::to_string(camDir.x) + ", " + std::to_string(camDir.y) + ")");

        window.draw(test);

        window.draw(text);
        // UI
        window.setView(window.getDefaultView());

        window.display();
    }

    return 0;
}