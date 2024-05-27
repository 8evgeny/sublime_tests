project(CoreLanguage LANGUAGES CXX)

add_executable(${PROJECT_NAME}_4_1_1_tooSpecific 4_1_1_tooSpecific.cpp)
add_executable(${PROJECT_NAME}_4_1_2_tooGeneric 4_1_2_tooGeneric.cpp)
add_executable(${PROJECT_NAME}_4_1_4_conceptsIntegralVariations 4_1_4_conceptsIntegralVariations.cpp)
add_executable(${PROJECT_NAME}_requiresClause requiresClause.cpp)
add_executable(${PROJECT_NAME}_compileTimePredicate compileTimePredicate.cpp)
add_executable(${PROJECT_NAME}_conceptsClassTemplate conceptClassTemplate.cpp)
add_executable(${PROJECT_NAME}_conceptMemberFunction conceptMemberFunction.cpp)
add_executable(${PROJECT_NAME}_allAnyNone allAnyNone.cpp)
add_executable(${PROJECT_NAME}_conceptsOverloadingFunctionTemplates conceptsOverloadingFunctionTemplates.cpp)
add_executable(${PROJECT_NAME}_conceptsSpecialization conceptsSpecialization.cpp)

add_executable(${PROJECT_NAME}_char8Str char8Str.cpp)
add_executable(${PROJECT_NAME}_enumUsing enumUsing.cpp) #не работает
add_executable(${PROJECT_NAME}_bitField bitField.cpp)
add_executable(${PROJECT_NAME}_virtualConstexpr virtualConstexpr.cpp)
add_executable(${PROJECT_NAME}_rangeBasedForLoopInitializer rangeBasedForLoopInitializer.cpp)
