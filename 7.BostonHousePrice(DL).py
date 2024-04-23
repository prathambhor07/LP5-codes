import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from keras.models import Sequential
from keras.layers import Dense

# Load the Boston housing dataset
df = pd.read_csv('Boston.csv')

# Drop unnecessary columns
df.drop(columns=['Unnamed: 15', 'Unnamed: 16', 'CAT. MEDV'], inplace=True)

# Check for missing values
print(df.isnull().sum())

# Get info about the dataset
print(df.info())

# Get statistical summary of the dataset
print(df.describe())

# Get correlation of features with target variable
print(df.corr()['MEDV'].sort_values())

# Select features and target variable
X = df[['LSTAT', 'PTRATIO', 'RM']]
y = df['MEDV']

# Split the data into train and test sets
x_train, x_test, y_train, y_test = train_test_split(X, y, test_size=0.25, random_state=10)

# Standardize features
scaler = StandardScaler()
x_train = scaler.fit_transform(x_train)
x_test = scaler.transform(x_test)

# Define the model
model = Sequential([
    Dense(128, input_shape=(3,), activation='relu', name='input'),
    Dense(64, activation='relu', name='layer_1'),
    Dense(1, activation='linear', name='output')
])

# Compile the model
model.compile(optimizer='adam', loss='mse', metrics=['mae'])

# Display model summary
model.summary()

# Train the model
model.fit(x_train, y_train, epochs=100, validation_split=0.05)

# Evaluate the model
output = model.evaluate(x_test, y_test)
print("Mean Squared Error:", output[0])
print("Mean Absolute Error:", output[1])

# Make predictions
y_pred = model.predict(x_test)
print("Predictions and actual values:")
for pred, actual in zip(y_pred, y_test):
    print(pred, actual)
