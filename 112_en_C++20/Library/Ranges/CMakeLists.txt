set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
    -std=c++20 \
    -pthread \
    -fcoroutines \
    -fmodules-ts" )
#stdlib=libc++/stdlib=libstdc++
add_executable(Library_1_bindFront  bindFront.cpp)
add_executable(Library_2_bit  bit.cpp)
add_executable(Library_3_bitFloorCeil  bitFloorCeil.cpp)
add_executable(Library_4_checkExistence  checkExistence.cpp)
add_executable(Library_5_constRangeModifiableElements  constRangeModifiableElements.cpp)
add_executable(Library_6_constantEvaluated  constantEvaluated.cpp)
#add_executable(Library_7_constexprVector  constexprVector.cpp)
add_executable(Library_8_containerView  containerView.cpp)
add_executable(Library_9_containtsElement  containtsElement.cpp)
#add_executable(Library_10_createCalendar  createCalendar.cpp)
add_executable(Library_11_createSpan  createSpan.cpp)
#add_executable(Library_12_cuteSyntax  cuteSyntax.cpp)
add_executable(Library_13_eraseCpp20  eraseCpp20.cpp)
add_executable(Library_14_eraseRemoveElements  eraseRemoveElements.cpp)
add_executable(Library_15_filterRanges  filterRanges.cpp)

#!!!!! sudo apt install libfmt-dev
find_package(fmt)
add_executable(Library_16_format  format.cpp )
target_link_libraries(Library_16_format fmt::fmt)

add_executable(Library_17_formatAlternate  formatAlternate.cpp)
target_link_libraries(Library_17_formatAlternate fmt::fmt)
add_executable(Library_18_formatArgumentID  formatArgumentID.cpp)
target_link_libraries(Library_18_formatArgumentID fmt::fmt)
add_executable(Library_19_formatFillAlign  formatFillAlign.cpp)
target_link_libraries(Library_19_formatFillAlign fmt::fmt)
add_executable(Library_20_formatHash formatHash.cpp)#2 примера не работают
target_link_libraries(Library_20_formatHash fmt::fmt)
add_executable(Library_21_formatSign formatSign.cpp)#изменил namespace
target_link_libraries(Library_21_formatSign fmt::fmt)

add_executable(Library_22_formatType  formatType.cpp)
target_link_libraries(Library_22_formatType fmt::fmt)
#add_executable(Library_23_formatVector  formatVector.cpp)
#target_link_libraries(Library_23_formatVector fmt::fmt)
#add_executable(Library_24_formatVectorLinebreak  formatVectorLinebreak.cpp)
#target_link_libraries(Library_24_formatVectorLinebreak fmt::fmt)
add_executable(Library_25_formatWidthPrecision  formatWidthPrecision.cpp)
target_link_libraries(Library_25_formatWidthPrecision fmt::fmt)

add_executable(Library_26_getEndianness  getEndianness.cpp)
#add_executable(Library_27_leapYear  leapYear.cpp)
add_executable(Library_28_listComprehensionRanges  listComprehensionRanges.cpp)
#add_executable(Library_29_localTime  localTime.cpp)
add_executable(Library_30_mapRanges  mapRanges.cpp)
add_executable(Library_31_mathematicConstants  mathematicConstants.cpp)
