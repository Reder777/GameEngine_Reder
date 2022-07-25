#pragma once
#include "core.h"
#include "layer.h"

namespace reder {
	class DLL_API layerStack
	{
	public:
		layerStack();
		~layerStack();

		void pushLayer(layer* layer);
		void pushOverLayer(layer* overLayer);

		void popLayer(layer* layer);
		void popOverLayer(layer* overLayer);

		std::vector<layer*>::iterator begin() { return layers.begin(); }
		std::vector<layer*>::iterator end() { return layers.end(); }
	private :
		std::vector<layer*> layers;
		std::vector<layer*>::iterator layers_Head;
	};

}