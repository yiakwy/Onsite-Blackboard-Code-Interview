#include <gtest/gtest.h>
#include "solutions/lucky_draw_stone_tech.hpp"

#include <vector>
using std::vector;

#include <iostream>

class SimpleBenchCall {
public:
    virtual ~SimpleBenchCall() {}
    
    void set_persons(int* persons) {
        persons_ = persons;
    }
    
    int run_once() {
        return lucky_draw(persons_);
    }
    
    void run_exec(int calls, vector<int>& out) {
        int i=0;
        while (i < calls) {
            int ret = run_once();
            out.push_back(ret);
            i++;
        }
    }
    
private:
    int* persons_;
    
};

class LuckyDrawTest: public ::testing::Test {
    public:
        virtual void SetUp() {
            Init_();
        }

        void Init_() {
            TearDown();
            
            persons = new int[calls];
            
            for (int i=0; i < calls; i++) {
                persons[i] = i;
            }
            
        }

        void TearDown() {
            if (persons != nullptr) {
                delete[] persons;
                persons = nullptr;
            }
        }

        ~LuckyDrawTest() {
            TearDown();
        }
    

    protected:
        int calls = 100;
        int *persons = nullptr;
        SimpleBenchCall benchmark;
};

TEST_F(LuckyDrawTest, BENCH_100_CALLS)
{
    vector<int> out;
    benchmark.set_persons(persons);
    benchmark.run_exec(calls, out);
    
    bool finished = true;
    
    int* queryTable = new int[calls];
    memset(queryTable, -1, calls*sizeof(int));
    
    for (auto id : out) {
        if (queryTable[id] == -1) {
            queryTable[id] = 1;
        } else {
            // set before
            std::cout << "<" << id << ">" << " is duplicated. Lucky draw failed." << std::endl;
            finished = false;
            break;
        }
    }
    
    EXPECT_EQ(finished, true);
    
}
