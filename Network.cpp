#include "Matrix.h"
#include "json.h"
#include "Network.h"
#include <chrono>

#define NETWORK_NUM_NEURONS_NAME    "Num_of_neurons"
#define NETWORK_ACTIVATION_FN_NAME  "Activation_function"
#define NETWORK_SYNAPSE_NAME        "Synapse"

Network::Network() = default;

Network::Network(const char *filename) {
    nlohmann::json input;

    {
        std::ifstream file(filename, std::ios::in | std::ios::binary);

        if (!file.is_open())
            throw std::runtime_error("Unable to open file");

        file >> input;
    }

    int i = 0;
    for (const auto &layer_data: input) {
        int num_neurons = layer_data.at(NETWORK_NUM_NEURONS_NAME);

        const auto &fn_name = layer_data.at(NETWORK_ACTIVATION_FN_NAME).get_ref<const std::string &>();
        FunctionType ft = function_type_from_string(fn_name);

        float b = 0.0f;

        if (network.empty()) {
            add_layer(LayerType::input, num_neurons, ft, b);
        }
        else if (i == input.size() - 1) {
                    add_layer(LayerType::output, num_neurons, ft, b);
                    continue;
        }else {
            add_layer(LayerType::hidden, num_neurons, ft, b);
        }

        auto &synapse_data = layer_data.at(NETWORK_SYNAPSE_NAME);
        synapse.push_back(synapse_data.get<std::vector<std::vector<float>>>());
        i++;
    }
}

void Network::add_layer(LayerType type, int number_of_neurons, FunctionType af, float b) {
    network.emplace_back();

    switch (type) {
        case LayerType::input:
            for (int neuron = 0; neuron < number_of_neurons; neuron++) {
                network[0].emplace_back(1, 0, af);
            }
            break;
        case LayerType::hidden:
            for (int neuron = 0; neuron < number_of_neurons; neuron++) {
                network[layers].emplace_back(layers + 1, 0, af);
            }
            break;
        case LayerType::output:
            for (int neuron = 0; neuron < number_of_neurons; neuron++) {
                network[network.size() - 1].emplace_back(layers + 1, 0, af);
            }
            break;
    }

    layers += 1;
}

void Network::create_synapse() {
    static std::random_device sepsis;
    static std::default_random_engine gen2(sepsis());
    std::uniform_real_distribution<float> dis2(0.1f, 1.0f);

    for (size_t i = 0; i < network.size() - 1; ++i) {
        synapse.emplace_back();

        if (network[i + 1].size() != 1) {
            for (size_t j = 0; j < network[i + 1].size(); ++j) {
                std::vector<float> demi_synapse;

                for (size_t k = 0; k < network[i].size(); ++k) {
                    float c_weight = dis2(gen2);
                    demi_synapse.push_back(c_weight);
                }

                synapse[i].emplace_back(std::move(demi_synapse));
            }
        } else {
            for (size_t j = 0; j < network[i].size(); ++j) {
                std::vector<float> demi_synapse;

                for (size_t k = 0; k < network[i + 1].size(); ++k) {
                    float c_weight = dis2(gen2);
                    demi_synapse.push_back(c_weight);
                }

                synapse[i].emplace_back(std::move(demi_synapse));
            }
        }
    }
}


void Network::build() {
    std::cout << "><><><><><>><><><><><><><><><><><><><><" << std::endl;
    std::cout << "     NETWORK WAS BUILT SUCCESSFULLY" << std::endl;
    std::cout << "><><><><><>><><><><><><><><><><><><><><" << std::endl;
    create_synapse();
}

void Network::show_network() {
    show_weights();
    show_synapse();

}

void Network::show_synapse() {
    for (int i = 0; i < layers - 1; i++) {
        std::cout << "Synapse weights from Layer " << i + 1 << " to Layer " << i + 2 << ":\n";
        std::cout << "-----------------------" << std::endl;
        for (auto &j: synapse[i]) {
            for (float k: j) {
                std::cout << k << ' ';
            }
            std::cout << '\n';
        }
        std::cout << "-----------------------" << std::endl;
    }
}

void Network::show_weights() {
    std::cout << "Neuron Weights" << std::endl;
    std::cout << "-----------------------" << std::endl;
    size_t max_neurons = 0;
    for (const auto &i: network) {
        max_neurons = std::max(max_neurons, i.size());
    }
    for (size_t i = 0; i < max_neurons; ++i) {
        for (auto &j: network) {
            if (i < j.size()) {
                std::cout << std::fixed << std::setprecision(1) << j[i].weight << " ";
            } else {
                std::cout << "    ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------" << std::endl;
}


void Network::train(std::vector<std::vector<std::vector<float>>> data, const std::vector<std::vector<float>> &answer,
                    int epochs, float test_data_per, float train_speed) {

    auto start_time = std::chrono::high_resolution_clock::now();

    std::cout << "-----------------------" << std::endl;
    std::cout << "    START TRAINING" << std::endl;
    std::cout << "-----------------------" << std::endl;

    for (int epoch = 0; epoch < epochs; ++epoch) {
        int data_ind = -1;
        for (auto &j: data) {
            data_ind += 1;
            clear_weights();
            std::vector<std::vector<float>> demi_res;

            for (int lay = 0; lay < layers - 1; lay++) {

                for (int k = 0; k < network[lay].size(); k++) {
                    if (lay == 0) {
                        network[lay][k].weight = j[k][0];
                    } else {
                        network[lay][k].weight = demi_res[k][0];
                    }
                }

                show_weights();

                size_t k = network[lay + 1].size();
                std::vector<std::vector<float>> local_inp = {};
                for (auto &d: network[lay]) {
                    local_inp.push_back({d.weight});
                }
                if (k == 1) {
                    std::vector<std::vector<float>> semi = {{}};
                    for (auto &h: synapse[lay])
                        semi[0].push_back(h[0]);

                    demi_res = through_layer(Matrix(semi), local_inp, network[lay][0].fn_type).getData();
                } else {
                    demi_res = through_layer(Matrix(synapse[lay]), local_inp,
                                             network[lay][0].fn_type).getData();
                }


                for (int neu = 0; neu < network[lay + 1].size(); neu++) {
                    network[lay + 1][neu].weight = demi_res[neu][0];
                }


                show_weights();

            }

            Matrix(neu_out).showMatrix("weight");

            //errors
            std::vector<std::vector<float>> errors;
            std::vector<std::vector<std::vector<float>>> errors_by_lay = {}; //first errors vec is last in this vec

            if (answer[data_ind].size() >= 2) {
                for (int len = 0; len < network[network.size() - 1].size(); len++) {
                    errors.push_back({answer[data_ind][len] - network[network.size() - 1][len].weight});
                }
            } else {
                for (int len = 0; len < network[network.size() - 1].size() - 1; len++) {
                    errors.push_back({answer[data_ind][len] - network[network.size() - 1][len].weight});

                }
            }
            errors_by_lay.push_back(errors);




            Matrix(errors).showMatrix("err");


            for (int lay = layers - 1; lay > 0; lay--) {

                size_t k = network[lay - 1].size();

                if (k == 1) {
                    std::vector<std::vector<float>> semi = {{}};
                    for (auto &h: synapse[lay-1])
                        semi[0].push_back(h[0]);

                    demi_res = divide(Matrix(semi).transpose(), Matrix(errors)).getData();
                } else {
                    //Matrix(synapse[lay-1]).transpose().showMatrix("map");
                    //Matrix(errors).transpose().showMatrix("lox");
                    demi_res = divide(Matrix(synapse[lay-1]).transpose(), Matrix(errors)).getData();
                }
                errors = demi_res;
                errors_by_lay.push_back(demi_res);


            }
            std::reverse(errors_by_lay.begin(), errors_by_lay.end());
            std::vector<Matrix> d_synapse;
//            for (int lay = layers - 1; lay > 0; lay--) {
//
//            }
            Matrix(neu_out).showMatrix("NEU");
            for (int i = 0; i < errors_by_lay.size(); i++){
                Matrix(errors_by_lay[i]).showMatrix("ERR");
            }





        neu_out.clear();
        }
        std::cout << "-----------------------" << std::endl;
        std::cout << "    FINISH TRAINING" << std::endl;
        std::cout << "-----------------------" << std::endl;
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        std::cout << "Training Time: " << duration.count() << " ms" << std::endl;


    }

}

Matrix Network::through_layer(const Matrix &weights, const std::vector<std::vector<float>> &input,
                              FunctionType af) {
    Matrix inp(input);

    Matrix res = weights * inp;

    std::vector<std::vector<float>> out = res.getData();
    std::vector<std::vector<float>> updatedData = res.getData();

    std::vector<float> edge = {};
    for (int i = 0; i < updatedData.size(); i++) {
        edge.push_back(updatedData[i][0]);
        updatedData[i][0] = call(af, updatedData[i][0]);
    }


    Matrix updatedRes(updatedData);

    neu_out.push_back(edge);
    return updatedRes;
}


void Network::save(const char *filename) const {
    nlohmann::json output;

    for (int i = 0; i <= layers - 1; ++i) {
        if (i != layers - 1) {
            nlohmann::json &layer_data = output.emplace_back();
            
            layer_data[NETWORK_NUM_NEURONS_NAME] = network[i].size();
            layer_data[NETWORK_ACTIVATION_FN_NAME] = function_type_to_string(network[i][0].fn_type);
            layer_data[NETWORK_SYNAPSE_NAME] = synapse[i];
        }else{
            nlohmann::json &layer_data = output.emplace_back();
            
            layer_data[NETWORK_NUM_NEURONS_NAME] = network[i].size();
            layer_data[NETWORK_ACTIVATION_FN_NAME] = function_type_to_string(network[i][0].fn_type);
        }
        
    }

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    file << output.dump(/* indent= */ 4) << std::endl;
}

void Network::clear_weights() {
    for (auto &lay: network) {
        for (auto &neu: lay) {
            neu.weight = 0.0f;
        }
    }
}

Matrix Network::divide(const Matrix &weights, const Matrix &input) {
    Matrix res = weights * input;
    return res;
}