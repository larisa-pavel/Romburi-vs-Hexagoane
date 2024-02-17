#include "lab_m1/lab3/lab3.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

float radians, translateY, translateX, signT = -1, scaleY = 1, signS = -1, ax = 0, signrot = -2, collision_time = 0;
int move_tank_x = 0, move_tank_y = 0;
int flag_animation[20];
int tank1X[36], tank1Y[36];
float start_enemy[7];
float start_placement[3];
int tank_type[36];
bool isDragging;
int nr[36];
float timer;
int height[7];
int hex_colour[7];
bool exist;
int hearts = 0;
int maximum_enemy;
float scale[7];
bool enemy[7];
int reset=0;
int meet_tank[36];
float tank_scale[36];
bool still_selected[36];
float starX[36][4], starY[36];
bool star_exist[36];
float star_timer[36];
int star_count[36];
int star_coll[36];
float star_stop[36];
int hex_coll[7];
int star_init[36];
int money;
float money_timer;
int nr_money;
int moneyX[2000], moneyY[2000];
bool money_flag[2000];

Lab3::Lab3()
{
}


Lab3::~Lab3()
{
}


void Lab3::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    float squareSide = 100;
    // compute coordinates of square center
    float cx = corner.x + squareSide / 2;
    float cy = corner.y + squareSide / 2;

    // initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;
    // initialize sx and sy (the scale factors)
    scaleY = 1;
    timer = -1;
    nr_money = 0;
    money_timer = -1;
    money = 5;
    for (int i = 0; i < 7; i++) {
        hex_colour[i] = 0;
        height[i] = 0;
        scale[i] = 1;
        start_enemy[i] = 1300;
        enemy[i] = false;
        hex_coll[i] = 0;
    }
    maximum_enemy = -1;

    for (int i = 0; i < 36; i++) {
        tank_type[i] = 0; 
        tank1X[i] = 100 + 150 * (i % 4);
        tank1Y[i] = 650;
        nr[i] = 0;
        meet_tank[i] = 0;
        tank_scale[i] = 1;
        still_selected[i] = false;
        star_exist[i] = false;
        for (int j = 0; j < 4; j++) {
            starX[i][j] = 0;
            star_stop[i] = 1300;
        }
        starY[i] = 0;
        star_timer[i] = 3;
        star_count[i] = 0;
        star_coll[i] = 0;
        star_init[i] = 0;
    }
    for (int i = 0; i < 3; i++) {
        start_placement[i] = 0;
    }
    // initialize angularStep
    angularStep = 0;

    //creare casute tunuri:
    Mesh* square01 = object2D::CreateSquare("square01", corner, squareSide, glm::vec3(0, 0, 0));
    AddMeshToList(square01);

    Mesh* square0 = object2D::CreateSquare("square0", corner, squareSide, glm::vec3(1, 0, 0), true);
    AddMeshToList(square0);
    //casute de pe teren
    Mesh* square1 = object2D::CreateSquare("square1", corner, squareSide, glm::vec3(0, 1, 0.5), true);
    AddMeshToList(square1);
    Mesh* square2 = object2D::CreateSquare("square2", corner, squareSide, glm::vec3(0.6f, 0.1f, 0.1f), true);
    AddMeshToList(square2);

    //fac rombuletul :)
    Mesh* tank1 = object2D::CreateDiamond("tank1", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(tank1);
    Mesh* tank2 = object2D::CreateDiamond("tank2", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(tank2);
    Mesh* tank3 = object2D::CreateDiamond("tank3", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(tank3);
    Mesh* tank4 = object2D::CreateDiamond("tank4", corner, squareSide, glm::vec3(0.5, 0, 1), true);
    AddMeshToList(tank4);

    //hexagon
    Mesh* hex2 = object2D::CreateHexagon("hex2", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(hex2);
    Mesh* hex1 = object2D::CreateHexagon("hex1", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(hex1);
    Mesh* hex3 = object2D::CreateHexagon("hex3", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(hex3);
    Mesh* hex4 = object2D::CreateHexagon("hex4", corner, squareSide, glm::vec3(0.5, 0, 1), true);
    AddMeshToList(hex4);
    //steaua
    Mesh* star1 = object2D::CreateStar("star1", corner, squareSide, glm::vec3(0.5, 0.5, 0.5), true);
    AddMeshToList(star1);
    Mesh* star01 = object2D::CreateStar("star01", corner, squareSide, glm::vec3(1, 0.5, 0), true);
    AddMeshToList(star01);
    Mesh* star02 = object2D::CreateStar("star02", corner, squareSide, glm::vec3(0, 0, 1), true);
    AddMeshToList(star02);
    Mesh* star03 = object2D::CreateStar("star03", corner, squareSide, glm::vec3(1, 1, 0), true);
    AddMeshToList(star03);
    Mesh* star04 = object2D::CreateStar("star04", corner, squareSide, glm::vec3(0.5, 0, 1), true);
    AddMeshToList(star04);
    Mesh* star = object2D::CreateStar("star", corner, squareSide, glm::vec3(0.5, 0.5, 1), true);
    AddMeshToList(star);
    //heart shape
    Mesh* heart1 = object2D::CreateHeart("heart1", corner, squareSide, glm::vec3(0.8, 0.1, 0.1), true);
    AddMeshToList(heart1);
    Mesh* heart2 = object2D::CreateHeart("heart2", corner, squareSide, glm::vec3(0.8, 0.1, 0.1), true);
    AddMeshToList(heart2);
    Mesh* heart3 = object2D::CreateHeart("heart3", corner, squareSide, glm::vec3(0.8, 0.1, 0.1), true);
    AddMeshToList(heart3);
    Mesh* heart4 = object2D::CreateHeart("heart4", corner, squareSide, glm::vec3(0.5, 0.5, 0.5), true);
    AddMeshToList(heart4);
}


void Lab3::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.15, 0.15, 0.15, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

int remain1, remain2;

void Lab3::Update(float deltaTimeSeconds)
{
    if (hearts != 3) {
        glm::vec3 corner = glm::vec3(0, 0, 0);
        // compute coordinates of square center
        float cx = corner.x;
        float cy = corner.y;
       
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 650);
        RenderMesh2D(meshes["tank1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(250, 650);
        RenderMesh2D(meshes["tank2"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(400, 650);
        RenderMesh2D(meshes["tank3"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(550, 650);
        RenderMesh2D(meshes["tank4"], shaders["VertexColor"], modelMatrix);


        //fac hexagon >:)
        timer -= deltaTimeSeconds;
        if (timer < 0) {
            height[reset] = 75 + 125 * (rand() % 3);
            hex_colour[reset] = rand() % 4;
            start_enemy[reset] = 1400;
            flag_animation[reset] = 0;
            scale[reset] = 1;
            hex_coll[reset] = 0;
            timer = (rand() % 5) + 5;
            enemy[reset] = true;
            if (reset == 6) {
                reset = -1;
            }
            reset++;
            if (maximum_enemy <= 5) {
                maximum_enemy++;
            }
        }
        for (int i = 0; i < maximum_enemy; i++) {
            modelMatrix = glm::mat3(1);
            if (hex_coll[i] >= 3) {
                scale[i] += (deltaTimeSeconds)*signS;
                modelMatrix *= transform2D::Translate(start_enemy[i], height[i]);
                modelMatrix *= transform2D::Scale(scale[i], scale[i]);
            }
            if (start_enemy[i] <= 50 && flag_animation[i] == 0 && enemy[i] && hex_coll[i] < 3) {
                scale[i] -= deltaTimeSeconds;
                hearts++;
                flag_animation[i] = 1;
                modelMatrix *= transform2D::Translate(50, height[i]);
            }
            else if (start_enemy[i] < 50 && flag_animation[i] == 1 && scale[i] >= 0 && enemy[i] && hex_coll[i] < 3) {
                scale[i] += (deltaTimeSeconds)*signS;
                modelMatrix *= transform2D::Translate(50, height[i]);
                modelMatrix *= transform2D::Scale(scale[i], scale[i]);
            }
            else if (enemy[i] && hex_coll[i] < 3) {
                start_enemy[i] -= 1;
                modelMatrix *= transform2D::Translate(start_enemy[i], height[i]);
            }
            
            if (scale[i] < 0) {
                enemy[i] = false;
                start_enemy[i] = 1400;
            }
            
            for (int j = 0; j < 36; j++) {
                if (start_enemy[i] <= tank1X[j] + 100 && start_enemy[i] >= tank1X[j] && height[i] == tank1Y[j] && tank_type[i] == 0) {
                    meet_tank[j] = 1;
                }

            }
            if (hex_colour[i] % 4 == 0 && enemy[i]) {
                RenderMesh2D(meshes["hex1"], shaders["VertexColor"], modelMatrix);
            }
            else if (hex_colour[i] % 4 == 1 && enemy[i]) {
                RenderMesh2D(meshes["hex2"], shaders["VertexColor"], modelMatrix);
            }
            else if (hex_colour[i] % 4 == 2 && enemy[i]) {
                RenderMesh2D(meshes["hex3"], shaders["VertexColor"], modelMatrix);
            }
            else if (hex_colour[i] % 4 == 3 && enemy[i]) {
                RenderMesh2D(meshes["hex4"], shaders["VertexColor"], modelMatrix);
            }
        }

        for (int j = 0; j < hearts; j++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1000 - j * 125, 650);
            RenderMesh2D(meshes["heart4"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 36; i++) {
            modelMatrix = glm::mat3(1);
            if (tank_scale[i] <= 0) {
                tank1X[i] = 100;
                tank1Y[i] = 650;
                meet_tank[i] = 0;
                tank_scale[i] = 1;
            }
            modelMatrix *= transform2D::Translate(tank1X[i], tank1Y[i]);
            if (meet_tank[i] == 1 && tank_scale[i] > 0 && tank_type[i] == 0) {
                tank_scale[i] -= deltaTimeSeconds;
                modelMatrix *= transform2D::Scale(tank_scale[i], tank_scale[i]);
            }
            if (i % 4 == 0) {
                RenderMesh2D(meshes["tank1"], shaders["VertexColor"], modelMatrix);
            }
            else if (i % 4 == 1) {
                RenderMesh2D(meshes["tank2"], shaders["VertexColor"], modelMatrix);
            }
            else if (i % 4 == 2) {
                RenderMesh2D(meshes["tank3"], shaders["VertexColor"], modelMatrix);
            }
            else if (i % 4 == 3) {
                RenderMesh2D(meshes["tank4"], shaders["VertexColor"], modelMatrix);
            }

            star_stop[i] = 1400;
            star_exist[i] = false;

            for (int j = maximum_enemy - 1; j >= 0; j--) {
                if (tank1Y[i] == height[j] && tank_type[i] == 0 && hex_colour[j] == i % 4
                    && enemy[j] == 1) {
                    star_stop[i] = start_enemy[j] - 100;
                    star_exist[i] = true;
                }
            }
            
        }
        for (int i = 0; i < 36; i++) {
            for (int j = 0; j < star_count[i]; j++) {
                bool flag = false;

                if (starX[i][j] == 1500)
                    continue;

                if (starX[i][j] < star_stop[i]) {
                    starX[i][j] += 100 * deltaTimeSeconds;

                    modelMatrix = glm::mat3(1);
                    modelMatrix *= transform2D::Translate(starX[i][j], starY[i]);
                    modelMatrix *= transform2D::Rotate(-starX[i][j] * M_PI / 100);
                    if (i % 4 == 0) {
                        RenderMesh2D(meshes["star01"], shaders["VertexColor"], modelMatrix);
                    }
                    else if (i % 4 == 1) {
                        RenderMesh2D(meshes["star02"], shaders["VertexColor"], modelMatrix);
                    }
                    else if (i % 4 == 2) {
                        RenderMesh2D(meshes["star03"], shaders["VertexColor"], modelMatrix);
                    }
                    else if (i % 4 == 3) {
                        RenderMesh2D(meshes["star04"], shaders["VertexColor"], modelMatrix);
                    }
                }
                else if (starX[i][j] < star_stop[i] + 100) {
                    for (int k = 0; k < maximum_enemy; k++) {
                        if (hex_colour[k] % 4 == i % 4 && height[k] == tank1Y[i] && hex_coll[k] < 3) {
                            hex_coll[k]++;
                            starX[i][j] = 1500;
                            flag = true;
                            break;
                        }
                    }
                    if (flag == true)
                        continue;

                }
            }

            if (tank_type[i] == 1 || tank1Y[i] == 650)
                continue;

            if (star_timer[i] == 3 && tank_scale[i] == 1) {
                if (star_exist[i] == true) {
                    star_count[i]++;
                    starX[i][star_count[i] - 1] = tank1X[i] + 100;
                    starY[i] = tank1Y[i];
                }
            }
            if (star_exist[i] == true) {
                star_timer[i] -= deltaTimeSeconds;
            }
            else
                star_timer[i] = 3;          
            
            if (star_timer[i] <= 0) {
                star_timer[i] = 3;
            }
        }
        //money money
        for (int i = 0; i < money; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(700 + 50 * i, 570);
            modelMatrix *= transform2D::Scale(0.4, 0.4);
            RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        }
        //random points generator
        money_timer -= deltaTimeSeconds;
        if (money_timer <= 0) {
            nr_money += 3;
            for (int i = nr_money - 3; i < nr_money; i++) {
                moneyX[i] = rand() % 1280;
                moneyY[i] = rand() % 700;
                money_flag[i] = false;
            }
            money_timer = rand() % 10 + 10;
        }
        for (int i = 0; i < nr_money; i++) {
            if (money_flag[i] == false) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(moneyX[i], moneyY[i]);
                modelMatrix *= transform2D::Scale(0.8, 0.8);
                RenderMesh2D(meshes["star"], shaders["VertexColor"], modelMatrix);
            }
        }


        //fac locul in care inamicii ma ataca :(

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(50, 200);
        modelMatrix *= transform2D::Scale(0.5, 3.5);
        RenderMesh2D(meshes["square0"], shaders["VertexColor"], modelMatrix);

        //fac casutele tunurilor
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 650);
        RenderMesh2D(meshes["square01"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(250, 650);
        RenderMesh2D(meshes["square01"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(400, 650);
        RenderMesh2D(meshes["square01"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(550, 650);
        RenderMesh2D(meshes["square01"], shaders["VertexColor"], modelMatrix);

        //fac celulele grilei
        //linia de jos

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(150, 75);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(275, 75);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(400, 75);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        //linia de mijloc

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(150, 200);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(275, 200);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(400, 200);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        //linia de sus

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(150, 325);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(275, 325);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(400, 325);
        RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

        //stelele
        //tank1
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        //tank2
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(225, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(275, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        //tank3
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(375, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(425, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);
        //tank4
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(510, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(550, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(590, 570);
        modelMatrix *= transform2D::Scale(0.4, 0.4);
        RenderMesh2D(meshes["star1"], shaders["VertexColor"], modelMatrix);


        //AM FACUT inimioara :) <3
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(750, 650);
        RenderMesh2D(meshes["heart1"], shaders["VertexColor"], modelMatrix);

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(875, 650);
        RenderMesh2D(meshes["heart1"], shaders["VertexColor"], modelMatrix);


        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1000, 650);
        RenderMesh2D(meshes["heart1"], shaders["VertexColor"], modelMatrix);
    }
    else {
        //G
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(120, 480);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(80, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(60, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(40, 480);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(40, 460);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(40, 440);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(40, 420);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(40, 400);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(60, 380);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(80, 380);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 380);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(120, 400);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(120, 420);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(100, 420);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        //A

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(240, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(220, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(200, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        for (int i = 0; i < 6; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(180, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(260, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(200 + i * 20, 420);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }

        //M
        for (int i = 0; i < 7; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(320, 500 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(400, 500 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(340, 480);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(360, 460);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(380, 480);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        //E
        for (int i = 0; i < 5; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(460, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(480 + 20 * j, 500 - 60 * i);
                modelMatrix *= transform2D::Scale(0.2, 0.2);
                RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
                
            }
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(540, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(540, 380);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        //O
        for (int i = 0; i < 5; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(680, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(760, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(700 + 20 * i, 500);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(700 + 20 * i, 380);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        //V
        for (int i = 0; i < 5; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(820, 500 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(900, 500 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(840, 400);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(880, 400);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(860, 380);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        //E
        for (int i = 0; i < 5; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(960, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                modelMatrix = glm::mat3(1);
                modelMatrix *= transform2D::Translate(980 + 20 * j, 500 - 60 * i);
                modelMatrix *= transform2D::Scale(0.2, 0.2);
                RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

            }
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1040, 500);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1040, 380);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

        //R
        for (int i = 0; i < 7; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1100, 500 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        for (int i = 0; i < 3; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1120 + i * 20, 500);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1120 + i * 20, 440);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        for (int i = 0; i < 2; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1180, 480 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(1180, 400 - 20 * i);
            modelMatrix *= transform2D::Scale(0.2, 0.2);
            RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);
        }
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1160, 420);
        modelMatrix *= transform2D::Scale(0.2, 0.2);
        RenderMesh2D(meshes["square2"], shaders["VertexColor"], modelMatrix);

    }
}


void Lab3::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Lab3::OnInputUpdate(float deltaTime, int mods)
{
    
}


void Lab3::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Lab3::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Lab3::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (isDragging) {
        for (int i = 0; i < 36; i++) {
            if (tank_type[i]) {
                tank1X[i] = mouseX;
                tank1Y[i] = 720 - mouseY;
            }
        }
    }
}


void Lab3::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2 && !isDragging) {
        for (int i = 0; i < 36; i++) {
            if (mouseX <= tank1X[i] + 50 && mouseX >= tank1X[i] - 50 && mouseY <= 720 - tank1Y[i] + 50 
                && mouseY >= 720 - tank1Y[i] - 50 && tank1X[i] == 100 + 150 * (i%4) && tank1Y[i] == 650 && tank_type[i] == 0) {
                if ((i % 4 == 0 && money >= 1) ||
                    ((i % 4 == 1 || i % 4 == 2) && money >= 2) ||
                    (i % 4 == 3 && money >= 3)) {
                    isDragging = true;
                    tank1X[i] = mouseX;
                    tank1Y[i] = 720 - mouseY;
                    tank_type[i] = 1;
                    break;
                }
            }
        }
        for (int i = 0; i < nr_money; i++) {
            if (money_flag[i] == false && mouseX <= moneyX[i] + 40 && mouseX >= moneyX[i] - 40 && mouseY <= 720 - moneyY[i] + 40
                && mouseY >= 720 - moneyY[i] - 40) {
                money_flag[i] = true;
                money++;
            }
        }
    }
    else if (button == GLFW_MOUSE_BUTTON_3) {
        for (int i = 0; i < 36; i++) {
            if (mouseX <= tank1X[i] + 50 && mouseX >= tank1X[i] - 50 && mouseY <= 720 - tank1Y[i] + 50
                && mouseY >= 720 - tank1Y[i] - 50) {
                meet_tank[i] = 1;
            }
        }
    }
}


void Lab3::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    int casutax = 150, casutay = 75, w;
    if (button == GLFW_MOUSE_BUTTON_2 && isDragging) {
        for (int i = 0; i < 36; i++) {
            if (tank_type[i]) {
                w = i;
            }
        }
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (mouseX <= casutax + 50 + i * 125 && mouseX >= casutax - 50 + i * 125 &&
                    mouseY <= 720 - 25 - j * 125 && mouseY >= 720 - 125 - j * 125) {
                    for (int k = 0; k < 36; k++) {
                        if (tank1X[k] == 150 + i * 125 && tank1Y[k] == 75 + j * 125) {
                            isDragging = false;
                            tank1X[w] = 100 + 150 * (w % 4);
                            tank1Y[w] = 650;
                            tank_type[w] = 0;
                        }
                    }
                    if (tank_type[w] == 1) {
                        isDragging = false;
                        tank1X[w] = 150 + i * 125;
                        tank1Y[w] = 75 + j * 125;
                        tank_type[w] = 0;
                        if (w % 4 == 0) {
                            money--;
                        }
                        else if (w % 4 == 1 || w % 4 == 2) {
                            money -= 2;
                        }
                        else if (w % 4 == 3) {
                            money -= 3;
                        }
                    }
                }
            }
        }
        if (isDragging) {
            isDragging = false;
            tank1X[w] = 100 + 150*(w%4);
            tank1Y[w] = 650;
            tank_type[w] = 0;
        }
    }
}


void Lab3::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Lab3::OnWindowResize(int width, int height)
{
}
