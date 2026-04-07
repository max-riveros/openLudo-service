add_library(controller)

target_sources(controller
        PUBLIC FILE_SET controller TYPE CXX_MODULES FILES
        Game.ixx
        impl/DefaultGame.ixx
)

target_link_libraries(controller PRIVATE model)
