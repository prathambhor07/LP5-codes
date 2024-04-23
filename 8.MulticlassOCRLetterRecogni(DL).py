import numpy as np
import pandas as pd
import seaborn as sns
from sklearn.model_selection import train_test_split
from keras.datasets import imdb
from keras.utils import to_categorical
from keras import models
from keras import layers
import tensorflow as tf

# Loading IMDb data
(X_train, y_train), (X_test, y_test) = imdb.load_data(num_words=10000)

# Consolidating data for EDA
data = np.concatenate((X_train, X_test), axis=0)
label = np.concatenate((y_train, y_test), axis=0)

# Function to perform relevant sequence adding on the data
def vectorize(sequences, dimension=10000):
    results = np.zeros((len(sequences), dimension))
    for i, sequence in enumerate(sequences):
        results[i, sequence] = 1
    return results

# Vectorizing sequences
data = vectorize(data)

# Splitting data into training and testing sets
test_x = data[:10000]
test_y = label[:10000]
train_x = data[10000:]
train_y = label[10000:]

# Creating DataFrame for labels
labelDF = pd.DataFrame({'label': label})

# Visualizing label distribution
sns.countplot(x='label', data=labelDF)

# Creating train and test data sets
X_train, X_test, y_train, y_test = train_test_split(data, label, test_size=0.20, random_state=1)

# Creating sequential model
model = models.Sequential()
model.add(layers.Dense(50, activation="relu", input_shape=(10000,)))
model.add(layers.Dropout(0.3))
model.add(layers.Dense(50, activation="relu"))
model.add(layers.Dropout(0.2))
model.add(layers.Dense(50, activation="relu"))
model.add(layers.Dense(1, activation="sigmoid"))
model.summary()

# Early stopping callback
callback = tf.keras.callbacks.EarlyStopping(monitor='loss', patience=3)

# Compiling the model
model.compile(optimizer="adam", loss="binary_crossentropy", metrics=["accuracy"])

# Fitting the model
results = model.fit(X_train, y_train, epochs=2, batch_size=500, validation_data=(X_test, y_test), callbacks=[callback])

# Mean accuracy of the model
print(np.mean(results.history["val_accuracy"]))

# Evaluating the model
score = model.evaluate(X_test, y_test, batch_size=500)
print('Test loss:', score[0])
print('Test accuracy:', score[1])

# Plotting training history
import matplotlib.pyplot as plt

print(results.history.keys())

plt.plot(results.history['accuracy'])
plt.plot(results.history['val_accuracy'])
plt.title('model accuracy')
plt.ylabel('accuracy')
plt.xlabel('epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()

plt.plot(results.history['loss'])
plt.plot(results.history['val_loss'])
plt.title('model loss')
plt.ylabel('loss')
plt.xlabel('epoch')
plt.legend(['train', 'test'], loc='upper left')
plt.show()
