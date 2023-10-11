#include "MeshManager.h"
#include "GameManager.h"
#include <malloc.h>

MeshManager::MeshManager()
{
}

Mesh MeshManager::GenerateMesh(Image cubicmap, Vector3 cubeSize)
{
#define COLOR_EQUAL(col1, col2) ((col1.r == col2.r)&&(col1.g == col2.g)&&(col1.b == col2.b)&&(col1.a == col2.a))

    numObjects = 0;
    Mesh mesh = { 0 };

    //if(objects != nullptr) free(objects);

    Color* pixels = LoadImageColors(cubicmap);

    int mapWidth = cubicmap.width;
    int mapHeight = cubicmap.height;

    // NOTE: Max possible number of triangles numCubes*(12 triangles by cube)
    int maxTriangles = cubicmap.width * cubicmap.height * 12;

    int vCounter = 0;       // Used to count vertices
    int tcCounter = 0;      // Used to count texcoords
    int nCounter = 0;       // Used to count normals

    float w = cubeSize.x;
    float h = cubeSize.z;
    float h2 = cubeSize.y;

    Vector3* mapVertices = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));
    Vector2* mapTexcoords = (Vector2*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector2));
    Vector3* mapNormals = (Vector3*)RL_MALLOC(maxTriangles * 3 * sizeof(Vector3));

    // Define the 6 normals of the cube, we will combine them accordingly later...
    Vector3 n1 = { 1.0f, 0.0f, 0.0f };
    Vector3 n2 = { -1.0f, 0.0f, 0.0f };
    Vector3 n3 = { 0.0f, 1.0f, 0.0f };
    Vector3 n4 = { 0.0f, -1.0f, 0.0f };
    Vector3 n5 = { 0.0f, 0.0f, -1.0f };
    Vector3 n6 = { 0.0f, 0.0f, 1.0f };

    // NOTE: We use texture rectangles to define different textures for top-bottom-front-back-right-left (6)
    typedef struct RectangleF {
        float x;
        float y;
        float width;
        float height;
    } RectangleF;

    //RectangleF rightTexUV = { 0.0f, 0.0f, 0.5f, 0.5f };
    RectangleF rightTexUV[4] = {
        {0.0f, 0.0f, 0.25f, 0.25f},
        {0.5f, 0.0f, 0.25f, 0.25f},
        {0.0f, 0.5f, 0.25f, 0.25f},
        {0.5f, 0.5f, 0.25f, 0.25f}
    };
    //RectangleF leftTexUV = { 0.5f, 0.0f, 0.5f, 0.5f };
    RectangleF leftTexUV[4] = {
        {0.25f, 0.0f, 0.25f, 0.25f},
        {0.75f, 0.0f, 0.25f, 0.25f},
        {0.25f, 0.5f, 0.25f, 0.25f},
        {0.75f, 0.5f, 0.25f, 0.25f}
    };
    //RectangleF frontTexUV = { 0.0f, 0.0f, 0.5f, 0.5f };
    RectangleF frontTexUV[4] = {
        {0.0f, 0.0f, 0.25f, 0.25f},
        {0.5f, 0.0f, 0.25f, 0.25f},
        {0.0f, 0.5f, 0.25f, 0.25f},
        {0.5f, 0.5f, 0.25f, 0.25f}
    };
    //RectangleF backTexUV = { 0.5f, 0.0f, 0.5f, 0.5f };
    RectangleF backTexUV[4] = {
        {0.25f, 0.0f, 0.25f, 0.25f},
        {0.5f, 0.0f, 0.25f, 0.25f},
        {0.25f, 0.5f, 0.25f, 0.25f},
        {0.5f, 0.5f, 0.25f, 0.25f}
    };
    //RectangleF topTexUV = { 0.0f, 0.5f, 0.5f, 0.5f };
    RectangleF topTexUV[4] = {
        {0.0f, 0.25f, 0.25f, 0.25f},
        {0.5f, 0.25f, 0.25f, 0.25f},
        {0.0f, 0.75f, 0.25f, 0.25f},
        {0.5f, 0.75f, 0.25f, 0.25f}
    };
    //RectangleF bottomTexUV = { 0.5f, 0.5f, 0.5f, 0.5f };
    RectangleF bottomTexUV[4] = {
        {0.25f, 0.25f, 0.25f, 0.25f},
        {0.75f, 0.25f, 0.25f, 0.25f},
        {0.25f, 0.75f, 0.25f, 0.25f},
        {0.75f, 0.75f, 0.25f, 0.25f}
    };

    for (int z = 0; z < mapHeight; ++z)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            // Define the 8 vertex of the cube, we will combine them accordingly later...
            Vector3 v1 = { w * (x - 0.5f), h2, h * (z - 0.5f) };
            Vector3 v2 = { w * (x - 0.5f), h2, h * (z + 0.5f) };
            Vector3 v3 = { w * (x + 0.5f), h2, h * (z + 0.5f) };
            Vector3 v4 = { w * (x + 0.5f), h2, h * (z - 0.5f) };
            Vector3 v5 = { w * (x + 0.5f), 0, h * (z - 0.5f) };
            Vector3 v6 = { w * (x - 0.5f), 0, h * (z - 0.5f) };
            Vector3 v7 = { w * (x - 0.5f), 0, h * (z + 0.5f) };
            Vector3 v8 = { w * (x + 0.5f), 0, h * (z + 0.5f) };
            if (pixels[z * cubicmap.width + x].r == 255)

                // We check pixel color to be WHITE -> draw full cube
                //if (COLOR_EQUAL(pixels[z * cubicmap.width + x], WHITE))
            {
                // Define triangles and checking collateral cubes
                //------------------------------------------------

                // Define top triangles (2 tris, 6 vertex --> v1-v2-v3, v1-v3-v4)
                // WARNING: Not required for a WHITE cubes, created to allow seeing the map from outside
                mapVertices[vCounter] = v1;
                mapVertices[vCounter + 1] = v2;
                mapVertices[vCounter + 2] = v3;
                mapVertices[vCounter + 3] = v1;
                mapVertices[vCounter + 4] = v3;
                mapVertices[vCounter + 5] = v4;
                vCounter += 6;

                mapNormals[nCounter] = n3;
                mapNormals[nCounter + 1] = n3;
                mapNormals[nCounter + 2] = n3;
                mapNormals[nCounter + 3] = n3;
                mapNormals[nCounter + 4] = n3;
                mapNormals[nCounter + 5] = n3;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x, topTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 1] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x, topTexUV[pixels[z * cubicmap.width + x].b].y + topTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 2] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x + topTexUV[pixels[z * cubicmap.width + x].b].width, topTexUV[pixels[z * cubicmap.width + x].b].y + topTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 3] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x, topTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 4] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x + topTexUV[pixels[z * cubicmap.width + x].b].width, topTexUV[pixels[z * cubicmap.width + x].b].y + topTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 5] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x + topTexUV[pixels[z * cubicmap.width + x].b].width, topTexUV[pixels[z * cubicmap.width + x].b].y };
                tcCounter += 6;

                // Define bottom triangles (2 tris, 6 vertex --> v6-v8-v7, v6-v5-v8)
                mapVertices[vCounter] = v6;
                mapVertices[vCounter + 1] = v8;
                mapVertices[vCounter + 2] = v7;
                mapVertices[vCounter + 3] = v6;
                mapVertices[vCounter + 4] = v5;
                mapVertices[vCounter + 5] = v8;
                vCounter += 6;

                mapNormals[nCounter] = n4;
                mapNormals[nCounter + 1] = n4;
                mapNormals[nCounter + 2] = n4;
                mapNormals[nCounter + 3] = n4;
                mapNormals[nCounter + 4] = n4;
                mapNormals[nCounter + 5] = n4;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x + bottomTexUV[pixels[z * cubicmap.width + x].b].width, bottomTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 1] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x, bottomTexUV[pixels[z * cubicmap.width + x].b].y + bottomTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 2] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x + bottomTexUV[pixels[z * cubicmap.width + x].b].width, bottomTexUV[pixels[z * cubicmap.width + x].b].y + bottomTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 3] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x + bottomTexUV[pixels[z * cubicmap.width + x].b].width, bottomTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 4] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x, bottomTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 5] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x, bottomTexUV[pixels[z * cubicmap.width + x].b].y + bottomTexUV[pixels[z * cubicmap.width + x].b].height };
                tcCounter += 6;

                if (((z < cubicmap.height - 1) && (pixels[(z + 1) * cubicmap.width + x].r == 0) || pixels[(z + 1) * cubicmap.width + x].r == 128) || (z == cubicmap.height - 1))
                    // Checking cube on bottom of current cube
                    //if (((z < cubicmap.height - 1) && COLOR_EQUAL(pixels[(z + 1) * cubicmap.width + x], BLACK)) || (z == cubicmap.height - 1))
                {
                    // Define front triangles (2 tris, 6 vertex) --> v2 v7 v3, v3 v7 v8
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v2;
                    mapVertices[vCounter + 1] = v7;
                    mapVertices[vCounter + 2] = v3;
                    mapVertices[vCounter + 3] = v3;
                    mapVertices[vCounter + 4] = v7;
                    mapVertices[vCounter + 5] = v8;
                    vCounter += 6;

                    mapNormals[nCounter] = n6;
                    mapNormals[nCounter + 1] = n6;
                    mapNormals[nCounter + 2] = n6;
                    mapNormals[nCounter + 3] = n6;
                    mapNormals[nCounter + 4] = n6;
                    mapNormals[nCounter + 5] = n6;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ frontTexUV[pixels[z * cubicmap.width + x].b].x, frontTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 1] = Vector2{ frontTexUV[pixels[z * cubicmap.width + x].b].x, frontTexUV[pixels[z * cubicmap.width + x].b].y + frontTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 2] = Vector2{ frontTexUV[pixels[z * cubicmap.width + x].b].x + frontTexUV[pixels[z * cubicmap.width + x].b].width, frontTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 3] = Vector2{ frontTexUV[pixels[z * cubicmap.width + x].b].x + frontTexUV[pixels[z * cubicmap.width + x].b].width, frontTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 4] = Vector2{ frontTexUV[pixels[z * cubicmap.width + x].b].x, frontTexUV[pixels[z * cubicmap.width + x].b].y + frontTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 5] = Vector2{ frontTexUV[pixels[z * cubicmap.width + x].b].x + frontTexUV[pixels[z * cubicmap.width + x].b].width, frontTexUV[pixels[z * cubicmap.width + x].b].y + frontTexUV[pixels[z * cubicmap.width + x].b].height };
                    tcCounter += 6;
                }

                if (((z > 0) && (pixels[(z - 1) * cubicmap.width + x].r == 0 || pixels[(z - 1) * cubicmap.width + x].r == 128)) || (z == 0))
                    // Checking cube on top of current cube
                    //if (((z > 0) && COLOR_EQUAL(pixels[(z - 1) * cubicmap.width + x], BLACK)) || (z == 0))
                {
                    // Define back triangles (2 tris, 6 vertex) --> v1 v5 v6, v1 v4 v5
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v1;
                    mapVertices[vCounter + 1] = v5;
                    mapVertices[vCounter + 2] = v6;
                    mapVertices[vCounter + 3] = v1;
                    mapVertices[vCounter + 4] = v4;
                    mapVertices[vCounter + 5] = v5;
                    vCounter += 6;

                    mapNormals[nCounter] = n5;
                    mapNormals[nCounter + 1] = n5;
                    mapNormals[nCounter + 2] = n5;
                    mapNormals[nCounter + 3] = n5;
                    mapNormals[nCounter + 4] = n5;
                    mapNormals[nCounter + 5] = n5;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ backTexUV[pixels[z * cubicmap.width + x].b].x + backTexUV[pixels[z * cubicmap.width + x].b].width, backTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 1] = Vector2{ backTexUV[pixels[z * cubicmap.width + x].b].x, backTexUV[pixels[z * cubicmap.width + x].b].y + backTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 2] = Vector2{ backTexUV[pixels[z * cubicmap.width + x].b].x + backTexUV[pixels[z * cubicmap.width + x].b].width, backTexUV[pixels[z * cubicmap.width + x].b].y + backTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 3] = Vector2{ backTexUV[pixels[z * cubicmap.width + x].b].x + backTexUV[pixels[z * cubicmap.width + x].b].width, backTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 4] = Vector2{ backTexUV[pixels[z * cubicmap.width + x].b].x, backTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 5] = Vector2{ backTexUV[pixels[z * cubicmap.width + x].b].x, backTexUV[pixels[z * cubicmap.width + x].b].y + backTexUV[pixels[z * cubicmap.width + x].b].height };
                    tcCounter += 6;
                }

                if (((x < cubicmap.width - 1) && (pixels[z * cubicmap.width + (x + 1)].r == 0) || pixels[z * cubicmap.width + (x + 1)].r == 128) || (x == cubicmap.width - 1))
                    // Checking cube on right of current cube
                    //if (((x < cubicmap.width - 1) && COLOR_EQUAL(pixels[z * cubicmap.width + (x + 1)], BLACK)) || (x == cubicmap.width - 1))
                {
                    // Define right triangles (2 tris, 6 vertex) --> v3 v8 v4, v4 v8 v5
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v3;
                    mapVertices[vCounter + 1] = v8;
                    mapVertices[vCounter + 2] = v4;
                    mapVertices[vCounter + 3] = v4;
                    mapVertices[vCounter + 4] = v8;
                    mapVertices[vCounter + 5] = v5;
                    vCounter += 6;

                    mapNormals[nCounter] = n1;
                    mapNormals[nCounter + 1] = n1;
                    mapNormals[nCounter + 2] = n1;
                    mapNormals[nCounter + 3] = n1;
                    mapNormals[nCounter + 4] = n1;
                    mapNormals[nCounter + 5] = n1;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ rightTexUV[pixels[z * cubicmap.width + x].b].x, rightTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 1] = Vector2{ rightTexUV[pixels[z * cubicmap.width + x].b].x, rightTexUV[pixels[z * cubicmap.width + x].b].y + rightTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 2] = Vector2{ rightTexUV[pixels[z * cubicmap.width + x].b].x + rightTexUV[pixels[z * cubicmap.width + x].b].width, rightTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 3] = Vector2{ rightTexUV[pixels[z * cubicmap.width + x].b].x + rightTexUV[pixels[z * cubicmap.width + x].b].width, rightTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 4] = Vector2{ rightTexUV[pixels[z * cubicmap.width + x].b].x, rightTexUV[pixels[z * cubicmap.width + x].b].y + rightTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 5] = Vector2{ rightTexUV[pixels[z * cubicmap.width + x].b].x + rightTexUV[pixels[z * cubicmap.width + x].b].width, rightTexUV[pixels[z * cubicmap.width + x].b].y + rightTexUV[pixels[z * cubicmap.width + x].b].height };
                    tcCounter += 6;
                }

                if (((x > 0) && (pixels[z * cubicmap.width + (x - 1)].r == 0) || pixels[z * cubicmap.width + (x - 1)].r == 128) || (x == 0))
                    // Checking cube on left of current cube
                    //if (((x > 0) && COLOR_EQUAL(pixels[z * cubicmap.width + (x - 1)], BLACK)) || (x == 0))
                {
                    // Define left triangles (2 tris, 6 vertex) --> v1 v7 v2, v1 v6 v7
                    // NOTE: Collateral occluded faces are not generated
                    mapVertices[vCounter] = v1;
                    mapVertices[vCounter + 1] = v7;
                    mapVertices[vCounter + 2] = v2;
                    mapVertices[vCounter + 3] = v1;
                    mapVertices[vCounter + 4] = v6;
                    mapVertices[vCounter + 5] = v7;
                    vCounter += 6;

                    mapNormals[nCounter] = n2;
                    mapNormals[nCounter + 1] = n2;
                    mapNormals[nCounter + 2] = n2;
                    mapNormals[nCounter + 3] = n2;
                    mapNormals[nCounter + 4] = n2;
                    mapNormals[nCounter + 5] = n2;
                    nCounter += 6;

                    mapTexcoords[tcCounter] = Vector2{ leftTexUV[pixels[z * cubicmap.width + x].b].x, leftTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 1] = Vector2{ leftTexUV[pixels[z * cubicmap.width + x].b].x + leftTexUV[pixels[z * cubicmap.width + x].b].width, leftTexUV[pixels[z * cubicmap.width + x].b].y + leftTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 2] = Vector2{ leftTexUV[pixels[z * cubicmap.width + x].b].x + leftTexUV[pixels[z * cubicmap.width + x].b].width, leftTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 3] = Vector2{ leftTexUV[pixels[z * cubicmap.width + x].b].x, leftTexUV[pixels[z * cubicmap.width + x].b].y };
                    mapTexcoords[tcCounter + 4] = Vector2{ leftTexUV[pixels[z * cubicmap.width + x].b].x, leftTexUV[pixels[z * cubicmap.width + x].b].y + leftTexUV[pixels[z * cubicmap.width + x].b].height };
                    mapTexcoords[tcCounter + 5] = Vector2{ leftTexUV[pixels[z * cubicmap.width + x].b].x + leftTexUV[pixels[z * cubicmap.width + x].b].width, leftTexUV[pixels[z * cubicmap.width + x].b].y + leftTexUV[pixels[z * cubicmap.width + x].b].height };
                    tcCounter += 6;
                }
            }
            else if (pixels[z * cubicmap.width + x].r == 0 || pixels[z * cubicmap.width + x].r == 128)
                // We check pixel color to be BLACK, we will only draw floor and roof
                //else if (COLOR_EQUAL(pixels[z * cubicmap.width + x], BLACK))
            {
                // Define top triangles (2 tris, 6 vertex --> v1-v2-v3, v1-v3-v4)
                mapVertices[vCounter] = v1;
                mapVertices[vCounter + 1] = v3;
                mapVertices[vCounter + 2] = v2;
                mapVertices[vCounter + 3] = v1;
                mapVertices[vCounter + 4] = v4;
                mapVertices[vCounter + 5] = v3;
                vCounter += 6;

                mapNormals[nCounter] = n4;
                mapNormals[nCounter + 1] = n4;
                mapNormals[nCounter + 2] = n4;
                mapNormals[nCounter + 3] = n4;
                mapNormals[nCounter + 4] = n4;
                mapNormals[nCounter + 5] = n4;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x, topTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 1] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x + topTexUV[pixels[z * cubicmap.width + x].b].width, topTexUV[pixels[z * cubicmap.width + x].b].y + topTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 2] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x, topTexUV[pixels[z * cubicmap.width + x].b].y + topTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 3] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x, topTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 4] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x + topTexUV[pixels[z * cubicmap.width + x].b].width, topTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 5] = Vector2{ topTexUV[pixels[z * cubicmap.width + x].b].x + topTexUV[pixels[z * cubicmap.width + x].b].width, topTexUV[pixels[z * cubicmap.width + x].b].y + topTexUV[pixels[z * cubicmap.width + x].b].height };
                tcCounter += 6;

                // Define bottom triangles (2 tris, 6 vertex --> v6-v8-v7, v6-v5-v8)
                mapVertices[vCounter] = v6;
                mapVertices[vCounter + 1] = v7;
                mapVertices[vCounter + 2] = v8;
                mapVertices[vCounter + 3] = v6;
                mapVertices[vCounter + 4] = v8;
                mapVertices[vCounter + 5] = v5;
                vCounter += 6;

                mapNormals[nCounter] = n3;
                mapNormals[nCounter + 1] = n3;
                mapNormals[nCounter + 2] = n3;
                mapNormals[nCounter + 3] = n3;
                mapNormals[nCounter + 4] = n3;
                mapNormals[nCounter + 5] = n3;
                nCounter += 6;

                mapTexcoords[tcCounter] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x + bottomTexUV[pixels[z * cubicmap.width + x].b].width, bottomTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 1] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x + bottomTexUV[pixels[z * cubicmap.width + x].b].width, bottomTexUV[pixels[z * cubicmap.width + x].b].y + bottomTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 2] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x, bottomTexUV[pixels[z * cubicmap.width + x].b].y + bottomTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 3] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x + bottomTexUV[pixels[z * cubicmap.width + x].b].width, bottomTexUV[pixels[z * cubicmap.width + x].b].y };
                mapTexcoords[tcCounter + 4] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x, bottomTexUV[pixels[z * cubicmap.width + x].b].y + bottomTexUV[pixels[z * cubicmap.width + x].b].height };
                mapTexcoords[tcCounter + 5] = Vector2{ bottomTexUV[pixels[z * cubicmap.width + x].b].x, bottomTexUV[pixels[z * cubicmap.width + x].b].y };
                tcCounter += 6;
            }
            if (pixels[z * cubicmap.width + x].g > 0) numObjects++;
            
        }
    }

    objects = (Object*)malloc(numObjects * sizeof(Object)*10);
    int counter = 0;

    for (int z = 0; z < mapHeight; ++z)
    {
        for (int x = 0; x < mapWidth; ++x)
        {
            switch (pixels[z * cubicmap.width + x].g)
            {
            case 1:
                objects[counter].position = { Vector3{(float)x, 0.f, (float)z } };
                objects[counter].textureType = TextureType::Castle;
                objects[counter].modelType = ModelType::castle;
                counter++;
                break;
            case 2:
                objects[counter].position = { Vector3{(float)x, 0.f, (float)z } };
                objects[counter].textureType = TextureType::House;
                objects[counter].modelType = ModelType::house;
                counter++;
                break;
            case 3:
                objects[counter].position = { Vector3{(float)x, 0.f, (float)z } };
                objects[counter].textureType = TextureType::Well;
                objects[counter].modelType = ModelType::well;
                counter++;
                break;
            default:
                break;
            }
        }
    }

    // Move data from mapVertices temp arays to vertices float array
    mesh.vertexCount = vCounter;
    mesh.triangleCount = vCounter / 3;

    mesh.vertices = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.normals = (float*)RL_MALLOC(mesh.vertexCount * 3 * sizeof(float));
    mesh.texcoords = (float*)RL_MALLOC(mesh.vertexCount * 2 * sizeof(float));
    mesh.colors = NULL;

    int fCounter = 0;

    // Move vertices data
    for (int i = 0; i < vCounter; i++)
    {
        mesh.vertices[fCounter] = mapVertices[i].x;
        mesh.vertices[fCounter + 1] = mapVertices[i].y;
        mesh.vertices[fCounter + 2] = mapVertices[i].z;
        fCounter += 3;
    }

    fCounter = 0;

    // Move normals data
    for (int i = 0; i < nCounter; i++)
    {
        mesh.normals[fCounter] = mapNormals[i].x;
        mesh.normals[fCounter + 1] = mapNormals[i].y;
        mesh.normals[fCounter + 2] = mapNormals[i].z;
        fCounter += 3;
    }

    fCounter = 0;

    // Move texcoords data
    for (int i = 0; i < tcCounter; i++)
    {
        mesh.texcoords[fCounter] = mapTexcoords[i].x;
        mesh.texcoords[fCounter + 1] = mapTexcoords[i].y;
        fCounter += 2;
    }

    RL_FREE(mapVertices);
    RL_FREE(mapNormals);
    RL_FREE(mapTexcoords);

    UnloadImageColors(pixels);   // Unload pixels color data

    // Upload vertex data to GPU (static mesh)
    UploadMesh(&mesh, false);

    return mesh;
}

void MeshManager::UnloadObjects() {
    free(objects);
    numObjects = 0;
}
