#ifndef STACK_H
#define STACK_H

namespace Stack {

    class Stack {
        public:
            Stack();
            void Draw(SDL_Renderer *p_renderer);
            bool area[20][10] {0};
            ~Stack();
        private:
    };

}

#endif
