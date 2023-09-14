cmake_minimum_required(VERSION 3.5)

project(C++20_in_detail LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(${PROJECT_NAME}_tooSpecific CoreLanguage/tooSpecific.cpp)
add_executable(${PROJECT_NAME}_tooGeneric CoreLanguage/tooGeneric.cpp)
add_executable(${PROJECT_NAME}_conceptsIntegralVariations CoreLanguage/conceptsIntegralVariations.cpp)
add_executable(${PROJECT_NAME}_requiresClause CoreLanguage/requiresClause.cpp)
add_executable(${PROJECT_NAME}_compileTimePredicate CoreLanguage/compileTimePredicate.cpp)
add_executable(${PROJECT_NAME}_conceptsClassTemplate CoreLanguage/conceptClassTemplate.cpp)
add_executable(${PROJECT_NAME}_conceptMemberFunction CoreLanguage/conceptMemberFunction.cpp)
add_executable(${PROJECT_NAME}_allAnyNone CoreLanguage/allAnyNone.cpp)
add_executable(${PROJECT_NAME}_conceptsOverloadingFunctionTemplates CoreLanguage/conceptsOverloadingFunctionTemplates.cpp)
add_executable(${PROJECT_NAME}_conceptsSpecialization CoreLanguage/conceptsSpecialization.cpp)

add_executable(${PROJECT_NAME}_char8Str CoreLanguage/char8Str.cpp)
add_executable(${PROJECT_NAME}_enumUsing CoreLanguage/enumUsing.cpp) #не работает
add_executable(${PROJECT_NAME}_bitField CoreLanguage/bitField.cpp)
add_executable(${PROJECT_NAME}_virtualConstexpr CoreLanguage/virtualConstexpr.cpp)
add_executable(${PROJECT_NAME}_rangeBasedForLoopInitializer CoreLanguage/rangeBasedForLoopInitializer.cpp)
