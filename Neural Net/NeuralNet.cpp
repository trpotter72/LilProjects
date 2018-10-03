#include <iostream>
#include <vector>
#include <math.h>

class NeuralNet {

public:
	NeuralNet();
	~NeuralNet();
	float evaluate(std::vector<bool> inputs);
	void train(std::vector<bool> inputs, float expected);
	int getInputs();
private:
	int inputs;
	std::vector<float> weights;
	float** values;

};

NeuralNet::NeuralNet(){

}

NeuralNet::~NeuralNet(){

}

float NeuralNet::evaluate(std::vector<bool> inputs){


}

void NeuralNet::train(std::vector<bool> inputs, float expected){


}

int NeuralNet::getInputs(){
	return inputs;
}

float sig(float x){
	return (1/(1+exp(-x)));
}

int main() {
	float x;
	std::cin >> x;
	std::cout << sig(x);
	return 0;
}
