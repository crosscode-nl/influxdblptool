#include <benchmark/benchmark.h>
#include <utility>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>

class Object {
    std::string _value;
public:
    Object()=default;
    explicit Object(std::string value) : _value{std::move(value)} {}
public:
    [[nodiscard]] const std::string &getValue() const {
        return _value;
    }

    bool operator ==(const Object&rhs) const{
        return this->_value==rhs._value;
    }

    bool operator <(const Object&rhs) const{
        return this->_value<rhs._value;
    }

};

namespace std
{
    template<> struct hash<Object>
    {
        std::size_t operator()(Object const& object) const noexcept
        {
            return std::hash<std::string>{}(object.getValue());
        }
    };
}

void StackVector(int count, bool overwrite=false) {
    std::vector<Object> _test;
    for (int i=0; i<count; i++) {
        auto ptrToErase = std::find(begin(_test),end(_test),Object{"Test"+std::to_string(i)});
        if (ptrToErase!=end(_test)) _test.erase(ptrToErase);
        _test.emplace_back("Test"+std::to_string(i));
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            auto ptrToErase = std::find(begin(_test), end(_test), Object{"Test" + std::to_string(i)});
            if (ptrToErase != end(_test)) _test.erase(ptrToErase);
            _test.emplace_back("Test" + std::to_string(i));
        }
    }
    std::sort(_test.begin(),_test.end());
    std::string result;
    std::for_each(_test.begin(),_test.end(),[&result](const auto &i){
        result+=i.getValue();
    });
}

void StackSet(int count, bool overwrite=false) {
    std::set<Object> _test;
    for (int i=0; i<count; i++) {
        _test.erase(Object{"Test"+std::to_string(i)});
        _test.insert(Object{"Test"+std::to_string(i)});
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            _test.erase(Object{"Test" + std::to_string(i)});
            _test.insert(Object{"Test" + std::to_string(i)});
        }
    }
    std::vector<Object> _vec;
    std::for_each(_test.begin(),_test.end(),[&_vec](const auto &i){
        _vec.push_back(i);
    });
    std::sort(_vec.begin(),_vec.end());
    std::string result;
    std::for_each(_vec.begin(),_vec.end(),[&result](const auto &i){
        result+=i.getValue();
    });
}

void StackUnorderedSet(int count, bool overwrite=false) {
    std::unordered_set<Object> _test;
    for (int i=0; i<count; i++) {
        _test.erase(Object{"Test"+std::to_string(i)});
        _test.insert(Object{"Test"+std::to_string(i)});
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            _test.erase(Object{"Test" + std::to_string(i)});
            _test.insert(Object{"Test" + std::to_string(i)});
        }
    }
    std::vector<Object> _vec;
    std::for_each(_test.begin(),_test.end(),[&_vec](const auto &i){
        _vec.push_back(i);
    });
    std::sort(_vec.begin(),_vec.end());
    std::string result;
    std::for_each(_vec.begin(),_vec.end(),[&result](const auto &i){
        result+=i.getValue();
    });
}

void StackUnorderedMapIndexed(int count, bool overwrite=false) {
    std::unordered_map<std::string, Object> _test;
    for (int i=0; i<count; i++) {
        Object o{"Test"+std::to_string(i)};
        _test[o.getValue()] = std::move(o);
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            Object o{"Test" + std::to_string(i)};
            _test[o.getValue()] = std::move(o);
        }
    }
    std::vector<Object> _vec;
    std::for_each(_test.begin(),_test.end(),[&_vec](const auto &i){
        _vec.push_back(i.second);
    });
    std::sort(_vec.begin(),_vec.end());
    std::string result;
    std::for_each(_vec.begin(),_vec.end(),[&result](const auto &i){
        result+=i.getValue();
    });
}

void StackUnorderedMapInsert(int count, bool overwrite=false) {
    std::unordered_map<std::string, Object> _test;
    for (int i=0; i<count; i++) {
        Object o{"Test"+std::to_string(i)};
        _test.insert(std::make_pair(o.getValue(),std::move(o)));
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            Object o{"Test" + std::to_string(i)};
            _test.insert(std::make_pair(o.getValue(), std::move(o)));
        }
    }
    std::vector<Object> _vec;
    std::for_each(_test.begin(),_test.end(),[&_vec](const auto &i){
        _vec.push_back(i.second);
    });
    std::sort(_vec.begin(),_vec.end());
    std::string result;
    std::for_each(_vec.begin(),_vec.end(),[&result](const auto &i){
        result+=i.getValue();
    });
}



void StackMapIndexed(int count, bool overwrite=false) {
    std::map<std::string, Object> _test;
    for (int i=0; i<count; i++) {
        Object o{"Test"+std::to_string(i)};
        _test[o.getValue()] = std::move(o);
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            Object o{"Test" + std::to_string(i)};
            _test[o.getValue()] = std::move(o);
        }
    }
    std::vector<Object> _vec;
    std::for_each(_test.begin(),_test.end(),[&_vec](const auto &i){
        _vec.push_back(i.second);
    });
    std::sort(_vec.begin(),_vec.end());
    std::string result;
    std::for_each(_vec.begin(),_vec.end(),[&result](const auto &i){
        result+=i.getValue();
    });
}

void StackMapInsert(int count, bool overwrite=false) {
    std::map<std::string, Object> _test;
    for (int i=0; i<count; i++) {
        Object o{"Test"+std::to_string(i)};
        _test.insert(std::make_pair(o.getValue(),std::move(o)));
    }
    if (overwrite) {
        for (int i = count - 1; i >= 0; i--) {
            Object o{"Test" + std::to_string(i)};
            _test.insert(std::make_pair(o.getValue(), std::move(o)));
        }
    }
    std::vector<Object> _vec;
    std::for_each(_test.begin(),_test.end(),[&_vec](const auto &i){
        _vec.push_back(i.second);
    });
    std::sort(_vec.begin(),_vec.end());
    std::string result;
    std::for_each(_vec.begin(),_vec.end(),[&result](const auto &i){
        benchmark::DoNotOptimize(result+=i.getValue());
    });
}

static void BM_StackVector(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackVector(state.range(0),state.range(1));
    }
}
BENCHMARK(BM_StackVector)->Ranges({{1,3<<10},{0,1}});

static void BM_StackSet(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackSet(state.range(0),state.range(1));
    }
}
BENCHMARK(BM_StackSet)->Ranges({{1,3<<10},{0,1}});

static void BM_StackUnorderedSet(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackUnorderedSet(state.range(0),state.range(1));
    }
}
BENCHMARK(BM_StackUnorderedSet)->Ranges({{1,3<<10},{0,1}});

static void BM_StackUnorderedMapIndexed(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackUnorderedMapIndexed(state.range(0),state.range(1));
    }
}
BENCHMARK(BM_StackUnorderedMapIndexed)->Ranges({{1,3<<10},{0,1}});

static void BM_StackUnorderedMapInsert(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackUnorderedMapInsert(state.range(0),state.range(1));
    }
}
BENCHMARK(BM_StackUnorderedMapInsert)->Ranges({{1,3<<10},{0,1}});

static void BM_StackMapIndexed(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackMapIndexed(state.range(0),state.range(1));
    }
}
BENCHMARK(BM_StackMapIndexed)->Ranges({{1,3<<10},{0,1}});


static void BM_StackMapInsert(benchmark::State& state) {
    // Perform setup here
    for (auto _ : state) {
        // This code gets timed
        StackMapInsert(state.range(0), state.range(1));
    }
}
BENCHMARK(BM_StackMapInsert)->Ranges({{1,3<<10},{0,1}});


// Run the benchmark
BENCHMARK_MAIN();