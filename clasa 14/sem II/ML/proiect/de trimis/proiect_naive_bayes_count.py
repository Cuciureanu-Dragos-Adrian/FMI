#!/usr/bin/env python
# coding: utf-8

# In[1]:


from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import MultinomialNB
from sklearn.metrics import accuracy_score


# In[2]:


#getting the data
def load_file(file_name, r_idx = False):
    f = open(file_name, 'r', encoding='utf8')
    
    indexes = []
    sentences = []
    
    for line in f.readlines():
        indexes.append(line[:6])
        sentences.append(line[7:].strip('\n'))
    
        
    if r_idx == True:
        return indexes, sentences
    else: 
        return sentences


#train data
train_indexes, train_samples = load_file("data/train_samples.txt", True)
train_labels = load_file("data/train_labels.txt")

#validation data
validation_indexes, validation_samples = load_file("data/validation_samples.txt", True)
validation_labels = load_file("data/validation_labels.txt")

#test data
test_indexes, test_samples = load_file("data/test_samples.txt", True)


# In[3]:


#initialize the naive bayes model
naive_bayes_model = MultinomialNB()

#initialize the count vector for our words
count_vector = CountVectorizer(analyzer='word', token_pattern=r'\w{1,}')
vocabulary = train_samples + validation_samples + test_samples
count_vector.fit(vocabulary)
    
    
#realize the count
train_samples_count = count_vector.transform(train_samples)
validation_samples_count = count_vector.transform(validation_samples)
test_samples_count = count_vector.transform(test_samples)


# In[4]:


#train the model
naive_bayes_model = MultinomialNB()
naive_bayes_model.fit(train_samples_count, train_labels)


# In[5]:


#get the prediction on the validation data
predicted = naive_bayes_model.predict(validation_samples_count)

print(accuracy_score(predicted, validation_labels))


# In[6]:


#get the prediction on the test data
predicted = naive_bayes_model.predict(test_samples_count)

#and write it in the csv
g = open("data/test_labels.txt", 'w')
g.write("id,label\n")

for idx in range(len(predicted)):
    g.write(f"{test_indexes[idx]},{predicted[idx]}\n")


# In[7]:


print(predicted[:10])


# In[ ]:




