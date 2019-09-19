#include<vector>
#include<cmath>
#include<cstdio>
#include"const.h"
#include"polygon.h"

namespace pys{

    point polygon::get_supporting_point(vector dir, int *index){
        point furthest_point = vertexs[0];
        float dis = vertexs[0] * dir;
        if(index != NULL) *index = 0;
        
        for(int i = 0; i < edges_num; i++){
            float _dis = vertexs[i] * dir;
            if(_dis > dis){
                dis = _dis;
                furthest_point = vertexs[i];
                if(index != NULL)
                    *index = i;
            }
        }
        return furthest_point;
    }

    void polygon::init(){
        for(int i = 0; i < edges_num - 1; i++){
            edges_dir.push_back(vertexs[i + 1] - vertexs[i]);
            edges_dir[i].standard();
            edges.push_back(line(vertexs[i], vertexs[i + 1]));
        }
        edges_dir.push_back(vertexs[0] - vertexs[edges_num - 1]);
        edges_dir[edges_num - 1].standard();
        edges.push_back(line(vertexs[0], vertexs[edges_num - 1]));

        for(int i = 0; i < edges_num; i++){
            edges_normal.push_back(edges_dir[i].right_normal());
        }

        for(int i = 0; i < edges_num; i++){
            vector n = edges_normal[i];
            point pr = get_supporting_point(n);
            point pl = get_supporting_point(n * -1);
            projection.push_back(fpair(pl * n, pr * n));
        }
    }
    
    polygon::polygon(point center, int edges_num, float edges_length, float mass, vector speed)
    :body(center, mass, speed, 3), edges_num(edges_num){ //定义正n边型
        float r = edges_length / (2 * sin(PI / edges_num));
        vector to_vertex(0, r);
        for(int i = 0; i < edges_num; i++){
            vertexs.push_back(center + to_vertex);
            to_vertex = rotate(to_vertex, PI * 2 / edges_num);
        }

        init();
    }

    polygon::polygon(std::vector<point> _vertexs, float mass, vector speed = vector(0, 0))
    :body(point(0, 0), mass, speed, 3){ //定义任意凸多边形
        vertexs = _vertexs;
        for(point item : vertexs){
            center += item;
        }
        edges_num = _vertexs.size();
        center /= edges_num;

        init();
    }

    float polygon::min_x(){
        float ret = vertexs[0].x;
        for(point item : vertexs){
            ret = min(ret, item.x);
        }
        return ret;
    }

    float polygon::max_x(){
        float ret = vertexs[0].x;
        for(point item : vertexs){
            ret = max(ret, item.x);
        }
        return ret;
    }

    float polygon::min_y(){
        float ret = vertexs[0].y;
        for(point item : vertexs){
            ret = min(ret, item.y);
        }
        return ret;
    }

    float polygon::max_y(){
        float ret = vertexs[0].y;
        for(point item : vertexs){
            ret = max(ret, item.y);
        }
        return ret;
    }

    void polygon::transform(const float angle){
        for(vector &item : edges_dir){
            item.rotate(angle);
        }
        
        for(vector &item : edges_normal){
            item.rotate(angle);
        }
        
        for(int i = 0; i < edges_num; i++){
            vertexs[i] = rotate(vertexs[i], angle, center);
        }
    }

    void polygon::update_line(){
        for(int i = 0; i < edges_num - 1; i++){
            edges[i] = line(vertexs[i], vertexs[i + 1]);
        }
        edges[edges_num - 1] = line(vertexs[0], vertexs[edges_num - 1]);
    }

    void polygon::single_update(const float time){
        basic_update(time);
        for(point &item : vertexs){
            item += speed * time;
        }
        transform(time * anglespeed);
    }

    void polygon::update(const float time){
        for(int i = 0; i < COLLISION_DETC_TIME_PER_SEPT; i++)
            single_update(time / COLLISION_DETC_TIME_PER_SEPT);
    }

    void polygon::position_correct(vector cor){
        center += cor;
        for(point &item : vertexs){
            item += cor;
        }
    }

}