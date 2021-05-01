#include "Input.hh"
#include "Debug.hh"

namespace Input {
    void keydown(SDL_Event *p_event, Tetromino::Tetromino *p_tetromino, Stack::Stack p_stack) {
        switch(p_event->key.keysym.sym) {
            case SDLK_RIGHT:
                p_tetromino->setX(p_tetromino->getX() + 1);
                if(p_tetromino->checkWallCollision(Tetromino::Direction::RIGHT) || p_tetromino->checkFullStackCollision(p_stack))
                    p_tetromino->setX(p_tetromino->getX() - 1);
                break;
            case SDLK_LEFT:
                p_tetromino->setX(p_tetromino->getX() - 1);
                if(p_tetromino->checkWallCollision(Tetromino::Direction::LEFT) || p_tetromino->checkFullStackCollision(p_stack))
                    p_tetromino->setX(p_tetromino->getX() + 1);
                break;
            case SDLK_DOWN:
                if(p_tetromino->getMerged())
                    break;
                if(p_tetromino->checkWallCollision(Tetromino::Direction::DOWN))
                    break;

                p_tetromino->setY(p_tetromino->getY() + 1);
                if(p_tetromino->checkFullStackCollision(p_stack))
                    p_tetromino->setY(p_tetromino->getY() - 1);
                break;
            case SDLK_UP:
                p_tetromino->Rotate();
                break;
            default:
                break;
        }
    }
}
