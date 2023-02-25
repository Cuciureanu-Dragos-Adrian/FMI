#!/usr/bin/env python
# coding: utf-8

# In[1]:


#importing the modules we need
from sklearn.naive_bayes import MultinomialNB
from sklearn import preprocessing
from scipy.sparse import csr_matrix
from sklearn.model_selection import GridSearchCV
import numpy as np


# In[2]:


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


# In[3]:


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


# In[4]:


#train data
train_indexes, train_samples = load_sample("data/train_samples.txt")
train_labels = load_label("data/train_labels.txt")

#validation data
validation_indexes, validation_samples = load_sample("data/validation_samples.txt")
validation_labels = load_label("data/validation_labels.txt")

#test data
test_indexes, test_samples = load_sample("data/test_samples.txt")


# In[5]:


bow = BagOfWords()
bow.build_vocabulary(train_samples)

all_features = bow.get_features(train_samples + validation_samples)
train_features = bow.get_features(train_samples)
validation_features = bow.get_features(validation_samples)
test_features = bow.get_features(test_samples)


# In[6]:


all_samples = train_labels + validation_labels

vect = []

for i in range(0, 2000):
    vect.append(0.1 + i/1000)

parameters = {'alpha':vect}


# In[7]:


#train the model
naive_bayes_model = MultinomialNB()

# naive_bayes_model.fit(train_features, train_labels)
clf = GridSearchCV(naive_bayes_model, parameters)

clf.fit(all_features, all_samples)


# In[8]:


print(clf.best_score_)
print(clf.best_params_)


# In[9]:


naive_bayes_model = MultinomialNB(alpha=1.045)
naive_bayes_model.fit(train_features, train_labels)

predicted = naive_bayes_model.predict(validation_features)


# In[11]:


def confusion_matrix(predicted_labels, actual_labels):    
    confusion = np.zeros((4, 4))
    
    for idx, elem in enumerate(predicted_labels):
        confusion[actual_labels[idx]][elem] += 1
            
    return confusion
    
print(confusion_matrix(predicted, validation_labels))

