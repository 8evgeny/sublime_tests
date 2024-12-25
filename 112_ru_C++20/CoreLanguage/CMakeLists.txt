project(CoreLanguage LANGUAGES CXX)

#add_executable(${PROJECT_NAME}_4_1_1_tooSpecific 4_1_1_tooSpecific.cpp)
#add_executable(${PROJECT_NAME}_4_1_2_tooGeneric 4_1_2_tooGeneric.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_conceptsIntegralVariations 4_1_4_conceptsIntegralVariations.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_requiresClause 4_1_4_requiresClause.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_compileTimePredicate 4_1_4_compileTimePredicate.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_conceptsClassTemplate 4_1_4_conceptClassTemplate.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_conceptMemberFunction 4_1_4_conceptMemberFunction.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_allAnyNone 4_1_4_allAnyNone.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_conceptsOverloadingFunctionTemplates 4_1_4_conceptsOverloadingFunctionTemplates.cpp)
#add_executable(${PROJECT_NAME}_4_1_4_conceptsSpecialization 4_1_4_conceptsSpecialization.cpp)
#add_executable(${PROJECT_NAME}_4_1_5_genericLambdaTemplate 4_1_5_genericLambdaTemplate.cpp)
#add_executable(${PROJECT_NAME}_4_1_5_placeholders 4_1_5_placeholders.cpp)
#add_executable(${PROJECT_NAME}_4_1_6_abbreviatedFunctionTemplates 4_1_6_abbreviatedFunctionTemplates.cpp)
#add_executable(${PROJECT_NAME}_4_1_6_conceptsOverloading 4_1_6_conceptsOverloading.cpp)
#add_executable(${PROJECT_NAME}_4_1_8_signedUnsignedIntegrals 4_1_8_signedUnsignedIntegrals.cpp)
#add_executable(${PROJECT_NAME}_4_1_8_typeRequirements 4_1_8_typeRequirements.cpp)
#add_executable(${PROJECT_NAME}_4_1_8_conceptsDefinitionEqual 4_1_8_conceptsDefinitionEqual.cpp)
#add_executable(${PROJECT_NAME}_4_1_8_nestedRequirements 4_1_8_nestedRequirements.cpp)
#add_executable(${PROJECT_NAME}_4_1_9_conceptsDefinitionOrdering 4_1_9_conceptsDefinitionOrdering.cpp)
#add_executable(${PROJECT_NAME}_4_1_9_regularSemiRegular 4_1_9_regularSemiRegular.cpp)

set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FORMAT "gcc")
set(CMAKE_EXPERIMENTAL_CXX_MODULE_MAP_FLAG
  "${compiler_flags_for_module_map} -fmodule-mapper=<MODULE_MAP_FILE>")
add_executable(${PROJECT_NAME}_4_2_1_client 4_2_1_client.cpp math.cxx)



#add_executable(${PROJECT_NAME}_char8Str char8Str.cpp)
#add_executable(${PROJECT_NAME}_enumUsing enumUsing.cpp) #не работает
#add_executable(${PROJECT_NAME}_bitField bitField.cpp)
#add_executable(${PROJECT_NAME}_virtualConstexpr virtualConstexpr.cpp)
#add_executable(${PROJECT_NAME}_4_9_2_rangeBasedForLoopInitializer 4_9_2_rangeBasedForLoopInitializer.cpp)
