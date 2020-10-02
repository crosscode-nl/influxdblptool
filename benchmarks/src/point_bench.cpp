#include <benchmark/benchmark.h>
#include "influxdblptool.h"
#include <iostream>

static void BM_Point_Construct_String(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        point("measurement",field("field","fieldString") );
    }
}
BENCHMARK(BM_Point_Construct_String);

static void BM_Point_Construct_Double(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        point("measurement",field("field",1.5) );
    }
}
BENCHMARK(BM_Point_Construct_Double);

static void BM_Point_Construct_Bool(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        point("measurement",field("field",true) );
    }
}
BENCHMARK(BM_Point_Construct_Bool);

static void BM_Point_Construct_Int(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        point("measurement",field("field",15) );
    }
}
BENCHMARK(BM_Point_Construct_Int);

static void BM_Point_Construct_UInt(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        point("measurement",field("field",15u) );
    }
}
BENCHMARK(BM_Point_Construct_UInt);

static void BM_Point_WithTag(benchmark::State& state) {
    using namespace influxdblptool;
    for (auto _ : state) {
        point p{"measurement",field{"field","fieldString"} };
        p << tag("mytag","tagvalue");
    }
}
// Register the function as a benchmark
BENCHMARK(BM_Point_WithTag);

static void BM_Point_Serialize_String(benchmark::State& state) {
    using namespace influxdblptool;
    point p("measurement",field("field","fieldString") );
    for (auto _ : state) {
        std::stringstream ss;
        for (int i=0; i<state.range(0);i++) ss << p << '\n';
        ss.str();
    }
}
BENCHMARK(BM_Point_Serialize_String)->Range(8, 512);

static void BM_Point_Serialize_Double(benchmark::State& state) {
    using namespace influxdblptool;
    point p("measurement",field("field",1.5) );
    for (auto _ : state) {
        std::stringstream ss;
        for (int i=0; i<state.range(0);i++) ss << p << '\n';
        ss.str();
    }
}
BENCHMARK(BM_Point_Serialize_Double)->Range(8, 512);

static void BM_Point_Serialize_Bool(benchmark::State& state) {
    using namespace influxdblptool;
    point p("measurement",field("field",true) );
    for (auto _ : state) {
        std::stringstream ss;
        for (int i=0; i<state.range(0);i++) ss << p << '\n';
        ss.str();
    }
}
BENCHMARK(BM_Point_Serialize_Bool)->Range(8, 512);

static void BM_Point_Serialize_Int(benchmark::State& state) {
    using namespace influxdblptool;
    point p("measurement",field("field",15) );
    for (auto _ : state) {
        std::stringstream ss;
        for (int i=0; i<state.range(0);i++) ss << p << '\n';
        ss.str();
    }
}
BENCHMARK(BM_Point_Serialize_Int)->Range(8, 512);

static void BM_Point_Serialize_UInt(benchmark::State& state) {
    using namespace influxdblptool;
    point p("measurement",field("field",15u) );
    for (auto _ : state) {
        std::stringstream ss;
        for (int i=0; i<state.range(0);i++) ss << p << '\n';
        ss.str();
    }
}
BENCHMARK(BM_Point_Serialize_UInt)->Range(8, 512);

BENCHMARK_MAIN();