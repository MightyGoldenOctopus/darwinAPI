# darwinAPI

## NOTE:
This API is a quite unprofessional noob-friendly FFN tool. As the result of my first C project and also my first implementation of a neural network, it can be quite messy and don't reflect a professional code  and architecture quality.  
This implementation use a full-matrix approach of the FFN using sigmoid activation functions and vanilla gradient descent without any other optimization.
If you are amateur enought to dare using this API, just make this include: `#include "ffnet.h"`


## API's Matrix System:
darwinAPI use it's own built-in matrix library using a 1-D array for basics optimization purpose.  
Here's a simple example how to make a 3x2 matrix:
```
double data[4] = {1, 2, 3, 4, 5, 6};
Matrix myMatrix = createMatrix(&data, 3, 2);
```
Note that darwinAPI is a full-matrix FFN implementation, all the elements that you are manipulating are matrix, for instance the input matrix n x p will correspond to a data set of n inputs of p elements. Of course you can input as many elements as you want since the only requirement is that the number of column match the size of the input layer. 

## FFN Functions:
-Create a new FFN: `FFNet createFFN(int layersSizes[], layersNb)`  
-Train a FFN: `void trainFFNet(FFNet* myFFNet, int epochs, Matrix* inputs, Matrix* desired_outputs)`  
-Compute with a FFN: `Matrix forwardPropagation(FFNet* myFFNet, Matrix inputs)`  
-Free a FFN: `void freeFFNet(FFNet* myFFNet)`  
-Save a FFN to a file: `void serialFFNet(FFNet* myFFNet, char* myfilename)`  
-Load a FFN from a file `FFNet loadFFNet(char* myfilename)`  

## Quick Start (demo with a XOR):
Let's make quickly a 2-3-1 FFN capable of learning a XOR.
```
#include "ffnet.h"

int main(){
int layers[3] = {2,3,1};
    FFNet = myFFNet(layers, 3);
    
    double inputs[8] = {0, 0, 0, 1, 1, 0, 1, 1};
    Matrix inputsMat = createMatrix(inputs, 4, 2);
    
    double desired_outputs = {0, 1, 1, 0};
    Matrix desired_outputsMat = createMatrix(desired_outputs, 4, 1);
    
    trainFFNet(&myFFNet, 250000, &inputsMat, &desired_ouputsMat);
    Matrix output = forwardPropagation(&myFFNet, inputsMat);
    
    saveFFNet(&myFFNet, "xor_demo");
    free(&myFFNet);
}
```






