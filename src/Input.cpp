#include "Input.hh"
#include "Debug.hh"

namespace Input {
    void keydown(SDL_Event *p_event, Tetromino::Tetromino *p_tetromino) {
        switch(p_event->key.keysym.sym) {
            case SDLK_RIGHT:
                p_tetromino->setX(p_tetromino->getX() + 1);
                if(p_tetromino->checkWallCollision(Tetromino::Direction::RIGHT)) {
                    Debug::Log("Collide with right wall!");
                    p_tetromino->setX(p_tetromino->getX() - 1);
                }
                break;
            case SDLK_LEFT:
                p_tetromino->setX(p_tetromino->getX() - 1);
                if(p_tetromino->checkWallCollision(Tetromino::Direction::LEFT)) {
                    Debug::Log("Collide with left wall!");
                    p_tetromino->setX(p_tetromino->getX() + 1);
                }
                break;
            case SDLK_DOWN:
                if(p_tetromino->checkWallCollision(Tetromino::Direction::DOWN)) {
                    Debug::Log("Collide with wall!");
                    break;
                }
                if(!p_tetromino->getMerged())
                    p_tetromino->setY(p_tetromino->getY() + 1);
                break;
            case SDLK_UP:
                p_tetromino->Rotate();
                break;
            default:
                break;
        }
    }
}
