void graphicComputer() {

    // DrawScreen Related Values :
    int PlayerSize;
    int screenWidth = 800;
    int screenHeight = 810;

    // Setting Input Data To Null Before Reading Them :
    getReadyToRead();

    // Set Default Screen To The Starting Screen :
    gameScreen currentScreen = starting;

    InitWindow(screenWidth, screenHeight, "Quoridor");

    SetTargetFPS(10);

    while (!WindowShouldClose()) {

        // Update Data And Draw Screen:
        switch (currentScreen) {
            case starting:
                nextMove = GetCharPressed();

                // Read and Save Board Size, Number Of Walls For Each Player And Their Names :
                if (!size.isSet) //User Is Not Done Typing Board Size.
                    getString(&size);
                else { // User Is Done Typing Board Size And Will Now Start Typing The Number Of Walls For Each Player.
                    if (!wallNo.isSet)
                        getString(&wallNo);
                    else {
                        if (!player1Name.isSet)
                            getString(&player1Name);
                        else {
                            strcpy(player2Name.value, "Mr. Jabal");
                            player2Name.isSet = 1;

                            getStarted(size, wallNo, player1Name, player2Name);

                            // Starting The Real Game :
                            if (nextMove == 'L')
                                currentScreen = game;
                        }
                    }
                }
                drawStarting();
                break;

            case game:

                PlayerSize = (screenWidth - 100) / gameState.size;

                if (!whoWins()) {
                    if (! turnSw)
                        nextMove = GetCharPressed();

                    if (invalidInput) {
                        invalidInput = 0;
                        SetTargetFPS(10);
                    }

                    if (!turnSw) {
                        if (nextMove == ' ') {
                            if (gameState.player1UsedWallNo == gameState.player1WallNo) {
                                invalidInput = 1;
                            } else {
                                setWallPos(PlayerSize);

                                if (!moveSw) {
                                    gameState.player1WallList[gameState.player1UsedWallNo].x =
                                            (wallStartPoint.x - 50) / PlayerSize;
                                    gameState.player1WallList[gameState.player1UsedWallNo].y =
                                            (wallStartPoint.y - 100) / PlayerSize;

                                    if (wallStartPoint.x != wallEndPoint.x)
                                        gameState.player1WallList[gameState.player1UsedWallNo].dir = 'h';
                                    else gameState.player1WallList[gameState.player1UsedWallNo].dir = 'v';

                                    blockCell(gameState.player1WallList[gameState.player1UsedWallNo]);

                                    gameState.player1UsedWallNo++;
                                    turnSw = 1;
                                } else
                                    moveSw = 0;

                                wallStartPoint.x = 50, wallStartPoint.y = 100;
                                wallEndPoint.x = 50, wallEndPoint.y = 100;

                            }
                        } else
                            nextMoveProcess(&turnSw, &gameState.player1Pos);
                    }
                    else {

                        minimax(true, 5, -inF, inF, true);

                        if (computerMove.type == 'p')
                            gameState.player2Pos = computerMove.playerPos;
                        else {
                            blockCell(computerMove.wallPos);
                            gameState.player2WallList[gameState.player2UsedWallNo] = computerMove.wallPos;
                            gameState.player2UsedWallNo++;
                        }
                        turnSw = 0;
                    }

                    drawBoard(PlayerSize);
                }
                else
                    drawEnding(whoWins());
                break;
        }

    }

    CloseWindow();

}