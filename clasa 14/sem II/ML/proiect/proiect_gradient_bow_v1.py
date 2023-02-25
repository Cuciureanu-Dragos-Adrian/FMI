#!/usr/bin/env python
# coding: utf-8

# In[8]:


from sklearn.ensemble import GradientBoostingClassifier
from scipy.sparse import csr_matrix
from sklearn.model_selection import GridSearchCV
import numpy as np


# In[9]:


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


# In[10]:


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


# In[11]:


#train data
train_indexes, train_samples = load_sample("data/train_samples.txt")
train_labels = load_label("data/train_labels.txt")

#validation data
validation_indexes, validation_samples = load_sample("data/validation_samples.txt")
validation_labels = load_label("data/validation_labels.txt")

#test data
test_indexes, test_samples = load_sample("data/test_samples.txt")


# In[12]:


bow = BagOfWords()
bow.build_vocabulary(train_samples + validation_samples)

train_labels = train_labels + validation_labels
train_features = bow.get_features(train_samples + validation_samples)
validation_features = bow.get_features(validation_samples)


# In[13]:


parameters = {'n_estimators':[100, 150, 200], 'learning_rate':[0.1, 0.15, 0.2, 0.25, 0.3], 'subsample':[0.75]}


# In[17]:


#train the model
gradient_model = GradientBoostingClassifier(n_estimators=100, learning_rate=0.1, subsample=0.75)
gradient_model.fit(train_features, train_labels)

# clf = GridSearchCV(gradient_model, parameters)

# clf.fit(train_features, train_labels)


# In[15]:


# print(clf.best_score_)
# print(clf.best_params_)


# In[18]:


predicted = gradient_model.predict(validation_features)

print(np.mean(predicted == validation_labels))


# In[ ]:




