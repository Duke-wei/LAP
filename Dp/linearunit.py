#!/usr/bin/python
# -*- coding:utf-8 -*-
from perceptron import Perceptron

f = lambda x:x

class LinearUnit(Perceptron):
    def __init__(self,input_num):
        Perceptron.__init__(self,input_num,f)

    def get_training_dataset():
        input_vecs = [[5],[3],[8],[1.4],[10.1]]
        labels = [5500,2300,7600,1800,11400]
        return input_vecs,labels

    def train_linear_unit():
        lu = LinearUnit(1)
        input_vecs,labels = get_training_dataset()
        lu.train(input_vecs,labels,10,0.01)
        return lu

if __name__ == '__main__':
    linear_unit = train_linear_unit()
    print linear_unit
    print 'work 3.4 year,mothly salary = %.2f'%linear_unit.predict([3.4])
    print 'work 13.4 year,mothly salary = %.2f'%linear_unit.predict([13.4])
