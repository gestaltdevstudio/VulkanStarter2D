#ifndef GRAPHICELEMENT_H_INCLUDED
#define GRAPHICELEMENT_H_INCLUDED

namespace GGE
{

    class GraphicElement
    {

        public:
            inline GraphicElement() { }
            inline virtual ~GraphicElement() { }
            int zOrder;

    };

}

#endif // GRAPHICELEMENT_H_INCLUDED
