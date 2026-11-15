#include "collision.h"

// separating axis theorum https://dyn4j.org/2010/01/sat/
//  its implemented differently here(without using vectors and using some botches) but generally works?

axis gradient(vector2f p1, vector2f p2)
{
    axis axis = {0, 0};
    float gradient = 0;
    if ((p1.y - p2.y) == 0)
    {
        gradient = 0;
        axis.horv = 1;
    }
    else if ((p1.x - p2.x) == 0)
    {
        gradient = 0;
        axis.horv = -1;
    }
    else
    {
        gradient = (p1.y - p2.y);
        gradient = gradient / (p1.x - p2.x);
    }

    axis.g = gradient;

    return axis;
}

axis perpendicular(axis oaxis)
{
    axis perpendicular = {0, 0};

    if (oaxis.g == 0 && oaxis.horv == -1)
    {
        perpendicular.horv = 1;
    }
    else if (oaxis.g == 0 && oaxis.horv == 1)
    {
        perpendicular.horv = -1;
    }
    else
    {
        perpendicular.g = -1;
        perpendicular.g = perpendicular.g / oaxis.g;
    }

    if (perpendicular.g <= -1 && perpendicular.g > -1.2)
    {
        perpendicular.g = -0.99;
    }

    return perpendicular;
}

vector2f2 findMostDistantPoints(vector2f a, vector2f b, vector2f c, vector2f d, axis paxis)
{
    vector2f2 mostdistantpoints = {{0, 0}, {0, 0}};
    float maxdistance = 0;
    float mindistance = 36526;

    float adistance = sqrt((a.x * a.x) + (a.y * a.y));
    float bdistance = sqrt((b.x * b.x) + (b.y * b.y));
    float cdistance = sqrt((c.x * c.x) + (c.y * c.y));
    float ddistance = sqrt((d.x * d.x) + (d.y * d.y));

    if (adistance > maxdistance)
    {
        maxdistance = adistance;
    }
    if (bdistance > maxdistance)
    {
        maxdistance = bdistance;
    }
    if (cdistance > maxdistance)
    {
        maxdistance = cdistance;
    }
    if (ddistance > maxdistance)
    {
        maxdistance = ddistance;
    }

    if (adistance < mindistance)
    {
        mindistance = adistance;
    }
    if (bdistance < mindistance)
    {
        mindistance = bdistance;
    }
    if (cdistance < mindistance)
    {
        mindistance = cdistance;
    }
    if (ddistance < mindistance)
    {
        mindistance = ddistance;
    }

    if (mindistance == adistance)
    {
        mostdistantpoints.v1 = a;
    }
    if (mindistance == bdistance)
    {
        mostdistantpoints.v1 = b;
    }
    if (mindistance == cdistance)
    {
        mostdistantpoints.v1 = c;
    }
    if (mindistance == ddistance)
    {
        mostdistantpoints.v1 = d;
    }

    if (maxdistance == adistance)
    {
        mostdistantpoints.v2 = a;
    }
    if (maxdistance == bdistance)
    {
        mostdistantpoints.v2 = b;
    }
    if (maxdistance == cdistance)
    {
        mostdistantpoints.v2 = c;
    }
    if (maxdistance == ddistance)
    {
        mostdistantpoints.v2 = d;
    }

    return mostdistantpoints;
}

int checkOverlap(vector2f2 fls1, vector2f2 fls2, axis paxis)
{
    int overlap = 0;
    vector2f2 ls1 = fls1;
    vector2f2 ls2 = fls2;
    if (fls1.v1.x < fls1.v2.x)
    {
        ls1.v1.x = fls1.v1.x;
        ls1.v2.x = fls1.v2.x;
    }
    else
    {
        ls1.v1.x = fls1.v2.x;
        ls1.v2.x = fls1.v1.x;
    }
    if (fls2.v1.x < fls2.v2.x)
    {
        ls2.v1.x = fls2.v1.x;
        ls2.v2.x = fls2.v2.x;
    }
    else
    {
        ls2.v1.x = fls2.v2.x;
        ls2.v2.x = fls2.v1.x;
    }

    if ((ls1.v1.x - ls1.v2.x) == 0)
    {
        if ((ls1.v2.y >= ls2.v1.y) && (ls1.v1.y <= ls2.v2.y))
        {
            overlap = 1;
        }
    }

    else if (((ls1.v2.x >= ls2.v1.x) && (ls1.v1.x <= ls2.v2.x)))
    {
        overlap = 1;
    }

    return overlap;
}

vector2f findoverlapdistance(vector2f2 fls1, vector2f2 fls2, axis paxis)
{
    vector2f overlapdistance = {0, 0};
    vector2f2 ls1 = fls1;
    vector2f2 ls2 = fls2;
    if(fls1.v1.x < fls1.v2.x)
   {
       ls1.v1.x = fls1.v1.x;
       ls1.v2.x = fls1.v2.x;
   }
   else
   {
       ls1.v1.x = fls1.v2.x;
       ls1.v2.x = fls1.v1.x;       
   }
   if(fls2.v1.x < fls2.v2.x)
   {
       ls2.v1.x = fls2.v1.x;
       ls2.v2.x = fls2.v2.x;
   }
   else
   {
       ls2.v1.x = fls2.v2.x;
       ls2.v2.x = fls2.v1.x;       

   }
    if((ls1.v1.x - ls1.v2.x) == 0)
    {
        if((ls1.v2.y >= ls2.v1.y) && (ls1.v1.y <= ls2.v2.y))
        {
            overlapdistance.y = ls2.v2.y - ls1.v1.y;

            if((overlapdistance.x*overlapdistance.x + overlapdistance.y*overlapdistance.y) > ((ls1.v2.x - ls2.v1.x)*(ls1.v2.x - ls2.v1.x) + (ls1.v2.y - ls2.v1.y)*(ls1.v2.y - ls2.v1.y)) )
            {
                overlapdistance.y = ls1.v2.y - ls2.v1.y;
            }           
        }
    }

    else if((ls1.v1.y - ls1.v2.y) == 0)
    {
        overlapdistance.x = ls2.v2.x - ls1.v1.x;


        if((overlapdistance.x*overlapdistance.x + overlapdistance.y*overlapdistance.y) > ((ls1.v2.x - ls2.v1.x)*(ls1.v2.x - ls2.v1.x) + (ls1.v2.y - ls2.v1.y)*(ls1.v2.y - ls2.v1.y)) )
        {
            overlapdistance.x = ls1.v2.x - ls2.v1.x;
        }
    }
    else
    {
        overlapdistance.x = ls2.v2.x - ls1.v1.x;
        overlapdistance.y = ls2.v2.y - ls1.v1.y;

        if((overlapdistance.x*overlapdistance.x + overlapdistance.y*overlapdistance.y) > ((ls1.v2.x - ls2.v1.x)*(ls1.v2.x - ls2.v1.x) + (ls1.v2.y - ls2.v1.y)*(ls1.v2.y - ls2.v1.y)) )
        {
            overlapdistance.x = ls1.v2.x - ls2.v1.x;
            overlapdistance.y = ls1.v2.y - ls2.v1.y;
        }
    }

    ////log << << overlapdistance.x << " " << overlapdistance.y << std::endl;

   return overlapdistance;
}

vector2f projectPoint(axis paxis, vector2f point) // axis is the gradient of the line to project the point onto, point is the point to project
{
    vector2f projectedpoint = {0, 0};

    if (paxis.horv == -1)
    {
        projectedpoint = {point.x, 0};
    }
    else if (paxis.horv == 1)
    {
        projectedpoint = {0, point.y};
    }
    else
    {

        float x = point.y + (point.x / paxis.g);
        x = x / (paxis.g + (1 / paxis.g));
        float y = paxis.g * x;
        projectedpoint = {x, y};
    }

    return projectedpoint;
}

int collision(hitbox h1, hitbox h2)
{
    int collision = 1;
    // a stands for axis
    axis a1 = perpendicular((gradient(h1.v1, h1.v2)));

    if (collision == 1)
    {
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a1, h1.v1), projectPoint(a1, h1.v2), projectPoint(a1, h1.v3), projectPoint(a1, h1.v4), a1);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a1, h2.v1), projectPoint(a1, h2.v2), projectPoint(a1, h2.v3), projectPoint(a1, h2.v4), a1);

        if (checkOverlap(ls1, ls2, a1) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a2 = perpendicular((gradient(h1.v2, h1.v3)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a2, h1.v1), projectPoint(a2, h1.v2), projectPoint(a2, h1.v3), projectPoint(a2, h1.v4), a2);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a2, h2.v1), projectPoint(a2, h2.v2), projectPoint(a2, h2.v3), projectPoint(a2, h2.v4), a2);

        if (checkOverlap(ls1, ls2, a2) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a3 = perpendicular((gradient(h1.v3, h1.v4)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a3, h1.v1), projectPoint(a3, h1.v2), projectPoint(a3, h1.v3), projectPoint(a3, h1.v4), a3);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a3, h2.v1), projectPoint(a3, h2.v2), projectPoint(a3, h2.v3), projectPoint(a3, h2.v4), a3);

        if (checkOverlap(ls1, ls2, a3) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a4 = perpendicular((gradient(h1.v4, h1.v1)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a4, h1.v1), projectPoint(a4, h1.v2), projectPoint(a4, h1.v3), projectPoint(a4, h1.v4), a4);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a4, h2.v1), projectPoint(a4, h2.v2), projectPoint(a4, h2.v3), projectPoint(a4, h2.v4), a4);

        if (checkOverlap(ls1, ls2, a4) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a5 = perpendicular((gradient(h2.v1, h2.v2)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a5, h1.v1), projectPoint(a5, h1.v2), projectPoint(a5, h1.v3), projectPoint(a5, h1.v4), a5);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a5, h2.v1), projectPoint(a5, h2.v2), projectPoint(a5, h2.v3), projectPoint(a5, h2.v4), a5);

        if (checkOverlap(ls1, ls2, a5) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a6 = perpendicular((gradient(h2.v2, h2.v3)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a6, h1.v1), projectPoint(a6, h1.v2), projectPoint(a6, h1.v3), projectPoint(a6, h1.v4), a6);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a6, h2.v1), projectPoint(a6, h2.v2), projectPoint(a6, h2.v3), projectPoint(a6, h2.v4), a6);

        if (checkOverlap(ls1, ls2, a6) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a7 = perpendicular((gradient(h2.v3, h2.v4)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a7, h1.v1), projectPoint(a7, h1.v2), projectPoint(a7, h1.v3), projectPoint(a7, h1.v4), a7);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a7, h2.v1), projectPoint(a7, h2.v2), projectPoint(a7, h2.v3), projectPoint(a7, h2.v4), a7);

        if (checkOverlap(ls1, ls2, a7) == 0)
        {
            collision = 0;
        }
    }
    if (collision == 1)
    {
        axis a8 = perpendicular((gradient(h2.v4, h2.v1)));
        vector2f2 ls1 = findMostDistantPoints(projectPoint(a8, h1.v1), projectPoint(a8, h1.v2), projectPoint(a8, h1.v3), projectPoint(a8, h1.v4), a8);
        vector2f2 ls2 = findMostDistantPoints(projectPoint(a8, h2.v1), projectPoint(a8, h2.v2), projectPoint(a8, h2.v3), projectPoint(a8, h2.v4), a8);

        if (checkOverlap(ls1, ls2, a8) == 0)
        {
            collision = 0;
        }
    }

    return collision;
}