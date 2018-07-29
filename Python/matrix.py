# -*- coding: utf-8 -*-
"""
Created on Sun Jul 29 00:17:25 2018

@author: maladas

pytorch matrices

"""

import numpy as np
import torch

a = np.array([[1.0,2.0],[4.0,3.0]])

a_th = torch.from_numpy(a)

e = torch.eig(a_th)   #eigen values
e, v = torch.eig(a_th, eigenvectors=True)   #eigen values and eigen vectors

d = torch.diag(e[:,0])       #diagonalize the matrix. Ignore the complex part
a_new1=v@d@torch.inverse(v)  #getting back the original


u,s,v_new = torch.svd(a_th)
a_new2=u@torch.diag(s)@v_new.inverse()





#experimenting with complex numbers
# it finds comple eigenvalues but not eigenvectors

a = np.array([[0.0,1.0],[-1.0,0.0]])

a_th = torch.from_numpy(a)

e = torch.eig(a_th)   #eigen values
e, v = torch.eig(a_th, eigenvectors=True)   #eigen values and eigen vectors



import tensorflow as tf

#x = tf.Variable([12.3 - 4.85j, 7.5 - 6.23j], tf.complex64)
x = tf.Variable([[0.0,1.0],[-1.0,0.0]], tf.complex64)
y, z=tf.linalg.eigh(x)

init = tf.global_variables_initializer()

with tf.Session() as sess:
    sess.run(init)
    v = sess.run(x)
    print(v)  # will show you your variable.
    
    v = sess.run(y)
    print(v)
    
    v = sess.run(z)
    print(v)
    
    
    
from numpy import linalg as LA
w,v=LA.eig(a)



import numba
b = np.array([[1.0+0j,2.0+0j],[4.0+0j,3.0+0j]])

@numba.jit(nopython=True)
def eig():
    w1,v1=LA.eig(b)
    return w1, v1

nw1, nw2 = eig()

    
    