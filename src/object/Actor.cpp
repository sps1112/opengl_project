#include <object/Actor.h>

Actor::Actor(std::string name_, Transform transform_)
    : name(name_), transform(transform_) {}

CameraActor::CameraActor(std::string name_, int id_, Transform transform_)
{
    name = name_;
    id = id_;
    cam = Camera(transform_.position);
    transform = Transform(cam.Position, Vec3(0.0f), Vec3(1.0f));
}

Camera *CameraActor::GetCamera()
{
    cam.Position = transform.position;
    return &cam;
}

RenderActor::RenderActor()
{
    isVisible = true;
    mat = material_template[0];
}

RenderActor::RenderActor(std::string name_, TEMPLATE_ACTORS template_, int id_)
{
    name = name_;
    transform = Transform();
    type = actor_types[template_];
    actor_template = template_;
    id = id_;
    path = resource_dir + template_actor_filepath[template_];
    isVisible = true;
    mat = material_template[default_actor_materials[template_]];
}

LightActor::LightActor()
{
}

ACTOR_TYPES actor_types[] = {
    PRIMITIVE_ACTOR,
    PRIMITIVE_ACTOR,
    PRIMITIVE_ACTOR,
    PRIMITIVE_ACTOR,
    PRIMITIVE_ACTOR,
    PRIMITIVE_ACTOR,
    PRIMITIVE_ACTOR,
    MODEL_ACTOR,
    MODEL_ACTOR,
    LIGHT_ACTOR,
    LIGHT_ACTOR,
    LIGHT_ACTOR,
    LIGHT_ACTOR,
    CAMERA_ACTOR,
};

std::string resource_dir = "resources/";

std::string template_actor_filepath[] = {
    "primitives/2D/triangle.2d",
    "primitives/2D/rectangle.2d",
    "primitives/2D/quad.2d",
    "primitives/3D/cube.3d",
    "primitives/3D/quad.3d",
    "primitives/3D/plane.3d",
    "primitives/3D/cubemap.3d",
    "models/backpack/backpack.obj",
    "models/sphere/sphere.obj",
    " ",
    " ",
    " ",
    " ",
    " "};

MATERIAL_TEMPLATES default_actor_materials[] = {
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    COLOR_3D_MAT,
    LIGHT_MAT,
    LIGHT_MAT,
    LIGHT_MAT,
    LIGHT_MAT,
    COLOR_2D_MAT};
