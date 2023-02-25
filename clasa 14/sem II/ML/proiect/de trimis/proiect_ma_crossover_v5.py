#!/usr/bin/env python
# coding: utf-8

# In[1]:


#importing the modules we need
from sklearn.naive_bayes import MultinomialNB
from sklearn.naive_bayes import ComplementNB
from sklearn.naive_bayes import BernoulliNB
from sklearn.ensemble import GradientBoostingClassifier
from xgboost import XGBClassifier
from sklearn.neural_network import MLPClassifier
from scipy.sparse import csr_matrix
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

#function for reading the samples
def load_sample(file_name):
    f = open(file_name, 'r', encoding='utf8')
    
    indexes = []
    sentences = []
    
    for line in f.readlines():
        indexes.append(int("".join(line[:6])))
        sentences.append(line[7:].strip('\n').split())
        
    return indexes, sentences

#function for reading the labels
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


#initialize bag of words
bow = BagOfWords()
bow.build_vocabulary(train_samples + validation_samples)

#get the features
train_features = bow.get_features(train_samples + validation_samples)
train_labels = train_labels + validation_labels
validation_features = bow.get_features(validation_samples)
test_features = bow.get_features(test_samples)


# In[6]:


#train the multinomial model
multinomial_model = MultinomialNB(alpha=1.045)
multinomial_model.fit(train_features, train_labels)


# In[7]:


#predict for multinomial model
predicted_multinomial_nb = multinomial_model.predict(test_features)

#overfitted percentege
predicted = multinomial_model.predict(validation_features)
percentege_multinomial_nb = np.mean(predicted == validation_labels)
#print(percentege_multinomial_nb)


# In[8]:


#train the complement model
complement_model = ComplementNB(alpha=1.635)
complement_model.fit(train_features, train_labels)


# In[9]:


#predict for complement model
predicted_complement_nb = complement_model.predict(test_features)

predicted = complement_model.predict(validation_features)
percentege_complement_nb = np.mean(predicted == validation_labels)
#print(percentege_complement_nb)


# In[10]:


#train the bernoulli model
bernoulli_model = BernoulliNB(alpha=0.86)
bernoulli_model.fit(train_features, train_labels)


# In[11]:


#predict for bernoulli model
predicted_bernoulli_nb = bernoulli_model.predict(test_features)

predicted = bernoulli_model.predict(validation_features)
percentege_bernoulli_nb = np.mean(predicted == validation_labels)
#print(percentege_bernoulli_nb)


# In[12]:


#train the xgboost model
xgboost_model = XGBClassifier(learning_rate=0.5, gamma=0.5, reg_alpha=0.5, reg_lambda=0.5, max_depth=10, subsample=0.95, colsample_bytree=0.75, n_estimators=500)

train_labels_xgboost = train_labels
for i in range(len(train_labels_xgboost)):
    train_labels_xgboost[i] -= 1

xgboost_model.fit(train_features, train_labels)


# In[13]:


#predict for xgboost model
predicted_xgboost = xgboost_model.predict(test_features)

for i in range(len(predicted_xgboost)):
    predicted_xgboost[i] += 1



predicted = xgboost_model.predict(validation_features)

for i in range(len(predicted)):
    predicted[i] += 1

percentege_xgboost = np.mean(predicted == validation_labels)
#print(percentege_xgboost)


# In[14]:


#increment back the labels
for i in range(len(train_labels_xgboost)):
    train_labels_xgboost[i] += 1


# In[15]:


#getting the final labels
predicted = []

for i in range(len(predicted_multinomial_nb)):
    predict = np.zeros(4)

    predict[predicted_multinomial_nb[i]] += percentege_multinomial_nb
    predict[predicted_complement_nb[i]] += percentege_complement_nb
    predict[predicted_bernoulli_nb[i]] += percentege_bernoulli_nb
    predict[predicted_xgboost[i]] += percentege_xgboost

    predicted.append(np.argmax(predict))


# In[16]:


#writing the data
g = open("data/test_labels.txt", 'w')
g.write("id,label\n")

for idx in range(len(predicted)):
    g.write(f"{test_indexes[idx]},{predicted[idx]}\n")

