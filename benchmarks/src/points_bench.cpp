#include <benchmark/benchmark.h>
#include <influxdblptool.h>

using namespace std::literals;

static void BM_Points(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        points pts;
        pts << point("measurement",field("field","fieldString") );
    }
}
BENCHMARK(BM_Points);

static void BM_Points_Serialize(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        points pts;
        for (int i=0; i<state.range(0); i++) {
            pts << point("measurement", field("field", "fieldString"));
        }
        std::stringstream ss;
        ss << pts;
        ss.str();
    }
}
BENCHMARK(BM_Points_Serialize)->Range(8, 512);

static void BM_Points_With_Reserve_Serialize(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        points pts;
        pts.reserve(state.range(0));
        for (int i=0; i<state.range(0); i++) {
            pts << point("measurement", field("field", "fieldString"));
        }
        std::stringstream ss;
        ss << pts;
        ss.str();
    }
}
BENCHMARK(BM_Points_With_Reserve_Serialize)->Range(8, 512);

static void BM_Vector_With_Reserve_Serialize(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        std::vector<point> v;
        v.reserve(state.range(0));
        for (int i=0; i<state.range(0); i++) {
            v.emplace_back(point("measurement", field("field", "fieldString")));
        }
        std::stringstream ss;
        std::for_each(begin(v),end(v),[&ss](auto item){
            ss << item << '\n';
        });
        ss.str();
    }
}
BENCHMARK(BM_Vector_With_Reserve_Serialize)->Range(8, 512);