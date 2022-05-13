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
void DrawVerticalLine(sf::VertexArray& image, int x, int yStart, int yEnd, const sf::Color& color)
{
    image[x*2] = sf::Vertex(sf::Vector2f( x, yStart ), color);
    image[x*2+1] = sf::Vertex(sf::Vector2f(x, yEnd), color);
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
void DrawRect(sf::VertexArray& vertexArrayOfTriangleFan, const sf::Vector2i& origin, const sf::Vector2i& size, const sf::Color& color, sf::Texture& textureWall)
{
    sf::Vector2u textureSize = textureWall.getSize();

    vertexArrayOfTriangleFan[0] = sf::Vertex((sf::Vector2f)origin, color, sf::Vector2f(0, 0));
    vertexArrayOfTriangleFan[1] = sf::Vertex({ (float)(origin.x + size.x), (float)origin.y }, color, sf::Vector2f(0, textureSize.y - 1));
    vertexArrayOfTriangleFan[2] = sf::Vertex((sf::Vector2f)(origin + size), color, sf::Vector2f(textureSize.x - 1, textureSize.y - 1));
    vertexArrayOfTriangleFan[3] = sf::Vertex({ (float)origin.x, (float)(origin.y + size.y) }, color,
        sf::Vector2f(textureSize.x - 1, 0)
    );
}



/// <summary>
///  The World map
/// >0 is a wall
/// </summary>
const sf::Color g_Colors[6] = { 
    sf::Color::White, 
    sf::Color::Red, 
    sf::Color::Yellow, 
    sf::Color::Magenta, 
    sf::Color::Green, 
    sf::Color::Cyan 
};

static const int g_mapWidth = 24;
static const int g_mapHeight = 24;

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

sf::VertexArray g_vertexArraysInWalls[g_mapWidth * g_mapHeight];
bool wallOnView[g_mapWidth * g_mapHeight];

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







inline int GetAreaValue(sf::Vector2f area){
    return (area.x < 0.f || area.x > g_mapWidth || area.y < 0.f || area.y > g_mapHeight)
        ? 0
        : g_worldMap[(int)floorf(area.x)][(int)floorf(area.y)];
}

void DrawWall(sf::VertexArray* vertexArraysInWalls, const sf::Vector2f& lastArea, const float firstHeightWall, const float lastHeightWall, const float switchFaceWall,
    const float firstColumnWall, const float lastColumnWall, const float switchFaceColumnWall, const sf::Texture& texture, const sf::Color* colors, const sf::Vector2i& projectionPlane, const sf::Vector2i& centerProjectionPlane) {

    const float startYFirst = centerProjectionPlane.y - firstHeightWall / 2.f;
    const float startYLast = centerProjectionPlane.y - lastHeightWall / 2.f;
    sf::VertexArray& vertexArray = vertexArraysInWalls[ConvertCoordsInOneDimension(lastArea, g_mapHeight)];
    sf::Vector2u size = texture.getSize();
    if (switchFaceWall != firstHeightWall && switchFaceWall != lastHeightWall)
    {

        vertexArray.resize(6);
        const float startYMax = centerProjectionPlane.y - switchFaceWall / 2.f;
        vertexArray[0] = sf::Vertex(
            {
                projectionPlane.x - 1 - switchFaceColumnWall,
                startYMax,
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(0, 0)
            );
        vertexArray[1] = sf::Vertex(
            {
                projectionPlane.x - 1 - lastColumnWall,
                startYLast
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(0, size.y - 1)

        );
        vertexArray[2] = sf::Vertex(
            {
                projectionPlane.x - 1 - lastColumnWall,
                startYLast + lastHeightWall - 1
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(size.x - 1, size.y - 1)


        );
        vertexArray[3] = sf::Vertex(
            {
                projectionPlane.x - 1 - switchFaceColumnWall,
                startYMax + switchFaceWall - 1
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(size.x - 1, 0)
        );
        vertexArray[4] = sf::Vertex(
            {
                projectionPlane.x - firstColumnWall,
                startYFirst + firstHeightWall - 1
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(size.x - 1, size.y - 1)


        );
        vertexArray[5] = sf::Vertex(
            {
                projectionPlane.x - firstColumnWall,
                startYFirst
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(0, size.y - 1)

        );

    }
    else {

        vertexArray.resize(4);
        vertexArray[0] = sf::Vertex(
            {
                projectionPlane.x - firstColumnWall,
                startYFirst
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(0, 0)

        );
        vertexArray[1] = sf::Vertex(
            {
                projectionPlane.x - 1 - lastColumnWall,
                startYLast
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(0, size.y - 1)

        );
        vertexArray[2] = sf::Vertex(
            {
                projectionPlane.x - 1 - lastColumnWall,
                startYLast + lastHeightWall - 1
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(size.x - 1, size.y - 1)

        );
        vertexArray[3] = sf::Vertex(
            {
                projectionPlane.x - firstColumnWall,
                startYFirst + firstHeightWall - 1
            },
            colors[GetAreaValue(lastArea)],
            sf::Vector2f(size.x - 1, 0)

        );

    }
}

const sf::Vector2f GetHoriztonalWallByRayDirection(const sf::Vector2f& cameraPosition, const sf::Vector2f rayDirection, const float angleBewteenAbscissaAndRayDirection, const float tangent) {
    sf::Vector2f nextIntersection = {
        0.f,
        floorf(cameraPosition.y) + (rayDirection.y < 0.f ? -0.0001f : 1.f)
    };

    nextIntersection.x = abs(angleBewteenAbscissaAndRayDirection) == 90.f
        ? cameraPosition.x
        : cameraPosition.x + (cameraPosition.y - nextIntersection.y) / tangent;
    const float moveY = rayDirection.y < 0 ? -1.f : 1.f;
    float moveX = abs(angleBewteenAbscissaAndRayDirection) == 90.f
        ? 0.f
        : 1.f / tangent;
    moveX = abs(moveX) * (rayDirection.x < 0 ? -1 : 1);

    while (GetAreaValue(nextIntersection) == 0)
    {
        nextIntersection.x += moveX;
        nextIntersection.y += moveY;
    
        if (nextIntersection.x < 0.f
            || nextIntersection.x > g_mapWidth
            || nextIntersection.y < 0.f
            || nextIntersection.y > g_mapHeight
            )
        {
            return sf::Vector2f(FLOAT_MAX, FLOAT_MAX);
        }
    }
    return nextIntersection;
}

const sf::Vector2f GetVerticalWallByRayDirection(const sf::Vector2f& cameraPosition, const sf::Vector2f rayDirection, const float angleBewteenAbscissaAndRayDirection, const float tangent) {
    sf::Vector2f nextIntersection = {
      floorf(cameraPosition.x) + (rayDirection.x < 0.f ? -0.0001f : 1.f),
      0.f
    };

    nextIntersection.y = abs(angleBewteenAbscissaAndRayDirection) == 180.f
        ? cameraPosition.y
        : cameraPosition.y + (cameraPosition.x - nextIntersection.x) * tangent;

    const float moveX = rayDirection.x < 0 ? -1.f : 1.f;

    float moveY = abs(angleBewteenAbscissaAndRayDirection) == 180.f
        ? 0.f
        : tangent;

    moveY = abs(moveY) * (rayDirection.y < 0 ? -1 : 1);

    while (GetAreaValue(nextIntersection) == 0)
    {
        nextIntersection.x += moveX;
        nextIntersection.y += moveY;

        if (nextIntersection.x < 0.f 
            || nextIntersection.x > g_mapWidth 
            || nextIntersection.y < 0.f 
            || nextIntersection.y > g_mapHeight
            )
        {
            return sf::Vector2f(FLOAT_MAX, FLOAT_MAX);
        }
    }
    return nextIntersection;
}

const sf::Vector2f  GetWallByRayDirection(const sf::Vector2f& cameraPosition, const sf::Vector2f rayDirection) {
    const float angleBewteenAbscissaAndRayDirection =  GetAngleBetweenVector({ 1.f, 0.f }, rayDirection);
    const float tangent = tanf(DegreeToRadian(angleBewteenAbscissaAndRayDirection));

  
    const sf::Vector2f nextIntersectionHorizontal = GetHoriztonalWallByRayDirection(cameraPosition, rayDirection, angleBewteenAbscissaAndRayDirection, tangent);
    const sf::Vector2f nextIntersectionVertical = GetVerticalWallByRayDirection(cameraPosition, rayDirection, angleBewteenAbscissaAndRayDirection, tangent);

    return GetDistanceBetween2Points(cameraPosition, nextIntersectionHorizontal) < GetDistanceBetween2Points(cameraPosition, nextIntersectionVertical)
            ? nextIntersectionHorizontal
            : nextIntersectionVertical;
}




// Solution start 
// ------------------------------------------------------------------


void RasterizeScene(const sf::Vector2f& cameraPosition, const sf::Vector2f& cameraDirection, 
    sf::VertexArray* raster, sf::Texture& texture, const sf::Vector2i& projectionPlane, const sf::Vector2i& centerProjectionPlane, 
    float fov, float distanceToProjectionPlane, const sf::Color* colors)
{
    sf::Vector2f lastArea(FLOAT_MAX, FLOAT_MAX);
    sf::Vector2f lastWall(FLOAT_MAX, FLOAT_MAX);

    float firstHeightWall = 0.f, switchFaceWall = 0.f, lastHeightWall = 0.f;
    float firstColumnWall = 0.f, switchFaceColumnWall = 0.f, lastColumnWall = 0.f;

    for (float column = 0.f; column < projectionPlane.x; ++column)
    {
        const sf::Vector2f rayDirection = GetRayDir(NormalizeFloat(column, projectionPlane.x - 1), cameraDirection);
        const sf::Vector2f wall = GetWallByRayDirection(cameraPosition, rayDirection);

        const float angleThatCausesDistortion = (fov / 2) * ((2 * NormalizeFloat(column, projectionPlane.x - 1)) - 1);
        const float correctionDistortion = cosf(DegreeToRadian(angleThatCausesDistortion));
        float distanceToWall = GetDistanceBetween2Points(cameraPosition, wall) * correctionDistortion;

        const float heightWall = 1.f / distanceToWall * distanceToProjectionPlane;
        const int startY = centerProjectionPlane.y - heightWall / 2;


        if (lastArea.x == FLOAT_MAX)
        {
            lastArea = FloorfVector(wall);
            firstHeightWall = heightWall;
            firstColumnWall = column;
            switchFaceWall = heightWall;
            lastWall = wall;
        }
        if (lastArea != FloorfVector(wall) || column + 1 == projectionPlane.x)
        {

            DrawWall(raster, lastArea, firstHeightWall, lastHeightWall, switchFaceWall, firstColumnWall, lastColumnWall, switchFaceColumnWall, texture, colors, projectionPlane, centerProjectionPlane);

            lastArea = FloorfVector(wall);
            firstHeightWall = heightWall;
            lastHeightWall = heightWall;
            switchFaceWall = heightWall;
            firstColumnWall = column;


        }
        if (
            lastWall.x - floorf(lastWall.x) == 0.f && wall.x - floorf(wall.x) != 0.f
            || lastWall.x - floorf(lastWall.y) == 0.f && wall.y - floorf(wall.y) != 0.f
            || lastWall.y == floorf(lastWall.y) && lastWall.y != wall.y
            || lastWall.y + 0.0001f == floorf(lastWall.y + 0.0001f) && lastWall.y != wall.y
            || lastWall.x + 0.0001f == floorf(lastWall.x + 0.0001f) && lastWall.x != wall.x
            )
        {
            switchFaceWall = heightWall;
            switchFaceColumnWall = column;
        }
        lastHeightWall = heightWall;
        lastColumnWall = column;
        lastWall = wall;



            //Fill image with blue color for sky
            //DrawVerticalLine(
            //    raster,
            //    projectionPlane.x - 1 - column, // because get ray dir draws rays from right to left
            //    ClampFloat(startY, 0, projectionPlane.y - 1.f),
            //    ClampFloat(startY + heightWall - 1, 0, projectionPlane.y - 1.f),
            //    colors[GetAreaValue(FloorfVector(wall))]
            //);

    }
}
// -------------------------------------------------------------------
// Solution End 

static const float g_fov = 66.f;  // It's the result if I print the angle between GetRayDir(0, cameraDirection) and GetRayDir(1,cameraDirection)
static const float g_halfFov = 66 / 2.f;
static const sf::Vector2i g_projectionPlane = { 1920, 1080 };

const sf::Vector2i g_centerProjectionPlane = g_projectionPlane / 2;
const float g_distanceToProjectionPlane = g_centerProjectionPlane.x / std::tanf(DegreeToRadian(g_halfFov));


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
    sf::Texture textureWall;
    if (!textureWall.loadFromFile("texture/wall.jpg"))
    {
        return 0;
    }
    sf::Text text;
    text.setFont(font); // font is a sf::Font
    text.setCharacterSize(20); // in pixels, not points!
    text.setFillColor(sf::Color::Black);

    // Image
    //sf::Image raster;
    //raster.create(window.getSize().x, window.getSize().y, sf::Color::Black);


    /// TEST ///

    sf::VertexArray sky(sf::TriangleFan, 4);
    sf::VertexArray floor(sf::TriangleFan, 4);
    //sf::VertexArray rasterVertex(sf::Lines, 2 * 1920);

    //init g_vertexArraysInWalls
    std::fill_n(
        g_vertexArraysInWalls, 
        g_mapWidth * g_mapHeight,
        sf::VertexArray(sf::TriangleFan)
    );
   ////////////

    //sf::Texture rasterTex;
    //rasterTex.loadFromImage(raster);
    //sf::Sprite test(rasterTex);

    const sf::Color floorColor(75, 43, 43);

    // Initial Camera position
    sf::Vector2f camPos(22, 12);
    //sf::Vector2f camPos(4.5f, 3.5f);
    // Initial camera direction vector
    sf::Vector2f camDir(-1.f, 0.f);
    // Camera rotation in speed in degree per second
    const float rotationSpeed = 45.0f;

    // Camera movement speed in m per second
    const float movementSpeed = 1.0f;

    // Main loop    
    sf::Clock clock;

    {
        //auto start = GetTickCount64();

        // Fill image with blue color for sky
        DrawRect(sky, sf::Vector2i(0, 0), { resolutionScreen.x, resolutionScreen.y / 2 }, sf::Color::Blue, textureWall);


        //Fill image with brown color for floor
        DrawRect(floor, sf::Vector2i(0, resolutionScreen.y / 2), { resolutionScreen.x, resolutionScreen.y / 2 }, floorColor, textureWall);

        //auto end = GetTickCount64();
        //auto delta = (end - start) / 1000.0f;
        //printf("Time drawRect : %f s\n", delta);

    }




    while (window.isOpen())
    {
        // Update delta time
        const float deltaTime = clock.restart().asSeconds();
        //auto startFrame = GetTickCount64();

        const float fps = 1.0f / deltaTime;


        // PROCESS INPUT START 
        // ------------------------------------------------------------------
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Get inputs
        float deltaPos = 0.0f;
        float rotationSign = GetCameraMovementFromInput(deltaPos);
        // PROCESS INPUT END 
        // ------------------------------------------------------------------



        // UPDATE PHYSICS START 
        // ------------------------------------------------------------------
        camDir = RotateVector(camDir, rotationSign * rotationSpeed * deltaTime);
        camDir = Normalize(camDir);

        const sf::Vector2f nextPosition = FloorfVector(camPos + camDir * deltaPos * movementSpeed * deltaTime);

        // add collision int walls inside map
        if (GetAreaValue(nextPosition) == 0)
            camPos += camDir * deltaPos * movementSpeed * deltaTime;


        // Clamp world position
        camPos = ClampVector(camPos, sf::Vector2f(0, 0), sf::Vector2f(g_mapWidth, g_mapHeight));
        // UPDATE PHYSICS END 
        // ------------------------------------------------------------------
        




       
        // RENDERING START 
        // ------------------------------------------------------------------
        window.clear(sf::Color(0, 128, 0));

        {


            {
                auto start = GetTickCount64();

                for (auto& vertexArray : g_vertexArraysInWalls)
                {
                    vertexArray.clear();
                }/*
                rasterVertex.clear();
                rasterVertex.resize(2 * 1920);*/
                for (size_t i = 0; i < 100; i++)
                {
                    RasterizeScene(camPos, camDir, g_vertexArraysInWalls, textureWall, g_projectionPlane, g_centerProjectionPlane, g_fov, g_distanceToProjectionPlane, g_Colors);

                }

                auto end = GetTickCount64();
                auto delta = (end - start) / 1000.0f;
                printf("Time RasterizeScene : %f s\n", delta);
                printf("\n\n\n");

            }

            // Update texture from image
            //rasterTex.loadFromImage(raster);
        }

        text.setString("FPS: " + std::to_string((int)roundf(fps)) + "\nCamera Position : (" + std::to_string(camPos.x) + ", " + std::to_string(camPos.y)
            + ")\nCamera Rotation : (" + std::to_string(camDir.x) + ", " + std::to_string(camDir.y) + ")");

        //window.draw(test);
        window.draw(sky);
        window.draw(floor);
        //window.draw(rasterVertex, &textureWall);

        for (auto& vertexArray : g_vertexArraysInWalls)
        {
            window.draw(vertexArray, &textureWall);
        }


        window.draw(text);
        // UI
        window.setView(window.getDefaultView());

        window.display();
    }

    return 0;
}