#include "light.hpp"

light::light()
{

}

light::~light()
{

}

light& light::operator=(const light &right)
{
    if (&right == this) return *this;
    color = right.color;
    position = right.position;
    return *this;
}

void light::setPosition(glm::vec4 pos)
{
    position = pos;
}

void light::setColor(glm::vec4 col)
{
    color = col;
}
