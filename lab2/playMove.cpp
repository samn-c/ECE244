//
//  playMove.cpp
//  TicTacToe
//
//  Created by Tarek Abdelrahman on 2019-06-07.
//  Modified by Tarek Abdelrahman on 2020-09-17.
//  Copyright © 2019-2020 Tarek Abdelrahman. All rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: write your code for playMove in this file

#include "globals.h"
#include "GameState.h"

void playMove(GameState& game_state) {
    int row = game_state.get_selectedRow();
    int col = game_state.get_selectedColumn();
    int position = game_state.get_gameBoard(row, col);

    //check move validity
    if (position == Empty) {
        game_state.set_moveValid(true);
    }
    else {
        game_state.set_moveValid(false);
    }

    // valid move, make the move
    if (game_state.get_moveValid()) {
        //place piece
        switch (game_state.get_turn()) {
            case (true):
                game_state.set_gameBoard(row, col, X);
                break;
            case (false):
                game_state.set_gameBoard(row, col, O);
                break;
        }

        //switch turn
        game_state.set_turn(game_state.get_turn() ? false : true);

        //winCode check
        int a, b, c;

        for (int i = 0; i < 3; i++) {
            //horizontal lines
            a = game_state.get_gameBoard(i, 0);
            b = game_state.get_gameBoard(i, 1);
            c = game_state.get_gameBoard(i, 2);
            
            if (a != Empty && a == b && b == c) {
                game_state.set_gameOver(true);
                game_state.set_winCode(i + 1);
            }
        }

        for (int i = 0; i < 3; i++) {
            //vertical lines
            a = game_state.get_gameBoard(0, i);
            b = game_state.get_gameBoard(1, i);
            c = game_state.get_gameBoard(2, i);
            
            if (a != Empty && a == b && b == c) {
                game_state.set_gameOver(true);
                game_state.set_winCode(i + 4);
            }
        }

        //top left - bot right diagonal
        a = game_state.get_gameBoard(0, 0);
        b = game_state.get_gameBoard(1, 1);
        c = game_state.get_gameBoard(2, 2);
        
        if (a != Empty && a == b && b == c) {
            game_state.set_gameOver(true);
            game_state.set_winCode(7);
        }

        //bot left - top right diagonal
        a = game_state.get_gameBoard(2, 0);
        b = game_state.get_gameBoard(1, 1);
        c = game_state.get_gameBoard(0, 2);
        
        if (a != Empty && a == b && b == c) {
            game_state.set_gameOver(true);
            game_state.set_winCode(8);
        }
    }
}
