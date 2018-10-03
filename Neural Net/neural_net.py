import math as m
import numpy as n
import random as r

INPUT_NEURONS = 2
HIDDEN_NEURONS = 2
OUTPUT_NEURONS = 1
LEARNING_RATE = .2
r.seed(10000)
class NeuralNet:
	def __init__(self, input_neurons, hidden_neurons, output_neurons, learning_rate):
		self.input_neurons = input_neurons
		self.hidden_neurons = hidden_neurons
		self.output_neurons = output_neurons
		self.total_neurons = input_neurons + hidden_neurons + output_neurons
		self.learning_rate = learning_rate

		#Neuron Attributes
		self.values = n.zeros(self.total_neurons)
		self.expected_values = n.zeros(self.total_neurons)
		self.thresholds = n.zeros(self.total_neurons)

		#Weight Matrix
		self.weights = n.zeros((self.total_neurons, self.total_neurons))

		for i in range(self.input_neurons, self.total_neurons):
			self.thresholds[i] = r.random() / r.random()
			for j in range(i + 1, self.total_neurons):
				self.weights[i][j] = r.random() * 2

	def forward_prop(self):
		#update the hidden neurons first using weights and input neurons
		for i in range(self.input_neurons, self.input_neurons + self.hidden_neurons):
			working_val = 0
			for j in range(self.input_neurons):
				working_val += self.weights[j][i] * self.values[j]
			working_val -= self.thresholds[i]
			self.values[i] = 1/(1 + m.exp(-working_val))

		#update the output nodes using the weights and hidden neurons
		for i in range(self.input_neurons + self.hidden_neurons, self.total_neurons):
			working_val = 0
			for j in range(self.input_neurons, self.input_neurons + self.hidden_neurons):
				working_val += self.weights[j][i] * self.values[j]
			working_val -= self.thresholds[i]
			self.values[i] = 1/(1 + m.exp(working_val * -1))

	def backward_prop(self):
		total_squared_error = 0

		#Start with output neurons (get their error and create error grad)
		for i in range( self.input_neurons + self.hidden_neurons, self.total_neurons):
			error = self.expected_values[i] - self.values[i]
			total_squared_error += m.pow(error,2)
			#						|-----derivative of sigmoid--------|
			neuron_error_gradient = self.values[i] * (1 - self.values[i]) * error

			#Adjusting weights from hidden layer to output layer
			for j in range( self.input_neurons, self.input_neurons + self.hidden_neurons):
				weight_change = neuron_error_gradient * self.values[j] * self.learning_rate
				self.weights[j][i] += weight_change
				hidden_error_gradient = neuron_error_gradient * self.values[j] * (1- self.values[j]) * self.weights[j][i]

				#Adjusting weights from input layer to hidden layer
				for k in range(self.input_neurons):
					weight_change = self.learning_rate * hidden_error_gradient * self.values[k]
					self.weights[k][j] += weight_change

				#Update thresholds
				threshold_change = self.learning_rate * -1 * hidden_error_gradient
				self.thresholds[j] += threshold_change
			#Update thresholds for output input_nodes
			threshold_change = self.learning_rate * -1 * neuron_error_gradient
			self.thresholds[i] += threshold_change

		return total_squared_error

	def learn(self, input, expected):
		#load input values into input neurons
		for i in range(self.input_neurons):
			self.values[i] = input[i]
		#load expected outputs into output values
		for i in range(self.input_neurons + self.hidden_neurons, self.total_neurons):
			self.expected_values[i] = expected[0]
		self.forward_prop()
		return self.backward_prop()

	def trainXOR(self, times):
		for i in range(times):
			bit1 = r.getrandbits(1)
			bit2 = r.getrandbits(1)
			error = self.learn([bit1,bit2],[bit1^bit2])
			#print("{}^{}={}\tError={}".format(bit1,bit2,bit1^bit2,error))
			print("Values:{}\n".format(self.values))


nn = NeuralNet(INPUT_NEURONS, HIDDEN_NEURONS, OUTPUT_NEURONS, LEARNING_RATE)


print(nn.values)
nn.trainXOR(15000)

print(nn.values)
