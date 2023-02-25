#!/usr/bin/env python
# coding: utf-8

# In[7]:


#importing the modules we need
from sklearn.neural_network import MLPClassifier
from scipy.sparse import csr_matrix
import numpy as np


# In[8]:


#bag of words class, made during ml lab
class BagOfWords:
    def __init__(self):
        self.vocabulary = dict()
        self.words = []  
        
        
    def build_vocabulary(self, data):
        for sentence in data:
            for word in sentence:
                if word not in self.vocabulary:
                    self.vocabulary[word] = len(self.vocabulary)
                    self.words.append(word)
                    
            
    def get_features(self, data):
        features = np.zeros((len(data), len(self.vocabulary)))
        
        for id_sen, document in enumerate(data):
            for word in document:
                if word in self.vocabulary:
                    features[id_sen, self.vocabulary[word]] += 1
                    
        return csr_matrix(features)


# In[9]:


#getting the data
def load_sample(file_name):
    f = open(file_name, 'r', encoding='utf8')
    
    indexes = []
    sentences = []
    
    for line in f.readlines():
        indexes.append(int("".join(line[:6])))
        sentences.append(line[7:].strip('\n').split())
        
    return indexes, sentences


def load_label(file_name):
    f = open(file_name, 'r', encoding='utf8')
    
    sentences = []
    
    for line in f.readlines():
        sentences.append(int(line[7]))
        
    return sentences


# In[10]:


#train data
train_indexes, train_samples = load_sample("data/train_samples.txt")
train_labels = load_label("data/train_labels.txt")

#validation data
validation_indexes, validation_samples = load_sample("data/validation_samples.txt")
validation_labels = load_label("data/validation_labels.txt")

#test data
test_indexes, test_samples = load_sample("data/test_samples.txt")


# In[11]:


bow = BagOfWords()
bow.build_vocabulary(train_samples)

train_features = bow.get_features(train_samples)
validation_features = bow.get_features(validation_samples)
test_features = bow.get_features(test_samples)


# In[39]:


neural_model = MLPClassifier(solver='lbfgs', alpha=1e-5, hidden_layer_sizes=(100,), random_state=0, max_iter=500)
neural_model.fit(train_features, train_labels)


# In[40]:


predicted = neural_model.predict(validation_features)


# In[41]:


print(np.mean(predicted == validation_labels))


# In[15]:


predicted = neural_model.predict(test_features)


# In[16]:


g = open("data/test_labels.txt", 'w')
g.write("id,label\n")

for idx in range(len(predicted)):
    g.write(f"{test_indexes[idx]},{predicted[idx]}\n")

