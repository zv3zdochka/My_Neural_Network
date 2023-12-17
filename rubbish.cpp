void Network::show_synapse() {
    for (int i = 0; i < layers - 1; i++) {
        std::cout << "Synapse weights from Layer " << i + 1 << " to Layer " << i + 2 << ":\n";

        for (size_t j = 0; j < network[i].size(); j++) {
            for (size_t k = 0; k < network[i + 1].size(); k++) {
                float cur_weight = synapse[i][(j * network[i + 1].size()) + k];

                std::cout << std::fixed << std::setprecision(1) << std::setw(5) << cur_weight;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
}


void Network::show_weights() {
    std::cout << "Neuron Weights" << std::endl;
    size_t max_neurons = 0;
    for (const auto & i : network) {
        max_neurons = std::max(max_neurons, i.size());
    }


    for (size_t i = 0; i < max_neurons; ++i) {

        for (auto & j : network) {
            if (i < j.size()) {
                std::cout << std::fixed << std::setprecision(1) << j[i].weight << " ";
            } else {
                std::cout << "    ";
            }
        }
        std::cout << std::endl;
    }


}