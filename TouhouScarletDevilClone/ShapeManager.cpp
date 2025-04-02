#include "ShapeManager.h"
#include "Shape.h"
#include "D2DImage.h"

void ShapeManager::Init()
{
    ShapeManager::GetInstance()->AddShapeCircle("Error", TEXT("Image/MissingNo.png"), 0.0f);

    D2DImage* image = nullptr;
    image = ImageManager::GetInstance()->AddImage("enemy", TEXT("Image/enemy1.png"), 4, 1);
    ShapeManager::GetInstance()->AddShapeCharacter("enemy", image, 3.0f);

    D2DImage* marisaImg = ImageManager::GetInstance()->AddImage("Marisa", TEXT("Image/Marisa_Move_Vertical.bmp"), 4, 1); 
    ShapeManager::GetInstance()->AddShapeCharacter("Marisa", marisaImg, 3.0f);

    ShapeManager::GetInstance()->AddShapeCircle("marisa_bullet", TEXT("Image/kunai.png"), 3.0f);

    ShapeManager::GetInstance()->AddShapeCircle("kunai", TEXT("Image/kunai.png"), 3.0f);
    ShapeManager::GetInstance()->AddShapeCircle("ball_green", TEXT("Image/ball_green.png"), 3.0f);

}

void ShapeManager::Release()
{
    for (map<string, Shape*>::iterator iter = mapShapes.begin(); iter != mapShapes.end(); ++iter)
    {
        if (iter->second)
        {
            delete (iter->second);
            (iter->second) = nullptr;
        }
    }
    mapShapes.clear();
    ReleaseInstance();
}

Shape* ShapeManager::AddShapeCharacter(string key, D2DImage* image, float radius)
{

    Shape* shape = nullptr;
    shape = FindShapeAdd(key);

    if (shape) return shape;

    shape = new ShapeCircle(image, radius);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

Shape* ShapeManager::AddShapeCircle(string key, const wchar_t* filePath, float radius)
{

    Shape* shape = nullptr;
    shape = FindShapeAdd(key);

    if (shape) return shape;

    D2DImage* image = ImageManager::GetInstance()->AddImage(key, filePath);
    shape = new ShapeCircle(image, radius);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

Shape* ShapeManager::AddShapeRect(string key, const wchar_t* filePath, float scaleX, float scaleY, float width, float height)
{

    Shape* shape = nullptr;
    shape = FindShapeAdd(key);

    if (shape) return shape;

    D2DImage* image = ImageManager::GetInstance()->AddImage(key, filePath);
    shape = new ShapeRect(image, scaleX, scaleY, width, height);
    mapShapes.insert(make_pair(key, shape));
    return shape;
}

void ShapeManager::DeleteShape(string key)
{
    map<string, Shape*>::iterator iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return;

    delete (iter->second);
    (iter->second) = nullptr;

    mapShapes.erase(iter);
}

Shape* ShapeManager::FindShapeAdd(string key)
{
    map<string, Shape*>::iterator iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return nullptr;

    return iter->second;
}

Shape* ShapeManager::FindShape(string key)
{
    map<string, Shape*>::iterator iter;
    iter = mapShapes.find(key);

    if (iter == mapShapes.end()) return mapShapes["Error"];

    return iter->second;
}