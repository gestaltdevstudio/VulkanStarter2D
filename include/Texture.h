#ifndef TEXTURE_SDL_H_INCLUDED
#define TEXTURE_SDL_H_INCLUDED

//#include <SDL.h>

namespace GGE
{
//    typedef SDL_Rect RenderRect;

    class Texture
    {

        public:
            inline Texture() { }
            inline virtual ~Texture() {} // { if (sdlTexture) SDL_DestroyTexture(sdlTexture); sdlTexture = NULL; }

//            inline void setSDLTexture(SDL_Texture *_sdlTexture) { sdlTexture = _sdlTexture; }
//            inline SDL_Texture* getSDLTexture() { return sdlTexture; }

        private:
//            SDL_Texture     *sdlTexture;


    };

}

#endif // TEXTURE_H_INCLUDED
