// Animates a sprite across the screen.
void animateSprite(struct Entity * entity)
{
    if (entity->x == REAL_LEFT)
    {
        if (entity->y == REAL_TOP)
        {
            entity->yVel = 0;
            entity->xVel = 1;
        }
        else if (entity->y == REAL_HEIGHT)
        {
            entity->yVel = -1;
            entity->xVel = 0;
        }
    }
    else if (entity->x == REAL_WIDTH)
    {
        if (entity->y == REAL_TOP)
        {
            entity->yVel = 1;
            entity->xVel = 0;
        }
        else if (entity->y == REAL_HEIGHT)
        {
            entity->xVel = -1;
            entity->yVel = 0;
        }
    }
}