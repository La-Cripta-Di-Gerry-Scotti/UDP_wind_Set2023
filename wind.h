//
// Created by Giacomo Cunardi on 25/09/23.
//

#ifndef WIND_UDP_CUNARDI_2392023_WIND_H
#define WIND_UDP_CUNARDI_2392023_WIND_H

struct wind_data
{
    float *wind_speed;
    int *wind_direction;
};

int wind(float *wind_speed, int *wind_direction)
{
    int h = 0;
    while(h == 0)
    {
        *wind_speed = rand()%350;
        *wind_direction = rand()%360;

        if(*wind_speed < 0 && *wind_speed > 140 && *wind_direction < 0 && *wind_direction > 360)
        {
            h = 1;
        }
        else
        {
            h = 0;
        }
    }
    return 0;
}

#endif //WIND_UDP_CUNARDI_2392023_WIND_H
