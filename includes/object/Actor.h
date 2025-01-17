#ifndef ACTOR_H
#define ACTOR_H

// Header declarations
#include <object/Transform.h>
#include <rendering/Camera.h>
#include <rendering/Material.h>
#include <object/Primitive.h>
#include <object/Model.h>
#include <rendering/Light.h>

#include <iostream>

// Type of Actors
enum ACTOR_TYPES
{
    PRIMITIVE_ACTOR,
    MODEL_ACTOR,
    LIGHT_ACTOR,
    CAMERA_ACTOR,
};

// Default Actors
enum TEMPLATE_ACTORS
{
    TRIANGLE_2D,
    RECTANGLE_2D,
    QUAD_2D,
    CUBE_3D,
    TRIANGLE_3D,
    QUAD_3D,
    PLANE_3D,
    CUBEMAP_3D,
    BACKPACK_MODEL,
    CYBORG_MODEL,
    NANOSUIT_MODEL,
    PLANET_MODEL,
    ROCK_MODEL,
    SPHERE_MODEL,
    TEAPOT_MODEL,
    COLOR_LIGHT_ACTOR,
    BASE_LIGHT_ACTOR,
    NORMAL_LIGHT_ACTOR,
    POINT_LIGHT_ACTOR,
    DIR_LIGHT_ACTOR,
    SPT_LIGHT_ACTOR,
    CAMERA_OBJECT_ACTOR,
};

extern std::string resource_dir;

struct ActorTemplate
{
    TEMPLATE_ACTORS templateType;
    ACTOR_TYPES type;
    std::string path;
    MATERIAL_TEMPLATES matTemplate;
    ActorTemplate()
    {
    }

    ActorTemplate(TEMPLATE_ACTORS template_, ACTOR_TYPES type_, std::string path_, MATERIAL_TEMPLATES mat_)
    {
        templateType = template_;
        type = type_;
        path = path_;
        matTemplate = mat_;
    }
};

extern ActorTemplate actorTemplates[22];

// Actor Class
class Actor
{
public:
    std::string name;
    Transform transform;
    ACTOR_TYPES type;
    int id;
    // Class Constructor
    Actor(std::string name_ = "New Actor", Transform transform_ = Transform());

private:
};

// Template Camera Actor
class CameraActor : public Actor
{
public:
    bool canMove;
    bool canRotate;
    bool isOrtho;
    float camSize;
    CameraActor(std::string name_, int id_, Transform transform_ = Transform(CAMERA_ORIGIN, Vec3(0.0f), Vec3(1.0f)));
    Camera *GetCamera();
    void RefreshCamera(bool transformCallback = false);
    void ResetTransform();

private:
    Camera cam;
};

// Template Actor
class RenderActor : public Actor
{
public:
    Material mat;
    std::string path;
    bool isVisible;
    TEMPLATE_ACTORS actor_template;
    RenderActor();
    RenderActor(std::string name_, TEMPLATE_ACTORS template_, int id_);

private:
};
#endif // !ACTOR_H
