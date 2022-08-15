// Testing file using Catch2

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "ra/filters.hpp"
#include <iostream>

using filter = ra::filters::filter;

TEST_CASE("Always true", "[filters]"){
    CHECK(true);
}
TEST_CASE("Constructor", "[filters]"){
    
    std::vector<double> vals = {500, 0.5};
    int filter_type = 1; // lowpass
    int filter_order = 1; // RC

    filter a(vals, filter_type, filter_order);

    CHECK(true);

    filter b = ra::filters::create_filter_vals(vals, filter_type, filter_order);


    CHECK(true);
}
TEST_CASE("Low pass", "[filters]"){
    std::vector<double> vals = {1.6, 10e-6};
    int filter_type = 1; // lowpass
    int filter_order = 1;

    filter a(vals, filter_type, filter_order);

    std::string s = a.get_magnitude_response(0, 100000.0, 1000.0, 1, 1);
    std::string s2 = a.get_phase_response(0, 100000.0, 1000.0, 1, 1);

    CHECK(true);
}
TEST_CASE("All filters", "[filters]"){

    // RC lowpass
    std::vector<double> v1 = {1.6, 10e-6};
    int ft1 = 1; // lowpass
    int fo1 = 1;
    filter f1(v1, ft1, fo1);
    std::string s1 = f1.get_magnitude_response(0, 100000.0, 1000.0, ft1, fo1);
    std::string s2 = f1.get_phase_response(0, 100000.0, 1000.0, ft1, fo1);

    // RC high
    std::vector<double> v2 = {1.6, 10e-6};
    int ft2 = 2; // lowpass
    int fo2 = 1;
    filter f2(v2, ft2, fo2);
    std::string s3 = f2.get_magnitude_response(0, 100000.0, 1000.0, ft2, fo2);
    std::string s4 = f2.get_phase_response(0, 100000.0, 1000.0, ft2, fo2);

    // RL lowpass
    std::vector<double> v3 = {1.6, 10e-6};
    int ft3 = 1; // lowpass
    int fo3 = 2;
    filter f3(v1, ft3, fo3);
    std::string s5 = f3.get_magnitude_response(0, 100000.0, 1000.0, ft3, fo3);
    std::string s6 = f3.get_phase_response(0, 100000.0, 1000.0, ft3, fo3);

    // RL highpass
    std::vector<double> v4 = {1.6, 10e-6};
    int ft4 = 2; // highpass
    int fo4 = 2;
    filter f4(v1, ft4, fo4);
    std::string s7 = f4.get_magnitude_response(0, 100000.0, 1000.0, ft4, fo4);
    std::string s8 = f4.get_phase_response(0, 100000.0, 1000.0, ft4, fo4);

    // RLC lowpass
    std::vector<double> v5 = {1.6, 10e-6, 10e-6};
    int ft5 = 1; // lowpass
    int fo5 = 3;
    filter f5(v5, ft5, fo5);
    std::string s9 = f5.get_magnitude_response(0, 100000.0, 1000.0, ft5, fo5);
    std::string s10 = f5.get_phase_response(0, 100000.0, 1000.0, ft5, fo5);

    // RLC highpass
    std::vector<double> v6 = {1.6, 10e-6, 10e-6};
    int ft6 = 2; // highpass
    int fo6 = 3;
    filter f6(v6, ft6, fo6);
    std::string s11 = f6.get_magnitude_response(0, 100000.0, 1000.0, ft6, fo6);
    std::string s12 = f6.get_phase_response(0, 100000.0, 1000.0, ft6, fo6);

    // RLC bandpass
    std::vector<double> v7 = {1.6, 10e-6, 10e-6};
    int ft7 = 3; // bandpass
    int fo7 = 3;
    filter f7(v7, ft7, fo7);
    std::string s13 = f7.get_magnitude_response(0, 100000.0, 1000.0, ft7, fo7);
    std::string s14 = f7.get_phase_response(0, 100000.0, 1000.0, ft7, fo7);

    // RLC bandstop
    std::vector<double> v8 = {1.6, 10e-6, 10e-6};
    int ft8 = 4; // bandstop
    int fo8 = 3;
    filter f8(v8, ft8, fo8);
    std::string s15 = f8.get_magnitude_response(0, 100000.0, 1000.0, ft8, fo8);
    std::string s16 = f8.get_phase_response(0, 100000.0, 1000.0, ft8, fo8);

    CHECK(s1 != "Invalid");
    CHECK(s2 != "Invalid");
    CHECK(s3 != "Invalid");
    CHECK(s4 != "Invalid");
    CHECK(s5 != "Invalid");
    CHECK(s6 != "Invalid");
    CHECK(s7 != "Invalid");
    CHECK(s8 != "Invalid");
    CHECK(s9 != "Invalid");
    CHECK(s10 != "Invalid");
    CHECK(s11 != "Invalid");
    CHECK(s12 != "Invalid");
    CHECK(s13 != "Invalid");
    CHECK(s14 != "Invalid");
    CHECK(s15 != "Invalid");
    CHECK(s16 != "Invalid");

    CHECK(true);
}