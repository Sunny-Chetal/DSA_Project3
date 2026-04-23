// #include <catch2/catch_test_macros.hpp>
// #include <iostream>
// #include "CampusCompass.h"
//
// using namespace std;
//
// TEST_CASE("Incorrect Commands", "[Incorrect]") {
//   CampusCompass compass;
//   compass.ParseCSV("data/edges.csv", "data/classes.csv");
//   set<string> classes = {"COP3530", "CDA3101"};
//   compass.insert("Sunny Chetal", "12345678", 8, classes);
//   REQUIRE_FALSE(compass.insert("SunnyVTWO", "12345678", 9, classes));
//   REQUIRE_FALSE(compass.remove("87654321"));
//   REQUIRE_FALSE(compass.dropClass("12345678", "NEW3745"));
//   REQUIRE_FALSE(compass.replaceClass("12345678", "COP3530","CDA3101"));
//   REQUIRE_FALSE(compass.removeClass("NEW3745"));
// }
//
// TEST_CASE("Edge Cases", "[edgeCases]") {
//     CampusCompass compass;
//     compass.ParseCSV("data/edges.csv", "data/classes.csv");
//     // Removing non-existent
//     REQUIRE_FALSE(compass.remove("00000000"));
//
//     //Trying to remove a student who no longer exists
//     set<string> classes = {"COP3530"};
//     compass.insert("ONECLASS", "11111111", 8, classes);
//     compass.dropClass("11111111", "COP3530");
//     REQUIRE_FALSE(compass.remove("11111111"));
//
//     //Testing edges that don't connect
//     REQUIRE_FALSE(compass.checkEdgeStatus(16, 10));
// }
//
// TEST_CASE("dropClass, removeClass, remove, replaceClass", "[class]") {
//     CampusCompass compass;
//     compass.ParseCSV("data/edges.csv", "data/classes.csv");
//
//     set<string> classes = {"COP3530", "CDA3101"};
//     compass.insert("Sunny", "00000000", 8, classes);
//
//     // Test replaceClass
//     REQUIRE(compass.replaceClass("00000000", "COP3530", "STA3032"));
//
//     // Test dropClass
//     REQUIRE(compass.dropClass("00000000", "CDA3101"));
//
//     // Test removeClass
//     compass.insert("SunnyTWO", "22222222", 8, {"STA3032"});
//     REQUIRE(compass.removeClass("STA3032"));
//
//     // Test remove
//     compass.insert("SunnyTHREE", "33333333", 8, {"COP3530"});
//     REQUIRE(compass.remove("33333333"));
// }
//
// TEST_CASE("printShortestEdges", "[shortestEdges]") {
//     CampusCompass compass;
//     compass.ParseCSV("data/edges.csv", "data/classes.csv");
//
//     set<string> classes = {"COP3530"};
//     compass.insert("Sunny", "62677665", 1, classes);
//
//     //printShortest Edges before closures
//     compass.printShortestEdges("62677665");
//     REQUIRE(compass.isConnected(1, 2));
//     vector<pair<int, int>> path = {
//         {1, 2}, {2, 1},
//         {1, 4}, {4, 1},
//         {1, 50}, {50, 1}
//     };
//
//     ////printShortest Edges after closures
//     compass.toggleEdgesClosure(path);
//     REQUIRE_FALSE(compass.isConnected(1, 2));
//     compass.printShortestEdges("62677665");
// }