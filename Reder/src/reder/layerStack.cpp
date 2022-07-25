#include "repch.h"
#include "layerStack.h"


namespace reder {
	layerStack::layerStack() {
		layers_Head = layers.begin();
	}

	layerStack::~layerStack() {
		for (layer* l:layers){
			delete l;
		}	
	}

	void layerStack::pushLayer(layer* layer) {
		layers_Head = layers.emplace(layers_Head, layer);
	}

	void layerStack::pushOverLayer(layer* overLayer) {
		layers.emplace_back(overLayer);
	}

	void layerStack::popLayer(layer* layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
			layers_Head--;
		}
	}

	void layerStack::popOverLayer(layer* overLayer) {
		auto it = std::find(layers.begin(), layers.end(), overLayer);
		if (it != layers.end()) {
			layers.erase(it);
		}
	}
}