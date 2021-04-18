#ifndef STACK_H
#define STACK_H

namespace Stack {

    class Stack {
        public:
            Stack();
            void Draw(SDL_Renderer *p_renderer);
            ~Stack();
        private:
            bool area[10][20] {0};
    };

}

#endif
