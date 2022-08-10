#include "repch.h"
#include "layerStack.h"


namespace reder {
	layerStack::layerStack() {
	}

	layerStack::~layerStack() {
		for (layer* l:layers){
			delete l;
		}	
	}

	void layerStack::pushLayer(layer* layer) {
		layers.emplace(this->begin()+layerIndex, layer);
		layerIndex++;
	}

	void layerStack::pushOverLayer(layer* overLayer) {
		layers.emplace_back(overLayer);
	}

	void layerStack::popLayer(layer* layer) {
		auto it = std::find(layers.begin(), layers.end(), layer);
		if (it != layers.end()) {
			layers.erase(it);
			layerIndex--;
		}
	}

	void layerStack::popOverLayer(layer* overLayer) {
		auto it = std::find(layers.begin(), layers.end(), overLayer);
		if (it != layers.end()) {
			layers.erase(it);
		}
	}
}