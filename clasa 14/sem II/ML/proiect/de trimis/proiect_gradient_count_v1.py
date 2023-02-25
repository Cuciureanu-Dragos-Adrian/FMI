#!/usr/bin/env python
# coding: utf-8

# In[3]:


from sklearn.feature_extraction.text import CountVectorizer
from sklearn.ensemble import GradientBoostingClassifier
import numpy as np


# In[4]:


#getting the data
def load_sample(file_name):
    f = open(file_name, 'r', encoding='utf8')
    
    indexes = []
    sentences = []
    
    for line in f.readlines():
        indexes.append(int("".join(line[:6])))
        sentences.append(line[7:].strip('\n'))
        
    return indexes, sentences


def load_label(file_name):
    f = open(file_name, 'r', encoding='utf8')
    
    sentences = []
    
    for line in f.readlines():
        sentences.append(int(line[7]))
        
    return sentences


# In[5]:


#train data
train_indexes, train_samples = load_sample("data/train_samples.txt")
train_labels = load_label("data/train_labels.txt")

#validation data
validation_indexes, validation_samples = load_sample("data/validation_samples.txt")
validation_labels = load_label("data/validation_labels.txt")

#test data
test_indexes, test_samples = load_sample("data/test_samples.txt")


# In[6]:


#initialize the gradient boosting model
gradient_model = GradientBoostingClassifier()

#initialize the count vector for our words
count_vector = CountVectorizer(analyzer='word', token_pattern=r'\w{1,}')
vocabulary = train_samples + test_samples
count_vector.fit(vocabulary)

train_samples_count = count_vector.transform(train_samples)
validation_samples_count = count_vector.transform(validation_samples)
test_samples_count = count_vector.transform(test_samples)


# In[7]:


#initialize the count vector for our words
count_vector = CountVectorizer(analyzer='word', token_pattern=r'\w{1,}')
vocabulary = train_samples + validation_samples + test_samples


# In[8]:


count_vector.fit(vocabulary)

all_train_samples = train_samples + validation_samples
all_train_samples_count = count_vector.transform(all_train_samples)
all_train_abels = train_labels + validation_labels

gradient_model = GradientBoostingClassifier(n_estimators=100, learning_rate=0.5)
gradient_model.fit(train_samples_count, train_labels)


# In[9]:


#get the prediction on the validation data
predicted = gradient_model.predict(validation_samples_count)

print(np.mean(predicted == validation_labels))


# In[10]:


#get the prediction on the test data
predicted = gradient_model.predict(test_samples_count)


# In[11]:


#and write it in the csv
g = open("data/test_labels.txt", 'w')
g.write("id,label\n")

for idx in range(len(predicted)):
    g.write(f"{test_indexes[idx]},{predicted[idx]}\n")

