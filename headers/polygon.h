#ifndef PYS_POLYGON_H
#define PYS_POLYGON_H

#include"fpair.h"
#include"body.h"
#include"line.h"
#include<vector>

namespace pys{
    class polygon: public body{
        public:
        std::vector<point> vertexs;
        std::vector<vector> edges_dir;
        std::vector<vector> edges_normal;
        std::vector<fpair> projection;
        std::vector<line> edges;
        int edges_num;

        fpair get_projection(int index);

        point get_supporting_point(vector dir, int *index = NULL);

        void init();
        
        polygon(point center, int edges_num, float edges_length, float mass, vector speed);

        polygon(std::vector<point> _vertexs, float mass, vector speed);

        float min_x();

        float max_x();

        float min_y();

        float max_y();

        void transform(const float angle);

        void update_line();

        void single_update(const float time);

        void update(const float time);

        void position_correct(vector);
    };
}

#endif