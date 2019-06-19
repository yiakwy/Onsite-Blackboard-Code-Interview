//
//  lucky_draw_stone_tech.hpp
//  ApolloTeam
//
//  Created by Wang Yi on 18/6/19.
//
//

#ifndef lucky_draw_stone_tech_hpp
#define lucky_draw_stone_tech_hpp

#include <random>
using std::random_device;

static std::mt19937 gen;
static std::uniform_int_distribution<int> integers_distr;

static bool initialized = false;
static int last_visited = 0;


void init(std::mt19937* gen_, std::uniform_int_distribution<int>* integers_distr_, int start, int end)
{
    std::random_device device;
    std::mt19937 gen(device());
    std::uniform_int_distribution<int> integers_distr(start, end);
    *gen_ = gen;
    *integers_distr_ = integers_distr;
}

void swap(int* left, int* right)
{
    int temp = *left;
    *left = *right;
    *right = temp;
}

int lucky_draw(int persons[])
{
    int size = 100;
    
    if (!initialized) {
        init(&gen, &integers_distr, 0, size);
        // in-placement random shuffle
        for (int i=size-1; i >0; i--) {
            int idx = integers_distr(gen) % i;
            swap(persons+i, persons+idx);
        }
        initialized = true;
    }
    
    if (last_visited >= size)
        last_visited = 0;
    return persons[last_visited++];
    
}

#endif /* lucky_draw_stone_tech_hpp */
