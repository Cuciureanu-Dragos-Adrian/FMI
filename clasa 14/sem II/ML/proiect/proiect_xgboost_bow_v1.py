#!/usr/bin/env python
# coding: utf-8

# In[2]:


from xgboost import XGBClassifier
from scipy.sparse import csr_matrix
from sklearn.model_selection import GridSearchCV
import numpy as np


# In[3]:


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


# In[4]:


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


# In[14]:


#train data
train_indexes, train_samples = load_sample("data/train_samples.txt")
train_labels = load_label("data/train_labels.txt")

#validation data
validation_indexes, validation_samples = load_sample("data/validation_samples.txt")
validation_labels = load_label("data/validation_labels.txt")

#test data
test_indexes, test_samples = load_sample("data/test_samples.txt")


# In[15]:


bow = BagOfWords()
bow.build_vocabulary(train_samples + validation_samples)

all_features = bow.get_features(train_samples + validation_samples)
train_features = bow.get_features(train_samples)
validation_features = bow.get_features(validation_samples)
test_features = bow.get_features(test_samples)


# In[16]:


for i in range(len(train_labels)):
    train_labels[i] = int(train_labels[i]) - 1

# for i in range(len(validation_labels)):
#     validation_labels[i] = int(validation_labels[i]) - 1


# In[42]:


all_samples = train_labels + validation_labels

rl = []
for i in range(10, 21):
    rl.append(i/20)

parameters = {'learning_rate':[0.15], 'gamma':[0.5], 'reg_alpha':[0.5], 'max_depth':[10], 'subsample':[0.8], 'colsample_bytree':rl, 'n_estimators':[475]}


# In[43]:


#train the model
xgboost_model = XGBClassifier()
# xgboost_model.fit(train_features, train_labels)
clf = GridSearchCV(xgboost_model, parameters)

clf.fit(all_features, all_samples)


# In[44]:


print(clf.best_score_)
print(clf.best_params_)


# In[17]:


xgboost_model = XGBClassifier(learning_rate=0.15, gamma=0.5, reg_alpha=0.5, max_depth=10, subsample=0.8, colsample_bytree=0.75, n_estimators=475)
xgboost_model.fit(train_features, train_labels)

predicted = xgboost_model.predict(validation_features)

for i in range(len(predicted)):
    predicted[i] += 1


# In[18]:


def confusion_matrix(predicted_labels, actual_labels):    
    confusion = np.zeros((4, 4))
    
    for idx, elem in enumerate(predicted_labels):
        confusion[actual_labels[idx]][elem] += 1
            
    return confusion
    
print(confusion_matrix(predicted, validation_labels))

