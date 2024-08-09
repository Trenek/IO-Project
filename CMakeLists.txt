cmake_minimum_required(VERSION 3.26)

project(IO-Project C)
project(Test C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(GAME_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/source/game/stateManager.c"
    "${CMAKE_SOURCE_DIR}/source/game/additions/fscanfWithAllocation/fscanfWithAllocation.c"
    "${CMAKE_SOURCE_DIR}/source/game/additions/removeDirectory/removeDirectory.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/achievementElem/achievementElem.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/button/button.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/choiceBox/choiceBox.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/choiceBox/saveData/saveData.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/chooseAction/chooseAction.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/equipementBox/equipementBox.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/fighterLabel/fighterLabel.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/inputBox/inputBox.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/itemBox/itemBox.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/shopInterface/shopInterface.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/slideBox/numbers/numberSlideBox.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/slideBox/string/stringSlideBox.c"
    "${CMAKE_SOURCE_DIR}/source/game/menu/tutorialSlide/tutorialSlide.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/hitbox/hitbox.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/ceiling/ceiling.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/characters/character.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/characters/types/player/camera.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/characters/types/player/player.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/floor/floor.c"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/wall/wall.c"
    "${CMAKE_SOURCE_DIR}/source/game/playState/playState.c"
    "${CMAKE_SOURCE_DIR}/source/game/renderer/renderer.c"
    "${CMAKE_SOURCE_DIR}/source/game/resources/loadResources.c"
    "${CMAKE_SOURCE_DIR}/source/game/resources/unloadResources.c"
    "${CMAKE_SOURCE_DIR}/source/game/saveFile/createSaveFile.c"
    "${CMAKE_SOURCE_DIR}/source/game/saveFile/loadSaveFile.c"
    "${CMAKE_SOURCE_DIR}/source/game/saveFile/saveSaveFile.c"
    "${CMAKE_SOURCE_DIR}/source/game/saveFile/unloadSaveFile.c"
    "${CMAKE_SOURCE_DIR}/source/game/state/state.c"
    "${CMAKE_SOURCE_DIR}/source/game/state/settings/loadSettings.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/characterCreator.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/loadGame.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/menu.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/newGame.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/settings.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/tutorial.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/achievements.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/deathScreen.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/dialog.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/equipement.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/explore.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/fight.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/pause.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/save.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/shop.c"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/fight/animateAttack/animateAttack.c"
)

set(TEST_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/source/tests/test_achievement.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_button.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_chooseAction.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_createSaveFile.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_equipmentBox.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_fighterLabel.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_inputBox.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_itemBox.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_numberSlideBox.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_saveData.c"
    "${CMAKE_SOURCE_DIR}/source/tests/test_stringSlideBox.c"
)

include_directories(
    "${CMAKE_SOURCE_DIR}/source/game"
    "${CMAKE_SOURCE_DIR}/source/game/additions/fscanfWithAllocation"
    "${CMAKE_SOURCE_DIR}/source/game/additions/removeDirectory"
    "${CMAKE_SOURCE_DIR}/source/game/menu/achievementElem"
    "${CMAKE_SOURCE_DIR}/source/game/menu/button"
    "${CMAKE_SOURCE_DIR}/source/game/menu/choiceBox"
    "${CMAKE_SOURCE_DIR}/source/game/menu/choiceBox/saveData"
    "${CMAKE_SOURCE_DIR}/source/game/menu/chooseAction"
    "${CMAKE_SOURCE_DIR}/source/game/menu/equipementBox"
    "${CMAKE_SOURCE_DIR}/source/game/menu/fighterLabel"
    "${CMAKE_SOURCE_DIR}/source/game/menu/inputBox"
    "${CMAKE_SOURCE_DIR}/source/game/menu/itemBox"
    "${CMAKE_SOURCE_DIR}/source/game/menu/shopInterface"
    "${CMAKE_SOURCE_DIR}/source/game/menu/slideBox/numbers"
    "${CMAKE_SOURCE_DIR}/source/game/menu/slideBox/string"
    "${CMAKE_SOURCE_DIR}/source/game/menu/tutorialSlide"
    "${CMAKE_SOURCE_DIR}/source/game/objects"
    "${CMAKE_SOURCE_DIR}/source/game/objects/hitbox"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/ceiling"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/characters/"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/characters/types"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/characters/types/player"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/floor"
    "${CMAKE_SOURCE_DIR}/source/game/objects/types/wall"
    "${CMAKE_SOURCE_DIR}/source/game/playState"
    "${CMAKE_SOURCE_DIR}/source/game/renderer"
    "${CMAKE_SOURCE_DIR}/source/game/resources"
    "${CMAKE_SOURCE_DIR}/source/game/saveFile"
    "${CMAKE_SOURCE_DIR}/source/game/state"
    "${CMAKE_SOURCE_DIR}/source/game/state/settings"
    "${CMAKE_SOURCE_DIR}/source/game/states/play/fight/animateAttack"
    "${CMAKE_SOURCE_DIR}/source/tests"
)

add_executable(IO-Project
    "${CMAKE_SOURCE_DIR}/source/gameMain.c"
    ${GAME_SOURCE_FILES}
)

add_executable(Test
    "${CMAKE_SOURCE_DIR}/source/testMain.c"
    ${GAME_SOURCE_FILES}
    ${TEST_SOURCE_FILES}
)

set(CMAKE_C_FLAGS "-W -Wall -Wextra -Wshadow -O2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -std=c23")

target_include_directories(IO-Project PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/include"
)

target_link_libraries(IO-Project PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/lib/libraylib.a"
    winmm
)

target_include_directories(Test PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/include"
    "${CMAKE_SOURCE_DIR}/dependencies/CUnit"
)

target_link_libraries(Test PRIVATE
    "${CMAKE_SOURCE_DIR}/dependencies/raylib/lib/libraylib.a"
    "${CMAKE_SOURCE_DIR}/dependencies/CUnit/lib/libcunit.a"
    winmm
)

file(COPY "${CMAKE_SOURCE_DIR}/gameFiles/dane" "${CMAKE_SOURCE_DIR}/gameFiles/resources" "${CMAKE_SOURCE_DIR}/gameFiles/config.cfg"
    DESTINATION "${CMAKE_BINARY_DIR}"
)
