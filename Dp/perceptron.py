#!/usr/bin/python
# -*- coding:utf-8 -*-
#########################################################################
# File Name: learnone.py
# Author: Duke-wei
# mail: 13540639584@163.com
# Created Time: 2017年03月01日 星期三 09时23分15秒
#########################################################################

class Perceptron(object):
    def __init__(self,imput_num,activator):
        self.activator = activator
        self.weights = [0.0 for _ in range(imput_num)]
        self.bias = 0.0

    def __str__(self):
        return 'weights\t:%s\nbias\t:%f\n'%(self.weights,self.bias)

    def predict(self,imput_vec):
        return self.activator(reduce(lambda a,b:a+b,map(lambda (x,w): x*w,zip(imput_vec,self.weights)),0.0)+self.bias)

    def train(self,imput_vecs,labels,iteration,rate):
        for i in range(iteration):
            self._one_iteration(imput_vecs,labels,rate)

    def _one_iteration(self,imput_vecs,labels,rate):
        samples = zip(imput_vecs,labels)
        for (input_vec,label) in samples:
            output = self.predict(input_vec)
            self._update_weights(input_vec,output,label,rate)

    def _update_weights(self,input_vec,output,label,rate):
        delta = label - output
        self.weights = map(lambda (x,w):w + rate*delta*x,zip(input_vec,self.weights))
        self.bias += rate*delta


def f(x):
    return 1 if x > 0 else 0

def get_training_dataset():
    input_vecs = [[1,1],[0,0],[1,0],[0,1]]
    labels = [1,0,0,0]
    return input_vecs,labels

def train_and_perceptron():
    p = Perceptron(2,f)
    input_vecs,labels = get_training_dataset()
    p.train(input_vecs,labels,10,0.1)
    return p

if __name__ == '__main__':
    and_perception = train_and_perceptron()
    print and_perception
    print '1 and 1 = %d' % and_perception.predict([1,1])
    print '1 and 0 = %d' % and_perception.predict([1,0])
    print '0 and 1 = %d' % and_perception.predict([0,1])
    print '0 and 0 = %d' % and_perception.predict([0,0])
