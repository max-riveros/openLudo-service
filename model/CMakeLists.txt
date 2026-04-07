add_library(model)

target_sources(model
        PUBLIC FILE_SET model TYPE CXX_MODULES FILES
        Board.ixx
        Pawn.ixx
        Field.ixx
        Dice.ixx
        Player.ixx
        impl/DefaultPawn.cpp
)
