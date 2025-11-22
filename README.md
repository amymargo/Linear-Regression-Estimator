### Linear Regression Estimator in C
***
A high-performance C program that performs linear regression using matrix mathematics.  
It reads structured training data, computes model coefficients using the normal equation, and predicts outputs for new inputs.  
This project demonstrates systems-level implementation of core ML techniques including matrix multiplication, transpose, and Gauss–Jordan matrix inversion.

### Features
***
- Fully implemented linear regression using the normal equation  
  ```
  W = (Xᵀ X)⁻¹ Xᵀ Y
  ```
- Matrix operations built from scratch: transpose, multiplication, and inversion  
- Gauss–Jordan elimination implemented manually for numerical solving  
- Dynamic memory allocation for all matrices  
- File-based workflow for training and prediction  
- Outputs final predicted values rounded to the nearest integer

### Dataset Format
***
This project includes a `data/` directory containing sets of files used for training, prediction, and verification.

Each set contains 3 files:

#### **Training Files** — `train.XX.txt`
Used to learn the regression weights.  
```
train
k              # number of attributes
n              # number of training samples
x1 x2 ... xk y # repeated n times
```

#### **Input Files** — `data.XX.txt`
Used to predict output values using the learned weights.  
```
data
k              # number of attributes
m              # number of input rows
x1 x2 ... xk   # repeated m times
```

#### **Reference Output Files** — `ref.XX.txt`
Contain the expected correct predictions for validation:
```
737861
203060
...
```

### How It Works
***
1. Loads training data into matrices **X** and **Y**  
2. Computes the regression coefficients:
   ```
   W = (Xᵀ X)⁻¹ Xᵀ Y
   ```
3. Loads new input features from a `data.XX.txt` file 
4. Predicts with:
   ```
   Y' = X' W
   ```
5. Print each prediction rounded to the nearest whole number (`%.0f`)

### Example Usage
***
Compile the project:
```
make
```

Run the estimator on any dataset in the `data/` folder:
```
./estimate data/train.01.txt data/data.01.txt
```

Example output:
```
716559
194430
323391
```

### Directory Structure
***
```
/
├── estimate.c          # core implementation of linear regression
├── Makefile            # build script
├── README.md           # project documentation
└── data/
    ├── train.00.txt
    ├── train.01.txt
    ├── ...
    ├── data.00.txt
    ├── data.01.txt
    ├── ...
    ├── ref.00.txt
    ├── ref.01.txt
    └── ...
```