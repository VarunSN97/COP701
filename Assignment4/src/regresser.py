import pandas as pd
from sklearn.neural_network import MLPRegressor
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import MinMaxScaler
from sklearn.metrics import mean_squared_error
import warnings

warnings.filterwarnings("ignore")
data = pd.read_csv("lib/housing_data.csv")
data.iloc[:,1:14]=MinMaxScaler().fit_transform(data.iloc[:,1:14])
data = data.iloc[:,1:15]


X_train,X_test,y_train,y_test = train_test_split(data.iloc[:,0:13].values,data.iloc[:,13].values,train_size=0.8,shuffle=True)
clf = MLPRegressor((2,2),activation='logistic',max_iter=500)
clf.fit(X_train,y_train)
pred  = clf.predict(X_test)

print("PYthon: ")
print("MEAN Squared ERROR - ",mean_squared_error(y_test,pred))
