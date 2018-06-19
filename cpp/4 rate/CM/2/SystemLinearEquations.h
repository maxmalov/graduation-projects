#ifndef _CLE_
#define _CLE_

#include <iostream>
using namespace std;

class SystemLinearEquations {

	int size;
	double** leftPart;
	double* rightPart;

	double* solution;

	SystemLinearEquations(void);
	SystemLinearEquations(const SystemLinearEquations&);

public:

	SystemLinearEquations(int N) {
		size = N;
		leftPart = new double* [size];
		rightPart = new double [size];
		
		for(int i = 0; i < size; ++i) {
			leftPart[i] = new double [size];
		}

		solution = 0;
	}

	~SystemLinearEquations(void) {
		delete rightPart;
		for(int i = 0; i < size; ++i) {
			delete leftPart[i];
		}
		delete leftPart;
		delete solution;
	}

	void put(double x, int i, int j) {
		if(-1 < i && i < size && -1 < j && j < size ) {
			leftPart[i][j] = x;
		}
	}
	
	void put(double x, int i) {
		if(-1 < i && i < size) {
			rightPart[i] = x;
		}
	}

	int getSize() const {
		return size;
	}

	/*
	const double const* count() {
		if(!solution) {
			double main;
			for(int i = 0; i < size; ++i) {
				for(int j = i + 1; j < size; ++j) {
					main = leftPart[j][i];
					rightPart[j] = rightPart[j] - rightPart[i] * leftPart[j][i] / leftPart[i][i];
					for(int k = i; k < size; ++k) {
						leftPart[j][k] = leftPart[j][k] - leftPart[i][k] * main / leftPart[i][i];	 
					}
				}
			}

			for(int i = size - 1; i >= 0; --i) {
				for(int j = i - 1; j >= 0; --j) {	
					main = leftPart[j][i];
					rightPart[j] = rightPart[j] - rightPart[i] * leftPart[j][i] / leftPart[i][i];
					for(int k = i; k >= j; --k) {
						leftPart[j][k] = leftPart[j][k] - leftPart[i][k] * main / leftPart[i][i];	
					}
				}
			}

			solution = new double [size];
			for(int i = 0; i < size; ++i) {
				solution[i]=rightPart[i]/leftPart[i][i];
			}
		}
		return solution;
	}
	*/


	const double const* count() {
		if(!solution) {
			double main;
        
			for (int i = 0; i < size; ++i) {
				for (int j = i + 1; j < size; ++j) {
                
					if(leftPart[i][i] == 0) {
						bool f = false;
                    
						for (int k = i; k <size; ++k) {
                        
							if(leftPart[k][i] != 0) {
								f = true;
								double tmp;
								for(int l = i; l < size; ++l) {
									tmp=leftPart[k][l];
									leftPart[k][l] = leftPart[i][l];
									leftPart[i][l] = tmp;
								}
								tmp = rightPart[k]; 
								rightPart[k] = rightPart[i];
								rightPart[i] = tmp;
								break;
							}
						}

						if (!f) { 
							break;
						}
					}

					main = leftPart[j][i];
                
					rightPart[j] = rightPart[j] - rightPart[i] * leftPart[j][i] / leftPart[i][i];
                
					for (int k = i; k < size; ++k) {
						leftPart[j][k] = leftPart[j][k] - leftPart[i][k] * main / leftPart[i][i];
					}

				}
			}

			for (int i = size - 1; i > -1; --i) {
				for (int j = i - 1; j > -1; --j) {
                
					main = leftPart[j][i];
                
					if(leftPart[i][i] == 0) {
                    
						bool f = false;
						for (int k = i; k >= j; k--) {
							if(leftPart[k][i] != 0) {
								f = true;
								double tmp;
								for(int l = i; l >= -1; --l) {
									tmp =leftPart[k][l];
									leftPart[k][l] = leftPart[i][l];
									leftPart[i][l] = tmp;
								}

								tmp = rightPart[k];
								rightPart[k] = rightPart[i];
								rightPart[i] = tmp;
								break;
							}
						}
						if (!f) {
							break;
						}
					}
                
					rightPart[j] = rightPart[j] - rightPart[i] * leftPart[j][i] / leftPart[i][i];
                
					for (int k = i; k >= j; --k) {
						leftPart[j][k] = leftPart[j][k] - leftPart[i][k] * main / leftPart[i][i];
					}

				}
			}

			solution = new double [size];
			for (int i = 0; i < size; ++i) {
					solution[i] = (leftPart[i][i] != 0) ? rightPart[i] / leftPart[i][i] : 0;
			}
		}
		return solution;
    }

	friend ostream& operator << (ostream& ost, const SystemLinearEquations& sle) {
		for(int i = 0; i <sle.size; ++i) {
			for(int j = 0; j < sle.size; ++j) {
				ost << sle.leftPart[i][j] << " ";
			}
			ost << "\t" << sle.rightPart[i] << endl;
		}

		return ost;
	}

};

#endif