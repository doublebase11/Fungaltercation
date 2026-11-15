#include "hitbox.h"

vector2f calculatevertex(vector2f tpoint, vector2f centre, float angle)
{
    vector2f point;
    double angler = angle * PI; //angle in radians. sdl uses degrees butcmath sin cosin etc functions use radians
    angler = angler/180;
    point.x = tpoint.x - centre.x;
    point.y = tpoint.y - centre.y;

   point= {(cos(angler) *  point.x -sin(angler) * point.y), sin(angler) * point.x + cos(angler)* point.y};

   point.x += centre.x;
   point.y += centre.y;

    return point;
}


hitbox calculatevertices(hitbox hbox, vector2f pos, vector2f centre, float angle)
{
    hitbox h = hbox;

    h.v1 = calculatevertex(hbox.v1, centre, angle);
    h.v2 = calculatevertex(hbox.v2, centre, angle);
    h.v3 = calculatevertex(hbox.v3, centre, angle);
    h.v4 = calculatevertex(hbox.v4, centre, angle);

    h = {{h.v1.x + pos.x, h.v1.y + pos.y}, {h.v2.x + pos.x, h.v2.y + pos.y}, {h.v3.x + pos.x, h.v3.y + pos.y}, {h.v4.x + pos.x, h.v4.y + pos.y}};

    ////log << << pos.x << " " << pos.y << " | " << h.v1.x << " " << h.v1.y << "    "<< h.v2.x << " " << h.v2.y << "    "<< h.v3.x << " " << h.v3.y << "    "<< h.v4.x << " " << h.v4.y << "    "<< std::endl;

    return h;
}